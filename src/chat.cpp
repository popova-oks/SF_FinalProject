#include "../headers/chat.h"
#include <iostream>
#include <QDebug>

Chat::Chat()
    : messages_ {nullptr}
    , db_mysql_ {nullptr}
{
    db_mysql_ = new Handler_MySQL();
    if (!db_mysql_->createConnection()) {
        qDebug() << "Failed to create database";
    }
    if (!db_mysql_->createTables()) {
        qDebug() << "Failed to create tables";
    }
    // добавляем админа
    if (!add_admin()){
        qDebug() << "Failed to add an admin";
    }
}

Chat::~Chat() {
    if (db_mysql_) {
        delete db_mysql_;
        db_mysql_ = nullptr;
    }
}
bool Chat::addUser(const std::string &login, const std::string &password)
{
    if (!db_mysql_->add_User(login.c_str(), password.c_str())) {
        qDebug() << "Failed to add the user";
        return false;
    }
    return true;
}

bool Chat::sendMessage(const std::string &sender, const std::string &receiver, const std::string &message)
{
    return true;
}

bool Chat::attachUser(const std::string &login, const std::string &password)
{
    if (!db_mysql_->attach_User(login.c_str(), password.c_str())) {
        qDebug() << "Failed to attach the user";
        return false;
    }
    return true;
}

bool Chat::add_admin()
{
    if (!db_mysql_->add_User("admin", "da39a3ee5e6b4b0d3255bfef95601890afd80709")) {
        return false;
    }
    return true;
}


