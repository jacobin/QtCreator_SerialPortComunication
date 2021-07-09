#ifndef SERIALPORTTHREAD_H
#define SERIALPORTTHREAD_H
#include <QThread>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class SerialPortThread:public QThread
{
    Q_OBJECT
public:
    SerialPortThread();//���캯��
    ~SerialPortThread();//��������
    void setIsEnd(bool b);//�����߳��Ƿ�ֹͣ��־
    bool getIsEnd();//��ȡ�߳��Ƿ�ֹͣ�ı�־
    void setSerialPortNumber(const QString & portNum);//���ô��ں�
    void setSerialPortBaudRate(int r);//���ò�����
    void setSerialPortParity(QSerialPort::Parity p);//����У��λ
    void setSerialPortDataBits(QSerialPort::DataBits d);//��������λ
    void setSerialPortStopBits(QSerialPort::StopBits s);//����ֹͣλ

    void setSendFlag(bool b);//���÷�����Ϣ�ı�־
    bool getSendFlag();//��ȡ������Ϣ�ı�־
    void setSendData(QByteArray send);//���÷�������
    bool getSendData();//��ȡ��������
signals:
    void serialPortOpenStatus(int status);//���ʹ��ڴ�״̬���ź�
    void serialPortReceivedData(QByteArray receivedData);//���ʹ��ڽ��յ������ݵ��ź�
protected:
    void run();//�߳�run����
private:
    bool isEnd;//�߳�ֹͣ��־
    QByteArray receivedData;//���յ�����
    QByteArray sendData;//���͵�����
    bool sendFlag;//���ͱ�־
    QString serialPortNumber;//���ں�
    int baudRate;//������
    QSerialPort::Parity parity;//У��λ
    QSerialPort::DataBits dataBits;//����λ
    QSerialPort::StopBits stopBits;//ֹͣλ
};

#endif // SERIALPORTTHREAD_H
