#include "mhead.h"
#include "newgamesettings.h"
#include "widget.h"
#include "ai.h"
#include "savegame.h"
#include "loadgame.h"
#include <QApplication>

int map[8][8] = {};
int mode;
int maxDepth;
QString p1, p2;
int cnt1, cnt2;
int recordBoard[8][8][64] = {};
Steps recordSteps[64] = {};
int recordNum = 0;
int testBoard[8][8][64];
int testNum;



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmapSplash(":/splash.png");
    QSplashScreen theSplash(pixmapSplash);                     //setting the beginning splash
    theSplash.show();
    theSplash.showMessage(QObject::tr("Loading..."), Qt::AlignLeft|Qt::AlignBottom);
    a.processEvents();
    Widget w;
    NewGameSettings settings;
    AI ai;
    SaveGame sg;
    LoadGame lg;
    QObject::connect(&w, SIGNAL(displaySettings()), &settings, SLOT(exec()));
    QObject::connect(&settings, SIGNAL(sendSetGameBoard()), &w, SLOT(setNewGameBoard()));
    QObject::connect(&w, SIGNAL(callForAI(QList<Steps>,int)), &ai, SLOT(recvCall(QList<Steps>,int)));
    QObject::connect(&ai, SIGNAL(sendAIStep(int,int,int)), &w, SLOT(takeStep(int,int,int)));
    QObject::connect(&lg, SIGNAL(updateBoard(QString)), &w, SLOT(update(QString)));
    QObject::connect(&w, SIGNAL(pushSave()), &sg, SLOT(exec()));
    QObject::connect(&w, SIGNAL(pushLoad()), &lg, SLOT(exec()));

    w.thread()->sleep(3);
    w.show();
    theSplash.finish(&w);

    return a.exec();
}
