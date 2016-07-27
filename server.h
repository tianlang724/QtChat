#ifndef SERVER_H
#define SERVER_H

#include "cudpbase.h"
#define UDP_LISTEN_PORT 6666
class CUdpBase;
class list;
class Server:public CUdpBase
{
    Q_OBJECT
public:
    Server();
    //广播上线消息
    void LoginBrocast(QString username);
    //广播下线消息
    void LogoutBrocast(QString username);

    //当前在线的用户列表
    QMap<QString,QHostAddress> *mOnlineUsrMap;
   //处理收到的聊天消息
    void ProcessRecvMsg(QByteArray data) override;
signals:
   void NewUsrOnline(QString username);
   void OldUsrOffline(QString username);

};

#endif // SERVER_H
