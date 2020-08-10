#include "rs_graphicview.h"

#include <cmath>

#include <QApplication>
#include <QDesktopWidget>

#include "rs_math.h"
#include "rs_settings.h"
#include "rs_painterqt.h"

RS_GraphicView::RS_GraphicView(QWidget *parent) : QWidget(parent)
    ,gridColor_(Qt::gray)
    ,metaGridColor_(64, 64, 64)
    ,redrawMethod_(RS2::RedrawAll)
    ,grid_(new RS_Grid(this)) {

    RS_SETTINGS->beginGroup("Colors");
    setBackground(QColor(RS_SETTINGS->readEntry("/background", Colors::background)));
    setGridColor(QColor(RS_SETTINGS->readEntry("/grid", Colors::grid)));
    setMetaGridColor(QColor(RS_SETTINGS->readEntry("/meta_grid", Colors::meta_grid)));
    RS_SETTINGS->endGroup();
}

void RS_GraphicView::setBackground(const RS_Color& bg) {
  background_ = bg;
  if (bg.red() + bg.green() + bg.blue() > 380) {
    foreground_ = RS_Color(0, 0, 0);
  } else {
    foreground_ = RS_Color(255, 255, 255);
  }
}

int RS_GraphicView::getWidth() const {
  if (scrollbars_) {
    return width() - vScrollBar_->sizeHint().width();
  } else {
    return width();
  }
}

int RS_GraphicView::getHeight() const {
  if (scrollbars_) {
    return height() - hScrollBar_->sizeHint().height();
  } else {
    return height();
  }
}

void RS_GraphicView::redraw(RS2::RedrawMethod method) {
  redrawMethod_ = (RS2::RedrawMethod) (redrawMethod_ | method);
  update();
}

void RS_GraphicView::setFactor(double f) {
  setFactorX(f);
  setFactorY(f);
}

RS_Vector RS_GraphicView::getFactor() const {
  return factor_;
}

void RS_GraphicView::setFactorX(double f) {
  if (!zoomFrozen_) {
    factor_.x = fabs(f);
  }
}

void RS_GraphicView::setFactorY(double f) {
  if (!zoomFrozen_) {
    factor_.y = fabs(f);
  }
}

void RS_GraphicView::setOffsetX(int ox) {
  offsetX_ = ox;
}

void RS_GraphicView::setOffsetY(int oy) {
  offsetY_ = oy;
}

int RS_GraphicView::getOffsetX() const {
  return offsetX_;
}

int RS_GraphicView::getOffsetY() const {
  return offsetY_;
}

RS_Vector RS_GraphicView::toGui(RS_Vector v) const {
  return RS_Vector(toGuiX(v.x), toGuiY(v.y));
}

double RS_GraphicView::toGuiX(double x) const {
  return x * factor_.x + offsetX_;
}

double RS_GraphicView::toGuiY(double y) const {
  return -y * factor_.y + getHeight() - offsetY_;
}

double RS_GraphicView::toGuiDX(double d) const {
  return d * factor_.x;
}

double RS_GraphicView::toGuiDY(double d) const {
  return d * factor_.y;
}

RS_Vector RS_GraphicView::toGraph(RS_Vector v) const {
  return RS_Vector(toGraphX(RS_Math::round(v.x)),
                   toGraphY(RS_Math::round(v.y)));
}

RS_Vector RS_GraphicView::toGraph(int x, int y) const {
  return RS_Vector(toGraphX(x), toGraphY(y));
}

double RS_GraphicView::toGraphX(int x) const {
  return (x - offsetX_) / factor_.x;
}

double RS_GraphicView::toGraphY(int y) const {
  return -(y - getHeight() + offsetY_) / factor_.y;
}

double RS_GraphicView::toGraphDX(int d) const {
  return d / factor_.x;
}

double RS_GraphicView::toGraphDY(int d) const {
  return d / factor_.y;
}





void RS_GraphicView::getPixmapForView(std::unique_ptr<QPixmap>& pm) {
  QSize const s0(getWidth(), getHeight());
  if(pm && pm->size()==s0) {
    return;
  }
  pm.reset(new QPixmap(getWidth(), getHeight()));
}

void RS_GraphicView::paintEvent(QPaintEvent *) {
  getPixmapForView(pixmapLayer1_);
  getPixmapForView(pixmapLayer2_);
  getPixmapForView(pixmapLayer3_);

  if (redrawMethod_ & RS2::RedrawGrid) {
    pixmapLayer1_->fill(background_);
    RS_PainterQt painter1(pixmapLayer1_.get());
    drawLayer1((RS_Painter *)&painter1);
    painter1.end();
  }


  RS_PainterQt wPainter(this);
  wPainter.drawPixmap(0, 0, *pixmapLayer1_);
  wPainter.end();
  //redrawMethod_ = RS2::RedrawNone;
}

void RS_GraphicView::resizeEvent(QResizeEvent* /*e*/) {
  redraw();
}

void RS_GraphicView::drawLayer1(RS_Painter *painter) {
  if (isPrintPreview()) {
    ;
  }

  if (!isPrintPreview()) {
    int dpiX = qApp->desktop()->logicalDpiX();
    const RS_Pen penSaved = painter->getPen();
    if (dpiX > 96) {
      RS_Pen pen = penSaved;
      pen.setWidth(RS2::Width01);
      painter->setPen(pen);
    }
    drawMetaGrid(painter);
    drawGrid(painter);

    if (dpiX > 96) {
      painter->setPen(penSaved);
    }
  }
}

void RS_GraphicView::drawMetaGrid(RS_Painter *painter) {
  if (!(grid_ && isGridOn())) {
    return;
  }

  grid_->updatePointArray();
  RS_Pen pen(metaGridColor_, RS2::Width00, RS2::DotLine);
  painter->setPen(pen);

  RS_Vector dv = grid_->getMetaGridWidth().scale(factor_);
  double dx = fabs(dv.x);
  double dy = fabs(dv.y);

  auto mx = grid_->getMetaX();
  for (auto const& x: mx) {
    painter->drawLine(RS_Vector(toGuiX(x), 0), RS_Vector(toGuiX(x), getHeight()));

    if (grid_->isIsometric()) {
      painter->drawLine(RS_Vector(toGuiX(x) + 0.5 * dx, 0),
                        RS_Vector(toGuiX(x) + 0.5 * dx, getHeight()));

    }
  }
  auto my = grid_->getMetaY();
  if(grid_->isIsometric()){//isometric metaGrid
    dx=fabs(dx);
    dy=fabs(dy);
    if(!my.size()|| dx<1 || dy<1) {
      return;
    }
    RS_Vector baseMeta(toGui(RS_Vector(mx[0], my[0])));
    RS_Vector vp0(-remainder(-baseMeta.x, dx) - dx,
        getHeight()-remainder(getHeight()-baseMeta.y, dy) + dy);

    RS_Vector vp1(vp0);
    RS_Vector vp2(getWidth()-remainder(getWidth()-baseMeta.x,dx)+dx,vp0.y);
    RS_Vector vp3(vp2);
    int cmx = round((vp2.x - vp0.x)/dx);
    int cmy = round((vp0.y +remainder(-baseMeta.y,dy)+dy)/dy);
    for(int i= cmx+cmy+2; i>=0; i--){
      if (i <= cmx) {
        vp0.x += dx;
        vp2.y -= dy;
      } else {
        vp0.y -= dy;
        vp2.x -= dx;
      }
      if (i <= cmy) {
        vp1.y -= dy;
        vp3.x -= dx;
      }else{
        vp1.x += dx;
        vp3.y -= dy;
      }
      painter->drawLine(vp0,vp1);
      painter->drawLine(vp2,vp3);
    }
  } else {
    for (auto const &y: my) {
      painter->drawLine(RS_Vector(0, toGuiY(y)),
                        RS_Vector(getWidth(), toGuiY(y)));
    }
  }
}

void RS_GraphicView::drawGrid(RS_Painter *painter) {
  if (!(grid_ && isGridOn())) {
    return;
  }

  painter->setPen(gridColor_);
  auto const &pts = grid_->getPoints();
  for (auto const &v: pts) {
    painter->drawGridPoint(toGui(v));
  }

  QString info = grid_->getInfo();

  updateGridStatusWidget(info);
}

void RS_GraphicView::updateGridStatusWidget(const QString &text) {
  emit gridStatusChanged(text);
}
