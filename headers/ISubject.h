#ifndef ISUBJECT_H
#define ISUBJECT_H
#include <iostream>
#include <string>

class ISubject {
  public:
    virtual ~ISubject(){};
    virtual bool addUser(const std::string &login, const std::string &password) = 0;
    virtual bool sendMessage(const std::string &sender, const std::string &receiver, const std::string &message) = 0;
};

#endif // ISUBJECT_H
