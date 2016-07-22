#ifndef CMSGOPERATION_H
#define CMSGOPERATION_H
#include <QJsonObject>
#include <QColor>
#include <QMap>
#include <QVariant>

class CMsgOperation
{
public:
    CMsgOperation();
    static QByteArray createBroadcast(int mode, QString username, QString ipAddress);
    static QJsonObject getJsonObject(QByteArray byteArray);
    static QByteArray createChatMsg(bool isBroadcast, QString fontFamily, int fontPointSize,
                                    QColor color, bool itatic, bool bold, QString textContent,
                                    QString ipAddress = NULL, QString port = NULL);
};

#endif // CMSGOPERATION_H
