#include "headers/user_screen.h"
#include <QLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QDialog>
#include <QMessageBox>
#include "../headers/sha1.h"

UserScreen::UserScreen(QWidget *parent)
    : QDialog(parent)
    , stackedWidget_{nullptr}{}

UserScreen::~UserScreen(){
    if (stackedWidget_) {
        delete stackedWidget_;
        stackedWidget_ = nullptr;
    }
}

void UserScreen::login_form() {
     // Установка начального заголовка
     setWindowTitle("Login");

     stackedWidget_ = new QStackedWidget (this);

     // Создаем виджеты, которые будут добавлены в QStackedWidget
     QWidget *ptopWidget1 = new QWidget (stackedWidget_);
     QWidget *ptopWidget2 = new QWidget (stackedWidget_);

     // Создаем виджеты для ввода логина и пароля для каждого экрана
     loginLineEditLogIn_  = new QLineEdit (ptopWidget1);
     passwordLineEditLogIn_ = new QLineEdit (ptopWidget1);
     passwordLineEditLogIn_->setEchoMode(QLineEdit::Password);

     loginLineEditSignIn_  = new QLineEdit (ptopWidget2);
     passwordLineEditSignIn_ = new QLineEdit (ptopWidget2);
     passwordLineEditSignIn_->setEchoMode(QLineEdit::Password);
     confPasswordLineEditSignIn_ = new QLineEdit (ptopWidget2);
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
     button1->setStyleSheet("background-color: cyan; font-size: 12pt; ");
     QPushButton *button2 = new QPushButton("Go to SignIn");
     button2->setStyleSheet("background-color: cyan; font-size: 12pt;");

     // Создаем макеты для каждого экрана
     QGridLayout* ptopLayoutLogin = new QGridLayout(ptopWidget1);
     QGridLayout* ptopLayoutSignin = new QGridLayout(ptopWidget2);

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
     ptopWidget1->setLayout(ptopLayoutLogin);
     ptopWidget2->setLayout(ptopLayoutSignin);
     //stackedWidget_ = new QStackedWidget (this);

     // Добавляем созданные виджеты в QStackedWidget
     stackedWidget_->addWidget(ptopWidget1);
     stackedWidget_->addWidget(ptopWidget2);

     // Подключение сигналов к слотам
     connect(button1, &QPushButton::clicked, this, &UserScreen::onLoginButtonClicked);
     connect(button2, &QPushButton::clicked, this, &UserScreen::onSignInButtonClicked);

      // Отобразим окно
      QVBoxLayout * mainLayout = new QVBoxLayout(stackedWidget_);
      mainLayout->addWidget(stackedWidget_);
      setLayout(mainLayout);
}

void UserScreen::close_form(const QString &client)
{
     // Установка заголовка
     setWindowTitle("Detach from the chat");

    // Создаем виджеты, которые будут добавлены в форму
     QWidget *ptopWidget = new QWidget (this);

     // Создаем метки для каждого экрана
     QString message = "Current user: " + client;
     QLabel* label1  = new QLabel(message, ptopWidget);
     QLabel* label2  = new QLabel("Do you want to leave the chat? ", ptopWidget);
     label1->setStyleSheet("color: blue; font-size: 12pt; font-weight: bold;");
     label2->setStyleSheet("color: red; font-size: 12pt; font-weight: bold;");

     // Создаем кнопки
     QPushButton *pcmdOk = new QPushButton("&Ok", ptopWidget);
     QPushButton *pcmdCancel = new QPushButton("&Cancel", ptopWidget);

     connect(pcmdOk, SIGNAL(clicked()), this, SLOT(accept()));
     connect(pcmdCancel, SIGNAL(clicked()), this, SLOT(reject()));

     // Создаем макеты для каждого экрана
     QGridLayout* ptopLayout = new QGridLayout(ptopWidget);

     // Добавляем элементы в макет экрана входа
     ptopLayout->addWidget(label1, 0, 0);
     ptopLayout->addWidget(label2, 1, 0);
     ptopLayout->addWidget(pcmdOk, 2, 1);
     ptopLayout->addWidget(pcmdCancel, 2, 2);

     // Устанавливаем макеты для каждого экрана
     ptopWidget->setLayout(ptopLayout);

     // Отобразим окно
      QVBoxLayout * mainLayout = new QVBoxLayout(this);
      mainLayout->addWidget(ptopWidget);
      setLayout(mainLayout);
}

void UserScreen::block_form(const QString &client)
{
     // Установка заголовка
     setWindowTitle("Block or unblock this client");

     //Создаем виджеты, которые будут добавлены в форму
     QWidget *ptopWidget = new QWidget (this);

     // Создаем метки для каждого экрана
     QString message = "The user: " + client;
     QLabel* label1  = new QLabel(message, ptopWidget);
     label1->setStyleSheet("color: red; font-size: 12pt; font-weight: bold;");
     QLabel* label2  = new QLabel("Enter password for admin! ");
     label2->setStyleSheet("font-size: 12pt; font-weight: bold;");

     // Создаем виджеты для ввода логина и пароля для каждого экрана
     loginLineEditLogIn_  = new QLineEdit (ptopWidget);
     loginLineEditLogIn_->setText("admin");
     passwordLineEditLogIn_ = new QLineEdit (ptopWidget);
     passwordLineEditLogIn_->setEchoMode(QLineEdit::Password);

     // Создаем метки для каждого экрана
     QLabel* lblLoginLogin  = new QLabel("&Login: ");
     QLabel* lblPasswordLogin  = new QLabel("&Password: ");

     // Связываем метки с соответствующими полями ввода
     lblLoginLogin->setBuddy(loginLineEditLogIn_);
     lblPasswordLogin->setBuddy(passwordLineEditLogIn_);

     // Создаем кнопки для каждого экрана
     QPushButton *pcmdOkLogIn = new QPushButton("&Ok");
     QPushButton *pcmdCancelLogIn = new QPushButton("&Cancel");

     //connect(pcmdOkLogin, SIGNAL(clicked()), this, SLOT(accept()));
     connect(pcmdOkLogIn, SIGNAL(clicked()), this, SLOT(onLoggedIn()));
     connect(pcmdCancelLogIn, SIGNAL(clicked()), this, SLOT(reject()));

     // Создаем макеты для каждого экрана
     QGridLayout* ptopLayoutLogin = new QGridLayout(ptopWidget);

     // Добавляем элементы в макет экрана входа
     ptopLayoutLogin->addWidget(label1, 0, 0);
     ptopLayoutLogin->addWidget(label2, 1, 0);
     ptopLayoutLogin->addWidget(lblLoginLogin, 2, 0);
     ptopLayoutLogin->addWidget(lblPasswordLogin, 3, 0);
     ptopLayoutLogin->addWidget(loginLineEditLogIn_, 2, 1);
     ptopLayoutLogin->addWidget(passwordLineEditLogIn_, 3, 1);
     ptopLayoutLogin->addWidget(pcmdOkLogIn, 4, 1);
     ptopLayoutLogin->addWidget(pcmdCancelLogIn, 4, 2);

     // Устанавливаем макеты для каждого экрана
     ptopWidget->setLayout(ptopLayoutLogin);

     // Отобразим окно
      QVBoxLayout * mainLayout = new QVBoxLayout(this);
      mainLayout->addWidget(ptopWidget);
      setLayout(mainLayout);
}

void UserScreen::message_form(const QString &sender, const QString &receiver, const QString &message)
{
    // Установка заголовка
    setWindowTitle("The message");

    // Создаем виджеты, которые будут добавлены в форму
     QWidget *ptopWidget = new QWidget (this);

     // Создаем метки для каждого экрана
     QString str_sender = "Sender: " + sender;
     QString str_receiver = "Receiver: " + receiver;
     QString str_message = "Message: " + message;
     QLabel* label1  = new QLabel(str_sender, ptopWidget);
     QLabel* label2  = new QLabel(str_receiver, ptopWidget);
     QLabel* label3  = new QLabel(str_message, ptopWidget);
     QLabel* label4  = new QLabel("Do you want to send this message? ");
     label4->setStyleSheet("color: red; font-size: 12pt; font-weight: bold;");

     // Создаем кнопки
     QPushButton *pcmdOk = new QPushButton("&Ok", ptopWidget);
     QPushButton *pcmdCancel = new QPushButton("&Cancel", ptopWidget);

     connect(pcmdOk, SIGNAL(clicked()), this, SLOT(accept()));
     connect(pcmdCancel, SIGNAL(clicked()), this, SLOT(reject()));

     // Создаем макеты для каждого экрана
     QGridLayout* ptopLayout = new QGridLayout(ptopWidget);

     // Добавляем элементы в макет экрана входа
     ptopLayout->addWidget(label1, 0, 0);
     ptopLayout->addWidget(label2, 1, 0);
     ptopLayout->addWidget(label3, 2, 0);
     ptopLayout->addWidget(label4, 3, 0);
     ptopLayout->addWidget(pcmdOk, 4, 1);
     ptopLayout->addWidget(pcmdCancel, 4, 2);

     // Устанавливаем макеты для каждого экрана
     ptopWidget->setLayout(ptopLayout);

     // Отобразим окно
      QVBoxLayout * mainLayout = new QVBoxLayout(this);
      mainLayout->addWidget(ptopWidget);
      setLayout(mainLayout);
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
    std::string password = passwordLineEditLogIn_->text().toStdString();
    password_ = sha1(password).c_str();
    accept();
}

void UserScreen::onSignedIn()
{
    if (passwordLineEditSignIn_->text()
            != confPasswordLineEditSignIn_->text()){
        QMessageBox::critical(this,
                              "Error",
                              "Password not match!");
        reject();
    } else {
        login_ = loginLineEditSignIn_->text();
        std::string password = passwordLineEditSignIn_->text().toStdString();
        password_ = sha1(password).c_str();
        accept();
    }
}

