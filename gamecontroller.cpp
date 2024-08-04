#include "gamecontroller.h"
#include<QKeyEvent>
#include<QDebug>
#include<QPointF>
#include<QTime>
#include<QGraphicsTextItem>
#include<QMessageBox>
GameController::GameController(QObject *parent) : QObject(parent)
{
    //初始化场景
    gameScene=new QGraphicsScene();
    //初始化游戏
    this->initgame();

    snakemode=Man;
    timenum=100;
    maze.resize(30);
    for (int i=0;i<30;i++)
    {
            maze[i].resize(48);
    }
    //打开文件

}

GameController::~GameController()
{
    delete gameScene;
    foods.clear();
    Snakebody.clear();
}

//初始化游戏
void GameController::initgame()
{

    gameScene->setSceneRect(-600, -375,1200,750); //设置场景固定大小
    gameScene->installEventFilter(this);
    BGM=new AudioPlayThread("Audio/BGM.mp3");
    Eat=new AudioPlayThread("Audio/Eat.mp3");
    Die=new AudioPlayThread("Audio/Die.mp3");

    //两个边界
  //  FoodItem *food1=new FoodItem(-600,-375,QString("image/Apple.png"));
  //  FoodItem *food2=new FoodItem(600,375,QString("image/Apple.png"));
    //gameScene->addItem(food1);
    //gameScene->addItem(food2);

    snakehead=new SnakeItem(QString("image/1.png"));
    gameScene->addItem(snakehead);

    openfile.setFileName("1.txt");
    openfile.open(QIODevice::ReadOnly);
    in.setDevice(&openfile);
    this->addNewFood();
}

//开始游戏
void GameController::start()
{
    s=this->startTimer(timenum);
    x=snakehead->startTimer(timenum);
    if(!Snakebody.empty())
    {
        for(int i=0;i<Snakebody.size();i++)
        {
            timerecord[i] =Snakebody[i]->startTimer(timenum);
        }
    }
    BGM->start();
}
//停止游戏
void GameController::stop()
{
    snakehead->killTimer(x);
    this->killTimer(s);
    for(int i=0;i<Snakebody.size();i++)
    {
        Snakebody[i]->killTimer(timerecord[i]);
    }
    BGM->player->pause();

}

//事件过滤器
bool GameController::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {

        QKeyEvent *ev=(QKeyEvent *)event;
        if(ev->key()==Qt::Key_Down)
        {
           //   qDebug()<<"下";
             if(snakehead->direction!=Up)
                snakehead->direction=Down;
        }
        else if(ev->key()==Qt::Key_Up)
        {
          //   qDebug()<<"上";
           if(snakehead->direction!=Down)
             snakehead->direction=Up;
        }
        if(ev->key()==Qt::Key_Left)
        {
          //   qDebug()<<"左";
           if(snakehead->direction!=Right)
                snakehead->direction=Left;
        }
        if(ev->key()==Qt::Key_Right)
        {
          //  qDebug()<<"右";
            if(snakehead->direction!=Left)
                snakehead->direction=Right;
        }
        return true;
    }
    else
    {
           return QObject::eventFilter(watched, event);
    }



}

//定时器
void GameController::timerEvent(QTimerEvent *)
{

    if(snakemode==AI)
    {
        this->creatMaze();
        AIsnake.InitAstar(this->maze);
        if(snakehead->p!=foods.first()->pos())
            path=AIsnake.GetPath(Point(snakehead->p),Point(foods.first()->x(),foods.first()->y()));
    }

    //进行蛇身体的移动
    if(!Snakebody.empty())
    {
        for(int i=Snakebody.size()-1;i>0;i--)
        {
            Snakebody[i]->p=Snakebody[i-1]->p;
        }
        Snakebody[0]->p=snakehead->p;
    }

    if(snakemode==Man)
    {
        //蛇头移动
        switch (snakehead->direction)
        {
        case Down:
            snakehead->p=snakehead->pos()+QPointF(0,25);
            break;
        case Up:
             snakehead->p=snakehead->pos()+QPointF(0,-25);
            break;
        case Left:
            snakehead->p=snakehead->pos()+QPointF(-25,0);
            break;
        case Right:
            snakehead->p=snakehead->pos()+QPointF(25,0);
            break;
        default:
            break;
        }
    }else
    {
        if(!path.empty())
        {
            path.pop_front();
            snakehead->p=path.first()->toPoint();
            path.clear();
        }
    }

    //身体碰撞
    if(snakemode==Man)
    {
        if(snakehead->IsbodyCollisions()&&Snakebody.size()>2)
        {
            qDebug()<<"身体撞了";
            this->gameover();

        }
        //设置墙
        if(snakehead->x()<-600||snakehead->x()>=600||snakehead->y()<-375||snakehead->y()>=375)
        {
            qDebug()<<"撞墙了";
            this->gameover();
        }
    }


    //碰撞
    FoodItem *p=(FoodItem*)snakehead->foodCollisions();
    if(p!=NULL)
    {

        gameScene->removeItem(p);
        if(p->word==foods.first()->word)
        {
            foods.pop_front();
            this->Growth();     //增加身体
            delete p;
            if(foods.isEmpty())
            {
                gameScene->removeItem(pItem);
                this->addNewFood();

            }
            Eat->start();
        }
        else
        {

            qDebug()<<"吃错了"<<p->word;
            this->gameover();
             Die->start();
        }


    }
    if(BGM->isFinished()==true)
    {
        BGM->start();
    }

}


//增加食物
void GameController::addNewFood()
{
    QString s;
    in>>s;
    in>>s;
  //  qDebug()<<s;
    pItem=new QGraphicsTextItem(s);
    QFont font = pItem->font();
    font.setPixelSize(30);  // 像素大小
    font.setItalic(true);  // 斜体
    font.setUnderline(true);  // 下划线
    pItem->setFont(font);
    pItem->setPos(-30,-400);
    gameScene->addItem(pItem);
    for(int i=0;i<s.size();i++)
    {
        int x=0, y=0;
        //qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        do
        {
            x = (int) (rand() % 1200)-600 ;
            y = (int) (rand() % 750)-350 ;
            //防止长在身体上
            for(int i=1;i<Snakebody.size();i++)
            {
                if(Snakebody[i]->x()==x&&Snakebody[i]->y()==y)
                    continue;
            }

        } while(x<-500||x>500||y<-300||y>300||(x%25!=0)||(y%25!=0));

        //新建食物并加入
        QString p=QString("image/Apple")+s[i];
        //qDebug()<<p;
        FoodItem *f= new FoodItem(x,y,p,QString(s[i]));
        foods.push_back(f);
        gameScene->addItem(f);
    }
    in>>s;
    in>>s;
 //   qDebug()<<s;
}

//蛇身体增加
void GameController::Growth()
{
    SnakeItem *p=new SnakeItem(QString("image/3.png"));
    int i=p->startTimer(timenum);   //开启动画，打开定时器
    timerecord.push_back(i);    //将时间记录下来
    if(Snakebody.empty())
    {
        p->p=snakehead->p+QPointF(-25,0);
    }
    else
    {
           SnakeItem *s=Snakebody.last();
           p->p=s->p+QPointF(-25,0);
    }
    //防止加的时候出现重影
    if(snakemode==Man)
    {
        switch (snakehead->direction)
        {
        case Down:
            p->p=p->p+QPointF(0,-25);
            break;
        case Up:
             p->p=p->p+QPointF(0,25);
            break;
        case Left:
            p->p=p->p+QPointF(25,0);
            break;
        case Right:
            p->p=p->p+QPointF(-25,0);
            break;
        default:
            break;
        }
    }

    p->setPos(p->p);
    gameScene->addItem(p);
    Snakebody.push_back(p);  //加入蛇身数组
}

//游戏结束
void GameController::gameover()
{
    this->stop();
    qDebug()<<"游戏结束";
    qDebug()<<snakehead->pos();
    Die->start();
    QMessageBox::information(NULL,"游戏结束","game over");
    this->cleargame();
}

//清空游戏，进行重新开始
void GameController::cleargame()
{

    for(int i=0;i<foods.size();i++)
    {
        FoodItem *f=foods[i];
        gameScene->removeItem(f);
        delete f;
    }
    for(int i=0;i<Snakebody.size();i++)
    {
        SnakeItem *s=Snakebody[i];
        gameScene->removeItem(s);
        delete s;
    }

    foods.clear();
    Snakebody.clear();
    snakehead->setPos(0,0);
    snakehead->p=QPointF(0,0);
    gameScene->removeItem(pItem);
    addNewFood();
}

//创造矩阵
void GameController::creatMaze()
{
    for(int i=0;i<29;i++)
        for(int j=0;j<48;j++)
            maze[i][j]=0;

    for(int i=0;i<48;i++)
    {
        maze[0][i]=1;
        maze[29][i]=1;
    }
    for(int i=1;i<28;i++)
    {
        maze[i][0]=1;
        maze[i][47]=1;
    }

    foreach (SnakeItem* s, Snakebody)
    {
         int x=(s->p.x()+600)/25-1;
         int y=(s->p.y()+375)/25-1;
         maze[y][x]=1;
    }

    for(int i=1;i<foods.size();i++)
    {
        int x=(foods[i]->x()+600)/25-1;
        int y=(foods[i]->y()+375)/25-1;
         maze[y][x]=1;
    }
}
