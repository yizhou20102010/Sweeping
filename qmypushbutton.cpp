#include "qmypushbutton.h"
#include <QDebug>
QMyPushButton::QMyPushButton(QWidget *parent) : QPushButton(parent)
{
    this->setStyleSheet("QPushButton{background-image: url(:/image/figure/back0.ico); \
                                       border-style:outset;border: 1px groove gray;border-radius: 1px;}"
                                    "QPushButton:hover{background-image: url(:/image/figure/back1.ico)}");
}

void QMyPushButton::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        emit mouseLeftPressPos(this->pos());
    }
    else if(event->buttons() & Qt::RightButton)
    {
        emit mouseRightPressPos(this->pos());
    }
}

void QMyPushButton::buttonshow()
{
    switch (state) {
    case -2:
        this->setStyleSheet("QPushButton{background-image: url(:/image/figure/mine.ico); border-style:inset;\
                                                            border: 1px groove gray; font-size:18px; font-family: Arial}");
        break;
    case -1:
        this->setStyleSheet("QPushButton{background-image: url(:/image/figure/back.ico); border-style:inset;\
                                                            border: 1px groove gray; font-size:18px; font-family: Arial}");
        break;
    case 0:
        this->setStyleSheet("QPushButton{background-image: url(:/image/figure/back0.ico); \
                                           border-style:outset;border: 1px groove gray;border-radius: 1px;}"
                                        "QPushButton:hover{background-image: url(:/image/figure/back1.ico)}");
        break;
    case 1:
        this->setStyleSheet("QPushButton{background-image: url(:/image/figure/flag0.ico); \
                    border-style:outset;border: 1px groove gray;border-radius: 1px;}"
                    "QPushButton:hover{background-image: url(:/image/figure/flag1.ico)}");
        break;
    case 2:
        this->setStyleSheet("QPushButton{background-image: url(:/image/figure/question0.ico); \
                           border-style:outset;border: 1px groove gray;border-radius: 1px;}"
                          "QPushButton:hover{background-image: url(:/image/figure/question1.ico)}");
        break;
    default:
        break;
    }
}
