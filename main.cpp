#include "mainwindow.h"
#include "api_generated.h"
#include <QApplication>
#include <QUdpSocket>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

    flatbuffers::FlatBufferBuilder builder(1024);

}
