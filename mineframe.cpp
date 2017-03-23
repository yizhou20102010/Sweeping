#include "mineframe.h"
#include <QLayout>
#include <QDebug>
#include <QtGlobal>
#include <QTime>
MineFrame::MineFrame(QWidget *parent) : QWidget(parent)
{
    myGridlayout=new QGridLayout;
    myGridlayout->setHorizontalSpacing(0);
    myGridlayout->setVerticalSpacing(0);
    myGridlayout->setContentsMargins(0,0,0,0);
    isFirstPress=true;
    showbtnnum=0;
}


void MineFrame::onMouseLeftPress(QPoint pos)
{
    if(isFirstPress)//开局计时
    {
        isFirstPress=false;
        emit GameBegin();
    }

    //根据鼠标位置，计算当前控件
    int index=pos.y()/32*colnum+pos.x()/32;
    if(index>=m_pbtnlist.size())return;

    QMyPushButton *btn=m_pbtnlist[index];
    if(btn->data==-1)//explode
    {
        btn->state=-2;
        btn->buttonshow();
        //展开所有位置
        for(int i=0;i<m_pbtnlist.size();i++)
        {
            btn=m_pbtnlist[i];
            if(btn->data==-1)
            {
                btn->state=-2;
                btn->buttonshow();
            }
        }
        emit GameOver(-1);
    }
    else if(btn->state!=-1)//not show
    {
        showblankaround(index);
        if(rownum*colnum-showbtnnum==minenum)
            emit GameOver(1);
    }
}

void MineFrame::onMouseRightPress(QPoint pos)
{
    if(isFirstPress)//开局计时
    {
        isFirstPress=false;
        emit GameBegin();
    }
    int index=pos.y()/32*colnum+pos.x()/32;
    if(index>=m_pbtnlist.size())return;

    QMyPushButton *btn=m_pbtnlist[index];

    //右键标记，发送剩余雷数的计算
    if(btn->state!=-1&&btn->state!=-2)
    {
        if(btn->state==1)emit MineFlag(1);
        btn->state=(btn->state+1)%3;
        btn->buttonshow();
        if(btn->state==1)emit MineFlag(-1);
    }
}

void MineFrame::randomGen()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int k=0, row, col;
    while(k<minenum) //随机生成分布图
    {
        row=qrand()%rownum;
        col=qrand()%colnum;
        if(m_pbtnlist[row*colnum+col]->data!=-1)
        {
            m_pbtnlist[row*colnum+col]->data=-1;
            k++;
            int i0,i1,j0,j1;
            i0 = 0 > row-1 ? 0 : row-1;
            i1 = row+1 < rownum-1 ? row+1 : rownum-1;
            j0 = 0 > col-1 ? 0 : col-1;
            j1 = col+1 < colnum-1 ? col+1 : colnum-1;
            for(int i=i0;i<=i1;i++)
                for(int j=j0;j<=j1;j++)
                    if(m_pbtnlist[i*colnum+j]->data!=-1)
                        m_pbtnlist[i*colnum+j]->data++;
        }
    }
}

void MineFrame::showblankaround(const int index)
{
    if(index<0||index>m_pbtnlist.size()-1)return;
    QMyPushButton *btn=m_pbtnlist[index];
    if(btn->data==-1||btn->state==-1)return;

    showbtnnum++;
    btn->state=-1;
    btn->buttonshow();
    if(btn->data!=0)
        btn->setText(QString("%1").arg(btn->data));
    else
    {
        showblankaround(index-1);
        showblankaround(index+1);
        showblankaround(index-colnum);
        showblankaround(index-colnum-1);
        showblankaround(index-colnum+1);
        showblankaround(index+colnum);
        showblankaround(index+colnum-1);
        showblankaround(index+colnum+1);
    }

}

void MineFrame::ShowMineFrame(const int rnum, const int cnum, const int mnum)
{
    rownum=rnum;
    colnum=cnum;
    minenum=mnum;

    QMyPushButton *btn;
    m_pbtnlist.clear();
    for(int i=0;i<rnum;i++)
        for(int j=0;j<cnum;j++)
        {
            btn=new QMyPushButton;
            btn->data=0;
            btn->state=0;
            m_pbtnlist.push_back(btn);            
        }

    for(int i=0;i<rnum;i++)
        for(int j=0;j<cnum;j++)
        {
            btn=m_pbtnlist[i*cnum+j];
            btn->setMaximumSize(32,32);
            btn->setMinimumSize(32,32);
            myGridlayout->addWidget(btn,i,j);
            connect(btn, SIGNAL(mouseLeftPressPos(QPoint)), this,SLOT(onMouseLeftPress(QPoint)));
            connect(btn, SIGNAL(mouseRightPressPos(QPoint)), this,SLOT(onMouseRightPress(QPoint)));
        }
    this->setLayout(myGridlayout);
    randomGen();
}
