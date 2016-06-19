#ifndef PIGGY_H
#define PIGGY_H

#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>

#include <gameitem.h>

#define PIGGY_DENSITY 1.0f
#define PIGGY_FRICTION 0.8f
#define PIGGY_RESTITUTION 0.3f

class Piggy : public GameItem
{
    Q_OBJECT
public:
    Piggy(float x, float y, float radius,float xbound,QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    bool collide(b2Vec2 birdPos);
    float boundary;
    int hp;
public slots:
    void OutOfBound();
};

#endif // PIGGY_H
