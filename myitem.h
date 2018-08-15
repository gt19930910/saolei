#ifndef MYITEM_H
#define MYITEM_H
#include<QString>
#include<QGraphicsPixmapItem>
#include<QGraphicsSceneMouseEvent>
#include<QMessageBox>
#include<QDebug>

class myitem : public QGraphicsPixmapItem
{
public:
    myitem(QString path);
    int flag;//0表示不是雷，1表示是雷
    void setNum(int y, int x);
private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    int boomNum;//周围雷的个数
    int IsflagOrwhiteblock;//0表示还未点开的状态，1表示插上了旗子，2表示点开来变成了白色的
    int spreadFlag;//当前块是否已经蔓延过了
    int m_x;//当前块的横坐标
    int m_y;//当前块的纵坐标
};

#endif // MYITEM_H
