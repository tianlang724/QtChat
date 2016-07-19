#ifndef DBOPERATION_H
#define DBOPERATION_H
#include <QtSql>
#include <QtWidgets>

/*
 * 功能：初始化一个数据库
 * */
QSqlError initDb() {
    QSqlDatabase db;
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::database("qt_sql_default_connection");
    }
    else {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("account.db");
        if (!db.open()) {
            return db.lastError();
        }
        QStringList tables = db.tables();
        QSqlQuery q;
        if (!tables.contains("userinfo")) {
            if (!q.exec(QLatin1String("create table userinfo(username varchar primary key, userpwd varchar)"))) {
                return q.lastError();
            }
        }
    }
    return QSqlError();
}

/*
 * 功能：向数据库添加一个用户信息
 * 参数：
 * q 为QSqlQuery对象
 * */
QSqlError addUser(QSqlQuery &q, const QString &username, const QString &userpwd) {
    if (!q.prepare(QLatin1String("insert into userinfo(username, userpwd) values(?,?)"))) {
        return q.lastError();
    }
    q.addBindValue(username);
    q.addBindValue(userpwd);
    q.exec();
    return QSqlError();
}

/*
 * 功能：从数据库中取得一个用户的密码信息
 * 参数：
 * q 为QSqlQuery对象
 * */
QString getUserPassword(QSqlQuery &q, const QString &username) {
    if (!q.exec(QLatin1String("select * from userinfo"))) {
        return NULL;
    }
    while (q.next()) {
        QString db_username = q.value(0).toString();
        if (db_username == username) {
            return q.value(1).toString();
        }
    }
    return NULL;
}

void showError(const QSqlError &err, QWidget *pthis) {
    QMessageBox::critical(pthis, "Unable to initialize Database",
                "Error initializing database: " + err.text());
}

#endif // DBOPERATION_H
