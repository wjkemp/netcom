#ifndef __SERVER_H__
#define __SERVER_H__

#include <QObject>
#include <QTcpServer>

#include "serial.h"

class Server : public QObject
{
    Q_OBJECT

public:
    Server(Serial *serial);

private:
    Q_SLOT void acceptConnection();

private:
    QTcpServer *_server{nullptr};
    Serial *_serial{nullptr};

};

#endif
