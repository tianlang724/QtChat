#include "cdatabaseoperation.h"

CDatabaseOperation::CDatabaseOperation()
{

}

/*
 * 功能：初始化一个数据库
 * */
QSqlError CDatabaseOperation::initDb() {
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
        if (!tables.contains("userconfig")) {
            if (!q.exec(QLatin1String("create table userconfig(username varchar primary key, fontfamily varchar, "
                                      "fontpointsize int, fontcolorr int, fontcolorg int, fontcolorb int, itatic int, bold int)"))) {
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
QSqlError CDatabaseOperation::addUser(QSqlQuery &q, const QString &username, const QString &userpwd) {
    if (!q.prepare(QLatin1String("insert into userinfo(username, userpwd) values(?,?)"))) {
        return q.lastError();
    }
    q.addBindValue(username);
    q.addBindValue(userpwd);
    q.exec();
    return QSqlError();
}

/*
 * 功能：查看某个已有表项是否含有已有用户用户名
 * 参数：
 * q 为QSqlQuery对象
 * */
bool CDatabaseOperation::isUserExistInTables(QSqlQuery &q, const QString &username, const QString &tableName) {
    if (!q.exec("select * from " + tableName + " where username glob \'" + username + "\'")) {
        return false;
    }
    if (q.next()) {
        return true;
    }
    return false;
}

/*
 * 功能：为已知用户添加一个用户配置
 * 参数：
 * q 为QSqlQuery对象
 * */
QSqlError CDatabaseOperation::addUserConfig(QSqlQuery &q, const QString &username, const QString &fontFamily, const int fontPointSize, const int fontColorR, const int fontColorG, const int fontColorB, const bool itatic, const bool bold) {
    if (isUserExistInTables(q, username, "userconfig")) {
        if (!q.exec("delete from userconfig where username glob \'" + username + "\'")) {
            return q.lastError();
        }
    }
    if (!q.prepare(QLatin1String("insert into userconfig(username, fontfamily, fontpointsize, fontcolorr, fontcolorg, fontcolorb, itatic, bold) values(?,?,?,?,?,?,?,?)"))) {
        return q.lastError();
    }
    q.addBindValue(username);
    q.addBindValue(fontFamily);
    q.addBindValue(fontPointSize);
    q.addBindValue(fontColorR);
    q.addBindValue(fontColorG);
    q.addBindValue(fontColorB);
    q.addBindValue(itatic == true ? 1 : 0);
    q.addBindValue(bold == true ? 1 : 0);
    q.exec();
    return QSqlError();
}

/*
 * 功能：从数据库中取得一个用户的密码信息
 * 参数：
 * q 为QSqlQuery对象
 * */
QString CDatabaseOperation::getUserPassword(QSqlQuery &q, const QString &username) {
    if (!q.exec("select * from userinfo where username glob \'" + username + "\'")) {
        return NULL;
    }
    if (q.next()) {
        return q.value(1).toString();
    }
    return NULL;
}

QSqlError CDatabaseOperation::getWidgetConfig(QSqlQuery &q, QString username, CSoftwareConfig *config) {
    if (!q.exec("select * from userconfig where username glob \'" + username + "\'")) {
        return QSqlError();
    }
    if(q.next()) {
        config->chatUsr = username;
        config->fontConfig.fontFamily = q.value(1).toString();
        config->fontConfig.fontPointSize = q.value(2).toInt();
        config->fontConfig.colorR = q.value(3).toInt();
        config->fontConfig.colorG = q.value(4).toInt();
        config->fontConfig.colorB = q.value(5).toInt();
        config->fontConfig.itatic = q.value(6).toInt() == 1 ? true : false;
        config->fontConfig.bold = q.value(7).toInt() == 1 ? true : false;
    }
    return QSqlError();
}

void CDatabaseOperation::showError(const QSqlError &err, QWidget *pthis) {
    QMessageBox::critical(pthis, "Unable to initialize Database",
                          "Error initializing database: " + err.text());
}
