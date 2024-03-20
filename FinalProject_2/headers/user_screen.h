#ifndef USER_SCREEN_H
#define USER_SCREEN_H
#include <QDialog>
#include <QLineEdit>
#include <QStackedWidget>

class UserScreen : public QDialog
{
    Q_OBJECT
 public:
    explicit UserScreen(QWidget *parent = nullptr) ;
    ~UserScreen();
    void login_form ();
    void close_form (const QString &client);
    void block_form (const QString &client);
    void message_form (const QString &sender, const QString &receiver, const QString &message);

    const QString &get_login() const;
    const QString &get_password() const;
    int get_index() const;
private:
    QString login_;
    QString password_;
    int index_ = 0;

    QStackedWidget *stackedWidget_;
    //QWidget *ptopWidget1_;
    //QWidget *ptopWidget2_;
    QLineEdit *loginLineEditLogIn_ ;
    QLineEdit *passwordLineEditLogIn_;
    QLineEdit *loginLineEditSignIn_;
    QLineEdit *passwordLineEditSignIn_;
    QLineEdit *confPasswordLineEditSignIn_;    

 private slots:
    void onLoginButtonClicked();
    void onSignInButtonClicked();
    void onLoggedIn();
    void onSignedIn();
};


#endif // USER_SCREEN_H
