#include "MainWindow.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.init();//�Զ���ĳ�ʼ������
    w.show();

    return a.exec();
}
