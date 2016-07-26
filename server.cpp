#include "server.h"


Server::Server()
{
    //获取本机ip地址
    QList<QHostAddress> vAddressList = QNetworkInterface::allAddresses();
    for(int i=0;i<vAddressList.size();i++)
    {
        if((vAddressList.at(i)!=QHostAddress::LocalHost)&&(vAddressList.at(i).protocol()==QAbstractSocket::IPv4Protocol))
        {
            mIP=vAddressList.at(i);
            break;
        }
    }

    //初始化套接字和在线用户
    udpServerSocket=new QUdpSocket(this);
    udpServerSocket->bind(UDP_LISTEN_PORT, QUdpSocket::ShareAddress);
    mOnlineUsrMap=new QMap<QString,QHostAddress>();
    //绑定发送按钮
    //connect(Buttom_Send, SIGNAL(clicked()), this, SLOT(SendProcess()));
    //绑定接受函数
    connect(udpServerSocket, SIGNAL(readyRead()),this, SLOT(ReadPendingData()));
}
void
Server::LoginBrocast(QString username)
{
    QByteArray datagram=CMsgOperation::createBroadcast(1, username, mIP.toString());
    udpServerSocket->writeDatagram(datagram.data(),datagram.size(),QHostAddress::Broadcast,UDP_LISTEN_PORT);
}
void
Server::LogoutBrocast(QString username)
{
    QByteArray datagram=CMsgOperation::createBroadcast(0, username, mIP.toString());
    udpServerSocket->writeDatagram(datagram.data(),datagram.size(),QHostAddress::Broadcast,UDP_LISTEN_PORT);
}
void
Server::ReadPendingData()
{

    while (udpServerSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpServerSocket->pendingDatagramSize());
        udpServerSocket->readDatagram(datagram.data(), datagram.size());
        //qDebug(datagram.data());
        ProcessRecvMsg(datagram);

    }

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
        if((*it)=="online"){
            mOnlineUsrMap->insert(username,ip);
            //构造信号函数，通知窗口更新用户列表
            emit NewUsrOnline(username);
        }
        else if((*it)=="offline"){
            QMap<QString,QHostAddress>::iterator it;
            it= mOnlineUsrMap->find(username);
            if(it!=mOnlineUsrMap->end()){
                mOnlineUsrMap->erase(it);
                //用户下线了，构造信号函数，通知窗口更新用户列表
                emit OldUsrOffline(username);
            }
        }
    }

}

void
Server::SendProcess()
{
    //qDebug("send conenct");
    QByteArray datagram=CMsgOperation::createChatMsg("zh","song",10,QColor(122,12,12),0,0,"nihao");
    udpServerSocket->writeDatagram(datagram.data(),datagram.size(),QHostAddress::Broadcast,UDP_LISTEN_PORT);

}
void
Server::ProcessDataMsg(QJsonObject json)
{
    QString usrName=json.value("userName").toString();
    QString context=json.value("content").toString();
    QJsonObject fontFamilyJson=json.value("fontStyle").toObject();
    QString fontFamily=fontFamilyJson.value("fontFamily").toString();
    int fontPointSize=fontFamilyJson.value("fontPointSize").toInt();
    bool isItatic=fontFamilyJson.value("isItatic").toBool();
    bool isBold=fontFamilyJson.value("isBold").toBool();
    QJsonObject colorJson=fontFamilyJson.value("color").toObject();
    int r,b,g;
    r=colorJson.value("r").toInt();
    b=colorJson.value("b").toInt();
    g=colorJson.value("g").toInt();
    QColor color(r,b,g);
}
