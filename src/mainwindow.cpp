#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qApp->installEventFilter(this);
    setFixedSize(1200,625);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    scene = new QGraphicsScene(0,0,width()-2,height()-2);
    ui->graphicsView->setScene(scene);

    world = new b2World(b2Vec2(0.0f, -9.8f));

    GameItem::setGlobalSize(QSizeF(World_Width,World_Height),size());

    QLabel *background = new QLabel();
    background->setGeometry(0,0,width(),height()*5/6);
    background->setPixmap(QPixmap(":/image/Background.png").scaled(width(),height()*5/6));
    background->setAttribute(Qt::WA_TranslucentBackground);
    scene->addWidget(background);

    QLabel *slingshot = new QLabel();
    slingshot->setGeometry(width()/6,height()*5/6-180,60,180);
    slingshot->setPixmap(QPixmap(":/image/Launcher.png").scaled(60,180));
    slingshot->setAttribute(Qt::WA_TranslucentBackground);
    scene->addWidget(slingshot);

    ground = new Ground(World_Width/2.0,World_Height/12.0,World_Width,World_Height/6.0,QPixmap(":/ground.png").scaled(width(),height()/6.0),world,scene);

    otherList.push_back(new Barrier(32.0f,World_Height/6.0f+2.5f,1.0f,5.0f,World_Width,&timer,QPixmap(":/image/barrier1.png").scaled(30,150),world,scene));
    otherList.push_back(new Barrier(28.0f,World_Height/6.0f+2.5f,1.0f,5.0f,World_Width,&timer,QPixmap(":/image/barrier1.png").scaled(30,150),world,scene));
    otherList.push_back(new Barrier(30.0f,World_Height/6.0f+5.6f,5.0f,1.0f,World_Width,&timer,QPixmap(":/image/barrier2.png").scaled(150,30),world,scene));

    piggyList.push_back(new Piggy(20.0f,World_Height/6.0f,1.0f,World_Width,&timer,QPixmap(":/image/piggy.png").scaled(60,60),world,scene));
    piggyList.push_back(new Piggy(30.0f,World_Height/6.0f,1.0f,World_Width,&timer,QPixmap(":/image/piggy.png").scaled(60,60),world,scene));
    piggyList.push_back(new Piggy(30.0f,World_Height/6.0f+6.7f,1.0f,World_Width,&timer,QPixmap(":/image/piggy.png").scaled(60,60),world,scene));

    birdList.push_back(new Bird(0,World_Width/6.0f-1,World_Height/6.0f+180/45,1.0f,&timer,QPixmap(":/bird.png").scaled(60,60),world,scene));

    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(&timer,SIGNAL(timeout()),this,SLOT(DeliverPos()));

    timer.start(100/6);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(!strcmp(obj->metaObject()->className(),"QWidget"))
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(birdList[birdCount]->haveLaunch == false)
            {
                event2 = static_cast<QMouseEvent*>(event);
                birdList[birdCount]->canDrag = true;

                float x = event2->x();
                float y = event2->y();

                if( x<=0 && y/30>=World_Height*5/6 )
                    birdList[birdCount]->g_body->SetTransform(b2Vec2(0,World_Height/6),0.0f);

                else if ( x>=0 && x/30<=World_Width/2.5 && y/30>=World_Height*5/6 )
                    birdList[birdCount]->g_body->SetTransform(b2Vec2(x/30,World_Height/6),0.0f);

                else if ( x/30>=World_Width/2.5 && y/30>=World_Height*5/6 )
                    birdList[birdCount]->g_body->SetTransform(b2Vec2(World_Width/2.5,World_Height/6),0.0f);

                else if ( x<=0 && y/30<=World_Height*5/6 && y/30>=World_Height/6)
                    birdList[birdCount]->g_body->SetTransform(b2Vec2(0,World_Height-y/30),0.0f);

                else if ( x/30>=World_Width/2.5 && y/30<=World_Height*5/6 && y/30>=World_Height/6 )
                    birdList[birdCount]->g_body->SetTransform(b2Vec2(World_Width/2.5,World_Height-y/30),0.0f);

                else if ( x<=0 && y/30<=World_Height/6 )
                    birdList[birdCount]->g_body->SetTransform(b2Vec2(0,World_Height*5/6),0.0f);

                else if ( x>=0 && x/30<=World_Width/2.5 && y/30<=World_Height/6 )
                    birdList[birdCount]->g_body->SetTransform(b2Vec2(x/30,World_Height*5/6),0.0f);

                else if ( x/30>=World_Width/2.5 && y/30<=World_Height/6 )
                    birdList[birdCount]->g_body->SetTransform(b2Vec2(World_Width/2.5,World_Height*5/6),0.0f);

                else
                    birdList[birdCount]->g_body->SetTransform(b2Vec2(x/30,World_Height-y/30),0.0f);
            }
            else if(!birdList[birdCount]->haveUsed)
            {
                birdList[birdCount]->doSomething();
            }
        }

        if(event->type() == QEvent::MouseMove)
        {
            if(birdList[birdCount]->canDrag == true)
            {
                float x = event2->x();
                float y = event2->y();

                if( x<=0 && y/30>=World_Height*5/6 )
                    birdList[birdCount]->g_body->SetTransform(b2Vec2(0,World_Height/6),0.0f);

                else if ( x>=0 && x/30<=World_Width/2.5 && y/30>=World_Height*5/6 )
                    birdList[birdCount]->g_body->SetTransform(b2Vec2(x/30,World_Height/6),0.0f);

                else if ( x/30>=World_Width/2.5 && y/30>=World_Height*5/6 )
                    birdList[birdCount]->g_body->SetTransform(b2Vec2(World_Width/2.5,World_Height/6),0.0f);

                else if ( x<=0 && y/30<=World_Height*5/6 && y/30>=World_Height/6)
                    birdList[birdCount]->g_body->SetTransform(b2Vec2(0,World_Height-y/30),0.0f);

                else if ( x/30>=World_Width/2.5 && y/30<=World_Height*5/6 && y/30>=World_Height/6 )
                    birdList[birdCount]->g_body->SetTransform(b2Vec2(World_Width/2.5,World_Height-y/30),0.0f);

                else if ( x<=0 && y/30<=World_Height/6 )
                    birdList[birdCount]->g_body->SetTransform(b2Vec2(0,World_Height*5/6),0.0f);

                else if ( x>=0 && x/30<=World_Width/2.5 && y/30<=World_Height/6 )
                    birdList[birdCount]->g_body->SetTransform(b2Vec2(x/30,World_Height*5/6),0.0f);

                else if ( x/30>=World_Width/2.5 && y/30<=World_Height/6 )
                    birdList[birdCount]->g_body->SetTransform(b2Vec2(World_Width/2.5,World_Height*5/6),0.0f);

                else
                    birdList[birdCount]->g_body->SetTransform(b2Vec2(x/30,World_Height-y/30),0.0f);
            }
        }

        if(event->type() == QEvent::MouseButtonRelease)
        {
            if(birdList[birdCount]->haveLaunch == false)
            {
                birdList[birdCount]->canDrag = false;
                birdList[birdCount]->g_body->SetType(b2_dynamicBody);

                float dx = birdList[birdCount]->g_body->GetPosition().x - World_Width/6.0-1;
                float dy = birdList[birdCount]->g_body->GetPosition().y - World_Height/6.0-180/35;

                birdList[birdCount]->g_body->SetLinearVelocity(b2Vec2(-k*dx,-k*dy));
            }
            birdList[birdCount]->haveLaunch = true;
        }

        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

            switch(keyEvent->key())
            {
            case Qt::Key_Space:
                if(birdList[birdCount]->haveLaunch == true && birdList[birdCount]->canDrag == false)
                    newBird();
                break;

            case Qt::Key_Escape:
            {
                disconnect(&timer,SIGNAL(timeout()),this,SLOT(DeliverPos()));
                remove();

                otherList.push_back(new Barrier(32.0f,World_Height/6.0f+2.5f,1.0f,5.0f,World_Width,&timer,QPixmap(":/image/barrier1.png").scaled(30,150),world,scene));
                otherList.push_back(new Barrier(28.0f,World_Height/6.0f+2.5f,1.0f,5.0f,World_Width,&timer,QPixmap(":/image/barrier1.png").scaled(30,150),world,scene));
                otherList.push_back(new Barrier(30.0f,World_Height/6.0f+5.6f,5.0f,1.0f,World_Width,&timer,QPixmap(":/image/barrier2.png").scaled(150,30),world,scene));

                piggyList.push_back(new Piggy(20.0f,World_Height/6.0f,1.0f,World_Width,&timer,QPixmap(":/image/piggy.png").scaled(60,60),world,scene));
                piggyList.push_back(new Piggy(30.0f,World_Height/6.0f,1.0f,World_Width,&timer,QPixmap(":/image/piggy.png").scaled(60,60),world,scene));
                piggyList.push_back(new Piggy(30.0f,World_Height/6.0f+6.7f,1.0f,World_Width,&timer,QPixmap(":/image/piggy.png").scaled(60,60),world,scene));

                birdList.push_back(new Bird(0,World_Width/6.0f-1,World_Height/6.0f+180/45,1.0f,&timer,QPixmap(":/bird.png").scaled(60,60),world,scene));

                birdCount = 0;

                connect(&timer,SIGNAL(timeout()),this,SLOT(DeliverPos()));

                break;
            }
            default:
                break;
            }
        }
    }

    return false;
}

void MainWindow::newBird()
{
    int rand = qrand()%4;
    switch (rand) {
    case 0:
        birdList.push_back(new Bird(0,0.0f,World_Height*11/12.0f,1.0f,&timer,QPixmap(":/bird.png").scaled(60,60),world,scene));
        break;
    case 1:
        birdList.push_back(new Bird(1,0.0f,World_Height*11/12.0f,0.8f,&timer,QPixmap(":/image/bird2.png").scaled(48,48),world,scene));
        break;
    case 2:
        birdList.push_back(new Bird(2,0.0f,World_Height*11/12.0f,1.2f,&timer,QPixmap(":/image/bird3.png").scaled(72,72),world,scene));
        break;
    case 3:
        birdList.push_back(new Bird(3,0.0f,World_Height*11/12.0f,1.0f,&timer,QPixmap(":/image/bird4.png").scaled(84,60),world,scene));
        break;
    default:
        break;
    }

    birdCount++;
}

void MainWindow::remove()
{
    int i=0;
    int size[3] = {otherList.size(),piggyList.size(),birdList.size()};

    while(1){
        if(!otherList.isEmpty()){
            otherList[size[0]-1-i++]->~GameItem();
            otherList.removeLast();
        }
        else{
            i=0;
            break;
        }
    }

    while(1){
        if(!piggyList.isEmpty()){
            piggyList[size[1]-1-i++]->~GameItem();
            piggyList.removeLast();
        }
        else{
            i=0;
            break;
        }
    }

    while(1){
        if(!birdList.isEmpty()){
            birdList[size[2]-1-i++]->~GameItem();
            birdList.removeLast();
        }
        else break;
    }
}

void MainWindow::DeliverPos()
{
    b2Vec2 birdPos = birdList[birdCount]->g_body->GetPosition();

    for(int i=0;i<piggyList.size();i++)
    {
        if(!piggyList.isEmpty())
        {
            if(piggyList[i]->collide(birdPos))
            {
                b2Vec2 v = birdList[birdCount]->g_body->GetLinearVelocity();
                if(v.x*v.x+v.y*v.y >= 100)
                {
                    switch(piggyList[i]->hp)
                    {
                    case 5:
                        piggyList[i]->g_pixmap.setPixmap(QPixmap(":/image/piggy2.png"));
                        piggyList[i]->hp--;
                        break;
                    case 2:
                        piggyList[i]->g_pixmap.setPixmap(QPixmap(":/image/piggy3.png"));
                        piggyList[i]->hp--;
                        break;
                    case 0:
                        piggyList.move(i,piggyList.size()-1);
                        piggyList[piggyList.size()-1]->~GameItem();
                        piggyList.removeLast();
                        break;
                    default:
                        if(piggyList[i]->hp>0)
                            piggyList[i]->hp--;
                        break;
                    }
                }
            }
        }
        else break;
    }
}

void MainWindow::closeEvent(QCloseEvent *)
{
    emit quitGame();
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
}

void MainWindow::QUITSLOT()
{
    std::cout << "Quit Game Signal receive !" << std::endl ;
}
