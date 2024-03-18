#include "../headers/user.h"
#include "../headers/chat.h"
//#include "../headers/sha1.h"
#include <iostream>

User::User(Chat* chat) : chat_(chat) { chat_->set_User(this); }

User* User::log_in(Chat* chat) {
    if(is_autorization_) {
        std::cout << "\nYou are login!\n";
    } else {
        chat->attach(this);
    }
    return this;
}

void User::exchange_messages() {
    char event;
    while(true) {
        std::cout << "\nEnter an action: s - send a message to any user, q - quit: ";
        std::cin >> event;
        if(event == 'q') {            
            return;
        } else if(event == 's') {
            chat_->notify(this, event);
        } else {
            std::cout << "\nTry agan!\n";
        }
    }
}

void User::display_Messages() {
    chat_->display_Messages_fromJSON(this);
}

void User::leave_chat(Chat* chat) {
    chat->detach(this);
    set_notAutorization();
    std::cout << "\nYou are detached from the chat!\n";
}

int User::static_counter = 0;
