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

QByteArray CMsgOperation::createChatMsg(QString username, QString fontFamily, int fontPointSize,
                                        QColor color, bool itatic, bool bold, QString textContent)
{
    //设置字体相关
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
    QVariant fontStyleMapVar(fontStyleMap);

    QMap<QString, QVariant> chatContentMap;
    chatContentMap.insert("userName",username);
    chatContentMap.insert("content", textContent);
    chatContentMap.insert("fontStyle", fontStyleMapVar);
    QVariant chatMsgContent(chatContentMap);
    QMap<QString, QVariant> chatMsgMap;
    chatMsgMap.insert("chatMsg", chatMsgContent);
    QJsonDocument chatMsgDocument(QJsonObject::fromVariantMap(chatMsgMap));
    return chatMsgDocument.toJson();
}
QByteArray CMsgOperation::createChatMsg(CSoftwareConfig config)
{
    QMap<QString, QVariant> fontStyleMap;
    QVariant fontFamilyVariant(config.fontConfig.fontFamily);
    QVariant fontPointSizeVariant(config.fontConfig.fontPointSize);
    QVariant itaticVariant(config.fontConfig.itatic);
    QVariant boldVariant(config.fontConfig.bold);
    fontStyleMap.insert("fontFamily", fontFamilyVariant);
    fontStyleMap.insert("fontPointSize", fontPointSizeVariant);
    fontStyleMap.insert("isItatic", itaticVariant);
    fontStyleMap.insert("isBold", boldVariant);
    QMap<QString, QVariant> rbgVariant;
    rbgVariant.insert("r", config.fontConfig.colorR);
    rbgVariant.insert("b", config.fontConfig.colorB);
    rbgVariant.insert("g", config.fontConfig.colorG);
    QVariant colorStyle(rbgVariant);
    fontStyleMap.insert("color", colorStyle);
    QVariant fontStyleMapVar(fontStyleMap);

    QMap<QString, QVariant> chatContentMap;
    chatContentMap.insert("userName",config.chatUsr);
    chatContentMap.insert("content", config.chatMsg);
    chatContentMap.insert("fontStyle", fontStyleMapVar);
    QVariant chatMsgContent(chatContentMap);
    QMap<QString, QVariant> chatMsgMap;
    chatMsgMap.insert("chatMsg", chatMsgContent);
    QJsonDocument chatMsgDocument(QJsonObject::fromVariantMap(chatMsgMap));
    return chatMsgDocument.toJson();
}
