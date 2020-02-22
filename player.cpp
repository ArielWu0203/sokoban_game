#include "player.h"

player::player(int x, int y)
{
    this->x_grid = x;
    this->y_grid = y;
    this->pixel = 64;
}

void player::set_origin(int x, int y){
    this->x_origin = x;
    this->y_origin = y;
    this->set_pos(x,y);
}

void player::back_origin() {
    this->set_pos(this->x_origin,this->y_origin);
}

void player::set_pos(int x, int y){
    this->x_grid = x;
    this->y_grid = y;
}

void player::move_right(int x, int y)
{
    this->set_pos(x,y);
    this->setPos(this->x()+this->pixel, this->y());
}

void player::move_left(int x, int y)
{
    this->set_pos(x,y);
    this->setPos(this->x()-this->pixel, this->y());
}

void player::move_up(int x, int y)
{
    this->set_pos(x,y);
    this->setPos(this->x(), this->y()-this->pixel);
}

void player::move_down(int x, int y)
{
    this->set_pos(x,y);
    this->setPos(this->x(), this->y()+this->pixel);
}
