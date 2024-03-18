#include "headers/user_screen.h"
#include <QLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QDialog>
#include <QMessageBox>
#include "../headers/sha1.h"

UserScreen::UserScreen(QWidget *parent) : QDialog(parent) {
    // Установка начального заголовка
    setWindowTitle("Login");

    // Создаем виджеты, которые будут добавлены в QStackedWidget
     ptopLogin_ = new QWidget;
     ptopSignin_ = new QWidget;

     // Создаем виджеты для ввода логина и пароля для каждого экрана
     loginLineEditLogIn_  = new QLineEdit (ptopLogin_);
     passwordLineEditLogIn_ = new QLineEdit (ptopLogin_);
     passwordLineEditLogIn_->setEchoMode(QLineEdit::Password);

     loginLineEditSignIn_  = new QLineEdit (ptopSignin_);
     passwordLineEditSignIn_ = new QLineEdit (ptopSignin_);
     passwordLineEditSignIn_->setEchoMode(QLineEdit::Password);
     confPasswordLineEditSignIn_ = new QLineEdit (ptopSignin_);
     confPasswordLineEditSignIn_->setEchoMode(QLineEdit::Password);

     // Создаем метки для каждого экрана
     QLabel* lblLoginLogin  = new QLabel("&Login: ");
     QLabel* lblPasswordLogin  = new QLabel("&Password: ");
     QLabel* lblLoginSignin  = new QLabel("&Login: ");
     QLabel* lblPasswordSignin  = new QLabel("&Password: ");
     QLabel* lblConfPassSignin = new QLabel("&Confirm password: ");

     // Связываем метки с соответствующими полями ввода
     lblLoginLogin->setBuddy(loginLineEditLogIn_);
     lblPasswordLogin->setBuddy(passwordLineEditLogIn_);
     lblLoginSignin->setBuddy(loginLineEditSignIn_);
     lblPasswordSignin->setBuddy(passwordLineEditSignIn_);
     lblConfPassSignin->setBuddy(confPasswordLineEditSignIn_);

     // Создаем кнопки для каждого экрана
     QPushButton *pcmdOkLogIn = new QPushButton("&Ok");
     QPushButton *pcmdCancelLogIn = new QPushButton("&Cancel");
     QPushButton *pcmdOkSignIn = new QPushButton("&Ok");
     QPushButton *pcmdCancelSignIn = new QPushButton("&Cancel");

     //connect(pcmdOkLogin, SIGNAL(clicked()), this, SLOT(accept()));
     connect(pcmdOkLogIn, SIGNAL(clicked()), this, SLOT(onLoggedIn()));
     connect(pcmdCancelLogIn, SIGNAL(clicked()), this, SLOT(reject()));

     //connect(pcmdOkSignin, SIGNAL(clicked()), this, SLOT(accept()));
     connect(pcmdOkSignIn, SIGNAL(clicked()), this, SLOT(onSignedIn()));
     connect(pcmdCancelSignIn, SIGNAL(clicked()), this, SLOT(reject()));

     QPushButton *button1 = new QPushButton("Go to Login");
     QPushButton *button2 = new QPushButton("Go to Sign in");

     // Создаем макеты для каждого экрана
     QGridLayout* ptopLayoutLogin = new QGridLayout();
     QGridLayout* ptopLayoutSignin = new QGridLayout();

     // Добавляем элементы в макет экрана входа
     ptopLayoutLogin->addWidget(lblLoginLogin, 1, 0);
     ptopLayoutLogin->addWidget(lblPasswordLogin, 2, 0);
     ptopLayoutLogin->addWidget(loginLineEditLogIn_, 1, 1);
     ptopLayoutLogin->addWidget(passwordLineEditLogIn_, 2, 1);
     ptopLayoutLogin->addWidget(pcmdOkLogIn, 3, 1);
     ptopLayoutLogin->addWidget(pcmdCancelLogIn, 3, 2);
     ptopLayoutLogin->addWidget(button2, 3, 3);

     // Добавляем элементы в макет экрана регистрации
     ptopLayoutSignin->addWidget(lblLoginSignin, 1, 0);
     ptopLayoutSignin->addWidget(lblPasswordSignin, 2, 0);
     ptopLayoutSignin->addWidget(lblConfPassSignin, 3, 0);
     ptopLayoutSignin->addWidget(loginLineEditSignIn_, 1, 1);
     ptopLayoutSignin->addWidget(passwordLineEditSignIn_, 2, 1);
     ptopLayoutSignin->addWidget(confPasswordLineEditSignIn_, 3, 1);
     ptopLayoutSignin->addWidget(pcmdOkSignIn, 4, 1);
     ptopLayoutSignin->addWidget(pcmdCancelSignIn, 4, 2);
     ptopLayoutSignin->addWidget(button1, 4, 3);

     // Устанавливаем макеты для каждого экрана
     ptopLogin_->setLayout(ptopLayoutLogin);
     ptopSignin_->setLayout(ptopLayoutSignin);
     stackedWidget_ = new QStackedWidget (this);

     // Добавляем созданные виджеты в QStackedWidget
     stackedWidget_->addWidget(ptopLogin_);
     stackedWidget_->addWidget(ptopSignin_);

     // Подключение сигналов к слотам
     connect(button1, &QPushButton::clicked, this, &UserScreen::onLoginButtonClicked);
     connect(button2, &QPushButton::clicked, this, &UserScreen::onSignInButtonClicked);

     // Устанавливаем начальную страницу
     stackedWidget_->setCurrentWidget(ptopLogin_);

     // Отобразим окно
      QVBoxLayout * mainLayout = new QVBoxLayout(this);
      mainLayout->addWidget(stackedWidget_);
      setLayout(mainLayout);
}

UserScreen::~UserScreen() {
    if (ptopLogin_) {
        delete ptopLogin_;
        ptopLogin_ = nullptr;
    }
    if (ptopSignin_) {
        delete ptopSignin_;
        ptopSignin_ = nullptr;
    }
    if (stackedWidget_) {
        delete stackedWidget_;
        stackedWidget_ = nullptr;
    }
}

const QString &UserScreen::get_login() const
{
    return login_;
}

const QString &UserScreen::get_password() const
{
    return password_;
}

int UserScreen::get_index() const
{
    return index_;
}

void UserScreen::onLoginButtonClicked()
{
    stackedWidget_->setCurrentIndex(0); // Установка виджета "Log in"
    index_ = 0;
    setWindowTitle("Login"); // Изменение заголовка
}

void UserScreen::onSignInButtonClicked()
{
    stackedWidget_->setCurrentIndex(1); // Установка виджета "Sign in"
    index_ = 1;
    setWindowTitle("Sign in"); // Изменение заголовка
}

void UserScreen::onLoggedIn()
{
    login_ = loginLineEditLogIn_->text();
    std::string password = passwordLineEditSignIn_->text().toStdString();
    password_ = sha1(password).c_str();
    accept();
}

void UserScreen::onSignedIn()
{
    if (passwordLineEditSignIn_->text()
            != confPasswordLineEditSignIn_->text()){
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Password not match") + "!");
        reject();
    } else {
        login_ = loginLineEditSignIn_->text();
        std::string password = passwordLineEditSignIn_->text().toStdString();
        password_ = sha1(password).c_str();
        accept();
    }
}

