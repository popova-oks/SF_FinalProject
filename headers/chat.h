#pragma once
#include "IObserver.h"
#include "ISubject.h"
#include "messages.h"
#include <list>
#include <vector>


class Chat : public ISubject {
  public:
    Chat() {}
    virtual ~Chat();
    void set_User(IObserver* observer) override;
    void attach(IObserver* observer) override;
    void detach(IObserver* observer) override;
    void notify(IObserver* sender, char event) override;
    bool is_check_Observer(IObserver* observer, std::string &login, std::string &password) override;
    IObserver* find_user(std::string login) override;

    bool is_Users() { return !all_users_.empty(); }
    bool is_Observes() { return !list_observers_.empty(); }
    void display_listObservers();
    void display_Messages_fromJSON(IObserver* user);
    void receive_message();

  private:
    std::vector<IObserver*> all_users_{};
    std::list<IObserver*> list_observers_{};
    Messages<std::string>* messages_ = nullptr;
};
