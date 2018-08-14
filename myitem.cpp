#include "myitem.h"
#include<unistd.h>
int gameoverFlag=0;
int a[8][8];
int Success=0;
extern myitem *item[64];
int flagNum;
extern int Click;
myitem::myitem(QString path)
{
    this->setPixmap(QPixmap(path));
    IsflagOrwhiteblock=0;
    spreadFlag=0;

}
void myitem::setNum(int j,int k)
{
    boomNum=0;
    if((j-1>=0)&&(k-1>=0)&&(a[j-1][k-1]==1))
    boomNum++;
    if((j-1>=0)&&a[j-1][k]==1)
    boomNum++;
    if((j-1>=0)&&(k+1<=7)&&(a[j-1][k+1]==1))
    boomNum++;
    if((k-1>=0)&&(a[j][k-1]==1))
    boomNum++;
    if((k+1<=7)&&(a[j][k+1]==1))
    boomNum++;
    if((k-1>=0)&&(j+1<=7)&&(a[j+1][k-1]==1))
    boomNum++;
    if((j+1<=7)&&(a[j+1][k]==1))
    boomNum++;
    if((j+1<=7)&&(k+1<=7)&&(a[j+1][k+1]==1))
    boomNum++;
   switch(boomNum)
    {
   case 1:  item[8*j+k]->setPixmap(QPixmap(":/11"));item[8*j+k]->IsflagOrwhiteblock+=2;Success++; break;
   case 2: item[8*j+k]->setPixmap(QPixmap(":/22"));item[8*j+k]->IsflagOrwhiteblock+=2;Success++;break;
   case 3:item[8*j+k]->setPixmap(QPixmap(":/33"));item[8*j+k]->IsflagOrwhiteblock+=2;Success++;break;
   case 4: item[8*j+k]->setPixmap(QPixmap(":/44"));item[8*j+k]->IsflagOrwhiteblock+=2;Success++;break;
   case 5: item[8*j+k]->setPixmap(QPixmap(":/55"));item[8*j+k]->IsflagOrwhiteblock+=2;Success++;break;
   case 6: item[8*j+k]->setPixmap(QPixmap(":/66"));item[8*j+k]->IsflagOrwhiteblock+=2;Success++;break;
   case 7: item[8*j+k]->setPixmap(QPixmap(":/77"));item[8*j+k]->IsflagOrwhiteblock+=2;Success++;break;
   case 8: item[8*j+k]->setPixmap(QPixmap(":/88"));item[8*j+k]->IsflagOrwhiteblock+=2;Success++;break;
   case 0: item[8*j+k]->setPixmap(QPixmap(":/f2"));
    if(j<7&&j>0&&k<7&&k>0&&item[8*j+k]->spreadFlag==0)
 {
Success++;
                     item[8*j+k]->spreadFlag=1;
                     setNum(j-1,k);
                     setNum(j,k-1);
                     item[8*j+k]->spreadFlag=1;
                     setNum(j+1,k);
                     item[8*j+k]->spreadFlag=1;
                     setNum(j,k+1);
                     item[8*j+k]->spreadFlag=1;
 }
    if(j==0&&(k!=0)&&(k!=7)&&item[8*j+k]->spreadFlag==0)//up
    {
Success++;
        setNum(j,k-1);
        item[8*j+k]->spreadFlag=1;
        setNum(j+1,k);
        item[8*j+k]->spreadFlag=1;
        setNum(j,k+1);
        item[8*j+k]->spreadFlag=1;
    }
if((k==0)&&(j!=0)&&(j!=7)&&item[8*j+k]->spreadFlag==0)//left
    {Success++;

        setNum(j-1,k);
        item[8*j+k]->spreadFlag=1;
        setNum(j+1,k);
        item[8*j+k]->spreadFlag=1;
        setNum(j,k+1);
        item[8*j+k]->spreadFlag=1;
    }
    if((j==7)&&(k!=0)&&(k!=7)&&item[8*j+k]->spreadFlag==0)//down
    {Success++;
        setNum(j-1,k);
        item[8*j+k]->spreadFlag=1;
        setNum(j,k-1);
        item[8*j+k]->spreadFlag=1;
        setNum(j,k+1);
        item[8*j+k]->spreadFlag=1;
    }
   if((k==7)&&(j!=0)&&(j!=7)&&item[8*j+k]->spreadFlag==0)//right
    {Success++;
        setNum(j-1,k);
        item[8*j+k]->spreadFlag=1;
        setNum(j,k-1);
        item[8*j+k]->spreadFlag=1;
        setNum(j+1,k);
        item[8*j+k]->spreadFlag=1;
    }
    if((k==0)&&(j==0)&&item[8*j+k]->spreadFlag==0)
    {Success++;
        item[8*j+k]->spreadFlag=1;
        setNum(j,k+1);

        setNum(j+1,k);
        item[8*j+k]->spreadFlag=1;
    }
    if((k==7)&&(j==7)&&item[8*j+k]->spreadFlag==0)
    {Success++;
        item[8*j+k]->spreadFlag=1;
        setNum(j-1,k);

        setNum(j,k-1);
        item[8*j+k]->spreadFlag=1;
     }
    if((j==7)&&(k==0)&&item[8*j+k]->spreadFlag==0)
    {Success++;
         item[8*j+k]->spreadFlag=1;
        setNum(j-1,k);

        setNum(j,k+1);
        item[8*j+k]->spreadFlag=1;
    }
    if((k==7)&&(j==0)&&item[8*j+k]->spreadFlag==0)
    {Success++;
        item[8*j+k]->spreadFlag=1;
        setNum(j+1,k);

        setNum(j,k-1);
        item[8*j+k]->spreadFlag=1;
    }
       item[8*j+k]->IsflagOrwhiteblock+=2;

       break;
   }
   qDebug()<<Success;
}
void myitem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
     if(event->button()==Qt::LeftButton&&flag==0&&IsflagOrwhiteblock==0)
    {
         m_x=this->pos().x();
         m_y=this->pos().y();
         setNum(m_y/48,m_x/48);

    }else if(event->button()==Qt::LeftButton&&flag==1&&IsflagOrwhiteblock==0)
    {
            this->setPixmap(QPixmap(":/l1"));
            gameoverFlag=1;

    }else if(event->button()==Qt::RightButton&&flag==1)
    {
        if(IsflagOrwhiteblock==0)
    {
        this->setPixmap(QPixmap(":/q1"));
        IsflagOrwhiteblock++;
        flagNum++;

     }else if(IsflagOrwhiteblock==1)
     {
        this->setPixmap(QPixmap(":/f3"));
        IsflagOrwhiteblock--;
        flagNum--;
     }

    }else if(event->button()==Qt::RightButton&&flag==0)
    {
        if(IsflagOrwhiteblock==0)
       {
            this->setPixmap(QPixmap(":/q1"));
            IsflagOrwhiteblock++;
        }else if(IsflagOrwhiteblock==1)
        {
               this->setPixmap(QPixmap(":/f3"));
               IsflagOrwhiteblock--;
        }
    }else if(event->button()==Qt::MidButton&&flag==1&&IsflagOrwhiteblock==0)
    {
        this->setPixmap(QPixmap(":/q1"));
        flagNum++;
    }
    Click++;
}
