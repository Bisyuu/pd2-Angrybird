#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QDesktopWidget>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <QtGlobal>
#include <iostream>
#include <QPixmap>
#include <QLabel>
#include <QTimer>
#include <QList>
#include <QDebug>

#include <gameitem.h>
#include <barrier.h>
#include <ground.h>
#include <piggy.h>
#include <bird.h>

#define World_Width 40
#define World_Height 22.5
#define k 2.8

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void showEvent(QShowEvent *);
    void closeEvent(QCloseEvent *);
    bool eventFilter(QObject *obj,QEvent *event);
    void newBird();
    void remove();

signals:
    void quitGame();

private slots:
    void tick();
    void QUITSLOT();
    void DeliverPos();

private:
    int birdCount = 0;


    QTimer timer;
    b2World *world;
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    Ground *ground;
    QMouseEvent *event2;

    QList<Bird *> birdList;
    QList<Piggy *> piggyList;
    QList<GameItem *> otherList;

};

#endif // MAINWINDOW_H
