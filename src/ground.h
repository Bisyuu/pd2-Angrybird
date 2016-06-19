#ifndef GROUND_H
#define GROUND_H

#include <QGraphicsScene>

#include <gameitem.h>

class Ground : public GameItem
{
public:
    Ground(float x, float y, float w, float h, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};

#endif // GROUND_H
