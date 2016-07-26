#ifndef CUDPBASE_H
#define CUDPBASE_H
#include <QtNetwork>
#include <QObject>
#include "cmsgoperation.h"
class QUdpSocket;
class CUdpBase:public QObject
{
    Q_OBJECT
public:
   // CUdpBase();
    //~CUdpBase();
    QUdpSocket *udpSocket;
    QHostAddress myIP;
    quint16 myUpdPort;
    QHostAddress remoteIP;
    quint16 remoteUpdPort;

    //处理收到的聊天消息
    void ProcessDataMsg(QJsonObject json);
    virtual void ProcessRecvMsg(QByteArray data)=0;
public slots:
    //点击发送按钮触发的事件，并处理需要发送的消息
    void SendProcess();
    //读取收到的数据
    void ReadPendingData();
};

#endif // CUDPBASE_H
