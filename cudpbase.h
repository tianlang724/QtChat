#ifndef CUDPBASE_H
#define CUDPBASE_H
#include <QtNetwork>
#include <QObject>
#include "cmsgoperation.h"
#include "csoftwareconfig.h"
class QUdpSocket;
class CUdpBase:public QObject
{
    Q_OBJECT
public:
    QUdpSocket *udpSocket;
    QHostAddress myIP;
    quint16 myUpdPort;
    QHostAddress remoteIP;
    quint16 remoteUpdPort;
    QString myName;
    //处理收到的聊天消息
    void ProcessDataMsg(QJsonObject json);
    virtual void ProcessRecvMsg(QByteArray data)=0;
public slots:
    //点击发送按钮触发的事件，并处理需要发送的消息
    void SendProcess(CSoftwareConfig config);
    //读取收到的数据
    void ReadPendingData();
signals:
    void InformUIRecvMsg(CSoftwareConfig config);
};

#endif // CUDPBASE_H
