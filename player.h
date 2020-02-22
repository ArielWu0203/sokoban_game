#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QDebug>

class player: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    player(int x, int y);
    void set_pos(int x, int y);
    void set_origin(int x, int y);
    void back_origin();
    int x_grid;
    int y_grid;
    int x_origin;
    int y_origin;
    int pixel;

public slots:
    void move_right(int x, int y);
    void move_left(int x,int y);
    void move_up(int x,int y);
    void move_down(int x,int y);
};

#endif // PLAYER_H
