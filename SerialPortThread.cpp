#include "SerialPortThread.h"
#include <iostream>
SerialPortThread::SerialPortThread():isEnd(false),serialPortNumber("COM1"),
    baudRate(9600),parity(QSerialPort::NoParity),dataBits(QSerialPort::Data8),
    stopBits(QSerialPort::OneStop)
{

}

SerialPortThread::~SerialPortThread()
{

}
//���ô��ں�
void SerialPortThread::setSerialPortNumber(const QString & portNum)
{
    serialPortNumber = portNum;
}
//���ò�����
void SerialPortThread::setSerialPortBaudRate(int r)
{
    baudRate = r;
}
//����У��λ
void SerialPortThread::setSerialPortParity(QSerialPort::Parity p)
{
    parity = p;
}
//��������λ
void SerialPortThread::setSerialPortDataBits(QSerialPort::DataBits d)
{
    dataBits = d;
}
//����ֹͣλ
void SerialPortThread::setSerialPortStopBits(QSerialPort::StopBits s)
{
    stopBits = s;
}

void SerialPortThread::run()
{
    //�򿪴���
    QSerialPort *serialPort = new QSerialPort;
    serialPort->setPortName(serialPortNumber);
    serialPort->setBaudRate(baudRate);
    serialPort->setParity(parity);
    serialPort->setDataBits(dataBits);
    serialPort->setStopBits(stopBits);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if(!serialPort->open(QIODevice::ReadWrite))
    {
        //���ڴ򿪲��ɹ�
        isEnd = true;
        emit serialPortOpenStatus(-1);
        delete serialPort;//������Դ
        return;
    }
    else
    {//�򿪳ɹ�
        isEnd = false;
        emit serialPortOpenStatus(1);
    }

    while(!isEnd)
    {//������
        if(serialPort->waitForReadyRead(50))
        {
           receivedData = serialPort->readAll();
           std::cout<<"receive data:"<<receivedData.toStdString()<<std::endl;
           emit serialPortReceivedData(receivedData);
        }
        //���������Ҫ����
        if(sendFlag)
        {//��������
            serialPort->write(sendData);
            sendFlag = false;
            if(serialPort->waitForBytesWritten(50))//���ջ�Ӧ
            {//����Ӧȫ������
                receivedData = serialPort->readAll();
                while (serialPort->waitForReadyRead(100))
                    receivedData += serialPort->readAll();
                emit serialPortReceivedData(receivedData);
                std::cout<<"receive data:"<<receivedData.toStdString()<<std::endl;
            }
        }
    }
    //�رմ���
    if(serialPort->isOpen())
        serialPort->close();
    isEnd = true;
    emit serialPortOpenStatus(0);
    delete serialPort;//������Դ
}
//��ȡ�߳��Ƿ�ֹͣ�ı�־
bool SerialPortThread::getIsEnd()
{
    return isEnd;
}
//�����߳��Ƿ�ֹͣ��־
void SerialPortThread::setIsEnd(bool b)
{
    isEnd = b;
}
//���÷�����Ϣ�ı�־
void SerialPortThread::setSendFlag(bool b)
{
    sendFlag = b;
}
//��ȡ������Ϣ�ı�־
bool SerialPortThread::getSendFlag()
{
    return sendFlag;
}
//���÷�������
void SerialPortThread::setSendData(QByteArray send)
{
    sendData = send;
}
