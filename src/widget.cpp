#include "../headers/widget.h"
#include "../headers/chat.h"
#include <QMenu>


Widget::Widget(QWidget *parent, Chat* chatPtr)
: QWidget::QWidget(parent)
{
    // создаем базу данных
    if (chatPtr_) {
        chatPtr_ = chatPtr;
    }
    chatPtr_ = new Chat();

    add_items();
    add_actions();
}

Widget::~Widget() {
    if (chatPtr_) {
        delete chatPtr_;
        chatPtr_ = nullptr;
    }
}

bool Widget::update_user() {
    UserScreen userScreen;
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
    }
    if (chatPtr_) {
        if (userScreen.get_index() == 1) {
            if (chatPtr_->addUser(curr_login.toStdString(), curr_password.toStdString())) {
                curr_user_->setText(curr_login);
            }
        } else if (userScreen.get_index() == 0) {
            if (chatPtr_->attachUser(curr_login.toStdString(), curr_password.toStdString())) {
                curr_user_->setText(curr_login);
            }
        }
    }
    return true;
}

bool Widget::update_messages()
{
    return true;
}

void Widget::add_items()
{    
    QLabel *label = new QLabel("Current user: ");
    QFont font("Arial", 14); // Создаем новый объект шрифта с заданным размером
    label->setFont(font); // Устанавливаем шрифт для QLabel

    curr_user_ = new QLabel("no user");
    curr_user_->setFont(font);
    curr_user_->setStyleSheet("color: blue;");

    label->setBuddy(curr_user_);

    QGridLayout *grid = new QGridLayout(this);
    grid->addWidget(label, 1, 0);
    grid->addWidget(curr_user_, 1, 1);
    setLayout(grid);
}

void Widget::add_actions()
{

}
