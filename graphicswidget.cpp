#include "graphicswidget.h"
#include "ui_graphicswidget.h"

GraphicsWidget::GraphicsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphicsWidget),
    scene(new QGraphicsScene)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
}

GraphicsWidget::~GraphicsWidget()
{
    delete ui;
}
