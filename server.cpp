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
    udpServerSocket=new QUdpSocket();
    udpServerSocket->bind(mIP,UDP_LISTEN_PORT);
    mOnlineUsrMap=new QMap<QString,QHostAddress>();
    //绑定发送按钮
    //connect(Buttom_Send, SIGNAL(clicked()), this, SLOT(SendProcess()));

}
void
Server::LoginBrocast(QString username)
{

    QByteArray datagram;
    QXmlStreamWriter stream(&datagram);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("LOGIN");
    stream.writeAttribute("username",username);
    stream.writeTextElement("ip",mIP.toString());
    stream.writeEndElement();
    stream.writeEndDocument();
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
    }
}
void
Server::ProcessRecvMsg(QByteArray data)
{
    readXml.addData(data);
    while (readXml.readNextStartElement()) {
        if (readXml.name() == "LOGIN"||readXml.name() == "LOGOUT")
            ProcessControlMsg();
        else if (readXml.name() == "DATA")
            ProcessDataMsg();
        else
            readXml.skipCurrentElement();
    }
}
void
Server::ProcessControlMsg()
{
    QString username;
    QString ipString;
    ipString=readXml.readElementText();
    QHostAddress ip=QHostAddress(ipString);
    username=readXml.attributes().value("username").toString();
    if(readXml.name() == "LOGIN")
        {
        mOnlineUsrMap->insert(username,ip);
        //用户上线了
    }
    else if(readXml.name() == "LOGOUT")
        {
        QMap<QString,QHostAddress>::iterator it;
       it= mOnlineUsrMap->find(username);
       if(it!=mOnlineUsrMap->end())
           {
           mOnlineUsrMap->erase(it);
           //用户下线了
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
