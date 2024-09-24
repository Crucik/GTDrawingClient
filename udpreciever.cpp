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
            case FigureType::FigureType_Rect:
            {
                qDebug("sending rectangle");
                auto fig = GetRoot<RectData>(figureContainer->payload()->data()); //messageString.payload.ptr.... why? o.O

                /*
                emit sendRect(QRect(fig->x(),fig->y(),fig->width(),fig->height()),
                                fig->color_hex()->c_str());
                */

                QGraphicsRectItem *newRect = new QGraphicsRectItem(QRect(fig->x(),fig->y(),fig->width(),fig->height())); //utechka?
                newRect->setBrush(QBrush(QColor(fig->color_hex()->c_str())));
                emit sendFigure(newRect);

            }
            break;
            case FigureType::FigureType_Ellipse:
            {
                qDebug("sending ellipse");
                auto fig = GetRoot<EllipseData>(figureContainer->payload()->data());

                /*
                emit sendEllipse(QRect(fig->x(),fig->y(),fig->r1(),fig->r2()),
                                fig->color_hex()->c_str());
                */

                QGraphicsEllipseItem *newEllipse = new QGraphicsEllipseItem(QRect(fig->x(),fig->y(),fig->r1(),fig->r2()));
                newEllipse->setBrush(QBrush(QColor(fig->color_hex()->c_str())));
                emit sendFigure(newEllipse);
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

                /*
                emit sendTriangle(triang,
                                  fig->color_hex()->c_str());
                */

                QGraphicsPolygonItem *newTriang = new QGraphicsPolygonItem(triang);
                newTriang->setBrush(QBrush(QColor(fig->color_hex()->c_str())));
                emit sendFigure(newTriang);

            }
            break;
            case FigureType::FigureType_Line:
            {
                qDebug("sending line");
                auto fig = GetRoot<LineData>(figureContainer->payload()->data());

                /*
                emit sendLine(QLine//.by оффают сессию в 4 утра. 2/10
                              (fig->x1(),fig->y1(),fig->x2(),fig->y2()),
                              fig->color_hex()->c_str());
                */

                QGraphicsLineItem *newLine = new QGraphicsLineItem(fig->x1(),fig->y1(),fig->x2(),fig->y2());
                newLine->setPen(QPen(QColor(fig->color_hex()->c_str())));
                emit sendFigure(newLine);
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

