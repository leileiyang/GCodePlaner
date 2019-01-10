#include "shapemonitor.h"
#include "ui_shapemonitor.h"

#define ZOOM_IN_STEP 1.1
#define ZOOM_OUT_STEP 0.9

ShapeMonitor::ShapeMonitor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShapeMonitor)
{
    ui->setupUi(this);
    ui->shape_view_->setRenderHint(QPainter::Antialiasing, false);
    ui->shape_view_->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->shape_view_->setInteractive(false);
    ui->shape_view_->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    ui->shape_view_->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    ui->shape_view_->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    ui->shape_view_->setMouseTracking(true);
    ui->shape_view_->setMatrix(QMatrix(1, 0, 0, -1, 0, 0));
}

ShapeMonitor::~ShapeMonitor()
{
    delete ui;
}

void ShapeMonitor::setScene(QGraphicsScene *scene) {
  if (scene) {
    ui->shape_view_->setScene(scene);
  }
}

void ShapeMonitor::setSceneRect(const QRectF &rect) {
  ui->shape_view_->fitInView(rect, Qt::KeepAspectRatio);
  ui->shape_view_->setSceneRect(rect);
  matrix_ = ui->shape_view_->matrix();
}

void ShapeMonitor::StepZoomIn() {
  ui->shape_view_->scale(ZOOM_IN_STEP, ZOOM_IN_STEP);
}

void ShapeMonitor::StepZoomOut() {
  ui->shape_view_->scale(ZOOM_OUT_STEP, ZOOM_OUT_STEP);
}

void ShapeMonitor::onRestore() {
  ui->shape_view_->setMatrix(matrix_);
}

void ShapeMonitor::wheelEvent(QWheelEvent *e) {
  if (e->modifiers() & Qt::ControlModifier) {
    if (e->delta() > 0) {
      StepZoomIn();
    } else {
      StepZoomOut();
    }
  } else {
    QWidget::wheelEvent(e);
  }
}
