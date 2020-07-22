#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include<QString>
#include<QVector>
#include<QPointF>
#include"fooditem.h"
#include<QPainterPath>

const  int SnakeBody =4;
const  QVariant v1=SnakeBody;
//方向
enum Direction
{
    Up,Down,Left,Right
};


//蛇类的节点
class SnakeItem :public QObject, public QGraphicsPixmapItem
{

public:
    SnakeItem(QString p);
    QRectF boundingRect()const;
    QPainterPath shape()const;

    void timerEvent(QTimerEvent *event);
    QGraphicsItem *foodCollisions();        //和食物发生碰撞
    bool IsbodyCollisions();        //和自己的身体发生碰撞
    QString path;
    Direction direction;
    QPointF p;

signals:
public slots:

};



#endif // SNAKE_H
