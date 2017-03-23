////////////////////////////////////////////////按钮
///
#ifndef QMYPUSHBUTTON_H
#define QMYPUSHBUTTON_H

#include <QPushButton>
#include <QMouseEvent>
class QMyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit QMyPushButton(QWidget *parent = 0);

signals:
    void mouseLeftPressPos(const QPoint pos);
    void mouseRightPressPos(const QPoint pos);
public slots:
    void mousePressEvent(QMouseEvent *event);//鼠标事件，左键、右键

private:


public:
    int data;//该按钮的0,-1,数量
    int state;//该按钮当前的状态，0,初始，-1，点开，1标记，2问号
    void buttonshow(void);//根据state显示按钮
};

#endif // QMYPUSHBUTTON_H
