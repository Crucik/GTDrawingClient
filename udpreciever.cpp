#include "udpreciever.h"
#include "api_generated.h"
#include "qbrush.h"

#include <qpen.h>

void UDPReciever::initSocket()
{
    qDebug("starting socket");
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::LocalHost, 10002);

    QAbstractSocket::connect(udpSocket, &QUdpSocket::readyRead,
                             this, &UDPReciever::readPendingDatagrams);
    qDebug("socket connected");

}

void UDPReciever::processTheDatagram(QNetworkDatagram datagram){
    qDebug("reciving datagram");
    if (datagram.isValid()){
        using namespace flatbuffers;
        if (auto figureContainer = GetRoot<Figure>(datagram.data().data())){ //datagram.qbytearray.ptr
            if (!figureContainer->payload()) return;
            switch(figureContainer->type()){
            static int id = 0;
            case FigureType::FigureType_Rect:
            {
                qDebug("sending rectangle");
                auto fig = GetRoot<RectData>(figureContainer->payload()->data()); //messageString.payload.ptr.... why? o.O

                QGraphicsRectItem *newFigure = new QGraphicsRectItem(QRect(fig->x(),fig->y(),fig->width(),fig->height())); //utechka?
                newFigure->setBrush(QBrush(QColor(fig->color_hex()->c_str())));
                newFigure->setData(0,id++);
                newFigure->setData(1,"Rectangle");
                emit sendFigure(newFigure);

            }
            break;
            case FigureType::FigureType_Ellipse:
            {
                qDebug("sending ellipse");
                auto fig = GetRoot<EllipseData>(figureContainer->payload()->data());

                QGraphicsEllipseItem *newFigure = new QGraphicsEllipseItem(QRect(fig->x(),fig->y(),fig->r1(),fig->r2()));
                newFigure->setBrush(QBrush(QColor(fig->color_hex()->c_str())));
                newFigure->setData(0,id++);
                newFigure->setData(1,"Ellipse");
                emit sendFigure(newFigure);
            }
            break;
            case FigureType::FigureType_Triangle:
            {
                qDebug("sending triangle");
                auto fig = GetRoot<TriangleData>(figureContainer->payload()->data());
                QPolygon triang;
                triang.append(QPoint(fig->x1(),fig->y1()));
                triang.append(QPoint(fig->x2(),fig->y2()));
                triang.append(QPoint(fig->x3(),fig->y3()));

                QGraphicsPolygonItem *newFigure = new QGraphicsPolygonItem(triang);
                newFigure->setBrush(QBrush(QColor(fig->color_hex()->c_str())));
                newFigure->setData(0,id++);
                newFigure->setData(1,"Triangle");
                emit sendFigure(newFigure);

            }
            break;
            case FigureType::FigureType_Line:
            {
                qDebug("sending line");
                auto fig = GetRoot<LineData>(figureContainer->payload()->data());

                QGraphicsLineItem *newFigure = new QGraphicsLineItem(fig->x1(),fig->y1(),fig->x2(),fig->y2());
                newFigure->setPen(QPen(QColor(fig->color_hex()->c_str())));
                newFigure->setData(0,id++);
                newFigure->setData(1,"Line");
                emit sendFigure(newFigure);
            }
            break;
            default:
                qDebug("figure payload isnt valid");
            return;
            }
        }else qDebug("datagram payload isnt valid");


    }
}

void UDPReciever::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        processTheDatagram(datagram);
    }
}

