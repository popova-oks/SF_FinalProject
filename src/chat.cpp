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
}

Chat::~Chat() {
    if (db_mysql_) {
         delete db_mysql_;
        db_mysql_ = nullptr;
    }
}
bool Chat::addUser(const std::string &login, const std::string &password)
{
    return true;
}

bool Chat::addMessage(const std::string &sender, const std::string &receiver, const std::string &message)
{
    return true;
}


