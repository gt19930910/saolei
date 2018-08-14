#include "myscenemain.h"

myscenemain::myscenemain(QObject *parent) : QGraphicsScene(parent)
{
    QString path=":/zhujiemian";
    itemmain = new myitemmain(path);
    this->addItem(itemmain);
}
