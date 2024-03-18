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

    bool add_User(const QString login, const QString password);
    bool attach_User(const QString login, const QString password);
    bool detach_User(const QString login, const QString password);  // соеденить с соответсвующем меню
    bool add_message(const QString sender, const QString receiver, const QString message);
private:
    bool block_user(const QString login, const QString password);   // только для админа

    bool check_user(const QString login, const QString password);
    bool is_block(const QString login);
    bool is_user(const QString login);
};

#endif // HANDLER_MYSQL_H
