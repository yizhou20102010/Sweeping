#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QLineEdit>
#include <QLCDNumber>
#include <QHBoxLayout>
#include "mineframe.h"
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_action_NewGame_triggered();

    void on_action_Option_triggered();

    void onTimerDone();
    void onGameBegin();
    void onGameOver(int flag);
    void onMineFlag(int remark);

private:
    Ui::MainWindow *ui;
    int rownum,colnum, minenum;
    QLineEdit *m_minenumber, *m_timenumber;
    QHBoxLayout *plcdlayerout, *pnumlayerout, *phlayout;
    MineFrame *pframe;
    int timercount;
    QTimer *m_timer;
public:
    int remainminenum;
    void showFrame(const int rnum=9, const int cnum=9, const int mnum=10);
};

#endif // MAINWINDOW_H
