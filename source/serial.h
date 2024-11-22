#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <QObject>
#include <QSerialPort>

class Serial : public QObject
{
    Q_OBJECT

public:
    Serial(QString const &name, unsigned int baudRate);
    Q_SIGNAL void dataRead(QByteArray const &data);
    Q_SLOT void write(QByteArray const &data);

private:
    Q_SLOT void _connect();
    Q_SLOT void _onReadyRead();
    Q_SLOT void _onErrorOccurred(QSerialPort::SerialPortError error);

private:
    QSerialPort *_serialPort;
    QString _name;
    unsigned int _baudRate;
};

#endif
