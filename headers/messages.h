#pragma once
#include "IObserver.h"
#include "jsonHandler.h"
#include <map>


template <typename T> class Messages {
  public:
    Messages();
    ~Messages(){};    
    nlohmann::json create_message(const std::string &sender, const std::string &receiver, T message);    
    void save_message(const nlohmann::json &json);
    void send_message(const nlohmann::json &json);
    void get_messages();
    void update_JSON(const char* message);
    const std::string& get_pathJSON () {return pathJSON_;}
  private:
    std::string pathJSON_;
};
