#include "headers/user_screen.h"
#include <QLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QDialog>

UserScreen::UserScreen(QWidget *parent) : QDialog(parent) {
    // Создаем виджеты, которые будут добавлены в QStackedWidget
     ptopLogin_ = new QWidget;
     ptopSignin_ = new QWidget;

     // Устанавливаем заголовки для виджетов
     ptopLogin_->setWindowTitle("Login");
     ptopSignin_->setWindowTitle("Sign in");

     // Создаем виджеты для ввода логина и пароля для каждого экрана
     loginLineEditLogin_  = new QLineEdit;
     passwordLineEditLogin_ = new QLineEdit;
     loginLineEditSignin_  = new QLineEdit;
     passwordLineEditSignin_ = new QLineEdit;
     confPasswordLineEditSignin_ = new QLineEdit;

     // Создаем метки для каждого экрана
     QLabel* lblLoginLogin  = new QLabel("&Login: ");
     QLabel* lblPasswordLogin  = new QLabel("&Password: ");
     QLabel* lblLoginSignin  = new QLabel("&Login: ");
     QLabel* lblPasswordSignin  = new QLabel("&Password: ");
     QLabel* lblConfPassSignin = new QLabel("&Confirm password: ");

     // Связываем метки с соответствующими полями ввода
     lblLoginLogin->setBuddy(loginLineEditLogin_);
     lblPasswordLogin->setBuddy(passwordLineEditLogin_);
     lblLoginSignin->setBuddy(loginLineEditSignin_);
     lblPasswordSignin->setBuddy(passwordLineEditSignin_);
     lblConfPassSignin->setBuddy(confPasswordLineEditSignin_);

     // Создаем кнопки для каждого экрана
     QPushButton *pcmdOkLogin = new QPushButton("&Ok");
     QPushButton *pcmdCancelLogin = new QPushButton("&Cancel");
     QPushButton *pcmdOkSignin = new QPushButton("&Ok");
     QPushButton *pcmdCancelSignin = new QPushButton("&Cancel");

     connect(pcmdOkLogin, SIGNAL(clicked()), this, SLOT(accept()));
     connect(pcmdCancelLogin, SIGNAL(clicked()), this, SLOT(reject()));
     connect(pcmdOkSignin, SIGNAL(clicked()), this, SLOT(accept()));
     connect(pcmdCancelSignin, SIGNAL(clicked()), this, SLOT(reject()));

     QPushButton *button1 = new QPushButton("Log in");
     QPushButton *button2 = new QPushButton("Registration");

     // Создаем макеты для каждого экрана
     QGridLayout* ptopLayoutLogin = new QGridLayout();
     QGridLayout* ptopLayoutSignin = new QGridLayout();

     // Добавляем элементы в макет экрана входа
     ptopLayoutLogin->addWidget(lblLoginLogin, 1, 0);
     ptopLayoutLogin->addWidget(lblPasswordLogin, 2, 0);
     ptopLayoutLogin->addWidget(loginLineEditLogin_, 1, 1);
     ptopLayoutLogin->addWidget(passwordLineEditLogin_, 2, 1);
     ptopLayoutLogin->addWidget(pcmdOkLogin, 3, 1);
     ptopLayoutLogin->addWidget(pcmdCancelLogin, 3, 2);
     ptopLayoutLogin->addWidget(button2, 3, 3);

     // Добавляем элементы в макет экрана регистрации
     ptopLayoutSignin->addWidget(lblLoginSignin, 1, 0);
     ptopLayoutSignin->addWidget(lblPasswordSignin, 2, 0);
     ptopLayoutSignin->addWidget(lblConfPassSignin, 3, 0);
     ptopLayoutSignin->addWidget(loginLineEditSignin_, 1, 1);
     ptopLayoutSignin->addWidget(passwordLineEditSignin_, 2, 1);
     ptopLayoutSignin->addWidget(confPasswordLineEditSignin_, 3, 1);
     ptopLayoutSignin->addWidget(pcmdOkSignin, 4, 1);
     ptopLayoutSignin->addWidget(pcmdCancelSignin, 4, 2);
     ptopLayoutSignin->addWidget(button1, 4, 3);

     // Устанавливаем макеты для каждого экрана
     ptopLogin_->setLayout(ptopLayoutLogin);
     ptopSignin_->setLayout(ptopLayoutSignin);
     stackedWidget_ = new QStackedWidget;

     // Добавляем созданные виджеты в QStackedWidget
     stackedWidget_->addWidget(ptopLogin_);
     stackedWidget_->addWidget(ptopSignin_);

     // Подключаем сигналы и слоты для переключения между страницами
     QObject::connect(button1, &QPushButton::clicked, [this]() {
         stackedWidget_->setCurrentIndex(0);
     });
     QObject::connect(button2, &QPushButton::clicked, [this]() {
         stackedWidget_->setCurrentIndex(1);
     });

     // Устанавливаем начальную страницу
     stackedWidget_->setCurrentWidget(ptopLogin_);

     // Отобразим окно
      QVBoxLayout * mainLayout = new QVBoxLayout(this);
      mainLayout->addWidget(stackedWidget_);
      setLayout(mainLayout);
}

UserScreen::~UserScreen()
{

}
