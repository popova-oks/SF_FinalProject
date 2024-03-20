#ifndef HANDLER_MYSQL_H
#define HANDLER_MYSQL_H

#include <QDebug>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Handler_MySQL {
public:
    Handler_MySQL();
    ~Handler_MySQL(){};
    bool createConnection();
    bool createTables();
    QStringList createListUsers();
    QStringList createListBlockUsers();
    QStringList createListUnblockUsers();
    QStringList createListPrivateMessages(const QString &receiver);
    QStringList createListMessagesForAll();

    bool add_user(const QString &login, const QString &password);
    bool attach_user(const QString &login, const QString &password);
    bool detach_user(const QString &login);
    bool add_message(const QString &sender, const QString &receiver, const QString &message);
    bool block_user(const QString &adm_login, const QString &adm_password, const QString &user);
    bool unblock_user(const QString &adm_login, const QString &adm_password, const QString &user);
private:    
    bool check_user(const QString &login, const QString &password);
    bool is_block(const QString &login);
    bool is_user(const QString &login);
};

#endif // HANDLER_MYSQL_H
