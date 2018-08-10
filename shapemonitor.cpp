#include "shapemonitor.h"
#include "ui_shapemonitor.h"

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
