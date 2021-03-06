#ifndef CMSGOPERATION_H
#define CMSGOPERATION_H
#include <QJsonObject>
#include <QColor>
#include <QMap>
#include <QVariant>
#include "csoftwareconfig.h"

class CMsgOperation
{
public:
    CMsgOperation();
    static QByteArray createBroadcast(int mode, QString username, QString ipAddress);
    static QJsonObject getJsonObject(QByteArray byteArray);
    static QByteArray createChatMsg(QString username, QString fontFamily, int fontPointSize,
                                    QColor color, bool itatic, bool bold, QString textContent);
    static QByteArray createChatMsg(CSoftwareConfig config);
};

#endif // CMSGOPERATION_H
