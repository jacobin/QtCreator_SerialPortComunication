#include "InputPlainTextEdit.h"

InputPlainTextEdit::InputPlainTextEdit(QWidget* parent):QPlainTextEdit(parent),isEnterSend(true)
{

}

InputPlainTextEdit::~InputPlainTextEdit()
{

}

// �����Ƿ�س�������Ϣ
void InputPlainTextEdit::setIsEnterSend(bool b)
{
    isEnterSend = b;
}

//������Ӧ����
void InputPlainTextEdit::keyPressEvent(QKeyEvent *event)
{
    QPlainTextEdit::keyPressEvent(event);//������������������޷�����������༭
    int key = event->key();

    if(key == Qt::Key_Up)
        emit arrowMessage(1);
    if(key == Qt::Key_Down)
        emit arrowMessage(0);

    if(!isEnterSend)return;

    if(key == Qt::Key_Return || key == Qt::Key_Enter)//�ֱ��Ǵ�С���̵Ļس�
    {
        emit sendMessage();
    }
}



