#include "../headers/widget.h"
#include <QMenu>


Widget::Widget(QWidget *parent, std::shared_ptr<Chat> chatPtr)
: QWidget::QWidget(parent)
{
    // создаем базу данных
    if (chatPtr_) {
        chatPtr_ = chatPtr;
    }
    chatPtr_ = std::make_shared<Chat>();

    add_items();
    add_actions();
}

Widget::~Widget() {

}

bool Widget::update_user() {
    UserScreen userScreen;
    auto result = userScreen.exec();
    if (result == QDialog::Rejected) {
        return false;
    }
    if (result == QDialog::Accepted) {
        //getUserID()
        //getUserName()
        //getLogin());
    }
    return true;
}

bool Widget::update_messages()
{
    return true;
}

void Widget::add_items()
{    
    // создаем меню верхнего уровня
    mnuBar_ = new QMenuBar();
    pmnu_ = new QMenu ( "&Registration");

    pmnu_->addAction("&AЬout Qt", this, SLOT(aboutQt()), Qt::CTRL+Qt::Key_Q);
    pmnu_->addSeparator();
    //pmnu->addAction("&Exit", &арр, SLOT(quit()));
    mnuBar_->addMenu(pmnu_);

    grid_ = new QGridLayout(this);
    grid_->addWidget(mnuBar_, 0, 0, 1, 2);
    setLayout(grid_);
}

void Widget::add_actions()
{

}
