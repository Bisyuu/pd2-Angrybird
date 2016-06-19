#include "piggy.h"

Piggy::Piggy(float x, float y, float radius,float xbound, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSizeF(radius*2,radius*2);
    boundary = xbound;
    hp = 6;

    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;
    bodydef.position.Set(x,y);
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);
    b2CircleShape bodyshape;
    bodyshape.m_radius = radius;
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;
    fixturedef.density = PIGGY_DENSITY;
    fixturedef.friction = PIGGY_FRICTION;
    fixturedef.restitution = PIGGY_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);

    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));
    connect(timer, SIGNAL(timeout()), this,SLOT(OutOfBound()));

    scene->addItem(&g_pixmap);
}

bool Piggy::collide(b2Vec2 birdPos)
{
    b2Vec2 dis = g_body->GetPosition() - birdPos;

    if(dis.x*dis.x+dis.y*dis.y < 4.5)
        return true;
    else
        return false;
}

void Piggy::OutOfBound()
{
    b2Vec2 pos = g_body->GetPosition();
    if(pos.x <= 0 || pos.x >= boundary){
        b2Vec2 velocity = g_body->GetLinearVelocity();
        g_body->SetLinearVelocity(b2Vec2(-velocity.x*1.05,velocity.y));
    }
}
