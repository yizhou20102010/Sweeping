#ifndef MINEFRAME_H
#define MINEFRAME_H

#include <QWidget>
#include "qmypushbutton.h"
#include <QGridLayout>
#include<vector>
#include <QMouseEvent>
using namespace std;

class MineFrame : public QWidget
{
    Q_OBJECT
public:
    explicit MineFrame(QWidget *parent = 0);

signals:
    void GameBegin(void);
    void GameOver(int flag);//1 success; -1 explode
    void MineFlag(int remark);

public slots:
    void onMouseLeftPress(QPoint pos);
    void onMouseRightPress(QPoint pos);
private:
    vector<QMyPushButton *>m_pbtnlist;
    QGridLayout *myGridlayout;
    void randomGen(void);
    int rownum, colnum;
    int minenum, showbtnnum;
    bool isFirstPress;
    void showblankaround(const int index);
public:
    void  ShowMineFrame(const int rnum=9, const int cnum=9, const int mnum=10);
};

#endif // MINEFRAME_H
