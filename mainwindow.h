#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QTimer>
#include"fooditem.h"
#include"snakeItem.h"
#include"gamecontroller.h"
#include<QKeyEvent>
#include"audioplaythread.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyReleaseEvent(QKeyEvent *event);
protected:

private slots:

    void on_actionstart_triggered();

    void on_actionstop_triggered();

    void on_actionMan_triggered();

    void on_actionAI_triggered();

    void on_actionReset_triggered();

    void on_actionEazy_triggered();

    void on_actionMid_triggered();

    void on_actionHard_triggered();

private:
    Ui::MainWindow *ui;
    GameController *game;           //游戏
    bool Iscontinue;                //判断是否继续
};

#endif // MAINWINDOW_H
