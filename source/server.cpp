#include "server.h"
#include "connection.h"
#include <QtNetwork>
#include <QDebug>

Server::Server(Serial *serial) :
    _serial(serial)
{
    _server = new QTcpServer(this);
    if (!_server->listen(QHostAddress::Any, 12000)) {
        qCritical() << tr("Unable to start the server: %1").arg(_server->errorString());
        return;
    }

    QString ipAddress;
    const QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (const QHostAddress &entry : ipAddressesList) {
        if (entry != QHostAddress::LocalHost && entry.toIPv4Address()) {
            ipAddress = entry.toString();
            break;
        }
    }

    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty()) {
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    }

    qInfo() << tr("The server is running on IP: %1, port: %2").arg(ipAddress).arg(_server->serverPort());

    connect(_server, &QTcpServer::newConnection, this, &Server::acceptConnection);

}

void Server::acceptConnection()
{
    qInfo() << "Incoming connection accepted";

    QTcpSocket *socket = _server->nextPendingConnection();
    Connection *connection = new Connection(socket, _serial);
}
