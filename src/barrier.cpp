#include "barrier.h"

Barrier::Barrier(float x, float y, float w,float h, float xbound, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSizeF(w,h);
    boundary = xbound;

    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.position.Set(x,y);
    bodydef.bullet = true;
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);

    b2PolygonShape barrierBox;
    barrierBox.SetAsBox(w/2,h/2);
    b2FixtureDef fixturedef;
    fixturedef.shape = &barrierBox;
    fixturedef.friction = BARRIER_FRICTION;
    fixturedef.density = BARRIER_DENSITY;
    fixturedef.restitution = BARRIER_RESTITUTION;
    g_body->CreateFixture(&fixturedef);
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&barrierBox,0.0f);

    //connect(timer ,SIGNAL(timeout()), this,SLOT(OutOfBound()));
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
}

void Barrier::OutOfBound()
{
    b2Vec2 pos = g_body->GetPosition();
    if(pos.x <= 0 || pos.x >= boundary){
        b2Vec2 velocity = g_body->GetLinearVelocity();
        g_body->SetLinearVelocity(b2Vec2(-velocity.x*1.05,velocity.y));
    }
}
