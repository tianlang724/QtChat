#include "login.h"
#include "dboperation.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    QSqlError err = initDb();
    if (err.type() != QSqlError::NoError) {
        QMessageBox::critical(this, "初始化数据库出错", err.text());
    }
    /* 数据库的初始化 */
}

Login::~Login()
{
    delete ui;
}

void Login::clicksignin()
{
    QString username = ui->user->text();
    QString userpwd = ui->password->text();
    mw->username=username;
    QSqlQuery q;
    QString db_password = getUserPassword(q, username);
    if (db_password != NULL) {
         if (userpwd == db_password) {
             mw->show();
             //登录成功，发送广播信息
             mw->server->LoginBrocast(username);
             close();
             return;
         }
         QMessageBox::information(this, "提示", "用户名密码错误");
         return;
    }
    QMessageBox::information(this, "提示", "用户名不存在");
    return;
}

void Login::clicksignup()
{
   QString username = ui->user->text();
   QString userpwd = ui->password->text();
   QSqlQuery q;
   if (!q.exec("select * from userinfo")) {
       QMessageBox::critical(this, "读取数据库出错", q.lastError().text());
       return;
   }
   while (q.next()) {
       QString db_username = q.value(0).toString();
       if (db_username == username) {
            QMessageBox::information(this, "提示", "用户名" + username + "已存在，无须注册！");
            return;
       }
   }
   QSqlError err = addUser(q, username, userpwd);
   if (err.type() != QSqlError::NoError) {
       QMessageBox::critical(this, "无法添加新用户", err.text());
       return;
   }
   QMessageBox::information(this, "提示", "新用户" + username + "已成功添加");
}
