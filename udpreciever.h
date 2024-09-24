#pragma once

#include "qudpsocket.h"
#include <QObject>
#include <QNetworkDatagram>
#include <qgraphicsitem.h>


class UDPReciever : public QObject
{
    Q_OBJECT

    public:
        UDPReciever()=default;
        void initSocket();;

    public slots:
        void start(){initSocket();};
        void readPendingDatagrams();

    signals:
//        void sendRect(QRect rect, QString color);
//        void sendEllipse(QRect rect, QString color);
//        void sendTriangle(QPolygon poly, QString color);
//        void sendLine(QLine line, QString color);
        void sendFigure(QGraphicsItem  *item);

    private:
        QUdpSocket *udpSocket;
        void processTheDatagram(QNetworkDatagram datagram);
};
