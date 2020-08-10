#ifndef RS_GRAPHICVIEW_H
#define RS_GRAPHICVIEW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QPixmap>

#include <memory>

#include "qg_scrollbar.h"
#include "rs.h"
#include "rs_color.h"
#include "rs_vector.h"
#include "rs_grid.h"

class RS_Painter;

class RS_GraphicView : public QWidget
{
    Q_OBJECT
 public:
  explicit RS_GraphicView(QWidget *parent = 0);

  void setSceneRect(const QRectF &/*rect*/) {}
  void setScene(QGraphicsScene */*scene*/) {}
  void onRestore() {}

  int getWidth() const;
  int getHeight() const;
  void redraw(RS2::RedrawMethod method=RS2::RedrawAll);

  void setBackground(const RS_Color& bg);
  RS_Color getBackground() const {
    return background_;
  }

  RS_Color getForeground() const {
    return foreground_;
  }

  void setGridColor(const RS_Color &c) {
    gridColor_ = c;
  }
  void setMetaGridColor(const RS_Color &c) {
    metaGridColor_ = c;
  }

  bool isPrintPreview() const {
    return printPreview_;
  }
  void setPrintPreview(bool pv) {
    printPreview_ = pv;
  }

  bool isGridOn() const {
    return true;
  }
  void updateGridStatusWidget(const QString &text);

  RS_Vector toGui(RS_Vector v) const;
  double toGuiX(double x) const;
  double toGuiY(double y) const;
  double toGuiDX(double d) const;
  double toGuiDY(double d) const;

  RS_Vector toGraph(RS_Vector v) const;
  RS_Vector toGraph(int x, int y) const;
  double toGraphX(int x) const;
  double toGraphY(int y) const;
  double toGraphDX(int d) const;
  double toGraphDY(int d) const;

  void setFactor(double f);
  void setFactorX(double f);
  void setFactorY(double f);
  RS_Vector getFactor() const;

  void setOffsetX(int ox);
  void setOffsetY(int oy);
  int getOffsetX() const;
  int getOffsetY() const;

 signals:
  void gridStatusChanged(const QString);

 public slots:

 protected:
  void paintEvent(QPaintEvent *) override;
  void resizeEvent(QResizeEvent* e) override;

 protected:
  RS_Color background_;
  RS_Color foreground_;
  RS_Color gridColor_;
  RS_Color metaGridColor_;

  QG_ScrollBar* hScrollBar_;
  QG_ScrollBar* vScrollBar_;

  RS2::RedrawMethod redrawMethod_;

  std::unique_ptr<RS_Grid> grid_;
  std::unique_ptr<QPixmap> pixmapLayer1_;
  std::unique_ptr<QPixmap> pixmapLayer2_;
  std::unique_ptr<QPixmap> pixmapLayer3_;

  void getPixmapForView(std::unique_ptr<QPixmap>& pm);
  void drawLayer1(RS_Painter *painter);
  void drawMetaGrid(RS_Painter *painter);
  void drawGrid(RS_Painter *painter);

 private:
  bool scrollbars_{false};
  bool zoomFrozen_{false};
  bool printPreview_{false};

  RS_Vector factor_= RS_Vector(1., 1.);
  int offsetX_ = 0;
  int offsetY_ = 0;
};

#endif // FL_GRAPHICVIEW_H
