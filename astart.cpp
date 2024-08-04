#include "astart.h"
#include<QVector>
#include<QDebug>
Astart::Astart()
{

}

//初始化，得到坐标矩阵
void Astart::InitAstar(QVector<QVector<int>> &_maze)
{
    maze = _maze;
}

QList<Point *> Astart::GetPath(Point startPoint, Point endPoint)
{
        //调用函数得到矩阵
       Point *result = findPath(startPoint, endPoint);
       QList<Point *> path;
        //返回路径，如果没找到路径，返回空链表
        while (result)
        {
            path.push_front(result);
            result = result->parent;
        }

        // 清空临时开闭列表，防止重复执行GetPath导致结果异常
        if(!openList.isEmpty())
            openList.clear();
        closeList.clear();
        return path;
}

//A*的核心算法
Point *Astart::findPath(Point &startPoint, Point &endPoint)
{
        openList.push_back(new Point(startPoint.toPoint())); //置入起点,拷贝开辟一个节点，内外隔离
        while (!openList.empty())
        {
            auto curPoint = getLeastFpoint(); //找到F值最小的点
            openList.removeOne(curPoint); //从开启列表中删除
            closeList.push_back(curPoint); //放到关闭列表
            //1,找到当前周围4个格中可以通过的格子

            auto surroundPoints = getSurroundPoints(curPoint);
            for (auto &target : surroundPoints)
            {
                //2,对某一个格子，如果它不在开启列表中，加入到开启列表，设置当前格为其父节点，计算F G H
                if (!isInList(openList, target))
                {
                    target->parent = curPoint;
                    target->G = calcG( target);
                    target->H = calcH(target, &endPoint);
                    target->F = calcF(target);

                    openList.push_back(target);
                }
                //3，对某一个格子，它在开启列表中，计算G值, 如果比原来的大, 就什么都不做, 否则设置它的父节点为当前点,并更新G和F
                else
                {
                    int tempG = calcG( target);
                    if (tempG<target->G)
                    {
                        target->parent = curPoint;

                        target->G = tempG;
                        target->F = calcF(target);
                    }
                }
                //判断endpoint是否在列表当中，在就结束
                Point *resPoint = isInList(openList, &endPoint);
                if (resPoint)
                    return resPoint; //返回列表里的节点指针，不要用原来传入的endpoint指针，因为发生了深拷贝
            }
        }

        return NULL;

}

//附近坐标
QVector<Point *> Astart::getSurroundPoints(const Point *point) const
{
        QVector<Point *> surroundPoints;

        //蛇以35格的像素点移动
        for (qreal x = point->x()-25; x <= point->x()+25; x=x+25)
            for (qreal y = point->y()-25; y <= point->y()+25; y=y+25)
                if (isCanreach(point, new Point(x, y)))
                    surroundPoints.push_back(new Point(x, y));

        return surroundPoints;

}

//判断能否到达
bool Astart::isCanreach(const Point *point, const Point *target) const
{

        if (target->x()<=-600 || target->x()>600
            || target->y()<=-375 || target->y()>375//在边界外
            || maze[(target->y()+375)/25-1][(target->x()+600)/25-1] == 1            //是障碍点
            || target->toPoint() == point->toPoint()
            || isInList(closeList, target)
            ) //如果点与当前节点重合、超出地图、是障碍物、或者在关闭列表中，返回false
         return false;
        else if (abs(point->x() - target->x()) + abs(point->y() - target->y()) == 25) //非斜角可以
        {

                return true;
        }
        else
        {
            return false;
        }

}

Point *Astart::isInList(const QList<Point *> &list, const Point *point) const
{
    //判断某个节点是否在列表中，这里不能比较指针，因为每次加入列表是新开辟的节点，只能比较坐标
        for (auto p : list)
        if (p->toPoint() == point->toPoint())
            return p;
        return NULL;

}

//找F值最小的点，其实可以用堆进行改进
Point *Astart::getLeastFpoint()
{
    if (!openList.empty())
        {
            auto resPoint = openList.front();
            for (auto &point : openList)
            if (point->F<resPoint->F)
                resPoint = point;
            return resPoint;
        }
        return NULL;

}

int Astart::calcG( Point *point)
{
        int extraG =cost;
        int parentG = point->parent == NULL ? 0 : point->parent->G; //如果是初始节点，则其父节点是空
        return parentG + extraG;
}

int Astart::calcH(Point *point, Point *end)
{

    return abs(point->x()-end->x())+abs(point->y()-end->y());//用曼哈顿距离作为标准
}

int Astart::calcF(Point *point)
{
    return point->G + point->H;
}
