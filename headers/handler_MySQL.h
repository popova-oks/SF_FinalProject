#ifndef HANDLER_MYSQL_H
#define HANDLER_MYSQL_H

#include <QDebug>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Handler_MySQL {
public:
    Handler_MySQL(){};
    ~Handler_MySQL(){};
    bool createConnection();
    bool createTables();
};

#endif // HANDLER_MYSQL_H
