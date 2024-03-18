#ifndef USER_SCREEN_H
#define USER_SCREEN_H
#include <QDialog>
#include <QLineEdit>
#include <QStackedWidget>

class UserScreen : public QDialog
{
    Q_OBJECT
 public:
    explicit UserScreen(QWidget *parent = nullptr);
    ~UserScreen();
    const QString &get_login() const;
    const QString &get_password() const;
private:
    QString login_;
    QString password_;

    QWidget *ptopLogin_;
    QWidget *ptopSignin_;
    QLineEdit *loginLineEditLogIn_ ;
    QLineEdit *passwordLineEditLogIn_;
    QLineEdit *loginLineEditSignIn_;
    QLineEdit *passwordLineEditSignIn_;
    QLineEdit *confPasswordLineEditSignIn_;

    QStackedWidget *stackedWidget_;
 private slots:
    void onLoginButtonClicked();
    void onSignInButtonClicked();
    void onLoggedIn();
    void onSignedIn();
};


#endif // USER_SCREEN_H
