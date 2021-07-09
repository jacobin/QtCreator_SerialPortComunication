#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
class SerialPortThread;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void init();//�Զ���ĳ�ʼ������

private slots:

    void serialPortOpenStatus(int status);//���մ����Ƿ�򿪵Ĳ�
    void serialPortReceivedData(QByteArray receivedData);//���մ����̴߳��������ݵĲ�
    void sendMessage();//���������س�������Ϣ�Ĳ�
    void arrowMessage(int arrow);//������������¼�ͷ�Ĳ�
    void on_onOffSerialPortButton_clicked();//���ش��ڰ�ť�Ĳ�
    void on_sendMessageButton_clicked();//������Ϣ��ť�Ĳ�
    void on_enterSendCheckBox_clicked();//���ûس����͵ļ���Ĳ�
    void on_autoEnterCheckBox_clicked();//���÷��͵������Զ����еļ���Ĳ�
    void on_clearShowButton_clicked();//�����ʾ��Ϣ��ť�Ĳ�
    void on_clearInputButton_clicked();//���������Ϣ��ť�Ĳ�

private:
    Ui::MainWindow *ui;//ui�ļ�
    SerialPortThread* serialPortThread;//�����߳�
    bool isEnterSend;//�Ƿ�س����͵ı�־
    bool isAutoEnter;//�Ƿ�������ʱ�Զ����еı�־
    QVector<QString> inputHistory;//������ʷ������
    QVector<QString>::iterator historyIterator;//ָ��ĳ����ʷ�����ַ���
    QString showString;//��ʾ���ַ���

};

#endif // MAINWINDOW_H
