#ifndef SAVEGAME_H
#define SAVEGAME_H
/*
 * as annoying as loading
 */
#include <QDialog>
#include "mhead.h"

namespace Ui {
class SaveGame;
}

class SaveGame : public QDialog
{
    Q_OBJECT

public:
    explicit SaveGame(QWidget *parent = 0);
    ~SaveGame();

private slots:
    void on_pushButton_clicked();             //save game data in data1/2/3

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::SaveGame *ui;
};

#endif // SAVEGAME_H
