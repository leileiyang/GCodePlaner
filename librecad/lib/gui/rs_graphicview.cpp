#include "rs_graphicview.h"

#include <cmath>
#include <tuple>

#include <QApplication>
#include <QDesktopWidget>

#include "rs_math.h"
#include "rs_settings.h"
#include "rs_painterqt.h"
#include "rs_debug.h"
#include "rs_actionzoomin.h"

RS_GraphicView::RS_GraphicView(QWidget *parent) : QWidget(parent)
    ,device_("Mouse")
    ,eventHandler_(new RS_EventHandler(this))
    ,gridColor_(Qt::gray)
    ,metaGridColor_(64, 64, 64)
    ,redrawMethod_(RS2::RedrawAll)
    ,grid_(new RS_Grid(this))
    ,savedViews_(16) {

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

void RS_GraphicView::adjustOffsetControls() {
  if (scrollbars_) {
    static bool running = false;
    if (running) {
      return;
    }
    running = true;
    if (hScrollBar_ == NULL || vScrollBar_ == NULL) {
      return;
    }
    running = false;
  }
}

void RS_GraphicView::adjustZoomControls() {}

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


RS_Vector RS_GraphicView::getMousePosition() const {
  //find mouse position
  QPoint vp = mapFromGlobal(QCursor::pos());
  //if cursor is not on widget, return the widget center position
  if(!rect().contains(vp)) {
    vp = QPoint(width()/2, height()/2);
  }
  return toGraph(vp.x(), vp.y());
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

RS_EntityContainer* RS_GraphicView::getOverlayContainer(\
    RS2::OverlayGraphics position) {

  if (overlayEntities_[position]) {
    return overlayEntities_[position];
  }
  overlayEntities_[position]=new RS_EntityContainer(nullptr);

  return overlayEntities_[position];
}

void RS_GraphicView::lockRelativeZero(bool lock) {
  relativeZeroLocked_ = lock;
}

bool RS_GraphicView::isRelativeZeroLocked() const {
  return relativeZeroLocked_;
}

RS_Vector const& RS_GraphicView::getRelativeZero() const {
  return relativeZero_;
}

void RS_GraphicView::setRelativeZero(const RS_Vector &pos) {
  if (!relativeZeroLocked_) {
    relativeZero_ = pos;
    emit relativeZeroChanged(pos);
  }
}

void RS_GraphicView::moveRelativeZero(const RS_Vector &pos) {
  setRelativeZero(pos);
  redraw(RS2::RedrawGrid);
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

void RS_GraphicView::wheelEventInTrackpad(QWheelEvent *e) {
  QPoint numPixels = e->pixelDelta();
  isSmoothScrolling_ |= !numPixels.isNull();
  if (isSmoothScrolling_) {
    if (e->phase() == Qt::ScrollEnd) {
      isSmoothScrolling_ = false;
    }
  } else {
    numPixels = e->angleDelta() / 4;
  }

  RS_Vector mouse = toGraph(e->x(), e->y());
  if (!numPixels.isNull()) {
    if (e->modifiers() == Qt::ControlModifier) {
      RS_SETTINGS->beginGroup("/Defaults");
      bool invZoom = (RS_SETTINGS->readNumEntry("/InvertZoomDirection", 0) == 1);
      RS_SETTINGS->endGroup();

      // Hold ctrl to zoom. 1 % per pixel
      double v = (invZoom) ? (numPixels.y() / 100.) : (-numPixels.y() / 100.);
      RS2::ZoomDirection direction;
      double factor;

      if (v < 0) {
          direction = RS2::Out; factor = 1-v;
      } else {
          direction = RS2::In;  factor = 1+v;
      }
      setCurrentAction(new RS_ActionZoomIn(*container_, *this, direction,
                                           RS2::Both, &mouse, factor));
    } else {
      RS_SETTINGS->beginGroup("/Defaults");
      bool inv_h = (RS_SETTINGS->readNumEntry("/WheelScrollInvertH", 0) == 1);
      bool inv_v = (RS_SETTINGS->readNumEntry("/WheelScrollInvertV", 0) == 1);
      RS_SETTINGS->endGroup();

      int hDelta = (inv_h) ? -numPixels.x() : numPixels.x();
      int vDelta = (inv_v) ? -numPixels.y() : numPixels.y();

      // scroll by scrollbars: issue #479 (it has its own issues)
      if (scrollbars_) {
        hScrollBar_->setValue(hScrollBar_->value() - hDelta);
        vScrollBar_->setValue(vScrollBar_->value() - vDelta);
      } else {
        //setCurrentAction(new RS_ActionZoomScroll(hDelta, vDelta,
        //                                         *container, *this));
      }
    }
    redraw();
  }
  e->accept();
}

void RS_GraphicView::wheelEventZoom(QWheelEvent *e) {
  /*
   * The zoomFactor effects how quickly the scroll wheel will zoom in & out.
   *
   * Benchmarks:
   * 1.250 - the original; fast & usable, but seems a choppy & a bit 'jarring'
   * 1.175 - still a bit choppy
   * 1.150 - smoother than the original, but still 'quick' enough for good navigation.
   * 1.137 - seems to work well for me
   * 1.125 - about the lowest that would be acceptable and useful, a tad on the slow side for me
   * 1.100 - a very slow & deliberate zooming, but feels very "cautious", "controlled", "safe", and "precise".
   * 1.000 - goes nowhere. :)
   */

  RS_Vector mouse = toGraph(e->x(), e->y());
  const double zoomFactor=1.137;
  RS_Vector mainViewCenter = toGraph(getWidth()/2, getHeight()/2);

  RS_SETTINGS->beginGroup("/Defaults");
  bool invZoom = (RS_SETTINGS->readNumEntry("/InvertZoomDirection", 0) == 1);
  RS_SETTINGS->endGroup();

  if ((e->delta() > 0 && !invZoom) || (e->delta() < 0 && invZoom)) {
    const double zoomInOvershoot=1.20;
    RS_Vector effect{mouse};
    {
      effect -= mainViewCenter;
      effect.scale(zoomInOvershoot);
      effect += mainViewCenter;
    }
    setCurrentAction(new RS_ActionZoomIn(*container_, *this,
        RS2::In, RS2::Both, &effect, zoomFactor));

  } else {
    const double zoomOutUndershoot=0.30;
    RS_Vector effect{mouse};
    {
      effect -= mainViewCenter;
      effect.scale(zoomOutUndershoot);
      effect += mainViewCenter;
    }
    setCurrentAction(new RS_ActionZoomIn(*container_, *this,
        RS2::Out, RS2::Both, &effect, zoomFactor));

  }
}

void RS_GraphicView::wheelEvent(QWheelEvent* e) {
  if (device_ == "Trackpad") {
    wheelEventInTrackpad(e);
    return;
  }

  if (e->delta() == 0) {
    e->accept();
    return;
  }

  bool scroll = false;
  RS2::Direction direction = RS2::Up;
  // scroll up / down:
  if (e->modifiers() == Qt::ControlModifier) {
    scroll = true;
    switch(e->orientation()){
      case Qt::Horizontal:
        direction = (e->delta() > 0) ? RS2::Left : RS2::Right;
        break;
      default:
      case Qt::Vertical:
        direction = (e->delta() > 0) ? RS2::Up : RS2::Down;
    }
  } else if	(e->modifiers() == Qt::ShiftModifier) { // scroll left / right:
    scroll = true;
    switch(e->orientation()){
      case Qt::Horizontal:
        direction = (e->delta() > 0) ? RS2::Up : RS2::Down;
        break;
      default:
      case Qt::Vertical:
        direction = (e->delta() > 0) ? RS2::Left : RS2::Right;
    }
  }

  if (scroll && scrollbars_) {
    //scroll by scrollbars: issue #479
    RS_SETTINGS->beginGroup("/Defaults");
    bool inv_h = (RS_SETTINGS->readNumEntry("/WheelScrollInvertH", 0) == 1);
    bool inv_v = (RS_SETTINGS->readNumEntry("/WheelScrollInvertV", 0) == 1);
    RS_SETTINGS->endGroup();

    int delta;
    switch(direction) {
      case RS2::Left:
      case RS2::Right:
        delta = (inv_h) ? -e->delta() : e->delta();
        hScrollBar_->setValue(hScrollBar_->value()+delta);
        break;
      default:
        delta = (inv_v) ? -e->delta() : e->delta();
        vScrollBar_->setValue(vScrollBar_->value()+delta);
    }
  } else if (e->modifiers() == 0) {
    wheelEventZoom(e);
  }
  redraw();
  e->accept();
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

RS_Grid* RS_GraphicView::getGrid() const {
  return grid_.get();
}

void RS_GraphicView::setDefaultSnapMode(RS_SnapMode sm) {
  defaultSnapMode_ = sm;
  //if (eventHandler_) {
    //eventHandler_->setSnapMode(sm);
  //}
}

RS_SnapMode RS_GraphicView::getDefaultSnapMode() const {
  return defaultSnapMode_;
}

void RS_GraphicView::setCrosshairType(RS2::CrosshairType chType) {
  grid_->setCrosshairType(chType);
}

RS2::CrosshairType RS_GraphicView::getCrosshairType() const {
  return grid_->getCrosshairType();
}

void RS_GraphicView::zoomIn(double f, const RS_Vector& center) {
  if (f < 1.0e-6) {
    RS_DEBUG->print(RS_Debug::D_WARNING,
                    "RS_GraphicView::zoomIn: invalid factor");
    return;
  }
  RS_Vector c = center;
  if (!c.valid) {
    //find mouse position
    c= getMousePosition();
  }
  zoomWindow(toGraph(0, 0).scale(c, RS_Vector(1.0/f,1.0/f)),
             toGraph(getWidth(), getHeight()).scale(c, RS_Vector(1.0/f,1.0/f)));

  redraw();
}

void RS_GraphicView::zoomInX(double f) {
  factor_.x *= f;
  offsetX_ = (int)((offsetX_ - getWidth()/2) * f) + getWidth()/2;
  adjustOffsetControls();
  adjustZoomControls();
  redraw();
}

void RS_GraphicView::zoomInY(double f) {
  factor_.y *= f;
  offsetY_ = (int)((offsetY_ - getHeight()/2) * f) + getHeight()/2;
  adjustOffsetControls();
  adjustZoomControls();
  redraw();
}

void RS_GraphicView::zoomOut(double f, const RS_Vector& center) {
  if (f < 1.0e-6) {
    RS_DEBUG->print(RS_Debug::D_WARNING,
                    "RS_GraphicView::zoomOut: invalid factor");
    return;
  }
  zoomIn(1/f, center);
}

void RS_GraphicView::zoomOutX(double f) {
  if (f < 1.0e-6) {
    RS_DEBUG->print(RS_Debug::D_WARNING,
                    "RS_GraphicView::zoomOutX: invalid factor");

    return;
  }
  factor_.x /= f;
  offsetX_ = (int)(offsetX_ / f);
  adjustOffsetControls();
  adjustZoomControls();
  redraw();
}

void RS_GraphicView::zoomOutY(double f) {
  if (f < 1.0e-6) {
    RS_DEBUG->print(RS_Debug::D_WARNING,
                    "RS_GraphicView::zoomOutY: invalid factor");

    return;
  }
  factor_.y /= f;
  offsetY_ = (int)(offsetY_ / f);
  adjustOffsetControls();
  adjustZoomControls();
  redraw();
}

void RS_GraphicView::zoomWindow(RS_Vector v1, RS_Vector v2,
                                bool keepAspectRatio) {

  double zoomX = 480.0;    // Zoom for X-Axis
  double zoomY = 640.0;    // Zoom for Y-Axis   (Set smaller one)
  int zoomBorder = 0;

  // Switch left/right and top/bottom is necessary:
  if(v1.x > v2.x) {
    std::swap(v1.x,v2.x);
  }
  if(v1.y > v2.y) {
    std::swap(v1.y,v2.y);
  }

  // Get zoom in X and zoom in Y:
  if(v2.x - v1.x >1.0e-6) {
    zoomX = getWidth() / (v2.x-v1.x);
  }
  if(v2.y - v1.y >1.0e-6) {
    zoomY = getHeight() / (v2.y-v1.y);
  }

  // Take smaller zoom:
  if (keepAspectRatio) {
    if(zoomX<zoomY) {
      if(getWidth()!=0) {
        zoomX = zoomY = ((double)(getWidth()-2*zoomBorder)) /
            (double)getWidth()*zoomX;
      }
    } else {
      if(getHeight()!=0) {
        zoomX = zoomY = ((double)(getHeight()-2*zoomBorder)) /
            (double)getHeight()*zoomY;
      }
    }
  }

  zoomX=fabs(zoomX);
  zoomY=fabs(zoomY);

  // Borders in pixel after zoom
  int pixLeft  =(int)(v1.x*zoomX);
  int pixTop   =(int)(v2.y*zoomY);
  int pixRight =(int)(v2.x*zoomX);
  int pixBottom=(int)(v1.y*zoomY);
  if (pixLeft == INT_MIN || pixLeft== INT_MAX ||
      pixRight == INT_MIN || pixRight== INT_MAX ||
      pixTop == INT_MIN || pixTop== INT_MAX ||
      pixBottom == INT_MIN || pixBottom== INT_MAX ) {

    return;
  }
  saveView();

  // Set new offset for zero point:
  offsetX_ = - pixLeft + (getWidth() -pixRight +pixLeft)/2;
  offsetY_ = - pixTop + (getHeight() -pixBottom +pixTop)/2;
  factor_.x = zoomX;
  factor_.y = zoomY;

  adjustOffsetControls();
  adjustZoomControls();

  redraw();
}

void RS_GraphicView::saveView() {
  //if (getGraphic()) {
  //  getGraphic()->setModified(true);
  //}
  QDateTime noUpdateWindow = QDateTime::currentDateTime().addMSecs(-500);
  //do not update view within 500 milliseconds
  if (previousViewTime > noUpdateWindow) {
    return;
  }
  previousViewTime = QDateTime::currentDateTime();
  savedViews_[savedViewIndex_] = std::make_tuple(offsetX_, offsetY_, factor_);
  savedViewIndex_ = (savedViewIndex_ + 1) % savedViews_.size();

  if(savedViewCount_< savedViews_.size()) {
    savedViewCount_++;
  }

  if(savedViewCount_ == 1){
    emit previousZoomState(true);
  }
}

void RS_GraphicView::setCurrentAction(RS_ActionInterface* action) {
  RS_DEBUG->print("RS_GraphicView::setCurrentAction");
  if (eventHandler_) {
    eventHandler_->setCurrentAction(action);
  }
  RS_DEBUG->print("RS_GraphicView::setCurrentAction: OK");
}

RS_ActionInterface* RS_GraphicView::getCurrentAction() {
  if (eventHandler_) {
    return eventHandler_->getCurrentAction();
  } else {
    return nullptr;
  }
}
