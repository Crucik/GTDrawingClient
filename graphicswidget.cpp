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


//signals
void GraphicsWidget::addItem(QGraphicsItem *item) {
    scene->addItem(item);
    item->setFlag(QGraphicsItem::ItemIsMovable);
    item->setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    //connect item to graphics slots
    //connect(item,&QCustomGraphicsItem::middleMouseButtonEvent,this,&GraphicsWidget::removeItem);
    //connect(item,&QCustomGraphicsItem::rightMouseButtonEvent,this,&GraphicsWidget::toggleItemVisibility);

    //pass thru signals
    //connect(item,&QCustomGraphicsItem::dragEndEvent,this,&GraphicsWidget::updateItemPositionEvent);
    //connect(item,&QCustomGraphicsItem::middleMouseButtonEvent,this,&GraphicsWidget::removeItemEvent);
    //connect(item,&QCustomGraphicsItem::rightMouseButtonEvent,this,&GraphicsWidget::toggleItemVisibilityEvent);

}

void GraphicsWidget::removeItem(QGraphicsItem *item){
    scene->removeItem(item);
}

void GraphicsWidget::toggleItemVisibility(QGraphicsItem *item){
    item->setVisible(!item->isVisible());
};
