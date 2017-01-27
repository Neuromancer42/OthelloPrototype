#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mhead.h"

namespace Ui {
class Widget;
}
/*
 * for clarity, each grid on the board has a number to represent a status
 * 0 for no pieces
 * 1 for a black piece
 * 2 for a wihte piece
 * 3 for it can be put a black piece on
 * 4 for it can be put a white piece on
 */
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QList<Steps> steps;                                 //record the current legal steps
    QTimer *timer1, *timer2;
    QMediaPlayer backgroundPlayer;                      //play the backgroundmusic
    int curcolor;

protected:
    void mousePressEvent(QMouseEvent *e);

signals:
    void sendChangeBoard(int x, int y, int id);
    void displaySettings();
    void callForStep(QString player, bool prior);       //call for the player/AI to take a step
    void callForAI(QList<Steps> steps, int color);
    void sendPlayerStep(int r, int c, int color);
    void sendEmptyStep(QString player);
    void sendEndGame();
    void pushSave();
    void pushLoad();

public slots:
    void setNewGameBoard();
    void recvChangeBoard(int x, int y, int id);
    void thinking(QString player, bool prior);           //the player/AI try to take a step
    void takeStep(int r, int c, int color);
    void emptyStep(QString player);
    void endGame();                                      //process the end of a game
    void callAI();
    void pass();
    void update(QString player);                         //update the gameboard after loading a game

private slots:
    void on_pushButtonLoad_2_clicked();

    void on_pushButtonLoad_3_clicked();

    void on_pushButtonSave_clicked();

    void on_pushButtonLoad_clicked();

private:
    Ui::Widget *ui;
    QList<QLabel*> gameBoard;
    QList<Steps> possiblesteps(int color);                //find possible steps for color black_1/white_2
    bool reversible(int x, int y, int dx, int dy, int color, bool rev);//check if the opposite color pieces can be reversed
    bool allowed;                                         //check if it is the player's turn and the player can take a step
};

#endif // WIDGET_H
