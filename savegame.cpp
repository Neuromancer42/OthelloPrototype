#include "savegame.h"
#include "ui_savegame.h"
/*
 * This part settles the savings of the gamedata.
 * It saves these datas:
 * 1. the next step's side
 * 2. player1(black)'s name player2(white)'s name
 * 3. the current gameboard
 */
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

SaveGame::SaveGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveGame)
{
    ui->setupUi(this);
}

SaveGame::~SaveGame()
{
    delete ui;
}

void SaveGame::on_pushButton_clicked()
{
    QFile outfile("data1.txt");
    if (!outfile.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, tr("Saving"), tr("Fail to save data."));
        return;
    }
    QTextStream tsOut( & outfile);
    tsOut << (3 - recordSteps[recordNum].color) << endl;                             //curcolor
    tsOut << p1 << endl << p2 << endl;
    int i, j;
    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
            tsOut << recordBoard[i][j][recordNum] << ' ';
        tsOut << endl;
    }

    QMessageBox::information(this, tr("Saving"), tr("Complete Saving."));

    outfile.close();
    SaveGame::close();
}

void SaveGame::on_pushButton_2_clicked()
{
    QFile outfile("data2.txt");
    if (!outfile.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, tr("Saving"), tr("Fail to save data."));
        return;
    }
    QTextStream tsOut( & outfile);
    tsOut << (3 - recordSteps[recordNum].color) << endl;                             //curcolor
    tsOut << p1 << endl << p2 << endl;
    int i, j;
    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
            tsOut << recordBoard[i][j][recordNum] << ' ';
        tsOut << endl;
    }

    QMessageBox::information(this, tr("Saving"), tr("Complete Saving."));

    outfile.close();
    SaveGame::close();
}

void SaveGame::on_pushButton_3_clicked()
{
    QFile outfile("data3.txt");
    if (!outfile.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, tr("Saving"), tr("Fail to save data."));
        return;
    }
    QTextStream tsOut( & outfile);
    tsOut << (3 - recordSteps[recordNum].color) << endl;                             //curcolor
    tsOut << p1 << endl << p2 << endl;
    int i, j;
    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
            tsOut << recordBoard[i][j][recordNum] << ' ';
        tsOut << endl;
    }

    QMessageBox::information(this, tr("Saving"), tr("Complete Saving."));

    outfile.close();
    SaveGame::close();
}
