#include "../headers/widget.h"
#include "../headers/chat.h"
#include <QMenu>
#include <QStringList>
#include <QListWidget>
#include <QTimer>


Widget::Widget(QWidget *parent, Chat* chatPtr)
: QWidget::QWidget(parent)
, chatPtr_ {nullptr}
, curr_user_ {nullptr}
, widget_listUsers_ {nullptr}
, start_screen_ {nullptr}
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
                    return false;
                }
            } else if (userScreen.get_index() == 0) {
                if (!chatPtr_->attachUser(curr_login, curr_password)) {
                    return false;
                }
            }
        }
        update_curr_user (curr_login);
        return true;
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
    QString blockUser = chouse_user();

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
        }
        return true;
    }
    return false;
}

bool Widget::unblock_user()
{
    UserScreen userScreen;
    QString unblockUser = chouse_user();

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
               return false;
            }
        }
        return true;
    }
    return false;
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

QString Widget::chouse_user()
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
    start_screen_->addWidget(widget_listUsers_, 2, 0);
}

void Widget::add_items()
{    
    QLabel *label = new QLabel("Current user: ");
    QFont font("Arial", 14);
    label->setFont(font);

    curr_user_ = new QLabel("no user");
    curr_user_->setFont(font);
    curr_user_->setStyleSheet("color: blue;");

    label->setBuddy(curr_user_);    
    get_attachedUsers();

    start_screen_ = new QGridLayout(this);
    start_screen_->addWidget(label, 1, 0);
    start_screen_->addWidget(curr_user_, 1, 1);
    start_screen_->addWidget(widget_listUsers_, 2, 0);
    setLayout(start_screen_);
}

