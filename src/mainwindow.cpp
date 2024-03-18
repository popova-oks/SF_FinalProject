#include "../headers/mainwindow.h"
#include "../headers/widget.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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
}

void MainWindow::add_items()
{
    QMenuBar *menuBar_ = new QMenuBar(this);
    menuBar_->setStyleSheet("color: red; font-size: 14pt; font-weight: bold;");

    QMenu *pmnu_ = new QMenu("&Menu");

    pmnu_->addAction("&Open another client", this, &MainWindow::on_actionOpenClient_triggered, Qt::CTRL+Qt::Key_O);
    pmnu_->addAction("&Close this client", this, &MainWindow::on_actionCloseThisClient_triggered, Qt::CTRL+Qt::Key_C);

    pmnu_->addSeparator();
    pmnu_->addAction("&Quit", this, &MainWindow::close, Qt::CTRL+Qt::Key_Q);

    menuBar_->addMenu(pmnu_);
    setMenuBar(menuBar_);
}

void MainWindow::on_actionOpenClient_triggered()
{
    auto result = widget_->update_user();
    if (result) {
       widget_->update_messages();
    }
}

void MainWindow::on_actionCloseThisClient_triggered()
{
    return;
}

