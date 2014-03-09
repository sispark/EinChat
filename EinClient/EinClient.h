#ifndef EINCLIENT_H
#define EINCLIENT_H
#include <QDialog>

//for mesg send 0
#include <iostream>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <iostream>

#define SERV_PORT        9877           /* TCP and UDP */
#define SA  struct sockaddr
#define MAXLINE     4096    /* max text line length */

extern const char* local_ip;
void SendMesg(const char* send_mesg);
ssize_t writen(int fd, const void* vptr, size_t n);
ssize_t my_read(int fd, char* ptr);
ssize_t readline(int fd, void* vptr, size_t maxlen);
//for mesg send 1

//对应控件的前置声明类
class QLabel;
class QTextEdit;
class QLineEdit;
class QPushButton;
//对话框类，在其中实现绝大部分逻辑功能
class EinClient : public QDialog {
    Q_OBJECT
public:
    EinClient(QWidget* p_parent = 0);

private:
    //警告信息
    void ErrorMessage(int num);

private slots:
    //各按钮对应的槽
    void SendClicked();
    void EnableSendButton();

private:
    //对话框中各控件
    QLabel* p_label_disp;
    QLabel* p_label_send;
    QTextEdit* p_mesg_disp;
    QTextEdit* p_mesg_send;
    QPushButton* p_send_button;
    //存储用户要发送与要显示的消息
    QString mesg_disp;
    QString mesg_send;
};

#endif
