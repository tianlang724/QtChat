#include "server.h"
#include "cmsgoperation.h"

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

    /*
    QByteArray datagram;
    QXmlStreamWriter stream(&datagram);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("LOGIN");
    stream.writeAttribute("username",username);
    stream.writeTextElement("ip",mIP.toString());
    stream.writeEndElement();
    stream.writeEndDocument();
    */
    QByteArray datagram=CMsgOperation::createBroadcast(1, username, mIP.toString());

    udpServerSocket->writeDatagram(datagram.data(),datagram.size(),QHostAddress::Broadcast,UDP_LISTEN_PORT);

}
void
Server::LogoutBrocast(QString username)
{
    QByteArray datagram;
    QXmlStreamWriter stream(&datagram);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("LOGOUT");
    stream.writeAttribute("username",username);
    stream.writeTextElement("ip",mIP.toString());
    stream.writeEndElement();
    stream.writeEndDocument();
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
        ProcessRecvMsg(datagram);
       // qDebug(datagram.data());
    }

}
void
Server::ProcessRecvMsg(QByteArray data)
{

    QJsonObject json=CMsgOperation::getJsonObject(data);
    QStringList keyList = json.keys();
    QStringList::iterator it=keyList.begin();
    if((*it)=="data") {
        //收到一般数据

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
        }
        else if((*it)=="offline"){
            QMap<QString,QHostAddress>::iterator it;
            it= mOnlineUsrMap->find(username);
            if(it!=mOnlineUsrMap->end()){
               mOnlineUsrMap->erase(it);
               //用户下线了，构造信号函数，通知窗口更新用户列表
               }
        }
    }

}

void
Server::SendProcess()
{

}
void
Server::ProcessDataMsg()
{

}
