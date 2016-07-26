#ifndef CDATABASEOPERATION_H
#define CDATABASEOPERATION_H
#include "csoftwareconfig.h"
#include <QtSql>
#include <QtWidgets>

class CDatabaseOperation
{
public:
    CDatabaseOperation();
    static QSqlError initDb();
    static QSqlError addUser(QSqlQuery &q, const QString &username, const QString &userpwd);
    static bool isUserExistInTables(QSqlQuery &q, const QString &username, const QString &tableName);
    static QSqlError addUserConfig(QSqlQuery &q, const QString &username, const QString &fontFamily, const int fontPointSize, const int fontColorR, const int fontColorB, const int fontColorG, const bool itatic, const bool bold);
    static QString getUserPassword(QSqlQuery &q, const QString &username);
    static QSqlError getWidgetConfig(QSqlQuery &q, QString username, CSoftwareConfig *config);
    static void showError(const QSqlError &err, QWidget *pthis);
};

#endif // CDATABASEOPERATION_H
