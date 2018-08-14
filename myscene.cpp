#include "myscene.h"
extern int a[8][8];
extern int gameoverFlag;
myitem *item[64];
int myscene::index=0;
myscene::myscene(QObject *parent) :
    QGraphicsScene(parent)
{
//    qsrand((unsigned)time(NULL));
    initImage();
    ptimer = new QTimer;
    connect(ptimer,SIGNAL(timeout()),this,SLOT(Update()));
    ptimer->start(1);
}
void myscene::initImage()
{
    for(int i=0;i<64;i++)
    {
        item[i] = new myitem(":/f3");
        item[i]->setPos(item[i]->boundingRect().width()*(i%8),item[i]->boundingRect().height()*(i/8));
        this->addItem(item[i]);
        a[i/8][i%8] = 0;

    }
    for(int j=0;j<8;j++)
    {
        index=qrand()%64;
        if( item[index]->flag==1)
        j--;
        item[index]->flag=1;
        a[index/8][index%8] = 1;
    }
}
void myscene::Update()
{
        if(gameoverFlag==1)
                 {
                    for(index=0;index<64;index++)
                        {
                            if(a[index/8][index%8]==1)
                                {
                                    item[index] = new myitem(":/l1");
                                    item[index]->setPos(item[index]->boundingRect().width()*(index%8),item[index]->boundingRect().height()*(index/8));
                                    this->addItem(item[index]);
                                }
                        }
                    ptimer->stop();
                }
}
