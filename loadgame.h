#ifndef LOADGAME_H
#define LOADGAME_H

/*
 * This part is about loading the data.
 * It's just quite annoying to settling File I/O with zero foundation.
 */
#include <QDialog>
#include "mhead.h"

namespace Ui {
class LoadGame;
}

class LoadGame : public QDialog
{
    Q_OBJECT

public:
    explicit LoadGame(QWidget *parent = 0);
    ~LoadGame();

signals:
    void updateBoard(QString player);      //send signals to update the gameboard after loading a data

private slots:
    void on_pushButton_clicked();          //loading from data1/2/3

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::LoadGame *ui;
};

#endif // LOADGAME_H
