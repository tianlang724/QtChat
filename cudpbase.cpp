#include "cudpbase.h"
void CUdpBase::SendProcess(CSoftwareConfig config)
{
    qDebug("服务器发送信息");
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
        ProcessRecvMsg(datagram);

    }
}
void CUdpBase::ProcessDataMsg(QJsonObject json)
{
    CSoftwareConfig config;
    config.chatUsr=json.value("userName").toString();
    config.chatMsg=json.value("content").toString();
    QJsonObject fontFamilyJson=json.value("fontStyle").toObject();
    config.fontConfig.fontFamily=fontFamilyJson.value("fontFamily").toString();
    config.fontConfig.fontPointSize=fontFamilyJson.value("fontPointSize").toInt();
    config.fontConfig.itatic=fontFamilyJson.value("isItatic").toBool();
    config.fontConfig.bold=fontFamilyJson.value("isBold").toBool();
    QJsonObject colorJson=fontFamilyJson.value("color").toObject();
    config.fontConfig.colorR=colorJson.value("r").toInt();
    config.fontConfig.colorB=colorJson.value("b").toInt();
    config.fontConfig.colorG=colorJson.value("g").toInt();
    emit InformUIRecvMsg(config);
}

