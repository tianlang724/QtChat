#ifndef CSOFTWARECONFIG_H
#define CSOFTWARECONFIG_H
#include <QString>
#include <QFont>
#include <QColor>

class CSoftwareConfig
{
public:
    CSoftwareConfig();

/* 字体设置 */
public:
    QFont editTextFontStyle;
    QColor editTextFontColor;
    QFont viewTextFontStyle;
    QColor viewTextFontColor;
};

#endif // CSOFTWARECONFIG_H
