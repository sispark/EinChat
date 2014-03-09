#ifndef EINCLIENT_H
#define EINCLIENT_H
#include <QDialog>
#include <vector>
#include <iterator>
using std::vector;
//对应控件的前置声明类
class QLabel;
class QLineEdit;
class QPushButton;
//对话框类，在其中实现绝大部分逻辑功能
class EinClient : public QDialog {
    Q_OBJECT
public:
    EinClient(QWidget* p_parent = 0);

private:
    //读取文件，对内容进行处理并保存在相应的数据存储结构中
    void ReadFile(QString&, vector<QString>&, vector<QString>&);
    //将数据存储结构中内容写入对应文件 
    void WriteFile(QString&, vector<QString>&);
    //判断读取的文件行是否应该写入文件
    bool NeedToInsertLine(QString&, vector<QString>&);
    //警告信息
    void ErrorMessage(int num);

private slots:
    //各按钮对应的槽
    void ChooseClicked1();
    void ChooseClicked2();
    void ProcessClicked();
    void EnableProcessButton();

private:
    //对话框中各控件
    QLabel* p_label1;
    QLabel* p_label2;
    QLineEdit* p_line_edit1;
    QLineEdit* p_line_edit2;
    QPushButton* p_choose_button1;
    QPushButton* p_choose_button2;
    QPushButton* p_process_button;
    //存储可以读取的两个文件的文件名信息
    QString file_name1;
    QString file_name2;
};

#endif
