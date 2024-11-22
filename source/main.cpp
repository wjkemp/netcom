#include <QCoreApplication>

#include "server.h"
#include "serial.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Serial serial(argv[1], 115200);
    Server server(&serial);

    return a.exec();
}
