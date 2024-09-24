#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "udpreciever.h"
#include <QAbstractGraphicsShapeItem>
#include <QMainWindow>
#include <qmap.h>
#include "graphicswidget.h"
#include "tablewidget.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void addItem(QGraphicsItem  *item);
    void switchToGraphicsView();;
    void switchToTableView();;

signals:
    void newItem(QGraphicsItem  *item);

private:  
    Ui::MainWindow *ui;
    UDPReciever *udpReciever;
    QThread *udpThread;
    GraphicsWidget *graphicsWidget;
    TableWidget *tableWidget;
};
#endif // MAINWINDOW_H
