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
    ~UserScreen() {}
 private:
    QWidget *ptopLogin_;
    QWidget *ptopSignin_;
    QLineEdit *loginLineEditLogin_ ;
    QLineEdit *passwordLineEditLogin_;
    QLineEdit *loginLineEditSignin_;
    QLineEdit *passwordLineEditSignin_;
    QLineEdit *confPasswordLineEditSignin_;
    QStackedWidget *stackedWidget_;
 private slots:
    void onLoginButtonClicked();
    void onSignInButtonClicked();

};


#endif // USER_SCREEN_H
