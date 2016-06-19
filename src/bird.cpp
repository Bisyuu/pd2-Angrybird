#include "bird.h"

Bird::Bird(int type,float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSizeF(radius*2,radius*2);
    birdtype = type;

    b2BodyDef bodydef;
    bodydef.type = b2_staticBody;
    bodydef.bullet = true;
    bodydef.position.Set(x,y);
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);

    bodyshape.m_radius = radius;
    fixturedef.shape = &bodyshape;
    fixturedef.density = BIRD_DENSITY;
    fixturedef.friction = BIRD_FRICTION;
    fixturedef.restitution = BIRD_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);

    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
}

void Bird::doSomething()
{
    switch(birdtype)
    {
    case 1:
    {
        if(!haveUsed)
        {
            b2Vec2 vel = g_body->GetLinearVelocity();
            g_body->SetLinearVelocity(b2Vec2(vel.x+15,vel.y));
            g_pixmap.setPixmap(QPixmap(":/image/bird2-2.png").scaled(60,48));
        }
        break;
    }
    case 2:
    {
        if(!haveUsed)
        {
            bodyshape.m_radius = bodyshape.m_radius*1.5;
            fixturedef.shape = &bodyshape;
            fixturedef.density = BIRD_DENSITY*0.66;
            g_body->CreateFixture(&fixturedef);
            g_pixmap.setPixmap(g_pixmap.pixmap().scaled(108,108));
        }
        break;
    }
    case 3:
    {
        if(!haveUsed)
        {
            b2Vec2 vel = g_body->GetLinearVelocity();
            g_body->SetLinearVelocity(b2Vec2(vel.x,vel.y-20));
            g_body->SetAngularVelocity(-500*3.14159f);
            g_pixmap.setPixmap(QPixmap(":/image/bird4-2.png").scaled(60,60));
        }
        break;
    }
    default:
        break;
    }
    haveUsed = true;
}
