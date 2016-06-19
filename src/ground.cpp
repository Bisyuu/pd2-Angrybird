#include <ground.h>

Ground::Ground(float x, float y, float w, float h, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    g_pixmap.setPixmap(pixmap);
    g_size = QSizeF(w,h);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(x,y);
    g_body = world->CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(w/2,h/2);
    g_body->CreateFixture(&groundBox,0.0f);
    scene->addItem(&g_pixmap);
    paint();
}
