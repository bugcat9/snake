#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPixmap>
#include<QDebug>
#include<QGraphicsPixmapItem>
#include<QMouseEvent>
#include<QPointF>
#include<QTimer>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap background("image/background.png");  //加载背景图片
    ui->GameView->setBackgroundBrush(background);
    //设置没有滚动条
    ui->GameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->GameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    game=new GameController();//初始化游戏控制类

    ui->GameView->setScene(game->gameScene);   //设置好了带有背景图的场景，还需要设置物体
    this->resize(1300,900);
    Iscontinue=true;
}

MainWindow::~MainWindow()
{
    delete game;
    delete ui;
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Space)
    {
        if(Iscontinue)
        {
            Iscontinue=false;
            game->start();
        }else
        {
            Iscontinue=true;
            game->stop();
        }
    }

}


//开始游戏
void MainWindow::on_actionstart_triggered()
{
     Iscontinue=false;
     game->start();

}
//停止游戏
void MainWindow::on_actionstop_triggered()
{
    Iscontinue=true;
    game->stop();
}

void MainWindow::on_actionMan_triggered()
{
    game->snakemode=Man;
}

void MainWindow::on_actionAI_triggered()
{
    game->snakemode=AI;
}
//重新开始
void MainWindow::on_actionReset_triggered()
{
    Iscontinue=true;
    game->cleargame();
}

void MainWindow::on_actionEazy_triggered()
{
    game->timenum=500;
}

void MainWindow::on_actionMid_triggered()
{
    game->timenum=200;
}

void MainWindow::on_actionHard_triggered()
{
    game->timenum=100;
}
