#ifndef ASTART_H
#define ASTART_H

#include <QObject>
#include<QVector>
#include<QList>
#include<QPointF>
const int cost=10;
//定义开始的点类
struct Point: public QPointF
{

    int F, G, H;      //F=G+H
    Point *parent;   //parent的坐标

    Point(QPointF p) : F(0), G(0), H(0), parent(NULL)  //变量初始化
    {
        this->setX(p.x());
        this->setY(p.y());
    }

    Point(qreal x,qreal y) : F(0), G(0), H(0), parent(NULL)  //变量初始化
    {
       this->setX(x);
       this->setY(y);
    }

};

//算法核心
class Astart
{
public:
        Astart();
        //初始化算法
         void InitAstar(QVector<QVector<int>> &_maze);
         //得到计算后的路径
        QList<Point *> GetPath(Point startPoint, Point endPoint);
protected:
        //A*算法的核心
        Point *findPath(Point &startPoint, Point &endPoint);
        //得到附近的四个点
        QVector<Point *> getSurroundPoints(const Point *point) const;
        //判断某点是否可以用于下一步判断
        bool isCanreach(const Point *point, const Point *target) const;

        Point *isInList(const QList<Point *> &list, const Point *point) const; //判断开启/关闭列表中是否包含某点

        Point *getLeastFpoint(); //从开启列表中返回F值最小的节点
        //计算FGH值
        int calcG( Point *point);
        int calcH(Point *point, Point *end);
        int calcF(Point *point);

private:
    QVector<QVector<int>> maze;
    QList<Point *> openList;  //开启列表
    QList<Point *> closeList; //关闭列表

};

#endif // ASTART_H
