#ifndef BARRIER_H
#define BARRIER_H

#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>

#include <gameitem.h>

#define BARRIER_DENSITY 1.0f
#define BARRIER_FRICTION 0.8f
#define BARRIER_RESTITUTION 0.5f

class Barrier : public GameItem
{
    Q_OBJECT
public:
    Barrier(float x, float y, float w,float h,float xbound,QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    float boundary;
public slots:
    void OutOfBound();
};

#endif // BARRIER_H
