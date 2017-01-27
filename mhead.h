#ifndef MHEAD_H
#define MHEAD_H

/*
 * I use it as a total header.h to arrange all the library citations.
 * Nothing much to say about.
 */

#include <QMessageBox>
#include <QMouseEvent>
#include <QList>
#include <QPixmap>
#include <QLabel>
#include <QThread>
#include <QTime>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QSplashScreen>
#include <QPixmap>
#include <QMediaPlayer>
#include <QResource>


struct Steps{
    int x,y,color;
};

const int drct[8][2] = {
    {-1, -1},
    {0, -1},
    {1, -1},
    {1, 0},
    {1, 1},
    {0, 1},
    {-1, 1},
    {-1, 0},
};                                                   //8 directions of the gameboard

const int w[8][8] = {
    { 1000,-100, 100, 100, 100, 100,-100,1000 },
    { -100,-100, -30, -30, -30, -30,-100,-100 },
    { 100, -30,  50,  50,  50,  50, -30, 100 },
    { 100, -30,  50,  50,  50,  50, -30, 100 },
    { 100, -30,  50,  50,  50,  50, -30, 100 },
    { 100, -30,  50,  50,  50,  50, -30, 100 },
    { -100,-100, -30, -30, -30, -30,-100,-100 },
    { 1000,-100, 100, 100, 100, 100,-100,1000 }
};                                                    //the matrix of weights of every points

#endif // MHEAD_H
