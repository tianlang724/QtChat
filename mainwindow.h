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
    explicit mainwindow(QWidget *parent = 0);
    ~mainwindow();

private:
    Ui::mainwindow *ui;
    Server *server;

};

#endif // MAINWINDOW_H
