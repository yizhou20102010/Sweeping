#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QInputDialog>
#include <QStringList>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    plcdlayerout=new QHBoxLayout;
    m_timenumber = new QLineEdit;

    pnumlayerout= new QHBoxLayout;
    m_minenumber = new QLineEdit;

    pframe=NULL;
    phlayout = new QHBoxLayout;
    showFrame(16,16,40);

    timercount=0;
    m_timer = new QTimer;
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimerDone()));
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::showFrame(const int rnum, const int cnum, const int mnum)
{
    timercount=0;
    m_timenumber->setText(QString("%1").arg(timercount));

    rownum=rnum;
    colnum=cnum;
    minenum=mnum;

    this->setFixedSize(colnum*32+40,rownum*32+150);

    m_timenumber->setAlignment(Qt::AlignCenter);
    m_timenumber->setReadOnly(true);
    m_timenumber->setText("0");
    plcdlayerout->addWidget(m_timenumber);
    plcdlayerout->setContentsMargins(0,0,0,0);
    plcdlayerout->setMargin(0);
    ui->LCDWidget->setLayout(plcdlayerout);
    QRect m_rect=this->geometry();
    ui->LCDWidget->setGeometry(m_rect.width()-84,20,64,32);


    remainminenum=minenum;
    m_minenumber->setReadOnly(true);
    m_minenumber->setText(QString("%1").arg(remainminenum));
    m_minenumber->setAlignment(Qt::AlignCenter);
    pnumlayerout->addWidget(m_minenumber);
    pnumlayerout->setContentsMargins(0,0,0,0);
    pnumlayerout->setSpacing(0);
    ui->NumWidget->setLayout(pnumlayerout);
    ui->NumWidget->setGeometry(20,20, 64,32);


    //mine分布
    ui->MineWidget->setGeometry(20,80,colnum*32,rownum*32);
    if(pframe!=NULL)
    {
        disconnect(pframe, SIGNAL(GameBegin()), this, SLOT(onGameBegin()));
        disconnect(pframe, SIGNAL(GameOver(int)),this, SLOT(onGameOver(int)));
        disconnect(pframe, SIGNAL(MineFlag(int)), this, SLOT(onMineFlag(int)));
        delete pframe;
    }
    pframe = new MineFrame;
    phlayout->setContentsMargins(0,0,0,0);
    phlayout->setSpacing(0);
    phlayout->addWidget(pframe);
    pframe->ShowMineFrame(rownum, colnum, minenum);
    ui->MineWidget->setLayout(phlayout);
    connect(pframe, SIGNAL(GameBegin()), this, SLOT(onGameBegin()));
    connect(pframe, SIGNAL(GameOver(int)),this, SLOT(onGameOver(int)));
    connect(pframe, SIGNAL(MineFlag(int)), this, SLOT(onMineFlag(int)));
}


void MainWindow::on_action_NewGame_triggered()
{
    showFrame(rownum, colnum, minenum);
}

void MainWindow::on_action_Option_triggered()
{
    QStringList levelstr;
    levelstr<<QString("初级")<<QString("中级")<<QString("高级");
    QString itemstr=QInputDialog::getItem(this, QString("Option"), QString("等级选择"), levelstr, 0, false);
    if(itemstr==QString("初级"))
        showFrame(9,9,10);
    else if(itemstr==QString("中级"))
        showFrame(16,16,40);
    else if(itemstr == QString("高级"))
        showFrame(16,30,99);
}

void MainWindow::onTimerDone()
{
    timercount++;
    m_timenumber->setText(QString("%1").arg(timercount));
}

void MainWindow::onGameBegin()
{
    m_timer->start(1000);
}

void MainWindow::onGameOver(int flag)
{
    m_timer->stop();
    QString titlestr, tipstr;
    if(flag==-1)
        titlestr=QString("游戏失败");
    else if(flag==1)
        titlestr=QString("游戏成功");
    tipstr=QString("请重新开局(Yes)或离开(No)");
    QMessageBox::StandardButton rb = QMessageBox::information(this, titlestr, tipstr,QMessageBox::Yes|QMessageBox::No,
                             QMessageBox::Yes);
    if(rb == QMessageBox::Yes)
    {
        showFrame(rownum, colnum, minenum);
    }
    else
    {
        this->close();
    }
}

void MainWindow::onMineFlag(int remark)
{
    remainminenum+=remark;
    remainminenum = remainminenum < minenum ? remainminenum : minenum;
    remainminenum = remainminenum > 0 ? remainminenum : 0;
    m_minenumber->setText(QString("%1").arg(remainminenum));
}
