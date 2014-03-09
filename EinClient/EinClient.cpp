#include <QtGui>
#include "EinClient.h"
#include <iostream>
using std::vector;
//对话框的构造函数
EinClient::EinClient(QWidget* p_parent)
    : QDialog(p_parent), file_name1(""), file_name2("") {
    //生成标签与文本框
    p_label1 = new QLabel(tr("File&1"));
    p_label2 = new QLabel(tr("File&2"));
    p_line_edit1 = new QLineEdit;
    p_line_edit2 = new QLineEdit;
    p_line_edit1->setText(file_name1);
    p_line_edit2->setText(file_name2);
    //将对应文本框设定为标签的伙伴(buddy)
    p_label1->setBuddy(p_line_edit1);
    p_label2->setBuddy(p_line_edit2);

    //生成选择按钮与进程按钮
    p_choose_button1 = new QPushButton(tr("&Choose"));
    p_choose_button2 = new QPushButton(tr("C&hoose"));
    p_process_button = new QPushButton(tr("&Process"));
    //将进程按钮设定为无效并设定鼠标停留时的提示信息
    p_process_button->setEnabled(false);
    p_process_button->setToolTip(tr("Unavailable Now!"));

    //文本框内容变化时更新进程按钮状态
    connect(p_line_edit1, SIGNAL(textChanged(const QString&)),
            this, SLOT(EnableProcessButton()));
    connect(p_line_edit2, SIGNAL(textChanged(const QString&)),
            this, SLOT(EnableProcessButton()));

    //点击选择按钮与进程按钮时执行对应的操作
    connect(p_choose_button1, SIGNAL(clicked()),
            this, SLOT(ChooseClicked1()));
    connect(p_choose_button2, SIGNAL(clicked()),
            this, SLOT(ChooseClicked2()));
    connect(p_process_button, SIGNAL(clicked()),
            this, SLOT(ProcessClicked()));

    //布局第一行控件(标签，文本框，选择按钮各一个，水平布局)
    QHBoxLayout* p_top_layout1 = new QHBoxLayout;
    p_top_layout1->addWidget(p_label1);
    p_top_layout1->addWidget(p_line_edit1);
    p_top_layout1->addWidget(p_choose_button1);

    //布局第二行控件(标签，文本框，选择按钮各一个，水平布局)
    QHBoxLayout* p_top_layout2 = new QHBoxLayout;
    p_top_layout2->addWidget(p_label2);
    p_top_layout2->addWidget(p_line_edit2);
    p_top_layout2->addWidget(p_choose_button2);

    //布局第三行控件(进程按钮一个，用弹簧控制位置)
    QHBoxLayout* p_bottom_layout = new QHBoxLayout;
    p_bottom_layout->addStretch(12);
    p_bottom_layout->addWidget(p_process_button);
    p_bottom_layout->addStretch(1);

    //布局主对话框(三行控件，垂直布局)
    QVBoxLayout* p_main_layout = new QVBoxLayout;
    p_main_layout->addLayout(p_top_layout1);
    p_main_layout->addLayout(p_top_layout2);
    p_main_layout->addLayout(p_bottom_layout);

    //设定主对话框
    setLayout(p_main_layout);
}

//点击选择按钮1，弹出文件选择框，选择文件后内容填入文本框1
void EinClient::ChooseClicked1() {
    file_name1 = QFileDialog::getOpenFileName(this,
            tr("Open File"), "", tr("Allfile(*.*)"));
    if(!file_name1.isNull()) {
        p_line_edit1->setText(file_name1);
    }
}

//点击选择按钮2，弹出文件选择框，选择文件后内容填入文本框2
void EinClient::ChooseClicked2() {
    file_name2 = QFileDialog::getOpenFileName(this,
            tr("Open File"), "", tr("Allfile(*.*)"));
    if(!file_name2.isNull()) {
        p_line_edit2->setText(file_name2);
    }
}

//点击进程按钮，读取文件，备份，删除重复行与空行
void EinClient::ProcessClicked() {
    //读取文件名相关信息
    file_name1 = p_line_edit1->text();
    file_name2 = p_line_edit2->text();
    //如果两个文件都存在
    if(QFile::exists(file_name1) && QFile::exists(file_name2)) {
        if(file_name1 == file_name2) {
            //两个文件相同
            ErrorMessage(1);
            return;
        }
        //备份两个文件
        QFile::copy(file_name1, file_name1 + ".bak");
        QFile::copy(file_name2, file_name2 + ".bak");
        //分别用来存取两个文件的数据结构
        vector<QString> file_line1, file_line2;
        //分别读取两个文件，删除空行与重复行，并将内容存入fileLine1和fileLine2中
        ReadFile(file_name1, file_line1, file_line2);
        ReadFile(file_name2, file_line2, file_line1);
        //将处理过的文件内容写入原文件
        WriteFile(file_name1, file_line1);
        WriteFile(file_name2, file_line2);
    } else {
        //文件不存在
        ErrorMessage(2);
    }
}

//读取文件内容，并处理和存入对应数据结构
//输入：fileName->要读取的文件名信息
//      fileLineStore->读取的文件内容存放的数据结构
//      fileLineRefer->存放另一个文件内容的数据结构
void EinClient::ReadFile(QString& file_name,
        vector<QString>& file_line_store, vector<QString>& file_line_refer) {
    QFile file(file_name);
    //打开文件
    if(file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        QString line;
        //按行读取文件内容
        while(!stream.atEnd()) {
            line = stream.readLine();
            //qDebug()<<line;
            //符合存储要求：非空行，且在两个文件中都无重复行
            if(NeedToInsertLine(line, file_line_store) &&
                    NeedToInsertLine(line, file_line_refer)) {
                //qDebug()<<"Need to Insert:"<<line;
                //存入对应数据结构
                file_line_store.push_back(line);
            }
        }
        //关闭文件
        file.close();
    } else {
        //文件无法打开
        ErrorMessage(3);
    }
}

//判断本行内容是否符合存储要求
//输入：line->供判断的内容行
//      fileLine->存有文件内容行的数据结构
//输出：true(符合存储要求), false(不符合存储要求)
bool EinClient::NeedToInsertLine(QString& line,
        vector<QString>& file_line) {
    //空行不符合
    if(line.isEmpty()) {
        return false;
    }
    //存储数据结构为空符合
    if(file_line.empty()) {
        return true;
    }
    //用迭代器遍历 
    vector<QString>::iterator find_point;
    for(find_point = file_line.begin(); find_point < file_line.end(); find_point++) {
        //若已存在同样内容行，不符合存储要求，且删除此内容行
        if(line == *find_point) {
            file_line.erase(find_point);
            return false;
        }
    }
    return true;
}

//将处理过的文件内容写入原文件
//输入：fileName->文件名信息
//      fileLine->已经处理过的对应文件内容
void EinClient::WriteFile(QString& file_name,
        vector<QString>& file_line) {
    //打开原文件
    QFile file(file_name);
    if(file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        //用迭代器遍历
        vector<QString>::iterator find_point;
        for(find_point = file_line.begin(); find_point < file_line.end(); find_point++) {
            //将内容行写入原文件
            stream<<*find_point<<"\n";
        }
        //关闭原文件
        file.close();
    } else {
        //文件无法打开
        ErrorMessage(3);
    }
}

//根据两个文本框的内容，更新进程按钮状态
void EinClient::EnableProcessButton() {
    //两个文本框都不为空
    if((!p_line_edit1->text().isEmpty())
            && (!p_line_edit2->text().isEmpty())) {
        //进程按钮有效，关闭提示信息
        p_process_button->setEnabled(true);
        p_process_button->setToolTip(tr(""));
    } else {//至少有一个文本框为空
        //进程按钮无效，能够显示提示信息
        p_process_button->setEnabled(false);
        p_process_button->setToolTip(tr("Unavailable Now!"));
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

