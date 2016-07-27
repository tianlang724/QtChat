#include "cudpbase.h"
void CUdpBase::SendProcess(CSoftwareConfig config)
{
    qDebug("发送信息");
    QByteArray datagram=CMsgOperation::createChatMsg(config);
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
    CSoftwareConfig config;
    config.recvUsr=json.value("userName").toString();
    config.recvMsg=json.value("content").toString();
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
    QFont font=QFont(fontFamily,fontPointSize,-1,isItatic);
    font.setBold(isBold);

    config.viewTextFontStyle=font;
    config.viewTextFontColor=color;
    emit InformUIRecvMsg(config);

}

