#ifndef TARGET_H
#define TARGET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QDebug>

class target: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    target();
    void set_origin(int x, int y);
    int x_origin;
    int y_origin;
    int pixel;
};

#endif // TARGET_H
