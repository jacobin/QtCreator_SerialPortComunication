/*
 * ����ļ��������������࣬�����˰����¼���Ӧ��
*/
#ifndef INPUTPLAINTEXTEDIT_H
#define INPUTPLAINTEXTEDIT_H
#include "QPlainTextEdit"

class InputPlainTextEdit:public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit InputPlainTextEdit(QWidget* parent = 0);
    ~InputPlainTextEdit();
    void keyPressEvent(QKeyEvent * event);//������Ӧ����

    void setIsEnterSend(bool b);//�����Ƿ�س�������Ϣ

signals:
    void sendMessage();//���ͷ�����Ϣ���źŸ�������
    void arrowMessage(int array);//���͵�����¼�ͷ���źŸ�������

private:
    bool isEnterSend;//�س�������Ϣ��־��true��ʾ�س�����

};

#endif // INPUTPLAINTEXTEDIT_H
