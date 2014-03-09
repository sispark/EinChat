#include <QtGui>
#include "EinClient.h"
#include <iostream>

//对话框的构造函数
EinClient::EinClient(QWidget* p_parent)
    : QDialog(p_parent), mesg_disp(""), mesg_send("") {
    //生成标签与文本框
    p_label_disp = new QLabel(tr("&Disp"));
    p_label_send = new QLabel(tr("&Mesg"));
    p_mesg_disp = new QTextEdit;
    p_mesg_send = new QLineEdit;
    p_mesg_disp->setText(mesg_disp);
    p_mesg_send->setText(mesg_send);
    //将对应文本框设定为标签的伙伴(buddy)
    p_label_disp->setBuddy(p_mesg_disp);
    p_label_send->setBuddy(p_mesg_send);

    //生成发送按钮
    p_send_button = new QPushButton(tr("&Send"));
    //将发送按钮设定为无效并设定鼠标停留时的提示信息
    p_send_button->setEnabled(false);
    p_send_button->setToolTip(tr("Unavailable Now!"));

    //文本框内容变化时更新进程按钮状态
    connect(p_mesg_send, SIGNAL(textChanged(const QString&)),
            this, SLOT(EnableSendButton()));

    //点击进程按钮时执行对应的操作
    connect(p_send_button, SIGNAL(clicked()),
            this, SLOT(SendClicked()));

    //布局第一行控件(显示标签-显示框，发送标签-发送框)
    QGridLayout* p_top_layout = new QGridLayout;
    p_top_layout->addWidget(p_label_disp, 0, 0);
    p_top_layout->addWidget(p_mesg_disp, 0, 1);
    p_top_layout->addWidget(p_label_send, 1, 0);
    p_top_layout->addWidget(p_mesg_send, 1, 1);

    //布局第二行控件(发送按钮一个，用弹簧控制位置)
    QHBoxLayout* p_bottom_layout = new QHBoxLayout;
    p_bottom_layout->addStretch(12);
    p_bottom_layout->addWidget(p_send_button);
    p_bottom_layout->addStretch(1);

    //布局主对话框(两行控件，垂直布局)
    QVBoxLayout* p_main_layout = new QVBoxLayout;
    p_main_layout->addLayout(p_top_layout);
    p_main_layout->addLayout(p_bottom_layout);

    //设定主对话框
    setLayout(p_main_layout);
}

//点击消息按钮，读取要发送的消息
void EinClient::SendClicked() {
    //读取要发送的消息
    mesg_send = p_mesg_send->text();
    mesg_disp = mesg_send;
    p_mesg_disp->setText(mesg_disp);
}

//根据消息文本框的内容，更新进程按钮状态
void EinClient::EnableSendButton() {
    //消息文本框不为空
    if(!p_mesg_send->text().isEmpty()) {
        //进程按钮有效，关闭提示信息
        p_send_button->setEnabled(true);
        p_send_button->setToolTip(tr(""));
    } else {//消息文本框为空
        //进程按钮无效，能够显示提示信息
        p_send_button->setEnabled(false);
        p_send_button->setToolTip(tr("Please input message!"));
    }
}

//根据错误种类弹出错误提示框
//1：两个文件是同一个
//2：文件不存在
//3：文件无法打开
//其他错误
void EinClient::ErrorMessage(int num) {
    QString error_info;
    switch(num) {
    case 1:
        error_info = "Two files are the same!";
        break;
    case 2:
        error_info = "Files are not exist!";
        break;
    case 3:
        error_info = "File can't be opened!";
        break;
    default:
        error_info = "Other errors!";
        break;
    }

    QMessageBox::critical(NULL, "Error",  
        error_info, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes); 
}

