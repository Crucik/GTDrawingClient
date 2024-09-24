#ifndef QCUSTOMGRAPHICSITEM_H
#define QCUSTOMGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QGraphicsSceneDragDropEvent>


class QCustomGraphicsItem : public QGraphicsItem {
public:
    QCustomGraphicsItem():QGraphicsItem(){
        this->setFlag(QGraphicsItem::ItemIsMovable);
        this->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    }

signals:
    void dragEndEvent(QCustomGraphicsItem *item);
    void middleMouseButtonEvent(QCustomGraphicsItem *item);
    void rightMouseButtonEvent(QCustomGraphicsItem *item);

protected:
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override{
        emit dragEndEvent(this);
    }

    void mousePressEvent(QGraphicsSceneDragDropEvent *event) {
        switch(event->buttons()){
        case(Qt::MouseButton::RightButton):
            emit rightMouseButtonEvent(this);
            break;
        case(Qt::MouseButton::MiddleButton):
            emit middleMouseButtonEvent(this);
            break;
        }
    }
};


class QCustomGraphicsLineItem: virtual public QCustomGraphicsItem, public QGraphicsLineItem {}; //QGraphicsLineItem
class QCustomAbstractGraphicsShapeItem : virtual public QCustomGraphicsItem, public QAbstractGraphicsShapeItem {}; //QAbstractGraphicsShapeItem
    class QCustomGraphicsEllipseItem: virtual public QCustomAbstractGraphicsShapeItem, public QGraphicsEllipseItem{}; //QGraphicsEllipseItem
    class QCustomGraphicsPolygonItem: virtual public QCustomAbstractGraphicsShapeItem, public QGraphicsPolygonItem{}; //QGraphicsPolygonItem
    class QCustomGraphicsRectItem: virtual public QCustomAbstractGraphicsShapeItem, public QGraphicsRectItem{}; //QGraphicsRectItem


#endif // QCUSTOMGRAPHICSITEM_H
