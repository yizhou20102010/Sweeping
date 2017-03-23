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
    void mousePressEvent(QMouseEvent *event);
//    void paintEvent();

private:


public:
    int data;//0,-1,数量
    int state;//0,初始，-1，点开，1标记，2问号
    void buttonshow(void);
};

#endif // QMYPUSHBUTTON_H
