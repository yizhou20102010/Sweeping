//////////////////////////////////////////////////////注释
/// 界面生成

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
    void onMouseLeftPress(QPoint pos);//响应鼠标左键信息
    void onMouseRightPress(QPoint pos);//响应鼠标右键信息
private:
    vector<QMyPushButton *>m_pbtnlist;//按钮列表
    QGridLayout *myGridlayout; //界面布局
    void randomGen(void);//根据行数、列数、雷数随机生成分布
    int rownum, colnum;//布局的行数和列数
    int minenum, showbtnnum;//总雷数，已翻转按钮个数
    bool isFirstPress;//启动标记
    void showblankaround(const int index);//显示索引为index的按钮
public:
    //根据行数、列数、雷数显示布局
    void  ShowMineFrame(const int rnum=9, const int cnum=9, const int mnum=10);
};

#endif // MINEFRAME_H
