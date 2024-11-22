#include "serial.h"
#include <QTimer>
#include <QDebug>

Serial::Serial(QString const &name, unsigned int baudRate) :
    _name(name),
    _baudRate(baudRate)
{
    QTimer::singleShot(1000, this, &Serial::_connect);
}

void Serial::write(QByteArray const &data)
{
    _serialPort->write(data);
}

void Serial::_connect()
{
    qInfo() << "Connecting to serial device " << _name;
    _serialPort = new QSerialPort(this);

    _serialPort->setPortName(_name);
    _serialPort->setBaudRate(_baudRate);
    _serialPort->setDataBits(QSerialPort::Data8);
    _serialPort->setParity(QSerialPort::NoParity);
    _serialPort->setStopBits(QSerialPort::OneStop);
    _serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if (_serialPort->open(QIODevice::ReadWrite)) {
        connect(_serialPort, &QSerialPort::readyRead, this, &Serial::_onReadyRead);

    } else {
        qWarning() << "Could not connect to serial device " << _name;
        delete _serialPort;
        QTimer::singleShot(1000, this, &Serial::_connect);
    }
}

void Serial::_onReadyRead()
{
    QByteArray data(_serialPort->readAll());
    emit dataRead(data);
}

void Serial::_onErrorOccurred(QSerialPort::SerialPortError error)
{
    qWarning() << "Serial port error: " << error;
    delete _serialPort;
    QTimer::singleShot(1000, this, &Serial::_connect);
}
