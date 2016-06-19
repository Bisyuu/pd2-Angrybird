#ifndef BIRD_H
#define BIRD_H

#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>

#include <gameitem.h>

#define BIRD_DENSITY 1.0f
#define BIRD_FRICTION 0.5f
#define BIRD_RESTITUTION 0.5f

class Bird : public GameItem
{
public:
    Bird(int type,float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);

    void doSomething();
    int birdtype = 0;
    bool canDrag = false;
    bool haveUsed = false;
    bool haveLaunch = false;
private:
    b2CircleShape bodyshape;
    b2FixtureDef fixturedef;
};

#endif // BIRD_H
