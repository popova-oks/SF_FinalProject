#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
#include <QObject>
#include <memory>
#include "chat.h"
#include "user_screen.h"


class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr, Chat* chatPtr = nullptr);
    ~Widget();    
    bool update_user ();
    bool detach_user ();
    bool block_user();
    bool unblock_user();
    bool send_message();
    void update_curr_user(QString &login);
public slots:
    void update_startScreen();
private slots:
    void slotButtonSendMessage();
private:
    Chat *chatPtr_;
    QLabel *curr_user_;
    QListWidget *widget_listUsers_;
    QListWidget *widget_listMessage_;
    QListWidget *widget_listPrivateMessage_;
    QGridLayout *start_screen_;
    QLineEdit *textMessage_;
    QLineEdit *receiver_;

    void add_items();
    QString get_curr_user() const;
    void get_attachedUsers();
    void get_messages();
    QString chouse_user();

};

#endif // WIDGET_H
