#ifndef FOODITEM_H
#define FOODITEM_H

#include <QWidget>
#include<QGraphicsPixmapItem>
#include<QPixmap>
#include<QString>
const  int FOOD =3;
const  QVariant v=FOOD; //用于判断是否是食物类

//食物类
class FoodItem :  public QObject,public QGraphicsPixmapItem
{

public:
    FoodItem(int x, int y,QString p,QString word="a");
    QRectF boundingRect()const;
    QString word;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
public slots:
private:

};

#endif // FOODITEM_H
