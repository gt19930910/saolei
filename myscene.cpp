#include "myscene.h"

extern int a[8][8];
extern int gameoverFlag;
myitem *item[64];
int myscene::index = 0;//本类内全局变量

myscene::myscene(QObject *parent) :
    QGraphicsScene(parent)
{
//    qsrand((unsigned)time(NULL));
    initImage();//初始化游戏界面
    ptimer = new QTimer;
    connect(ptimer, SIGNAL(timeout()), this, SLOT(Update()));
    ptimer->start(1);//每秒刷新一次界面
}

void myscene::initImage()
{
    for(int i=0; i<64; i++)
    {
        item[i] = new myitem(":/source_pic/f3");//8x8每个图标初始化图片
        item[i]->setPos(item[i]->boundingRect().width()*(i%8), item[i]->boundingRect().height()*(i/8));//8x8排列摆放
        this->addItem(item[i]);//每个item添加到scene上面
        a[i/8][i%8] = 0;//每个item背后的值赋值为0

    }
    for(int j=0; j<8; j++)//随机取八个雷,赋值为1
    {
        index = qrand()%64;//在64内取八个随机数
        if(item[index]->flag == 1)//如果重复则重新取
            j--;
        item[index]->flag = 1;//item成员变量flag设置为1
        a[index/8][index%8] = 1;//8x8方格背后的值赋值为1
    }
}

void myscene::Update()//游戏结束时调用显示所有的地雷
{
    if(gameoverFlag == 1)
    {
        for(index=0; index<64; index++)
        {
            if(a[index/8][index%8] == 1)
            {
                item[index] = new myitem(":/source_pic/l1");//地雷
                item[index]->setPos(item[index]->boundingRect().width()*(index%8), item[index]->boundingRect().height()*(index/8));
                this->addItem(item[index]);
            }
        }
        ptimer->stop();
    }
}
