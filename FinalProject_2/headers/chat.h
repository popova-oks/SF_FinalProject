#ifndef CHAT_H
#define CHAT_H

#include <QList>
#include "ISubject.h"
#include "handler_MySQL.h"

class Chat : public ISubject {
  public:
    Chat();
    virtual ~Chat();
    bool addUser(const QString &login, const QString &password) override;
    bool sendMessage(const QString &sender, const QString &receiver, const QString &message) override;
    bool attachUser(const QString &login, const QString &password) override;
    bool detachUser(const QString &login) override;
    bool blockUser(const QString &admin_login, const QString &admin_password, const QString &user) override;
    bool unblockUser(const QString &admin_login, const QString &admin_password, const QString &user) override;
    QStringList attachedUsers();
    QStringList listBlockedUsers();
    QStringList listUnblockedUsers();
    QStringList privateMessages(const QString &receiver);
    QStringList messagesForAll();
private:
    Handler_MySQL* db_mysql_;
};

#endif // CHAT_H
