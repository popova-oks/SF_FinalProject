#pragma once
#include "chat.h"
#include <map>
#include <string>

class User : public IObserver {
  public:
    User(Chat* chat);
    virtual ~User() {}

    const std::string& get_name() const override { return name_; }
    const std::string& get_login() const override { return login_; }
    const std::string& get_password() const override { return password_; }
    int get_userID() const override { return user_ID_; }

    User* log_in(Chat* chat);
    void exchange_messages();
    void leave_chat(Chat* chat);
    void display_Messages();

    void set_name(const std::string &name) { name_ = name; }
    void set_login(const std::string &login) { login_ = login; }
    void set_password(const std::string &password) { password_ = password; }	// Вызов хэш функции!!!!
    void set_userID() { user_ID_ = ++static_counter; }
    void set_isAutorization() { is_autorization_ = true; }
    void set_notAutorization() { is_autorization_ = false; }

  private:
    Chat* chat_ = nullptr;
    std::string name_{};
    std::string login_{};
    std::string password_{};
    int user_ID_{0};
    bool is_autorization_{false};
    
    static int static_counter;
};
