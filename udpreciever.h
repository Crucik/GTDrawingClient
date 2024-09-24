#pragma once

#include "qcustomgraphicsitem.h"
#include "qudpsocket.h"
#include <QObject>
#include <QNetworkDatagram>


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
        void sendFigure(QGraphicsItem  *item);

    private:
        QUdpSocket *udpSocket;
        void processTheDatagram(QNetworkDatagram datagram);
};
