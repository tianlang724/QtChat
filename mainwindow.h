#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QListWidgetItem>
#include <QListWidget>
#include <QMessageBox>
#include <QToolTip>
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
    void CreateLabel();

    // 服务器
    QString username;
    Server *server;


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

};

#endif // MAINWINDOW_H
