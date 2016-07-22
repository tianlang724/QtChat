#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "server.h"

namespace Ui {
class mainwindow;
}
class Server;
class mainwindow : public QWidget
{
    Q_OBJECT

public:
    ~mainwindow();
    explicit mainwindow(QWidget *parent = 0);
    void initWidgets();
    QString username;
    Server *server;

public slots:
    void updateFontStyle();
    void openColorSetting();

private:
    Ui::mainwindow *ui;



};

#endif // MAINWINDOW_H
