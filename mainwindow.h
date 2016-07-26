#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "server.h"
#include "csoftwareconfig.h"
#include "cdatabaseoperation.h"

namespace Ui {
class mainwindow;
}
class Server;
class mainwindow : public QWidget
{
    Q_OBJECT

private:
    Ui::mainwindow *ui;
    void setColor(QColor color);

public:
    ~mainwindow();
    explicit mainwindow(QWidget *parent = 0);
    void initWidgets();
    void configWidgets();
    QString username;
    Server *server;

public:
    CSoftwareConfig *widgetconfig;

public slots:
    void updateFontStyle();
    void openColorSetting();
    void updateViewText();
};

#endif // MAINWINDOW_H
