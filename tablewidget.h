#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QGraphicsItem>
#include <QWidget>

namespace Ui {
class TableWidget;
}

class TableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TableWidget(QWidget *parent = nullptr);
    ~TableWidget();

public slots:
    void addItem (QGraphicsItem *item) {};
    void removeItem (QGraphicsItem *item){};
    void toggleItemVisibility (QGraphicsItem *item){};
    void updateItemPosition (QGraphicsItem *item){};

signals:
    void removeItemEvent(QGraphicsItem *item);
    void toggleItemVisibilityEvent(QGraphicsItem *item);


private:
    Ui::TableWidget *ui;
};

#endif // TABLEWIDGET_H
