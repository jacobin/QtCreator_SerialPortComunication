#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "SerialPortThread.h"
#include <QMessageBox>
//���캯��
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),isEnterSend(true),isAutoEnter(true),historyIterator(inputHistory.end()),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serialPortThread = new SerialPortThread();
}

MainWindow::~MainWindow()
{
    delete ui;
    if(serialPortThread->isRunning())
    {
        serialPortThread->setIsEnd(true);
        serialPortThread->wait();//qt��wait������join()
    }
    delete serialPortThread;
}
//�Զ���ĳ�ʼ������
void MainWindow::init()
{
    connect(serialPortThread,SIGNAL(serialPortOpenStatus(int)),this,SLOT(serialPortOpenStatus(int)));
    connect(serialPortThread,SIGNAL(serialPortReceivedData(QByteArray)),this,SLOT(serialPortReceivedData(QByteArray)));
    connect(ui->inputPlainTextEdit,SIGNAL(sendMessage()),this,SLOT(sendMessage()));
    connect(ui->inputPlainTextEdit,SIGNAL(arrowMessage(int)),this,SLOT(arrowMessage(int)));
}

//���մ����Ƿ�򿪵Ĳ�
void MainWindow::serialPortOpenStatus(int status)
{
    switch(status)
    {
    case -1://����ǵ���򿪰�ť������ʧ�ܵ���Ӧ
    {
        ui->onOffSerialPortButton->setText(QStringLiteral("�򿪴���"));
        ui->serialPortComboBox->setEnabled(true);
        ui->baudRateComboBox->setEnabled(true);
        ui->parityComboBox->setEnabled(true);
        ui->dataBitsComboBox->setEnabled(true);
        ui->stopBitsComboBox->setEnabled(true);
        QMessageBox::warning(NULL, QStringLiteral("����"), QStringLiteral("���ںŲ����ڻ��߱���������ռ��!"), QMessageBox::Ok, QMessageBox::Ok);
        break;
    }
    case 0://�����رմ���
    {
        ui->onOffSerialPortButton->setText(QStringLiteral("�򿪴���"));
        ui->serialPortComboBox->setEnabled(true);
        ui->baudRateComboBox->setEnabled(true);
        ui->parityComboBox->setEnabled(true);
        ui->dataBitsComboBox->setEnabled(true);
        ui->stopBitsComboBox->setEnabled(true);
        break;
    }
    case 1://�ɹ��򿪴���
    {
        ui->onOffSerialPortButton->setText(QStringLiteral("�رմ���"));
        ui->serialPortComboBox->setEnabled(false);
        ui->baudRateComboBox->setEnabled(false);
        ui->parityComboBox->setEnabled(false);
        ui->dataBitsComboBox->setEnabled(false);
        ui->stopBitsComboBox->setEnabled(false);
        break;
    }
    default:
        break;

    }
}
//���մ����̴߳��������ݵĲ�
void MainWindow::serialPortReceivedData(QByteArray receivedData)
{
    showString.append(receivedData);
    ui->textBrowser->clear();
    ui->textBrowser->append(showString);
}
//���������س�������Ϣ�Ĳ�
void MainWindow::sendMessage()
{
    if(!serialPortThread->isRunning())return;//��������߳�û�����У�����������
    QString sendStr = ui->inputPlainTextEdit->toPlainText();
    inputHistory.push_back(sendStr.trimmed());
    historyIterator = inputHistory.end();//ÿһ�η������ݣ���Ҫ������end()
    ui->inputPlainTextEdit->clear();
    serialPortThread->setSendData(sendStr.toUtf8());//QByteArray()
    serialPortThread->setSendFlag(true);
}
//������������¼�ͷ�Ĳ�
void MainWindow::arrowMessage(int arrow)
{
    if(inputHistory.isEmpty())
        return;
    if(arrow == 1)//up
    {
        historyIterator--;
        if(historyIterator == inputHistory.begin() - 1)
            historyIterator = inputHistory.end() - 1;
    }
    if(arrow == 0)//down
    {
        if(historyIterator == inputHistory.end())
            historyIterator = inputHistory.begin();
        else if(historyIterator == inputHistory.end() - 1)
            historyIterator = inputHistory.begin();
        else
            historyIterator++;
    }

    ui->inputPlainTextEdit->clear();
    ui->inputPlainTextEdit->appendPlainText(*historyIterator);//��ʾ��ʷ����
}
//���ش��ڰ�ť�Ĳ�
void MainWindow::on_onOffSerialPortButton_clicked()
{
    //����������У���رմ����߳�
    if(serialPortThread->isRunning())
    {
        serialPortThread->setIsEnd(true);
    }
    else//�򿪴����߳�
    {//�������ô��ڲ���
        serialPortThread->setSerialPortNumber(ui->serialPortComboBox->currentText());

        serialPortThread->setSerialPortBaudRate(ui->baudRateComboBox->currentText().toInt());

        QSerialPort::Parity parity;
        switch(ui->parityComboBox->currentIndex())
        {
        case 0:
            parity = QSerialPort::Parity::NoParity;
            break;
        case 1:
            parity = QSerialPort::Parity::EvenParity;
            break;
        case 2:
            parity = QSerialPort::Parity::OddParity;
            break;
        case 3:
            parity = QSerialPort::Parity::SpaceParity;
            break;
        case 4:
            parity = QSerialPort::Parity::MarkParity;
            break;
        default:
            parity = QSerialPort::Parity::UnknownParity;
            break;
        }
        serialPortThread->setSerialPortParity(parity);

        QSerialPort::DataBits dataBits;
        switch(ui->dataBitsComboBox->currentIndex())
        {
        case 0:
            dataBits = QSerialPort::DataBits::Data5;
            break;
        case 1:
            dataBits = QSerialPort::DataBits::Data6;
            break;
        case 2:
            dataBits = QSerialPort::DataBits::Data7;
            break;
        case 3:
            dataBits = QSerialPort::DataBits::Data8;
            break;

        default:
            dataBits = QSerialPort::DataBits::UnknownDataBits;
            break;
        }
        serialPortThread->setSerialPortDataBits(dataBits);

        QSerialPort::StopBits stopBits;
        switch(ui->dataBitsComboBox->currentIndex())
        {
        case 0:
            stopBits = QSerialPort::StopBits::OneStop;
            break;
        case 1:
            stopBits = QSerialPort::StopBits::OneAndHalfStop;
            break;
        case 2:
            stopBits = QSerialPort::StopBits::TwoStop;
            break;

        default:
            stopBits = QSerialPort::StopBits::UnknownStopBits;
            break;
        }
        serialPortThread->setSerialPortStopBits(stopBits);
        serialPortThread->setIsEnd(false);//����ֹͣ��־Ϊfalse
        serialPortThread->start();//��ʼ�߳�
    }

}
//������Ϣ��ť�Ĳ�
void MainWindow::on_sendMessageButton_clicked()
{
    if(!serialPortThread->isRunning())return;//��������߳�û�����У�����������
    QString sendStr = ui->inputPlainTextEdit->toPlainText();
    inputHistory.push_back(sendStr.trimmed());//�����ʷָ��
    historyIterator = inputHistory.end();
    ui->inputPlainTextEdit->clear();//��������
    if(isAutoEnter)sendStr += "\n";//����Զ�����
    serialPortThread->setSendData(sendStr.toUtf8());//QByteArray()
    serialPortThread->setSendFlag(true);
}

//���ûس����͵ļ���Ĳ�
void MainWindow::on_enterSendCheckBox_clicked()
{
    isEnterSend = ui->enterSendCheckBox->isChecked();
    ui->inputPlainTextEdit->setIsEnterSend(isEnterSend);
}
//���÷��͵������Զ����еļ���Ĳ�
void MainWindow::on_autoEnterCheckBox_clicked()
{
    isAutoEnter = ui->autoEnterCheckBox->isChecked();
}
//�����ʾ��Ϣ��ť�Ĳ�
void MainWindow::on_clearShowButton_clicked()
{
    ui->textBrowser->clear();
    showString.clear();
}

//���������Ϣ��ť�Ĳ�
void MainWindow::on_clearInputButton_clicked()
{
    ui->inputPlainTextEdit->clear();
}
