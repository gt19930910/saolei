#include "mainwindow.h"
#include "ui_mainwindow.h"

extern int gameoverFlag;
extern int flagNum;
int Click = 0;//玩家需要点击了方块才会开始计时

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scmain = new myscenemain;
    ui->graphicsView_main->setScene(scmain);
    ui->stackedWidget->setCurrentIndex(0);
    timeFailorWin = new QTimer;
    currentTime = new QTimer;
    connect(timeFailorWin, SIGNAL(timeout()), this, SLOT(Update()));
    connect(currentTime, SIGNAL(timeout()), this, SLOT(updateCount()));
    currentTime->start(1);//当前时间，每隔1秒调用一次updateCount()
    t.setHMS(0, 0, 0);//lcd显示器初始化为0
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Update()
{
    if(gameoverFlag == 1)
    {
        Click = 0;
        t.setHMS(0, 0, 0);
        ui->lcdNumber->display("00:00");
        QMessageBox::information(this, "info", "you failed!");//8*8 失败
        gameoverFlag--;
        timeFailorWin->stop();
        gameoverFlag--;

    }else if(flagNum == 8)//所有的雷都找出来算成功
    {
        Click = 0;
        QMessageBox::information(this, "info", "you win!");//8*8 成功
        flagNum = 0;
        timeFailorWin->stop();
        flagNum = 0;
    }
}
void MainWindow::on_pushButton_clicked()
{
   sc = new myscene;
   ui->graphicsView_8x8->setScene(sc);
   ui->stackedWidget->setCurrentIndex(1);
   timeFailorWin->start(500);//每个半秒检测是否赢了或者输了，执行Update函数
}
void MainWindow::updateCount()
{
    if(Click > 0)//需要玩家开始玩游戏的时候计时器才会开始计时并显示在lcd上
    {
        currentTime->start(1);
        t = t.addMSecs(1.5);
        QString stime = t.toString("mm:ss");
        ui->lcdNumber->display(stime);
    }
}
void MainWindow::on_pushButtonrestart_clicked()
{
    delete sc;
    sc = new myscene;
    ui->graphicsView_8x8->setScene(sc);
    flagNum = 0;
    timeFailorWin->start(500);
    Click = 0;
    t.setHMS(0, 0, 0);
    ui->lcdNumber->display("00:00");
}
void MainWindow::on_pushButtonexit_clicked()
{
    delete sc;
    ui->stackedWidget->setCurrentIndex(0);
    flagNum = 0;
    Click = 0;
    t.setHMS(0, 0, 0);
    ui->lcdNumber->display("00:00");
}
