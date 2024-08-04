#include "snakeItem.h"
#include<QPixmap>
#include<QPainter>
#include<QList>
#include<QDebug>
SnakeItem::SnakeItem(QString p)
{
    path=p;

    this->setFlag(QGraphicsItem::ItemIsSelectable);
    this->setFlag(QGraphicsItem::ItemIsMovable);
    QPixmap pix(path);
    pix= pix.scaled(30,30,Qt::KeepAspectRatio);
    this->setPixmap(pix);
    direction=Down;   //设置初始方向为向上
    this->setData(SnakeBody,v1);

}

QRectF SnakeItem::boundingRect()const
{
    return QRectF(0,0,30,30);  //设置矩阵的大小
}

QPainterPath SnakeItem::shape()const
{
        QPainterPath p;
        p.addRect(0,0,15,15);
        return p;
}

//重写定时器
void SnakeItem::timerEvent(QTimerEvent *event)
{
    setPos(p);  //给设置位置
}

//和食物的碰撞
QGraphicsItem *SnakeItem::foodCollisions()
{
    QList<QGraphicsItem *> list = collidingItems();
    foreach (QGraphicsItem *collidingItem, list)
    {
            if (collidingItem->data(FOOD)==v)
            {

                return collidingItem;
            }
    }
    return NULL;

}

//和蛇身碰撞
bool SnakeItem::IsbodyCollisions()
{
    QList<QGraphicsItem *> list = collidingItems();
    //int i=0;
    //qDebug()<<list.size();
    foreach (QGraphicsItem *collidingItem, list)
    {
            if (collidingItem->data(SnakeBody)==v1)
            {
               return true;
            }
    }
   return false;
}




