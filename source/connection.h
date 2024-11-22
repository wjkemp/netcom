#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include <QObject>
#include <QTcpSocket>

#include "serial.h"

class Connection : public QObject
{
    Q_OBJECT

public:
    Connection(QTcpSocket *socket, Serial *serial);
    void write(QByteArray const &data);

private:
    Q_SLOT void _onReadyRead();
    Q_SLOT void _onSerialDataRead(QByteArray const &data);
    Q_SLOT void _onDisconnected();
    Q_SLOT void _onErrorOccurred(QAbstractSocket::SocketError socketError);

private:
    QTcpSocket *_socket;
    Serial *_serial;

};

#endif
