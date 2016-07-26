#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGlobal>
#include <QColorDialog>

#define MINIMUM_FONTSIZE 10
#define MAXIMUM_FONTSIZE 40

/* 初始化列表必须按照成员声明顺序，否则会出现错误 */
mainwindow::mainwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainwindow),
    server(new Server),
    widgetconfig(new CSoftwareConfig)
{
    ui->setupUi(this);
    initWidgets();
/*服务器与ui交互信号绑定
 * */
    //绑定发送按钮
    connect(ui->Buttom_Send,SIGNAL(clicked()),server,SLOT(SendProcess()));
    //绑定用户上线，更新在线用户列表
    connect(server,SIGNAL(NewUsrOnline(QString)),this,SLOT(AddOnlineMember(QString)));
    //绑定用户下线，更新在线用户列表
    connect(server,SIGNAL(OldUsrOffline(QString)),this,SLOT(RemoveOnlineMember(QString)));
    //鼠标进去用户列表事件绑定，单击显示用户详细信息
    ui->listWidget_OnMembers->setMouseTracking(true);
    connect(ui->listWidget_OnMembers,SIGNAL(itemEntered(QListWidgetItem*)),
            this,SLOT(ShowMemberDetial(QListWidgetItem*)));
    //用户列表双击事件绑定，双击建立私人聊天
    connect(ui->listWidget_OnMembers,SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this,SLOT(PointToPointChat(QListWidgetItem*)));
}

mainwindow::~mainwindow()
{
    QSqlQuery q;
    int r, g, b;
    widgetconfig->editTextFontColor.getRgb(&r, &g, &b);
    CDatabaseOperation::addUserConfig(q, username, widgetconfig->editTextFontStyle.family(), widgetconfig->editTextFontStyle.pointSize(),
                  r, g, b, widgetconfig->editTextFontStyle.italic(), widgetconfig->editTextFontStyle.bold());
    delete ui;
}

void mainwindow::initWidgets() {
    /* 初始化字号SpinBox */
    ui->SBox_FontSize->setMinimum(MINIMUM_FONTSIZE);
    ui->SBox_FontSize->setMaximum(MAXIMUM_FONTSIZE);

}
void mainwindow::setColor(QColor color) {
    QPalette pl = ui->TextEdit_SendMsg->palette();
    pl.setColor(QPalette::Text, color);
    ui->TextEdit_SendMsg->setPalette(pl);
}

void mainwindow::configWidgets() {
    ui->SBox_FontSize->setValue(widgetconfig->editTextFontStyle.pointSize());
    ui->Comb_Font->setCurrentFont(widgetconfig->editTextFontStyle);
    ui->TextEdit_SendMsg->setFont(widgetconfig->editTextFontStyle);
    if (widgetconfig->editTextFontStyle.italic()) {
        ui->CB_Italic->setCheckState(Qt::Checked);
    }
    if (widgetconfig->editTextFontStyle.bold()) {
        ui->CB_Bold->setCheckState(Qt::Checked);
    }
    setColor(widgetconfig->editTextFontColor);
    connect(ui->SBox_FontSize, SIGNAL(valueChanged(int)), this, SLOT(updateFontStyle()));
    connect(ui->Comb_Font, SIGNAL(currentFontChanged(QFont)), this, SLOT(updateFontStyle()));
    connect(ui->CB_Bold, SIGNAL(stateChanged(int)), this, SLOT(updateFontStyle()));
    connect(ui->CB_Italic, SIGNAL(stateChanged(int)), this, SLOT(updateFontStyle()));
}

/*
 * 功能：更新输入框字体大小和样式
 * */
void mainwindow::updateFontStyle() {
    widgetconfig->editTextFontStyle = ui->Comb_Font->currentFont();
    widgetconfig->editTextFontStyle.setPointSize(ui->SBox_FontSize->value());
    if (ui->CB_Italic->isChecked()) {
        widgetconfig->editTextFontStyle.setItalic(true);
    }
    else {
        widgetconfig->editTextFontStyle.setItalic(false);
    }
    if (ui->CB_Bold->isChecked()) {
        widgetconfig->editTextFontStyle.setBold(true);
    }
    else {
        widgetconfig->editTextFontStyle.setBold(false);
    }
    ui->TextEdit_SendMsg->setFont(widgetconfig->editTextFontStyle);
}

/*
 * 功能：设置输入框字体颜色
 * */
void mainwindow::openColorSetting() {
    widgetconfig->editTextFontColor = QColorDialog::getColor();
    setColor(widgetconfig->editTextFontColor);
}

void mainwindow::updateViewText() {
    QString sendContent = ui->TextEdit_SendMsg->toPlainText();
    if(sendContent == NULL) return;
    ui->TextEdit_RecvMsg->setTextBackgroundColor(Qt::GlobalColor::gray);
    ui->TextEdit_RecvMsg->setFontFamily("WenQuanYi Micro Hei");
    ui->TextEdit_RecvMsg->setFontPointSize(10);
    ui->TextEdit_RecvMsg->setFontItalic(false);
    ui->TextEdit_RecvMsg->setFontWeight(QFont::Thin);
    ui->TextEdit_RecvMsg->setTextColor(Qt::GlobalColor::black);
    QTime currentSendTime = QTime::currentTime();
    ui->TextEdit_RecvMsg->append(currentSendTime.toString());
    ui->TextEdit_RecvMsg->setAlignment(Qt::AlignCenter);
    ui->TextEdit_RecvMsg->setTextBackgroundColor(Qt::GlobalColor::gray);
    ui->TextEdit_RecvMsg->setFontFamily("WenQuanYi Micro Hei");
    ui->TextEdit_RecvMsg->setFontPointSize(10);
    ui->TextEdit_RecvMsg->setFontItalic(false);
    ui->TextEdit_RecvMsg->setFontWeight(QFont::Thin);
    ui->TextEdit_RecvMsg->setTextColor(Qt::GlobalColor::black);
    ui->TextEdit_RecvMsg->append(username + " 说:");
    ui->TextEdit_RecvMsg->setAlignment(Qt::AlignLeft);
    ui->TextEdit_RecvMsg->setTextBackgroundColor(Qt::GlobalColor::transparent);
    ui->TextEdit_RecvMsg->setFontFamily(widgetconfig->editTextFontStyle.family());
    ui->TextEdit_RecvMsg->setFontPointSize(widgetconfig->editTextFontStyle.pointSize());
    ui->TextEdit_RecvMsg->setFontItalic(widgetconfig->editTextFontStyle.italic());
    ui->TextEdit_RecvMsg->setFontWeight(widgetconfig->editTextFontStyle.bold() == 1 ? QFont::Bold: QFont::Thin);
    ui->TextEdit_RecvMsg->setTextColor(widgetconfig->editTextFontColor);
    ui->TextEdit_RecvMsg->append(sendContent);
    ui->TextEdit_RecvMsg->setAlignment(Qt::AlignLeft);
}
/*
 * 新用户上线更新
 * */
void mainwindow:: AddOnlineMember(QString username)
{
    QListWidgetItem *newItem = new QListWidgetItem;
    newItem->setText(username);
    ui->listWidget_OnMembers->insertItem(0,newItem);
}
/*
 * 用户下线更新
 * */
void mainwindow::RemoveOnlineMember(QString username)
{
    QList<QListWidgetItem*> qlistItems=ui->listWidget_OnMembers->findItems(username,0);
    QList<QListWidgetItem*>::iterator it=qlistItems.begin();
    if(it!=qlistItems.end()){
        ui->listWidget_OnMembers->removeItemWidget(*it);
        it++;
        }
}
/*
 * 显示用户详细信息
 * */
void mainwindow::ShowMemberDetial(QListWidgetItem *item)
{
   qDebug("show user detail");
   QString usrname=item->text();
   QString ip=server->mOnlineUsrMap->find(usrname).value().toString();
   QToolTip::showText(cursor().pos(),"username: "+usrname+"\n"+"IP："+ip);

}
/* 建立私聊窗口
 * */
void mainwindow::PointToPointChat(QListWidgetItem *item)
{

}
/*
 * 关闭主窗口的时候进行提示，并发送广播退出消息
 * */
void mainwindow::closeEvent(QCloseEvent *event)
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle("提示");
    msgBox.setInformativeText("确定关闭所有聊天窗口吗?");
    QAbstractButton *discardButton =msgBox.addButton(tr("取消"), QMessageBox::ActionRole);
    QAbstractButton *okButton =msgBox.addButton(tr("确定"), QMessageBox::ActionRole);
    msgBox.exec();
    if(msgBox.clickedButton()==okButton){
        server->LogoutBrocast(username);
        event->accept();
    }
    else if(msgBox.clickedButton()==discardButton)
        event->ignore();

}
