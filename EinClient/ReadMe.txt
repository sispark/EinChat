工程说明：

  本工程是一个简单的文件处理程序。用于选择两个文本文件，将其备份，读取两个文件内容，删除空行和重复行并写入原文件。
  
  关于此工程，具体内容如下：
  
  一：目录组织结构
  EinClient
  ├── file1.txt             ->输入文件1，为题中例子
  ├── file2.txt             ->输入文件2，为题中例子
  ├── MainWindow.cpp        ->主窗口类的实现
  ├── MainWindow.h          ->主窗口类的定义
  ├── Makefile              ->makefile文件，为qmake自动生成
  ├── ReadMe.txt            ->对本工程的说明文件
  ├── EinClient             ->最终生成的可执行文件
  ├── EinClient.cpp         ->主对话框类的实现
  ├── EinClient.h           ->主对话框类的定义
  ├── EinClient.pro         ->QT工程文件，qmake自动生成
  └── TestMainWindow.cpp    ->测试文件(main函数)

  二：开发环境搭建
  电脑安装的是GNU/Linux Debian 7。由于Gnome3的桌面环境标题显示与传统样式不大相同，临时安装了xfce4桌面环境进行开发与测试。
  在Debian下搭建开发环境十分方便，在root终端执行如下命令：
  apt-get install qt4-dev-tools #开发包
  apt-get install qtcreator #IDE
  apt-get install qt4-doc #开发帮助文档
  apt-get install qt4-qtconfig #配置工具
  apt-get install qt4-demos #DEMO源码
  Qt与qmake的版本为：
  QMake version 2.01a
  Using Qt version 4.8.2 in /usr/lib/x86_64-linux-gnu
  gcc与g++版本为：
  gcc (Debian 4.7.2-5) 4.7.2
  g++ (Debian 4.7.2-5) 4.7.2

  三：工程编译
  采用的是qmake方式，在对应工程目录下执行如下命令：
  qmake -project #生成QT工程文件(projectName.pro)
  qmake ProjectName.pro #生成Makefile文件
  make #编译工程
  ./ProgramName #运行可执行文件
  
  四：参考资料
  主要资料：
  《C++.GUI.Qt.4编程(第二版)》，Jasmin Blanchette, Mark Summerfield著，电子工业出版社，主要参考了第二章，第三章，第四章

  《24小时学通Qt编程，Daniel》 Solin著，人民邮电出版社出版，因为里面是使用Qt3，与Qt4有较大差别，主要参考了第三学时与第四学时的理论部分

  http://blog.chinaunix.net/uid-27177626-id-3944473.html #对话框的一些实例

  http://blog.sina.com.cn/s/blog_687fabcb0101kd9b.html #窗口操作的一些知识

  http://www.cnblogs.com/ylan2009/archive/2012/05/06/2486606.html #文件对话框的一些知识

  http://www.360doc.com/content/11/0921/13/3989678_150081018.shtml #文件操作函数

  http://blog.chinaunix.net/uid-9787967-id-1988915.html #信号与槽的一些知识

  http://blog.csdn.net/haishengflying/article/details/7704866 #弹簧的用法

  http://blog.csdn.net/c05170519/article/details/6372069 #错误弹出框的用法

  http://www.cnblogs.com/rollenholt/archive/2012/05/22/2513764.html #窗口设置的方法

  本工程是在Debian7+Xfce4环境下开发与测试，未进行跨平台测试。

  以上
  2013.12.08

