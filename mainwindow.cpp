#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QDebug"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(0,0,513,577))
{
    ui->setupUi(this);
//    setCentralWidget(ui->graphicsView);
    ui->graphicsView->setScene(scene);

    // pixel
    pixel = 64;

    // stage
    now_stage = 0;

    // target number
    get_target_num = 0;

    // player
    Player = new player(0,0);

    // Add wall and ground
    for(int i=0; i<8; i++) {
        for(int j=0;j<9;j++) {
            if(map[now_stage][i][j] == WALL) {
                GraphicMap[i][j] = new QGraphicsPixmapItem(QPixmap(":/res/wall.png"));
            } else {
                GraphicMap[i][j] = new QGraphicsPixmapItem(QPixmap(":/res/ground.png"));
            }
            GraphicMap[i][j]->setPos(i*pixel,j*pixel);
            scene->addItem(GraphicMap[i][j]);
        }
    }

    // Add player
    bool flag = false;
    for(int i=0; i<8; i++) {
        for(int j=0;j<9;j++) {
           if(map[now_stage][i][j] == PLAYER) {
               Player->set_origin(i,j);
               Player->setPixmap(QPixmap(":/res/player_front.png"));
               Player->setPos(i*pixel,j*pixel);
               scene->addItem(Player);
               flag = true;
               break;
           }
        }
        if(flag) break;
    }

    // Add targets
    for (int i=0;i<total[now_stage]; i++) {
        Target[i] = new target();
        Target[i]->setPixmap(QPixmap(":/res/target.png"));
    }
    int target_index = 0;
    for(int i=0; i<8; i++) {
        for(int j=0;j<9;j++) {
            if(map[now_stage][i][j] == TARGET || map[now_stage][i][j] == FULLBOX) {
                Target[target_index]->set_origin(i,j);
                Target[target_index]->setPos(i*pixel, j*pixel);
                scene->addItem(Target[target_index]);
                target_index++;
            }
        }
    }

    // Add boxes
    for (int i=0;i<total[now_stage]; i++) {
        Box[i] = new box(0,0);
    }
    int box_index = 0;
    for(int i=0; i<8; i++) {
        for(int j=0;j<9;j++) {
            if(map[now_stage][i][j] == EMPTYBOX) {
                Box[box_index]->set_origin(i,j);
                Box[box_index]->setPixmap(QPixmap(":/res/empty_box.png"));
                Box[box_index]->setPos(i*pixel,j*pixel);
                scene->addItem(Box[box_index]);
                box_index++;
            } else if (map[now_stage][i][j] == FULLBOX) {
                Box[box_index]->set_origin(i,j);
                Box[box_index]->setPixmap(QPixmap(":/res/full_box.png"));
                Box[box_index]->setPos(i*pixel,j*pixel);
                scene->addItem(Box[box_index]);
                box_index++;
                get_target_num++;
            }
        }
    }

    // Signals & Slots
    connect(this, SIGNAL(Right(int,int)), Player, SLOT(move_right(int,int)));
    connect(this, SIGNAL(Left(int,int)), Player, SLOT(move_left(int,int)));
    connect(this, SIGNAL(Up(int,int)), Player, SLOT(move_up(int,int)));
    connect(this, SIGNAL(Down(int,int)), Player, SLOT(move_down(int,int)));
    for(int i=0;i<total[now_stage];i++) {
        connect(this, SIGNAL(Right(int,int)), Box[i], SLOT(move_right(int,int)));
        connect(this, SIGNAL(Left(int,int)), Box[i], SLOT(move_left(int,int)));
        connect(this, SIGNAL(Up(int,int)), Box[i], SLOT(move_up(int,int)));
        connect(this, SIGNAL(Down(int,int)), Box[i], SLOT(move_down(int,int)));
    }
    connect(ui->pushButton, SIGNAL(clicked(bool)),this,SLOT(restart()));
    connect(ui->pushButton_2, SIGNAL(clicked(bool)),this, SLOT(next_level()));
}

MainWindow::~MainWindow()
{
    delete scene;
    delete Player;
    for(int i=0; i<8; i++) {
        for(int j=0;j<9;j++) {
            delete GraphicMap[i][j];
        }
    }
    for (int i=0;i<total[now_stage]; i++) {
        delete Box[i];
        delete Target[i];
    }
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
    int x_now = 0, y_now = 0;
    x_now = Player->x_grid;
    y_now = Player->y_grid;
    switch (e->key()) {
    case Qt::Key_D:
        if(check(x_now, y_now, RIGHT)) {
            x_now++;
            emit Right(x_now, y_now);
            Player->setPixmap(QPixmap(":/res/player_right.png"));
        }
        break;
    case Qt::Key_A:
        if(check(x_now, y_now, LEFT)) {
            x_now--;
            emit Left(x_now, y_now);
            Player->setPixmap(QPixmap(":/res/player_left.png"));
        }
        break;
    case Qt::Key_W:
        if(check(x_now, y_now, UP)) {
            y_now--;
            emit Up(x_now, y_now);
            Player->setPixmap(QPixmap(":/res/player_back.png"));
        }
        break;
    case Qt::Key_S:
        if(check(x_now, y_now, DOWN)) {
            y_now++;
            emit Down(x_now, y_now);
            Player->setPixmap(QPixmap(":/res/player_front.png"));
        }
        break;
    default:
        break;
    }

    Test();

    // Success?
    if(get_target_num == total[now_stage]) {
        QMessageBox msgBox;
        msgBox.setText("Success!!!");
        msgBox.setInformativeText("Next Level?");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Ok:
            next_level();
            break;
        case QMessageBox::Cancel:
            restart();
            break;
        default:
            break;
        }
    }
}

void MainWindow::Test() {
    for(int i=0; i<9; i++) {
        QString str = "";
        for(int j=0;j<8;j++) {
            str += QString::number( map[now_stage][j][i] );
        }
        qDebug()<<str;
    }
    qDebug()<<endl;
}

bool MainWindow::check(int x, int y, int direction) {
    int next_x = x, next_y = y;
    // check nexp step
    if(direction == RIGHT) {
        next_x++;
    } else if (direction == LEFT) {
        next_x--;
    } else if (direction == UP) {
        next_y--;
    } else if (direction == DOWN) {
        next_y++;
    }

    // is ground or target
    if (map[now_stage][next_x][next_y] == GROUND || map[now_stage][next_x][next_y] == TARGET) {
        if (map[now_stage][x][y] == TWO) {map[now_stage][x][y] = TARGET;}
        else {map[now_stage][x][y] = GROUND;}
        if (map[now_stage][next_x][next_y] == TARGET) {map[now_stage][next_x][next_y] = TWO;}
        else {map[now_stage][next_x][next_y] = PLAYER;}
        return true;
    }

    // check wall
    else if (map[now_stage][next_x][next_y] == WALL) {
        return false;
    }

    // check box
    else {
        // collide box or wall
        int event = check_box(next_x,next_y, direction);
        if(event == NOMOVE) {
            return false;
        }
        // is ground or target
        else {
            // update now grid
            if (map[now_stage][x][y] == TWO) {map[now_stage][x][y] = TARGET;}
            else {map[now_stage][x][y] = GROUND;}

            // update next grid
            if (map[now_stage][next_x][next_y] == GROUND) {map[now_stage][next_x][next_y] = PLAYER;}
            else {map[now_stage][next_x][next_y] = TWO;}

            // change picture
            if (event == PICK) {
                int index = find_box(next_x,next_y);
                Box[index]->setPixmap(QPixmap(":/res/full_box.png"));
                get_target_num++;

            }
            else if (event == DROP){
                int index = find_box(next_x,next_y);
                Box[index]->setPixmap(QPixmap(":/res/empty_box.png"));
                get_target_num--;
            }

            return true;
        }

    }
}

int MainWindow::check_box(int x, int y, int direction)
{
    int next_x = x, next_y = y;
    // check nexp step
    if(direction == RIGHT) {
        next_x++;
    } else if (direction == LEFT) {
        next_x--;
    } else if (direction == UP) {
        next_y--;
    } else if (direction == DOWN) {
        next_y++;
    }

    if (map[now_stage][next_x][next_y] == GROUND) {
        if (map[now_stage][x][y] == EMPTYBOX) {
            map[now_stage][next_x][next_y] = EMPTYBOX;
            map[now_stage][x][y] = GROUND;
            return MOVE;
        }
        else {
            map[now_stage][next_x][next_y] = EMPTYBOX;
            map[now_stage][x][y] = TARGET;
            return DROP;
        }

    }
    else if (map[now_stage][next_x][next_y] == TARGET) {
        if (map[now_stage][x][y] == EMPTYBOX) {
            map[now_stage][next_x][next_y] = FULLBOX;
            map[now_stage][x][y] = GROUND;
            return PICK;
        }
        else {
            map[now_stage][next_x][next_y] = FULLBOX;
            map[now_stage][x][y] = TARGET;
            return MOVE;
        }
    }
    return NOMOVE;
}

int MainWindow::find_box(int x, int y)
{
    for (int i=0;i<total[now_stage];i++) {
        if(Box[i]->is_it(x,y)) {return i;}
    }
}

void MainWindow::restart()
{
    get_target_num = 0;
    for (int i=0;i<8;i++) {
        for (int j=0;j<9;j++) {
            if(map[now_stage][i][j]==TARGET || map[now_stage][i][j]==TWO || map[now_stage][i][j]==FULLBOX) {map[now_stage][i][j] = TARGET;}
            else if (map[now_stage][i][j]!=WALL) {map[now_stage][i][j]=GROUND;}
        }
    }

    for (int i=0;i<total[now_stage];i++) {
        // reset Box
        Box[i]->back_origin();
        Box[i]->setPos(pixel*Box[i]->x_origin, pixel*Box[i]->y_origin);

        if(map[now_stage][Box[i]->x_origin][Box[i]->y_origin] == TARGET) {
            map[now_stage][Box[i]->x_origin][Box[i]->y_origin] = FULLBOX;
            Box[i]->setPixmap(QPixmap(":/res/full_box.png"));
            get_target_num++;
        } else {
            map[now_stage][Box[i]->x_origin][Box[i]->y_origin] = EMPTYBOX;
            Box[i]->setPixmap(QPixmap(":/res/empty_box.png"));
        }
    }

    // reset player
    map[now_stage][Player->x_origin][Player->y_origin] = PLAYER;
    Player->back_origin();
    Player->setPos(pixel*Player->x_origin, pixel*Player->y_origin);
    Player->setPixmap(QPixmap(":/res/player_front.png"));
}

void MainWindow::next_level() {

    if((total_stage-1) == now_stage) {
        QMessageBox msgBox;
        msgBox.setText("Compelete!!!");
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    } else {
        // Clean level
        restart();
        // Next level Start!
        now_stage++;
        get_target_num = 0;
        // Wall & Ground
        for(int i=0; i<8; i++) {
            for(int j=0;j<9;j++) {
                if(map[now_stage][i][j] == WALL) {
                    GraphicMap[i][j]->setPixmap(QPixmap(":/res/wall.png"));
                } else {
                    GraphicMap[i][j]->setPixmap(QPixmap(":/res/ground.png"));
                }
                GraphicMap[i][j]->setPos(i*pixel,j*pixel);
            }
        }
        // Add player
        bool flag = false;
        for(int i=0; i<8; i++) {
            for(int j=0;j<9;j++) {
               if(map[now_stage][i][j] == PLAYER) {
                   Player->set_origin(i,j);
                   Player->setPixmap(QPixmap(":/res/player_front.png"));
                   Player->setPos(i*pixel,j*pixel);
                   scene->addItem(Player);
                   flag = true;
                   break;
               }
            }
            if(flag) break;
        }

        // Add targets
        int target_index = 0;
        for(int i=0; i<8; i++) {
            for(int j=0;j<9;j++) {
                if(map[now_stage][i][j] == TARGET || map[now_stage][i][j] == FULLBOX) {
                    Target[target_index]->set_origin(i,j);
                    Target[target_index]->setPos(i*pixel, j*pixel);
                    Target[target_index]->setVisible(true);
                    target_index++;
                }
            }
        }
        for(int i = target_index;i<7;i++) {
            Target[target_index]->set_origin(0,0);
            Target[target_index]->setPos(0,0);
            Target[target_index]->setVisible(false);
            target_index++;
        }

        // Add boxes
        int box_index = 0;
        for(int i=0; i<8; i++) {
            for(int j=0;j<9;j++) {
                if(map[now_stage][i][j] == EMPTYBOX) {
                    Box[box_index]->set_origin(i,j);
                    Box[box_index]->setPixmap(QPixmap(":/res/empty_box.png"));
                    Box[box_index]->setPos(i*pixel,j*pixel);
                    Box[box_index]->setVisible(true);
                    box_index++;
                } else if (map[now_stage][i][j] == FULLBOX) {
                    Box[box_index]->set_origin(i,j);
                    Box[box_index]->setPixmap(QPixmap(":/res/full_box.png"));
                    Box[box_index]->setPos(i*pixel,j*pixel);
                    Box[box_index]->setVisible(true);
                    box_index++;
                    get_target_num++;
                }
            }
        }
        for(int i = box_index;i<7;i++) {
            Box[box_index]->set_origin(0,0);
            Box[box_index]->setPos(0,0);
            Box[box_index]->setVisible(false);
            box_index++;
        }
    }
}
