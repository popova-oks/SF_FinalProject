#pragma once
#include "chat.h"
#include "user.h"
#include <iostream>

class ClientCode {
  public:
    void start();
    bool containsOnlyLettersNum(std::string const& str);
    User* make_user(Chat* chat);
    User* login_user(Chat* chat);
};
