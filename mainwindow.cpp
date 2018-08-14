#include "mainwindow.h"
#include "ui_mainwindow.h"
extern int Success;
extern int gameoverFlag;
extern int flagNum;
int Click=0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scmain = new myscenemain;
    ui->graphicsView_main->setScene(scmain);
    ui->stackedWidget->setCurrentIndex(0);
    time_fail_or_win = new QTimer;
    current_time = new QTimer;
    connect(time_fail_or_win,SIGNAL(timeout()),this,SLOT(Update()));
    connect(current_time,SIGNAL(timeout()),this,SLOT(Updatecount()));
    current_time->start(1);
    t.setHMS(0,0,0);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::Update()
{
    if(gameoverFlag==1)
    {
        Click=0;
        t.setHMS(0,0,0);
        ui->lcdNumber->display("00:00");
        QMessageBox::information(this,"info","you failed!");//8*8 fail
        gameoverFlag--;
        time_fail_or_win->stop();
        gameoverFlag--;

    }else if(flagNum==8&&Success>10)
    {
        Click=0;
          QMessageBox::information(this,"info","you win!");//8*8 success
            flagNum=0;
            time_fail_or_win->stop();
            flagNum=0;
    }
}
void MainWindow::on_pushButton_clicked()
{
   sc = new myscene;
   ui->graphicsView_8x8->setScene(sc);
   ui->stackedWidget->setCurrentIndex(1);
   time_fail_or_win->start(500);
}
void MainWindow::Updatecount()
{
    if(Click>0)
     {
        current_time->start(1);
        t=t.addMSecs(1.5);
        QString stime = t.toString("mm:ss");
        ui->lcdNumber->display(stime);
    }
}
void MainWindow::on_pushButtonrestart_clicked()
{
    delete sc;
    sc = new myscene;
    ui->graphicsView_8x8->setScene(sc);
    flagNum=0;
    time_fail_or_win->start(500);
    Click=0;
    t.setHMS(0,0,0);
    ui->lcdNumber->display("00:00");
}
void MainWindow::on_pushButtonexit_clicked()
{
    delete sc;
    ui->stackedWidget->setCurrentIndex(0);
    flagNum=0;
    Click=0;
    t.setHMS(0,0,0);
    ui->lcdNumber->display("00:00");
}
