#include "fooditem.h"
#include<QPixmap>
#include<QPainter>
#include<QDebug>
#include<QPainterPath>
#include<QGraphicsSceneMouseEvent>
#include<QGraphicsView>
#include<QPoint>
#include<QPointF>
#include<QGraphicsScene>
FoodItem::FoodItem(int x, int y,QString p,QString word)
{

    this->word=word;
    this->setPos(mapToParent(x,y));
    this->setFlag(QGraphicsItem::ItemIsSelectable);
    QPixmap pix;
    if(pix.load(p))
    {
        qDebug()<<"a加载成功";
    }
    this->setPixmap(pix);
    setFlag(QGraphicsItem::ItemIsMovable);
    setData(FOOD,v);
}


QRectF FoodItem::boundingRect()const
{
    return QRectF(0,0,25,25);  //设置矩阵的大小
}

void FoodItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    qDebug()<<this->word<<this->pos();
}







