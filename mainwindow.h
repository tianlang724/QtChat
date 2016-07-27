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

    void configWidgets();
    QString username;
    Server *server;
    CSoftwareConfig *sendMsgConfig;
    CSoftwareConfig *recvWidgetConfig;



public slots:
    void updateFontStyle();
    void openColorSetting();

    void AddOnlineMember(QString username);
    void RemoveOnlineMember(QString username);
    void ShowMemberDetial(QListWidgetItem *item);
    void PointToPointChat(QListWidgetItem *item);
    void updateViewText();
    void GetSendInformationSlot();
signals:
    void SendInformationOKSignal(CSoftwareConfig config);

protected:
     void closeEvent(QCloseEvent *event) override;




};

#endif // MAINWINDOW_H
