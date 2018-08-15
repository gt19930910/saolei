#include "myitem.h"
#include <unistd.h>

int gameoverFlag = 0;
int a[8][8];
int flagNum;//找到雷的个数(插上旗)
extern int Click;
extern myitem *item[64];

myitem::myitem(QString path)
{
    this->setPixmap(QPixmap(path));
    IsflagOrwhiteblock = 0;//0表示还未点开的状态
    spreadFlag = 0;
    flag = 0;
}

void myitem::setNum(int y, int x)
{
    boomNum = 0;
    if((y-1 >= 0) && (x-1 >= 0) && (a[y-1][x-1] == 1))//四周八块方块一一检测总共有多少个雷
        boomNum++;
    if((y-1 >= 0) && a[y-1][x] == 1)
        boomNum++;
    if((y-1 >= 0) && (x+1 <= 7) && (a[y-1][x+1] == 1))
        boomNum++;
    if((x-1 >= 0) && (a[y][x-1] == 1))
        boomNum++;
    if((x+1 <= 7) && (a[y][x+1] == 1))
        boomNum++;
    if((x-1 >= 0) && (y+1 <= 7) && (a[y+1][x-1] == 1))
        boomNum++;
    if((y+1 <= 7) && (a[y+1][x] == 1))
        boomNum++;
    if((y+1 <= 7) && (x+1 <= 7) && (a[y+1][x+1] == 1))
        boomNum++;
    switch(boomNum)//根据周围雷的个数在当前块上显示数字
    {
        case 1: item[8*y+x]->setPixmap(QPixmap(":/source_pic/11")); item[8*y+x]->IsflagOrwhiteblock += 2; break;
        case 2: item[8*y+x]->setPixmap(QPixmap(":/source_pic/22")); item[8*y+x]->IsflagOrwhiteblock += 2; break;
        case 3: item[8*y+x]->setPixmap(QPixmap(":/source_pic/33")); item[8*y+x]->IsflagOrwhiteblock += 2; break;
        case 4: item[8*y+x]->setPixmap(QPixmap(":/source_pic/44")); item[8*y+x]->IsflagOrwhiteblock += 2; break;
        case 5: item[8*y+x]->setPixmap(QPixmap(":/source_pic/55")); item[8*y+x]->IsflagOrwhiteblock += 2; break;
        case 6: item[8*y+x]->setPixmap(QPixmap(":/source_pic/66")); item[8*y+x]->IsflagOrwhiteblock += 2; break;
        case 7: item[8*y+x]->setPixmap(QPixmap(":/source_pic/77")); item[8*y+x]->IsflagOrwhiteblock += 2; break;
        case 8: item[8*y+x]->setPixmap(QPixmap(":/source_pic/88")); item[8*y+x]->IsflagOrwhiteblock += 2; break;
        case 0: item[8*y+x]->setPixmap(QPixmap(":/source_pic/f2"));//表示周围没有雷,下面分不同位置的块按照不同的方法向四周蔓延
        if(y < 7 && y > 0 && x < 7 && x > 0 && item[8*y+x]->spreadFlag == 0)//属于中间的方块
        {
            item[8*y+x]->spreadFlag = 1;
            setNum(y-1, x);
            setNum(y, x-1);
            setNum(y+1, x);
            setNum(y, x+1);
        }
        if(y == 0 && (x != 0) && (x != 7) && item[8*y+x]->spreadFlag == 0)//顶上的方块不包含两边
        {
            item[8*y+x]->spreadFlag = 1;
            setNum(y, x-1);
            setNum(y+1, x);
            setNum(y, x+1);
        }
        if((x == 0) && (y != 0) && (y != 7) && item[8*y+x]->spreadFlag == 0)//左边的方块不包含两边
        {
            item[8*y+x]->spreadFlag = 1;
            setNum(y-1, x);
            setNum(y+1, x);
            setNum(y, x+1);
        }
        if((y == 7) && (x != 0) && (x != 7) && item[8*y+x]->spreadFlag == 0)//下面的方块不包含两边
        {
            item[8*y+x]->spreadFlag = 1;
            setNum(y-1, x);
            setNum(y, x-1);
            setNum(y, x+1);
        }
        if((x == 7) && (y != 0) && (y != 7) && item[8*y+x]->spreadFlag == 0)//右边的方块不包含两边
        {
            item[8*y+x]->spreadFlag = 1;
            setNum(y-1, x);
            setNum(y, x-1);
            setNum(y+1, x);
        }
        if((x == 0) && (y == 0) && item[8*y+x]->spreadFlag == 0)//左上角
        {
            item[8*y+x]->spreadFlag = 1;
            setNum(y, x+1);
            setNum(y+1, x);
        }
        if((x == 7) && (y == 7) && item[8*y+x]->spreadFlag == 0)//右下角
        {
            item[8*y+x]->spreadFlag = 1;
            setNum(y-1, x);
            setNum(y, x-1);
         }
        if((y == 7) && (x == 0) && item[8*y+x]->spreadFlag == 0)//左下角
        {
            item[8*y+x]->spreadFlag = 1;
            setNum(y-1, x);
            setNum(y, x+1);
        }
        if((x == 7)&&(y == 0) && item[8*y+x]->spreadFlag == 0)//右上角
        {
            item[8*y+x]->spreadFlag = 1;
            setNum(y+1, x);
            setNum(y, x-1);
        }
        item[8*y+x]->IsflagOrwhiteblock += 2;

       break;
   }
}
void myitem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && flag == 0 && IsflagOrwhiteblock == 0)//方块未点击状态，左击鼠标并且不是雷
    {
        m_x = this->pos().x();
        m_y = this->pos().y();//获取此块坐标
        setNum(m_y/48, m_x/48);//取[0,0]->[7,7]，判断周围雷的个数并显示，或者蔓延没有雷的情况

    }else if(event->button() == Qt::LeftButton && flag == 1 && IsflagOrwhiteblock == 0)//方块未点击状态，左击是雷
    {
        this->setPixmap(QPixmap(":/source_pic/l1"));//设置雷的图标
        gameoverFlag = 1;//游戏结束

    }else if(event->button() == Qt::RightButton && flag == 1)//右击是雷的方块
    {
        if(IsflagOrwhiteblock == 0)//方块还没被点过
        {
            this->setPixmap(QPixmap(":/source_pic/q1"));//插旗
            IsflagOrwhiteblock++;//表示此块已经被插上了旗
            flagNum++;//找到雷的个数加一

        }else if(IsflagOrwhiteblock == 1)//如果这块已经被插上了旗子了
        {
            this->setPixmap(QPixmap(":/source_pic/f3"));//将旗子取消掉
            IsflagOrwhiteblock--;//状态回到为点之前
            flagNum--;//找到的雷的个数减一
        }

    }else if(event->button() == Qt::RightButton && flag == 0)//右击不是雷的方块
    {
        if(IsflagOrwhiteblock == 0)//没点过则插旗,显示此块已经插旗
        {
            this->setPixmap(QPixmap(":/source_pic/q1"));
            IsflagOrwhiteblock++;
            flagNum--;//插错旗-1
        }else if(IsflagOrwhiteblock == 1)//已经插旗，则取消插旗
        {
           this->setPixmap(QPixmap(":/source_pic/f3"));
           IsflagOrwhiteblock--;
           flagNum++;//取消插错的旗+1
        }
    }
    /*
    else if(event->button() == Qt::MidButton && flag == 1 && IsflagOrwhiteblock == 0)
    {
        this->setPixmap(QPixmap(":/source_pic/q1"));
        flagNum++;
    }
    */
    Click++;//点击的次数加一
}
