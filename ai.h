#ifndef AI_H
#define AI_H

/*
 * This part is an AI class which receives a signal before computation and
 * gives back a solution which it "thinks" is the best among all possibles.
 */

#include <QObject>
#include "mhead.h"

#define Max 100000

class AI : public QObject
{
    Q_OBJECT
public:
    explicit AI(QObject *parent = 0);

signals:
    void sendAIStep(int x, int y, int color);         //the feedback

public slots:
    void recvCall(QList<Steps> steps, int color);     //the signal

private:
    void TakeMoves(int x, int y, int color);          //suppose (x, y) is taken
    bool Reverse(int x, int y, int dx, int dy, int color, bool rev);
    QList<Steps> FindPossible(int color);             //reverse and findpossible, the same as in the widget class
    double Reckon();                                  //the Eval-function, just a simple model
    double MaxSearch(int d, double& beta);
    double MinSearch(int d, double& alpha);           //Minimax Search
    double EndGame();                                 //EndGame Judgement
};

#endif // AI_H
