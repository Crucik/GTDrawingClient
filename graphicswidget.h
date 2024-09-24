#ifndef GRAPHICSWIDGET_H
#define GRAPHICSWIDGET_H

#include "qgraphicsscene.h"
#include <QGraphicsItem>
#include <QWidget>

namespace Ui {
class GraphicsWidget;
}

class GraphicsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GraphicsWidget(QWidget *parent = nullptr);
    ~GraphicsWidget();

public slots:
    void addItem (QGraphicsItem *item) {scene->addItem(item);};
    void removeItem (QGraphicsItem *item){scene->removeItem(item);};
    void toggleItemVisibility (QGraphicsItem *item){};//TODO

signals:
    void removeItemEvent(QGraphicsItem *item);
    void toggleItemVisibilityEvent(QGraphicsItem *item);
    void updateItemPositionEvent(QGraphicsItem *item);

private:
    Ui::GraphicsWidget *ui;
    QGraphicsScene *scene;
};

#endif // GRAPHICSWIDGET_H
