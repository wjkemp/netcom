#include "connection.h"
#include <QDebug>

Connection::Connection(QTcpSocket *socket, Serial *serial) :
    _socket(socket),
    _serial(serial)
{

    connect(socket, &QTcpSocket::readyRead, this, &Connection::_onReadyRead);
    connect(serial, &Serial::dataRead, this, &Connection::_onSerialDataRead);
}

void Connection::write(QByteArray const &data)
{
    _socket->write(data);
}

void Connection::_onSerialDataRead(QByteArray const &data)
{
    _socket->write(data);
}

void Connection::_onReadyRead()
{
    QByteArray bytes(_socket->readAll());
    _serial->write(bytes);
}

void Connection::_onDisconnected()
{
    delete _socket;
    deleteLater();
}

void Connection::_onErrorOccurred(QAbstractSocket::SocketError socketError)
{
    delete _socket;
    deleteLater();
}
