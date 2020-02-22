#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QMessageBox>
#include <player.h>
#include <box.h>
#include <target.h>


#define GROUND      0
#define WALL        1
#define EMPTYBOX    2
#define FULLBOX     3
#define TARGET      4
#define PLAYER      5
#define TWO         6

#define RIGHT       7
#define LEFT        8
#define UP          9
#define DOWN        10

#define NOMOVE      11
#define MOVE        12
#define PICK        13
#define DROP        14


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void Right(int x, int y);
    void Left(int x, int y);
    void Up(int x, int y);
    void Down(int x, int y);

public slots:
    virtual void keyPressEvent(QKeyEvent *e);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    int pixel;
    int now_stage;
    int get_target_num;
    int total_stage = 3;

    // # of boxes
    int total[3] = {7,3,4};

    int map[3][8][9] = {
                        {
                          {0,1,1,1,1,1,1,1,1},
                          {0,1,4,1,4,0,2,0,1},
                          {1,1,5,1,1,1,0,0,1},
                          {1,0,2,0,1,0,3,0,1},
                          {1,0,0,2,2,4,2,4,1},
                          {1,0,0,4,0,0,2,0,1},
                          {1,1,1,1,1,1,4,0,1},
                          {0,0,0,0,0,1,1,1,1}
                        },
                        {
                          {1,1,1,1,1,1,1,1,1},
                          {1,1,1,1,4,4,4,1,1},
                          {1,5,0,1,1,2,0,1,1},
                          {1,0,0,2,0,0,0,1,1},
                          {1,1,0,1,1,0,0,1,1},
                          {1,1,0,0,0,1,2,1,1},
                          {1,1,1,1,0,0,0,1,1},
                          {1,1,1,1,1,1,1,1,1}
                        },
                        {
                          {1,1,1,1,1,1,1,1,1},
                          {1,1,1,1,4,4,4,1,1},
                          {1,5,0,1,1,2,0,1,1},
                          {1,0,0,2,0,0,0,1,1},
                          {1,1,0,1,1,0,0,1,1},
                          {1,1,0,0,0,1,2,1,1},
                          {1,4,2,0,0,0,0,1,1},
                          {1,1,1,1,1,1,1,1,1}
                        }
                       };//[stage][x][y];

    QGraphicsPixmapItem *GraphicMap[8][9];
    player *Player;
    target *Target[7];
    box *Box[7];

    bool check(int x, int y, int direction);
    int check_box(int x, int y, int direction);
    int find_box(int x, int y);
    void Test();

public slots:
    void restart();
    void next_level();

};

#endif // MAINWINDOW_H
