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
    bool update_messages ();
    bool update_user ();

public slots:

private:
    Chat *chatPtr_;
    QLabel *curr_user_;

    void add_items();
    void add_actions();

    //QMenuBar *mnuBar_;
    //QMenu *pmnu_;
    //QGridLayout *grid_;
    //UserScreen *userScreen_;
};

#endif // WIDGET_H
