#pragma once
#include <map>
#include <string>

class IObserver {
  public:
    virtual ~IObserver(){};
    
    virtual const std::string& get_name() const = 0;
    virtual const std::string& get_login() const = 0;
    virtual const std::string& get_password() const = 0;
    virtual int get_userID() const = 0;
};
