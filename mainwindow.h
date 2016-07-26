#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QListWidgetItem>
#include <QListWidget>
#include <QMessageBox>
#include <QToolTip>
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

    void CreateLabel();

    // 服务器
    QString username;
    Server *server;

    void configWidgets();
    QString username;
    Server *server;

public:
    CSoftwareConfig *widgetconfig;


public slots:
    void updateFontStyle();
    void openColorSetting();

    void AddOnlineMember(QString username);
    void RemoveOnlineMember(QString username);
    void ShowMemberDetial(QListWidgetItem *item);
    void PointToPointChat(QListWidgetItem *item);

private:
    Ui::mainwindow *ui;

protected:
     void closeEvent(QCloseEvent *event) override;


    void updateViewText();

};

#endif // MAINWINDOW_H
