#ifndef CHAT_H
#define CHAT_H

#include "ISubject.h"
#include "messages.h"
#include "handler_MySQL.h"

class Chat : public ISubject {
  public:
    Chat();
    virtual ~Chat();
    bool addUser(const std::string &login, const std::string &password) override;
    bool addMessage(const std::string &sender, const std::string &receiver, const std::string &message) override;

  private:
    Messages* messages_;
    Handler_MySQL* db_mysql_;
};

#endif // CHAT_H
