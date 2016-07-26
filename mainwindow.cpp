#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>

#define MINIMUM_FONTSIZE 10
#define MAXIMUM_FONTSIZE 40

mainwindow::mainwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainwindow),
    server(new Server)
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
    delete ui;
}

void mainwindow::initWidgets() {
    /* 初始化字号SpinBox */
    ui->SBox_FontSize->setMinimum(MINIMUM_FONTSIZE);
    ui->SBox_FontSize->setMaximum(MAXIMUM_FONTSIZE);
}
/*
 * 功能：更新输入框字体大小和样式
 * */
void mainwindow::updateFontStyle() {
    QFont currentFontStyle = ui->Comb_Font->currentFont();
    currentFontStyle.setPointSize(ui->SBox_FontSize->value());
    if (ui->CB_Italic->isChecked()) {
        currentFontStyle.setItalic(true);
    }
    if (ui->CB_Bold->isChecked()) {
        currentFontStyle.setBold(true);
    }
    ui->TextEdit_SendMsg->setFont(currentFontStyle);
}

/*
 * 功能：设置输入框字体颜色
 * */
void mainwindow::openColorSetting() {
    const QColor fontColor = QColorDialog::getColor();
    QPalette pl = ui->TextEdit_SendMsg->palette();
    pl.setColor(QPalette::Text, fontColor);
    ui->TextEdit_SendMsg->setPalette(pl);
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
void mainwindow::PointToPointChat(QListWidgetItem *item)
{

}
