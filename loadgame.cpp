#include "loadgame.h"
#include "ui_loadgame.h"

extern int map[8][8];
extern int cnt1;
extern int cnt2;
extern int recordBoard[8][8][64];
extern Steps recordSteps[64];
extern int recordNum;
extern QString p1;
extern QString p2;
extern int maxDepth;
extern int mode;

LoadGame::LoadGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadGame)
{
    ui->setupUi(this);
}

LoadGame::~LoadGame()
{
    delete ui;
}

void LoadGame::on_pushButton_clicked()
{
    int tempColor, tempmap[8][8] = {};
    QFile infile("data1.txt");
    if (!infile.open(QIODevice::ReadOnly))             //Loading Fail information
    {
        QMessageBox::warning(this, tr("Loading"), tr("Fail to load data."));
        return;
    }
    QTextStream tsIn( & infile);
    tsIn >> tempColor >> p1 >> p2;                      //read the data and restore the saved game.
    int i, j;
    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
            tsIn >> tempmap[i][j];
    }

    QMessageBox::information(this, tr("Loading"), tr("Complete Loading."));

    infile.close();
    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
        {
            map[i][j] = tempmap[i][j];
            recordBoard[i][j][0] = map[i][j];
            recordNum = 0;
        }
    }
    if (tempColor == 1)                                 //call for the update slot to update the gameboard
    {
        emit updateBoard(p1);
    }
    else
    {
        emit updateBoard(p2);
    }

    LoadGame::close();
}
                                                        //the following two are the same
void LoadGame::on_pushButton_2_clicked()
{
    int tempColor, tempmap[8][8] = {};
    QFile infile("data2.txt");
    if (!infile.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, tr("Loading"), tr("Fail to load data."));
        return;
    }
    QTextStream tsIn( & infile);
    tsIn >> tempColor >> p1 >> p2;
    int i, j;
    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
            tsIn >> tempmap[i][j];
    }

    QMessageBox::information(this, tr("Loading"), tr("Complete Loading."));

    infile.close();
    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
        {
            map[i][j] = tempmap[i][j];
            recordBoard[i][j][0] = map[i][j];
            recordNum = 0;
        }
    }
    if (tempColor == 1)
    {
        emit updateBoard(p1);
    }
    else
    {
        emit updateBoard(p2);
    }

    LoadGame::close();
}



void LoadGame::on_pushButton_3_clicked()
{
    int tempColor, tempmap[8][8] = {};
    QFile infile("data3.txt");
    if (!infile.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, tr("Loading"), tr("Fail to load data."));
        return;
    }
    QTextStream tsIn( & infile);
    tsIn >> tempColor >> p1 >> p2;
    int i, j;
    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
            tsIn >> tempmap[i][j];
    }

    QMessageBox::information(this, tr("Loading"), tr("Complete Loading."));

    infile.close();
    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
        {
            map[i][j] = tempmap[i][j];
            recordBoard[i][j][0] = map[i][j];
            recordNum = 0;
        }
    }
    if (tempColor == 1)
    {
        emit updateBoard(p1);
    }
    else
    {
        emit updateBoard(p2);
    }

    LoadGame::close();
}
