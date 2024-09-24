#include "tablewidget.h"
#include "ui_tablewidget.h"

#include <QPainter>

TableWidget::TableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableWidget)
{
    ui->setupUi(this);

    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "ID"
                                                             << "Type"
                                                             << "Position"
                                                             << "Region"
                                                             << "Hide"
                                                             << "Remove");
}


TableWidget::~TableWidget()
{
    delete ui;
}


void TableWidget::addItem(QGraphicsItem *item) {

    //extract props
    unsigned int newRowId = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(newRowId);

    //display props (что за ужас)
    ui->tableWidget->setItem(newRowId,0,new QTableWidgetItem(item->data(0).toString()));
    ui->tableWidget->setItem(newRowId,1,new QTableWidgetItem(item->data(1).toString()));
    updateLocationHelper(item,newRowId);

    //create buttons
    QPushButton* removeBtn = new QPushButton();
    removeBtn->setIcon(QIcon(":/resources/tableWidget/remove.jpg"));
    QPushButton* hideBtn = new QPushButton;
    hideBtn->setIcon(QIcon(":/resources/tableWidget/hide.jpg"));

    //link buttons
    connect(removeBtn,&QPushButton::clicked,this,[item,this](){this->removeItem(item);});
    connect(removeBtn,&QPushButton::clicked,this,[item,this](){this->removeItemEvent(item);});
    connect(hideBtn,&QPushButton::clicked,this,[hideBtn,this](){this->hideIconHelper(hideBtn);});
    connect(hideBtn,&QPushButton::clicked,this,[item,this](){this->toggleItemVisibilityEvent(item);});

    //display buttons
    ui->tableWidget->setCellWidget(newRowId,4,removeBtn);
    ui->tableWidget->setCellWidget(newRowId,5,hideBtn);

    //
    ui->tableWidget->resizeColumnsToContents();
}


void TableWidget::removeItem(QGraphicsItem *item){
    QString id = item->data(0).toString();

    for(int i = 0; i < ui->tableWidget->rowCount(); ++i)//.....
    {
        if(ui->tableWidget->item(i, 0)->text() == id)
        {
            ui->tableWidget->removeRow(i);
            ui->tableWidget->resizeColumnsToContents();
            return;
        }
    }
}


void TableWidget::toggleItemVisibility(QGraphicsItem *item){
    QString id = item->data(0).toString();

    for(int i = 0; i < ui->tableWidget->rowCount(); ++i)
    {
        if(ui->tableWidget->item(i, 0)->text() == id)
        {
            if(item->isVisible()){
                hideIconHelper(dynamic_cast<QPushButton*>(ui->tableWidget->cellWidget(i,5)));
            }else{
                hideIconHelper(dynamic_cast<QPushButton*>(ui->tableWidget->cellWidget(i,5)),false);
            }
            return;
        }
    }
}


void TableWidget::updateItemPosition(QGraphicsItem *item){
    QString id = item->data(0).toString();

    for(int i = 0; i < ui->tableWidget->rowCount(); ++i)
    {
        if(ui->tableWidget->item(i, 0)->text() == id)
        {
            this->updateLocationHelper(item,i);
            return;
        }
    }
}


void TableWidget::updateLocationHelper(QGraphicsItem *item, const int row){
    QPointF position =  item->scenePos();
    QRectF boundrect =  item->boundingRect();
    ui->tableWidget->setItem(row,2,new QTableWidgetItem(QString("%1px, %2px")
                                                            .arg(position.x())
                                                            .arg(boundrect.y())));
    ui->tableWidget->setItem(row,3,new QTableWidgetItem(QString("%1px, %2px")
                                                            .arg(boundrect.width())
                                                            .arg(boundrect.height())));
}


void TableWidget::hideIconHelper(QPushButton *button, bool transparent){
    if(!button)return;
    if (transparent) {
        QPixmap transparentPixmap = QIcon(":/resources/tableWidget/hide.jpg").pixmap(32, 32);
        QPixmap semiTransparent(transparentPixmap.size());
        semiTransparent.fill(Qt::transparent);

        QPainter painter(&semiTransparent);
        painter.setOpacity(0.5);
        painter.drawPixmap(0, 0, transparentPixmap);
        painter.end();

        button->setIcon(QIcon(semiTransparent));
    } else {
        button->setIcon(QIcon(":/resources/tableWidget/hide.jpg"));
    }
}
