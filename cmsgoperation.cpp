#include "cmsgoperation.h"
#include <QJsonDocument>

CMsgOperation::CMsgOperation()
{

}

QByteArray CMsgOperation::createBroadcast(int mode, QString username, QString ipAddress)
{
    QMap<QString, QVariant> broadcastContentMap;
    QVariant usernameVariant(username);
    QVariant ipAddressVariant(ipAddress);
    broadcastContentMap.insert("userName", usernameVariant);
    broadcastContentMap.insert("ipAddress", ipAddressVariant);
    QVariant broadcastContent(broadcastContentMap);
    QMap<QString, QVariant> broadcastMap;
    broadcastMap.insert(mode == 1 ? "online" : "offline", broadcastContent);
    QJsonDocument broadcastJsonDocument(QJsonObject::fromVariantMap(broadcastMap));
    return broadcastJsonDocument.toJson();
}

QJsonObject CMsgOperation::getJsonObject(QByteArray byteArray)
{
    QJsonDocument broadcastDocument = QJsonDocument::fromJson(byteArray);
    return broadcastDocument.object();
}

QByteArray CMsgOperation::createChatMsg(bool isBroadcast, QString fontFamily, int fontPointSize,
                                        QColor color, bool itatic, bool bold, QString textContent,
                                        QString ipAddress,QString port)
{
    QMap<QString, QVariant> fontStyleMap;
    QVariant fontFamilyVariant(fontFamily);
    QVariant fontPointSizeVariant(fontPointSize);
    QVariant itaticVariant(itatic);
    QVariant boldVariant(bold);
    fontStyleMap.insert("fontFamily", fontFamilyVariant);
    fontStyleMap.insert("fontPointSize", fontPointSizeVariant);
    fontStyleMap.insert("isItatic", itaticVariant);
    fontStyleMap.insert("isBold", boldVariant);
    QMap<QString, QVariant> rbgVariant;
    int r,b,g;
    color.getRgb(&r, &b, &g);
    rbgVariant.insert("r", r);
    rbgVariant.insert("b", b);
    rbgVariant.insert("g", g);
    QVariant colorStyle(rbgVariant);
    fontStyleMap.insert("color", colorStyle);
    QVariant fontStyle(fontStyleMap);
    QMap<QString, QVariant> chatContentMap;
    chatContentMap.insert("content", textContent);
    chatContentMap.insert("fontStyle", fontStyle);
    if (!isBroadcast) {
        QVariant ipAddressVariant(ipAddress);
        QVariant portVariant(port);
        QMap<QString, QVariant> networkInfoMap;
        networkInfoMap.insert("fromIP", ipAddress);
        networkInfoMap.insert("fromPort", port);
        chatContentMap.insert("networkInfo", QVariant(networkInfoMap));
    }
    QVariant chatMsgContent(chatContentMap);
    QMap<QString, QVariant> chatMsgMap;
    chatMsgMap.insert("chatMsg", chatMsgContent);
    QJsonDocument chatMsgDocument(QJsonObject::fromVariantMap(chatMsgMap));
    return chatMsgDocument.toBinaryData();
}
