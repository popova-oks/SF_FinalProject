#include "../headers/chat.h"
#include <iostream>
#include <QDebug>

Chat::Chat()
    : db_mysql_ {nullptr}
{
    db_mysql_ = new Handler_MySQL();
}

Chat::~Chat() {
    if (db_mysql_) {
        delete db_mysql_;
        db_mysql_ = nullptr;
    }
}
bool Chat::addUser(const QString &login, const QString &password)
{
    if (!db_mysql_->add_user(login, password)) {
        qDebug() << "Failed to add the user";
        return false;
    }
    return true;
}

bool Chat::sendMessage(const QString &sender, const QString &receiver, const QString &message)
{
    return true;
}

bool Chat::attachUser(const QString &login, const QString &password)
{
    if (!db_mysql_->attach_user(login, password)) {
        qDebug() << "Failed to attach the user";
        return false;
    }
    return true;
}

bool Chat::detachUser(const QString &login)
{
    if (!db_mysql_->detach_user(login)) {
        qDebug() << "Failed to detach the user";
        return false;
    }
    return true;
}

bool Chat::blockUser(const QString &admin_login, const QString &admin_password, const QString &user)
{
    if (!db_mysql_->block_user(admin_login, admin_password, user)) {
        qDebug() << "Failed to block the user";
        return false;
    }
    return true;
}

bool Chat::unblockUser(const QString &admin_login, const QString &admin_password, const QString &user)
{
    if (!db_mysql_->unblock_user(admin_login, admin_password, user)) {
        qDebug() << "Failed to unblock the user";
        return false;
    }
    return true;
}

QStringList Chat::attachedUsers()
{
    return db_mysql_->createListUsers();
}

QStringList Chat::listBlockedUsers()
{
    return db_mysql_->createListBlockUsers();
}
QStringList Chat::listUnblockedUsers()
{
    return db_mysql_->createListUnblockUsers();
}



