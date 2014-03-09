#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "EinClient.h"

//主窗口类
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();

private:
    //主窗口上的对话框
    EinClient* p_ein_client;
};

#endif
