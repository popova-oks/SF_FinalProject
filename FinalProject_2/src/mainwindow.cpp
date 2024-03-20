#include "../headers/mainwindow.h"
#include "../headers/widget.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , widget_ {nullptr}
{
    ui->setupUi(this);
    add_items();

    widget_ = new Widget(this);
    widget_->resize(400, 400);
    setCentralWidget(widget_);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (widget_) {
        delete widget_;
        widget_ = nullptr;
    }
}

void MainWindow::add_items()
{
    QMenuBar *menuBar_ = new QMenuBar(this);
    QMenu *pmnu_ = new QMenu("&Menu", this);
    QMenu *pmnu_user = new QMenu ("&Attach or Detach", this);
    menuBar_->setStyleSheet("color: red; font-size: 12pt; font-weight: bold;");

    pmnu_user->addAction("&Login or SignIn", this, &MainWindow::on_actionOpenClient_triggered, Qt::CTRL+Qt::Key_L);
    pmnu_user->addAction("&Detach this client", this, &MainWindow::on_actionCloseClient_triggered, Qt::CTRL+Qt::Key_E);

    QMenu* adminSuЬMenu = new QMenu("&Admin", pmnu_);
    pmnu_->addMenu(adminSuЬMenu);
    adminSuЬMenu->addAction("&Block the client", this, &MainWindow::on_actionBlockClient_triggered,
                            Qt::CTRL+Qt::Key_B);
    adminSuЬMenu->addAction("&Unblock the client", this, &MainWindow::on_actionUnblockClient_triggered,
                            Qt::CTRL+Qt::Key_U);

    pmnu_->addSeparator();
    pmnu_->addAction("&Quit", this, &MainWindow::close, Qt::CTRL+Qt::Key_Q);

    menuBar_->addMenu(pmnu_);
    menuBar_->addMenu(pmnu_user);
    setMenuBar(menuBar_);
}

void MainWindow::on_actionOpenClient_triggered()
{    
    if (widget_->update_user()) {
        widget_->update_startScreen();
    }
}

void MainWindow::on_actionCloseClient_triggered()
{
    if (widget_->detach_user()) {
        QString none = "no user";
        widget_->update_curr_user(none);
        widget_->update_startScreen();

    }
}

void MainWindow::on_actionBlockClient_triggered()
{
    if (widget_->block_user()) {
        QString none = "no user";
        widget_->update_curr_user(none);
        widget_->update_startScreen();
    }
}

void MainWindow::on_actionUnblockClient_triggered()
{
    if (widget_->unblock_user()) {
        widget_->update_startScreen();
    }
}

