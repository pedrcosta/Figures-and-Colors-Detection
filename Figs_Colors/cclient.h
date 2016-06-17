#ifndef CCLIENT_H
#define CCLIENT_H

#include <QtCore>
#include <QCoreApplication>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QString>
#include <QObject>

#define LEN 50
#define CONNECT_TIME_OUT 5000

class CClient : public QObject
{
    Q_OBJECT
public:
    CClient(QObject* parent = 0);
    ~CClient();

    bool start(QString address, quint16 port);
    void stop();

    const char *qstringToConstChar(QString qtStrData);

public slots:
    void startTransfer(const char* sendbuf, int length);
    void startTransfer(const char* sendbuf);
    void startTransfer(QString qtStrData);
    QString qStringTransfer(const char *sendbuf, int length);

private:
    QTcpSocket client;

};

#endif // CCLIENT_H
