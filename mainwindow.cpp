#include "mainwindow.h"
#include "graphicswidget.h"
#include "tablewidget.h"
#include "./ui_mainwindow.h"

#include <QThread>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , udpReciever(new UDPReciever)
    , udpThread(new QThread)
    , graphicsWidget(new GraphicsWidget)
    , tableWidget(new TableWidget)
{
//    connect(udpReciever,&UDPReciever::sendRect,this,&MainWindow::addRect);
//    connect(udpReciever,&UDPReciever::sendEllipse,this,&MainWindow::addEllipse);
//    connect(udpReciever,&UDPReciever::sendTriangle,this,&MainWindow::addTriangle);
//    connect(udpReciever,&UDPReciever::sendLine,this,&MainWindow::addLine);

    //Setup widgets
    ////mainWindow signals
    connect(this,&MainWindow::newItem,graphicsWidget,&GraphicsWidget::addItem);
    connect(this,&MainWindow::newItem,tableWidget,&TableWidget::addItem);
    ////tableWidget signals
    connect(tableWidget,&TableWidget::removeItemEvent,graphicsWidget,&GraphicsWidget::removeItem);
    connect(tableWidget,&TableWidget::toggleItemVisibilityEvent,graphicsWidget,&GraphicsWidget::toggleItemVisibility);
    ////grapthicsWidget signals
    connect(graphicsWidget,&GraphicsWidget::removeItemEvent,tableWidget,&TableWidget::removeItem);
    connect(graphicsWidget,&GraphicsWidget::toggleItemVisibilityEvent,tableWidget,&TableWidget::toggleItemVisibility);
    connect(graphicsWidget,&GraphicsWidget::updateItemPositionEvent,tableWidget,&TableWidget::updateItemPosition);
    //

    //Setup ui
    ui->setupUi(this);
    ui->stackedWidget->addWidget(graphicsWidget);
    ui->stackedWidget->addWidget(tableWidget);
    connect(ui->showGraphics,&QAction::triggered,this,&MainWindow::switchToGraphicsView);
    connect(ui->showTable,&QAction::triggered,this,&MainWindow::switchToTableView);
    //

    //Setup reciver
    connect(udpReciever,&UDPReciever::sendFigure,this,&MainWindow::addItem);
    udpReciever->moveToThread(udpThread);
    connect(udpThread, SIGNAL(started()), udpReciever, SLOT(start()));
    connect(udpThread, SIGNAL(finished()), udpReciever, SLOT(deleteLater()));
    udpThread->start();
    //
}

//void MainWindow::addRect(QRect rect, QString color){
//    QGraphicsRectItem *newrect = scene->addRect(rect);
//    newrect->setBrush(QBrush(QColor(color)));
//}
//void MainWindow::addEllipse(QRect rect, QString color){ // treating ellipse like rectangle (width=r1;height=r2)
//    QGraphicsEllipseItem *newrect = scene->addEllipse(rect);
//    newrect->setBrush(QBrush(QColor(color)));
//}
//void MainWindow::addLine(QLine line, QString color){
//    QGraphicsLineItem *newline = scene->addLine(line);
//    newline->setPen(QPen(QColor(color)));
//}
//void MainWindow::addTriangle(QPolygon poly, QString color){
//    QGraphicsPolygonItem *newpoly = scene->addPolygon(poly);
//    newpoly->setBrush(QBrush(QColor(color)));
//}
void MainWindow::addItem(QGraphicsItem  *item){
    emit newItem(item);
}

void MainWindow::switchToGraphicsView(){
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::switchToTableView(){
    ui->stackedWidget->setCurrentIndex(2);
};




MainWindow::~MainWindow()
{
    delete graphicsWidget;
    delete tableWidget;
    delete ui;
    delete udpReciever;
}

