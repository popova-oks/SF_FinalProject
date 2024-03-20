#ifndef ISUBJECT_H
#define ISUBJECT_H
#include <iostream>
#include <QString>

class ISubject {
  public:
    virtual ~ISubject(){};
    virtual bool addUser(const QString &login, const QString &password) = 0;
    virtual bool sendMessage(const QString &sender, const QString &receiver, const QString &message) = 0;
    virtual bool attachUser(const QString &login, const QString &password) = 0;
    virtual bool detachUser(const QString &login) = 0;
    virtual bool blockUser(const QString &admin_login, const QString &admin_password, const QString &user) = 0;
    virtual bool unblockUser(const QString &admin_login, const QString &admin_password, const QString &user) = 0;
};

#endif // ISUBJECT_H
