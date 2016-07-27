#ifndef CSOFTWARECONFIG_H
#define CSOFTWARECONFIG_H
#include <QString>
#include <QFont>
#include <QColor>

class CSoftwareConfig
{
public:
    CSoftwareConfig();
    //CSoftwareConfig(QFont,QColor);

/* 字体设置 */
public:
    QString chatMsg;
    QString chatUsr;
    QString fontFamily;
    int fontPointSize;
    bool itatic;
    bool bold;
    int r;
    int b;
    int g;
};

#endif // CSOFTWARECONFIG_H
