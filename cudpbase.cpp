#include "cudpbase.h"
/*
CUdpBase::CUdpBase()
{

}

CUdpBase::~CUdpBase()
{

}
*/
void CUdpBase::SendProcess()
{
    qDebug("发送按钮点击");
    QByteArray datagram=CMsgOperation::createChatMsg("zh","song",10,QColor(122,12,12),0,0,"nihao");
    udpSocket->writeDatagram(datagram.data(),datagram.size(),remoteIP,remoteUpdPort);
}
void CUdpBase::ReadPendingData()
{
    while (udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
        //qDebug(datagram.data());
        ProcessRecvMsg(datagram);

    }
}
void CUdpBase::ProcessDataMsg(QJsonObject json)
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
/*
void CUdpBase::ProcessRecvMsg(QByteArray data)
{

} */
