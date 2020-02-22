#include "box.h"

box::box(int x, int y)
{
    this->x_grid = x;
    this->y_grid = y;
    this->pixel = 64;
}

void box::set_origin(int x, int y) {
    this->x_origin = x;
    this->y_origin = y;
    this->set_pos(x,y);
}

void box::back_origin(){
    this->set_pos(this->x_origin,this->y_origin);
}

void box::set_pos(int x, int y)
{
    this->x_grid = x;
    this->y_grid = y;
}

bool box::is_it(int x, int y)
{
    if (this->x_grid == x && this->y_grid == y) {return true;}
    return false;
}

void box::move_right(int x, int y){
    if(is_it(x,y)) {
        this->set_pos(x+1,y);
        this->setPos(this->x()+this->pixel, this->y());
    }
}

void box::move_left(int x, int y){
    if(is_it(x,y)) {
        this->set_pos(x-1,y);
        this->setPos(this->x()-this->pixel, this->y());
    }
}

void box::move_up(int x, int y){
    if(is_it(x,y)) {
        this->set_pos(x,y-1);
        this->setPos(this->x(), this->y()-this->pixel);
    }
}

void box::move_down(int x, int y){
    if(is_it(x,y)) {
        this->set_pos(x,y+1);
        this->setPos(this->x(), this->y()+this->pixel);
    }
}

