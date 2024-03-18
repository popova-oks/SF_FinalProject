#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "widget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void add_items();
    bool createClient();

    Ui::MainWindow *ui;
    Widget *widget_;
    //QMenuBar *menuBar_;
    //QMenu* pmnu_;

private slots:
    void on_actionOpenClient_triggered();
    void on_actionCloseThisClient_triggered();
};
#endif // MAINWINDOW_H
