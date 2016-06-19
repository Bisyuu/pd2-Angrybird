#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <QGraphicsPixmapItem>
#include <Box2D/Box2D.h>
#include <QTransform>
#include <QPainter>
#include <QtMath>

class GameItem : public QObject
{
    Q_OBJECT
public:
    GameItem(b2World *world);
    ~GameItem();
    static void setGlobalSize(QSizeF worldsize, QSizeF windowsize);

    QSizeF g_size;
    b2Body *g_body;
    b2World *g_world;
    QGraphicsPixmapItem g_pixmap;
    static QSizeF g_worldsize, g_windowsize;

public slots:
    void paint();
};

#endif // GAMEITEM_H
