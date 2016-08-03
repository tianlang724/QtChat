#include "server.h"

#define UDP_LISTEN_PORT 6666


Server::Server()
{
    //获取本机ip地址
    QList<QHostAddress> vAddressList = QNetworkInterface::allAddresses();
    for(int i=0;i<vAddressList.size();i++)
    {
        if((vAddressList.at(i)!=QHostAddress::LocalHost)&&(vAddressList.at(i).protocol()==QAbstractSocket::IPv4Protocol))
        {
            myIP=vAddressList.at(i);
            break;
        }
    }
    remoteIP=QHostAddress::Broadcast;
    myUpdPort=UDP_LISTEN_PORT;
    remoteUpdPort=UDP_LISTEN_PORT;

    //初始化套接字和在线用户
    udpSocket=new QUdpSocket(this);
    udpSocket->bind(myUpdPort, QUdpSocket::ShareAddress);
    mOnlineUsrMap=new QMap<QString,QHostAddress>();
    //绑定接受函数
    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(ReadPendingData()));
}
void
Server::LoginBrocast(QString username)
{

    qDebug("广播上线消息");
    myName=username;
    mOnlineUsrMap->insert(username,myIP);
    emit NewUsrOnline(username);
    QByteArray datagram=CMsgOperation::createBroadcast(1, username, myIP.toString());
    udpSocket->writeDatagram(datagram.data(),datagram.size(),remoteIP,remoteUpdPort);

}
void
Server::LogoutBrocast(QString username)
{
    qDebug("广播下线消息");
    QByteArray datagram=CMsgOperation::createBroadcast(0, username, myIP.toString());
    int ret=udpSocket->writeDatagram(datagram.data(),datagram.size(),remoteIP,remoteUpdPort);
}

void
Server::ProcessRecvMsg(QByteArray data)
{
    QJsonObject json=CMsgOperation::getJsonObject(data);
    QStringList keyList = json.keys();
    QStringList::iterator it=keyList.begin();
    if((*it)=="chatMsg"){
        //收到一般数据
        QJsonObject dataJson=json.value(*it).toObject();
        ProcessDataMsg(dataJson);
    }
    else if((*it)=="online"||(*it)=="offline") {
        QString username=NULL;
        QString ipString=NULL;
        QJsonObject attr=json.value(*it).toObject();
        username=attr.value("userName").toString();
        ipString=attr.value("ipAddress").toString();
        QHostAddress ip=QHostAddress(ipString);
        QMap<QString,QHostAddress>::iterator itfind;
        itfind=mOnlineUsrMap->find(username);
        if((*it)=="online"){
            if(itfind==mOnlineUsrMap->end())
            {
                mOnlineUsrMap->insert(username,ip);
                //构造信号函数，通知窗口更新用户列表
                emit NewUsrOnline(username);
            }
            if(username!=myName)
            {
                QByteArray datagram=CMsgOperation::createBroadcast(1, myName, myIP.toString());
                qint64 ret=udpSocket->writeDatagram(datagram.data(),datagram.size(),QHostAddress(ipString),remoteUpdPort);
                if(ret==0)
                    qDebug("回复广播消息失败");
            }
        }
        else if((*it)=="offline"){
            if(itfind!=mOnlineUsrMap->end()){
                mOnlineUsrMap->erase(itfind);
                //用户下线了，构造信号函数，通知窗口更新用户列表
                emit OldUsrOffline(username);
            }
        }
    }

}


