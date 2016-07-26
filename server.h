#ifndef SERVER_H
#define SERVER_H
#include <QtNetwork>
#include "cmsgoperation.h"
#define UDP_LISTEN_PORT 6666
class QUdpSocket;
class list;
class Server:public QObject
{
	Q_OBJECT
public:
    Server();
    //广播上线消息
    void LoginBrocast(QString username);
    //广播下线消息
    void LogoutBrocast(QString username);
   //处理收到的聊天消息
    void ProcessDataMsg(QJsonObject json);
    void ProcessRecvMsg(QByteArray data);

    //当前在线的用户列表
    QMap<QString,QHostAddress> *mOnlineUsrMap;
public slots:
    //点击发送按钮触发的事件，并处理需要发送的消息
    void SendProcess();
    //读取收到的数据
    void ReadPendingData();
signals:
    void NewUsrOnline(QString username);
    void OldUsrOffline(QString username);

 

private:
    //服务器的套接字
    QUdpSocket *udpServerSocket;
    //本机ip地址
    QHostAddress mIP;
};

#endif // SERVER_H
