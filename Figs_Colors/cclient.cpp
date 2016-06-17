#include "cclient.h"

CClient::CClient(QObject* parent): QObject(parent)
{
    //connect(&client, SIGNAL(connected()), this, SLOT(connected()));
}

CClient::~CClient()
{
    client.close();
}

bool CClient::start(QString address, quint16 port)
{
    QHostAddress hostAddr(address);
    client.connectToHost(hostAddr, port);

    if(client.waitForConnected(CONNECT_TIME_OUT))
    {
//        QHostAddress hostAddr = client.localAddress();
//        QString addr = "";

//        if(hostAddr != QHostAddress::Null)
//        {
//            addr=hostAddr.toString();
//        }
        return true; //Connected
    }
    else
    {
        return false; //Failed to connect
    }

}

void CClient::stop()
{
    client.close();
}

const char *CClient::qstringToConstChar(QString qtStrData)
{
    qtStrData += "\n";
    QByteArray inBytes;
    const char *cStrData;

    inBytes = qtStrData.toUtf8();
    return cStrData = inBytes.constData();
}


void CClient::startTransfer(const char *sendbuf, int length)
{
    client.write(sendbuf, length);

}

void CClient::startTransfer(const char *sendbuf)
{
    client.write(sendbuf, strlen(sendbuf));
}

void CClient::startTransfer(QString qtStrData)
{
    qtStrData += "\n";
    QByteArray inBytes;
    const char *cStrData;

    inBytes = qtStrData.toUtf8();
    cStrData = inBytes.constData();

    client.write(cStrData, strlen(cStrData));
}

QString CClient::qStringTransfer(const char *sendbuf, int length)
{
    QString buffer;
   client.write(sendbuf, length);

   return sendbuf;
}
