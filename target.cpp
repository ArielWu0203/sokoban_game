#include "target.h"

target::target()
{
    this->pixel = 64;
    this->x_origin = 0;
    this->y_origin = 0;
}

void target::set_origin(int x, int y)
{
    this->x_origin = x;
    this->y_origin = y;
}
