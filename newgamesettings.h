#ifndef NEWGAMESETTINGS_H
#define NEWGAMESETTINGS_H

/*
 * This part is based on a list of settings about thier dogs;
 */

#include <QDialog>
#include "mhead.h"

namespace Ui {
class NewGameSettings;
}

class NewGameSettings : public QDialog
{
    Q_OBJECT

public:
    explicit NewGameSettings(QWidget *parent = 0);
    ~NewGameSettings();

protected:
    void mousePressEvent(QMouseEvent *e);

signals:
    void sendGameMode(int id);
    void sendColor(int id);
    void sendLevel(int id);
    void sendSettings(int gameMode, int color, int level);
    void sendSetGameBoard();

public slots:
    void recvGameMode(int id);
    void recvColor(int id);
    void recvLevel(int id);
    void recvSettings(int gameMode, int color, int level);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::NewGameSettings *ui;
    int curGameMode, curColor, curLevel;
};

#endif // NEWGAMESETTINGS_H
