#include "../headers/widget.h"
#include "../headers/chat.h"
#include <QMenu>
#include <QStringList>
#include <QListWidget>
#include <QTimer>

Widget::Widget(QWidget *parent, Chat* chatPtr)
: QWidget::QWidget(parent)
, chatPtr_ {nullptr}
//, curr_user_ {nullptr}
, widget_listUsers_ {nullptr}
, widget_listMessage_ {nullptr}
, widget_listPrivateMessage_ {nullptr}
//, start_screen_ {nullptr}
//, textMessage_LineEdit {nullptr}
//, receiver_LineEdit {nullptr}
{
    // создаем базу данных
    if (chatPtr_) {
        chatPtr_ = chatPtr;
    }
    chatPtr_ = new Chat();
    add_items();
    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::update_startScreen);
    timer->start(100);
}

Widget::~Widget() {
    if (chatPtr_) {
        delete chatPtr_;
        chatPtr_ = nullptr;
    }
}

bool Widget::update_user() {
    UserScreen userScreen;
    userScreen.login_form();
    auto result = userScreen.exec();
    if (result == QDialog::Rejected) {
        return false;
    }
    QString curr_login;
    QString curr_password;
    if (result == QDialog::Accepted) {
        curr_login = userScreen.get_login();
        curr_password = userScreen.get_password();
        if (curr_login.isEmpty() || curr_password.isEmpty()) {
            return false;
        }    
        if (chatPtr_) {
            if (userScreen.get_index() == 1) {
                if (!chatPtr_->addUser(curr_login, curr_password)) {
                    QMessageBox::critical(this,
                                          "Error",
                                          "Failed to add the user!");
                    return false;
                }
            } else if (userScreen.get_index() == 0) {
                if (!chatPtr_->attachUser(curr_login, curr_password)) {
                    QMessageBox::critical(this,
                                          "Error",
                                          "Failed to attach the user!");
                    return false;
                }
            }
            update_curr_user (curr_login);
            return true;
        }

    }
    return false;
}

bool Widget::detach_user()
{
    UserScreen userScreen;
    userScreen.close_form(get_curr_user());

    auto result = userScreen.exec();
    if (result == QDialog::Rejected) {
        return false;
    }
    if (result == QDialog::Accepted) {
        if (chatPtr_) {
            if (!chatPtr_->detachUser(curr_user_->text())) {

                QMessageBox::critical(this,
                                      "Error",
                                      "Failed to detach the user!");
                return false;
            }
            return true;
        }
    }
    return false;
}

bool Widget::block_user()
{
    UserScreen userScreen;
    QString blockUser = choose_user();

    userScreen.block_form(blockUser);
    auto result = userScreen.exec();
    if (result == QDialog::Rejected) {
        return false;
    }
    QString admin_login;
    QString admin_password;
    if (result == QDialog::Accepted) {
        admin_login = userScreen.get_login();
        admin_password = userScreen.get_password();
        if (admin_login.isEmpty() || admin_password.isEmpty()) {
            return false;
        }
        if (chatPtr_) {
            if (!chatPtr_->blockUser(admin_login, admin_password, blockUser)) {
               return false;
            }
            return true;
        }
    }
    return false;
}

bool Widget::unblock_user()
{
    UserScreen userScreen;
    QString unblockUser = choose_user();

    userScreen.block_form(unblockUser);
    auto result = userScreen.exec();
    if (result == QDialog::Rejected) {
        return false;
    }
    QString admin_login;
    QString admin_password;
    if (result == QDialog::Accepted) {
        admin_login = userScreen.get_login();
        admin_password = userScreen.get_password();
        if (admin_login.isEmpty() || admin_password.isEmpty()) {
            return false;
        }
        if (chatPtr_) {
            if (!chatPtr_->unblockUser(admin_login, admin_password, unblockUser)) {
                QMessageBox::critical(this,
                                      "Error",
                                      "Failed to block the user!");
               return false;
            }
            return true;
        }        
    }
    return false;
}

bool Widget::send_message()
{
    QString message = textMessage_LineEdit->text();
    QString receiver = receiver_LineEdit->text();;
    QString sender = get_curr_user();

    if (message.isEmpty() || receiver.isEmpty() || sender.isEmpty()) {
        return false;
    } else {
        UserScreen userScreen;
        userScreen.message_form(sender, receiver, message);

        auto result = userScreen.exec();
        if (result == QDialog::Rejected) {
            return false;
        }
        if (result == QDialog::Accepted) {
            if (chatPtr_) {
                if (!chatPtr_->sendMessage(sender, receiver, message)) {
                   QMessageBox::critical(this,
                                          "Error",
                                          "Failed to send the message!");
                   return false;
                }
                return true;
            }
        }
        return false;
    }
}

void Widget::update_curr_user(QString &login)
{
    if (!login.isEmpty()){
       curr_user_->setText(login);
    }
}

QString Widget::get_curr_user() const
{
    return curr_user_->text();
}

void Widget::get_attachedUsers()
{
    if(widget_listUsers_ != nullptr) {
        delete widget_listUsers_;
        widget_listUsers_ = nullptr;
    }

    QListWidget *listUsers = new QListWidget(this);
    if (chatPtr_) {
        QStringList list_users = chatPtr_->attachedUsers();
        if (list_users.isEmpty()) {
            listUsers->addItem("No users available");
        } else {
            std::sort(list_users.begin(), list_users.end());
            listUsers->addItems(list_users);
        }
    } else {
        // Если указатель chatPtr_ равен nullptr, добавляем пустой элемент в список
        listUsers->addItem("No users available");
    }    
    widget_listUsers_ = listUsers;
    // Включаем возможность выбора пользователей
    widget_listUsers_->setSelectionMode(QAbstractItemView::SingleSelection);
}

void Widget::get_messages()
{
    if(widget_listMessage_ != nullptr) {
        delete widget_listMessage_;
        widget_listMessage_ = nullptr;
    }
    if(widget_listPrivateMessage_ != nullptr) {
        delete widget_listPrivateMessage_;
        widget_listPrivateMessage_ = nullptr;
    }
    QListWidget *listMessages = new QListWidget(this);
    QListWidget *listPrivateMessages = new QListWidget(this);
    if (get_curr_user() == "no user") {
        listPrivateMessages->addItem("No private messages available");
    } else {
        if (chatPtr_) {
            QStringList list_messages = chatPtr_->privateMessages(get_curr_user());
            if (list_messages.isEmpty()) {
                listPrivateMessages->addItem("No messages available");
            } else {
                std::sort(list_messages.begin(), list_messages.end());
                listPrivateMessages->addItems(list_messages);
            }
        } else {
            // Если указатель chatPtr_ равен nullptr, добавляем пустой элемент в список
            listPrivateMessages->addItem("No messages available");
        }
    }
    if (chatPtr_) {
        QStringList list_messages = chatPtr_->messagesForAll();
        if (list_messages.isEmpty()) {
            listMessages->addItem("No messages available");
        } else {
            std::sort(list_messages.begin(), list_messages.end());
            listMessages->addItems(list_messages);
        }
    } else {
        // Если указатель chatPtr_ равен nullptr, добавляем пустой элемент в список
        listMessages->addItem("No messages available");
    }
    widget_listPrivateMessage_ = listPrivateMessages;
    widget_listMessage_ = listMessages;
}

QString Widget::choose_user()
{
    QString user;
    QDialog dlg(this);

    if (!chatPtr_) {
        qDebug() << "Chat pointer is not initialized";
        return user;
    }

    QStringList list_blockedUsers = chatPtr_->listBlockedUsers();
    QStringList list_unblockedUsers = chatPtr_->listUnblockedUsers();

    if (list_blockedUsers.isEmpty() && list_unblockedUsers.isEmpty()) {
        qDebug() << "No users available";
        return user;
    }

    QGridLayout *mainLayout = new QGridLayout(&dlg);

    QLabel label3 ("Choose the user!");
    QLabel label4 ("Blocked users:");
    QLabel label5 ("Unblocked users:");
    QPushButton *okButton = new QPushButton("OK", &dlg);
    QPushButton *cancelButton = new QPushButton("Cancel", &dlg);

    QListWidget *listBlockedUsers = new QListWidget(&dlg);
    QListWidget *listUnblockedUsers = new QListWidget(&dlg);

    if (!list_blockedUsers.isEmpty()) {
        std::sort(list_blockedUsers.begin(), list_blockedUsers.end());
        listBlockedUsers->addItems(list_blockedUsers);
        listBlockedUsers->setSelectionMode(QAbstractItemView::SingleSelection);
    } else {
        listBlockedUsers->addItem("No blocked users available");
    }

    if (!list_unblockedUsers.isEmpty()) {
        std::sort(list_unblockedUsers.begin(), list_unblockedUsers.end());
        listUnblockedUsers->addItems(list_unblockedUsers);
        listUnblockedUsers->setSelectionMode(QAbstractItemView::SingleSelection);
    } else {
        listUnblockedUsers->addItem("No unblocked users available");
    }

    mainLayout->addWidget(&label3, 1, 1);
    mainLayout->addWidget(&label4, 2, 0);
    mainLayout->addWidget(listBlockedUsers, 3, 0, 1, 2);
    mainLayout->addWidget(&label5, 2, 3);
    mainLayout->addWidget(listUnblockedUsers, 3, 2, 1, 2);
    mainLayout->addWidget(okButton, 5, 0);
    mainLayout->addWidget(cancelButton, 5, 2);

    connect(okButton, &QPushButton::clicked, &dlg, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, &dlg, &QDialog::reject);

    if (dlg.exec() == QDialog::Accepted) {
        if (listBlockedUsers->currentItem() != nullptr) {
            user = listBlockedUsers->currentItem()->text();
        } else if (listUnblockedUsers->currentItem() != nullptr) {
            user = listUnblockedUsers->currentItem()->text();
        }
    } else {
        user.clear();
    }
    return user;
}

void Widget::update_startScreen()
{
    get_attachedUsers();
    get_messages();
    start_screen_->addWidget(widget_listUsers_, 2, 0);
    start_screen_->addWidget(widget_listMessage_, 2, 1, 2, 1);
    start_screen_->addWidget(widget_listPrivateMessage_, 2, 2, 2, 1);
}

void Widget::slotButtonSendMessage()
{
    if (!send_message()) {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Message could not be sent!") + "!");
        return;
    } else {
        update_startScreen();
    }

}

void Widget::add_items()
{    
    QLabel *label1 = new QLabel("Current user: ", this);
    label1->setStyleSheet("color: blue; font-size: 12pt; font-weight: bold;");
    QLabel *label2 = new QLabel("Messages for all: ", this);
    label2->setStyleSheet("color: blue; font-size: 12pt; font-weight: bold;");
    QLabel *label3 = new QLabel("Private messages: ", this);
    label3->setStyleSheet("color: blue; font-size: 12pt; font-weight: bold;");

    curr_user_ = new QLabel("no user", this);
    curr_user_->setStyleSheet("color: red; font-size: 12pt; font-weight: bold;");
    label1->setBuddy(curr_user_);

    get_attachedUsers();
    widget_listMessage_= new QListWidget (this);
    widget_listPrivateMessage_ = new QListWidget (this);

    QLabel *label4 = new QLabel("Messages: ", this);
    label4->setStyleSheet("color: blue; font-size: 12pt; font-weight: bold;");
    textMessage_LineEdit = new QLineEdit(this);
    label4->setBuddy(textMessage_LineEdit);

    QLabel *label5 = new QLabel("Enter login receiver or all: ", this);
    label5->setStyleSheet("color: blue; font-size: 12pt; font-weight: bold;");
    receiver_LineEdit = new QLineEdit(this);
    label5->setBuddy(receiver_LineEdit);

    QPushButton *button_sendMessage = new QPushButton("Send Message", this);
    button_sendMessage->setStyleSheet("font-size: 12pt; font-weight: bold; color: blue;");
    connect(button_sendMessage, SIGNAL(clicked()), this, SLOT(slotButtonSendMessage()));

    start_screen_ = new QGridLayout(this);
    start_screen_->addWidget(label1, 0, 0);
    start_screen_->addWidget(curr_user_, 1, 0);
    start_screen_->addWidget(label2, 1, 1);
    start_screen_->addWidget(label3, 1, 2);

    start_screen_->addWidget(widget_listUsers_, 2, 0, 2, 1);
    start_screen_->addWidget(widget_listMessage_, 2, 1, 2, 1);
    start_screen_->addWidget(widget_listPrivateMessage_, 2, 2, 2, 1);

    start_screen_->addWidget(label4, 4, 0);
    start_screen_->addWidget(textMessage_LineEdit, 4, 1, 1, 2);
    start_screen_->addWidget(label5, 5, 0);
    start_screen_->addWidget(receiver_LineEdit, 5, 1, 1, 2);
    start_screen_->addWidget(button_sendMessage, 6, 1, 1, 1);

    setLayout(start_screen_);
}
