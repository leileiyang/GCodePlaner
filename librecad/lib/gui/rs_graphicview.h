#ifndef RS_GRAPHICVIEW_H
#define RS_GRAPHICVIEW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QPixmap>
#include <QMap>
#include <QDateTime>

#include <memory>

#include "qg_scrollbar.h"
#include "rs.h"
#include "rs_color.h"
#include "rs_vector.h"
#include "rs_grid.h"
#include "rs_entitycontainer.h"
#include "rs_graphic.h"
#include "rs_snapper.h"
#include "rs_actioninterface.h"
#include "rs_eventhandler.h"

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
  void adjustOffsetControls();
  void adjustZoomControls();

  //RS_Graphic *getGraphic() const;


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

  void setDefaultSnapMode(RS_SnapMode sm);
  RS_SnapMode getDefaultSnapMode() const;

  bool isGridOn() const { return true; }
  void setCrosshairType(RS2::CrosshairType chType);
  RS2::CrosshairType getCrosshairType() const;

  void updateGridStatusWidget(const QString &text);
  RS_Grid* getGrid() const;

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

  RS_Vector getMousePosition() const;

  RS_Vector const &getRelativeZero() const;
  void setRelativeZero(const RS_Vector &pos);
  void moveRelativeZero(const RS_Vector &pos);

  void lockRelativeZero(bool lock);
  bool isRelativeZeroLocked() const;

  void zoomIn(double f=1.5, const RS_Vector& center=RS_Vector(false));
  void zoomInX(double f=1.5);
  void zoomInY(double f=1.5);
  void zoomOut(double f=1.5, const RS_Vector& center=RS_Vector(false));
  void zoomOutX(double f=1.5);
  void zoomOutY(double f=1.5);
  void zoomWindow(RS_Vector v1, RS_Vector v2, bool keepAspectRatio=true);
  void saveView();

  RS_EntityContainer* getOverlayContainer(RS2::OverlayGraphics position);

  //void setDefaultAction(RS_ActionInterface* action);
  //RS_ActionInterface*  getDefaultAction();
  void setCurrentAction(RS_ActionInterface* action);
  RS_ActionInterface* getCurrentAction();

  QString device_;

 signals:
  void gridStatusChanged(const QString);
  void relativeZeroChanged(const RS_Vector);
  void previousZoomState(bool);

 public slots:

 protected:
  void paintEvent(QPaintEvent *) override;
  void resizeEvent(QResizeEvent* e) override;
  void wheelEvent(QWheelEvent* e) override;

 private:
  void wheelEventInTrackpad(QWheelEvent *e);
  void wheelEventZoom(QWheelEvent *e);

 protected:
  RS_EntityContainer *container_{nullptr};
  RS_EventHandler *eventHandler_;

  RS_Color background_;
  RS_Color foreground_;
  RS_Color gridColor_;
  RS_Color metaGridColor_;

  QG_ScrollBar* hScrollBar_;
  QG_ScrollBar* vScrollBar_;
  bool isSmoothScrolling_{false};

  RS2::RedrawMethod redrawMethod_;

  std::unique_ptr<RS_Grid> grid_;
  std::unique_ptr<QPixmap> pixmapLayer1_;
  std::unique_ptr<QPixmap> pixmapLayer2_;
  std::unique_ptr<QPixmap> pixmapLayer3_;

  RS_SnapMode defaultSnapMode_;

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

  //circular buffer for saved views
  std::vector<std::tuple<int, int, RS_Vector> > savedViews_;
  unsigned short savedViewIndex_ = 0;
  unsigned short savedViewCount_ = 0;
  QDateTime previousViewTime;

  RS_Vector relativeZero_{false};
  bool relativeZeroLocked_{false};

  QMap<int, RS_EntityContainer *> overlayEntities_;
};

#endif // FL_GRAPHICVIEW_H
