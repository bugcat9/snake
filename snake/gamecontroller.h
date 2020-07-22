#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include"fooditem.h"
#include"snakeItem.h"
#include<QVector>
#include<QGraphicsScene>
#include"snakeItem.h"
#include<QTimerEvent>
#include"astart.h"
#include<QList>
#include<QVector>
#include<QFile>
#include<QTextStream>
#include<QMediaPlayer>
#include"audioplaythread.h"
//玩的模式
enum Mode
{
    AI,Man
};

//游戏的控制中心
class GameController : public QObject
{
    Q_OBJECT
public:
    //构造函数
    explicit GameController(QObject *parent = nullptr);

    //析构函数
    ~GameController();

    //初始化游戏
     void initgame();

     //开始游戏和结束游戏
     void start();
     void stop();
     //从新开始
     void cleargame();
     //事件过滤器
     bool eventFilter(QObject *watched, QEvent *event);
     void timerEvent(QTimerEvent *);

     //游戏结束
     void gameover();





    int foodnum;                    //当前食物的数量
    QVector<QVector<int>> maze;     //矩阵用于A*算法
    //FoodItem *food;
    QGraphicsTextItem *pItem;//存写的字
    //创造的迷宫
    void creatMaze();
    //加食物
    void addNewFood();
    //蛇身体的增长
    void Growth();
    Mode snakemode;
    int timenum;                         //用于等级
    QGraphicsScene *gameScene;          //游戏场景
signals:

public slots:

private:
    int s;
    int x;              //x,s是用来专门记录蛇头和游戏控制本身的定时器
    QVector<int>timerecord;        //其他游戏定时器记录的数组
    Astart AIsnake;
    QList<Point *>path;             //记录A*算法的路径
    QFile openfile;                 //用于打开文件
    QTextStream in;
    AudioPlayThread *BGM;           //背景音乐
    AudioPlayThread *Eat;           //吃东西时的声音
    AudioPlayThread *Die;           //死亡时的声音

    QVector<FoodItem*>foods;            //储存食物
    QVector<SnakeItem*>Snakebody;       //储存蛇身体的节点
    SnakeItem   *snakehead;             //蛇的头
};

#endif // GAMECONTROLLER_H
