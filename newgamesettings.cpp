#include "newgamesettings.h"
#include "ui_newgamesettings.h"

/*
 * This part settles the settings when starting a new game
 * 1. Follow the mouseEvent to choose different choices
 * 2. Font changing
 * 3. Image changing
 *
 * Most of this part is trivial, so there is not much to explain
 */
extern int mode;
extern int maxDepth;
extern QString p1;
extern QString p2;

NewGameSettings::NewGameSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewGameSettings)
{
    ui->setupUi(this);

    ui->Image->setPixmap(QPixmap(":/Image_6.png"));

    QPalette plt;
    plt.setColor(QPalette::WindowText, Qt::black);
    ui->labelGameMode->setPalette(plt);

    ui->labelPVP->setPalette(plt);
    ui->labelPVE->setPalette(plt);

    plt.setColor(QPalette::WindowText, Qt::gray);
    ui->labelColor->setPalette(plt);
    ui->labelBlack->setPalette(plt);
    ui->labelRandom->setPalette(plt);
    ui->labelWhite->setPalette(plt);
    ui->labelLevel->setPalette(plt);
    ui->labelEasy->setPalette(plt);
    ui->labelMedium->setPalette(plt);;
    ui->labelHard->setPalette(plt);;

    connect(this, SIGNAL(sendGameMode(int)), this, SLOT(recvGameMode(int)));
    connect(this, SIGNAL(sendColor(int)), this, SLOT(recvColor(int)));
    connect(this, SIGNAL(sendLevel(int)), this, SLOT(recvLevel(int)));
    connect(this, SIGNAL(sendSettings(int,int,int)), this, SLOT(recvSettings(int,int,int)));
}

NewGameSettings::~NewGameSettings()
{
    delete ui;
}

void NewGameSettings::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        int posX = e->x(), posY = e->y();                //using the relative range of mousepress locations to find which choice is chosen
        if ((posY > 20) && (posY < 70))
        {
            if ((posX > 120) && (posX < 240))
            {
                emit sendGameMode(0);
            }
            else if ((posX > 240) && (posX < 360))
            {
                emit sendGameMode(1);
            }
        }
        else if (curGameMode == 1)
        {
            if ((posY > 80) && (posY < 130))
            {
                if ((posX > 120) && (posX < 200))
                {
                    emit sendColor(1);
                }
                else if ((posX > 280) && (posX < 360))
                {
                    emit sendColor(2);
                }
                else if ((posX > 200) && (posX < 280))
                {
                    emit sendColor(3);
                }
            }
            else if ((posY > 140) && (posY < 220))
            {
                if ((posX > 120) && (posX < 200))
                {
                    emit sendLevel(1);
                }
                else if ((posX > 200) && (posX < 280))
                {
                    emit sendLevel(2);
                }
                else if ((posX > 280) && (posX < 360))
                {
                    emit sendLevel(3);
                }
            }
        }
    }
}

void NewGameSettings::recvGameMode(int id)
{
    curGameMode = id;
    QPalette plt;
    switch(id){
    case 0:
        curColor = 0;
        curLevel = 0;

        ui->Image->setPixmap(QPixmap(":/Image_6.png"));

        plt.setColor(QPalette::WindowText, Qt::white);
        ui->labelPVP->setPalette(plt);
        plt.setColor(QPalette::WindowText, Qt::black);
        ui->labelPVE->setPalette(plt);
        plt.setColor(QPalette::WindowText, Qt::gray);
        ui->labelColor->setPalette(plt);
        ui->labelBlack->setPalette(plt);
        ui->labelRandom->setPalette(plt);
        ui->labelWhite->setPalette(plt);
        ui->labelLevel->setPalette(plt);
        ui->labelEasy->setPalette(plt);
        ui->labelMedium->setPalette(plt);
        ui->labelHard->setPalette(plt);

        break;

    case 1:

        ui->Image->setPixmap(QPixmap(":/Image_8.png"));

        plt.setColor(QPalette::WindowText, Qt::white);
        ui->labelPVE->setPalette(plt);
        plt.setColor(QPalette::WindowText, Qt::black);
        ui->labelPVP->setPalette(plt);
        plt.setColor(QPalette::WindowText, Qt::black);
        ui->labelColor->setPalette(plt);
        ui->labelBlack->setPalette(plt);
        ui->labelRandom->setPalette(plt);
        ui->labelWhite->setPalette(plt);
        ui->labelLevel->setPalette(plt);
        ui->labelEasy->setPalette(plt);
        ui->labelMedium->setPalette(plt);
        ui->labelHard->setPalette(plt);

        break;

    default:
        break;
    }
}

void NewGameSettings::recvColor(int id)
{
    curColor = id;
    QPalette plt;
    switch(id){
    case 1:
        plt.setColor(QPalette::WindowText, Qt::white);
        ui->labelBlack->setPalette(plt);
        plt.setColor(QPalette::WindowText, Qt::black);
        ui->labelRandom->setPalette(plt);
        ui->labelWhite->setPalette(plt);
        break;
    case 3:
        plt.setColor(QPalette::WindowText, Qt::white);
        ui->labelRandom->setPalette(plt);
        plt.setColor(QPalette::WindowText, Qt::black);
        ui->labelWhite->setPalette(plt);
        ui->labelBlack->setPalette(plt);
        break;
    case 2:
        plt.setColor(QPalette::WindowText, Qt::white);
        ui->labelWhite->setPalette(plt);
        plt.setColor(QPalette::WindowText, Qt::black);
        ui->labelRandom->setPalette(plt);
        ui->labelBlack->setPalette(plt);
        break;
    default:
        break;
    }
}

void NewGameSettings::recvLevel(int id)
{
    curLevel = id;
    QPalette plt;
    switch(id){
    case 1:

        ui->Image->setPixmap(QPixmap(":/Image_1.png"));

        plt.setColor(QPalette::WindowText, Qt::white);
        ui->labelEasy->setPalette(plt);
        plt.setColor(QPalette::WindowText, Qt::black);
        ui->labelMedium->setPalette(plt);
        ui->labelHard->setPalette(plt);
        break;

    case 2:

        ui->Image->setPixmap(QPixmap(":/Image_2.png"));

        plt.setColor(QPalette::WindowText, Qt::white);
        ui->labelMedium->setPalette(plt);
        plt.setColor(QPalette::WindowText, Qt::black);
        ui->labelEasy->setPalette(plt);
        ui->labelHard->setPalette(plt);
        break;

    case 3:

        ui->Image->setPixmap(QPixmap(":/Image_3.png"));

        plt.setColor(QPalette::WindowText, Qt::white);
        ui->labelHard->setPalette(plt);
        plt.setColor(QPalette::WindowText, Qt::black);
        ui->labelMedium->setPalette(plt);
        ui->labelEasy->setPalette(plt);
        break;
    default:
        break;
    }
}

void NewGameSettings::on_buttonBox_accepted()
{
    int gamemode = curGameMode, color = curColor, level = curLevel;
    if (color == 3)
    {
        QTime t;
        t= QTime::currentTime();
        qsrand(t.msec()+t.second()*1000);
        color = qrand() % 2 + 1;
    }
    emit sendSettings(gamemode, color, level);
}

void NewGameSettings::recvSettings(int gameMode, int color, int level)
{
    mode = gameMode;                                 //record the settings
    if (mode == 1)
    {
        maxDepth = 2 * level;
        switch(color){
        case 1:
            p1 = tr("Player");
            p2 = tr("AI");
            break;
        case 2:
            p1 = tr("AI");
            p2 = tr("Player");
            break;
        default:
            p1 = tr("Player");
            p2 = tr("AI");
            break;
        }
    }
    else
    {
        p1 = tr("Player1");
        p2 = tr("Player2");
    }

    emit sendSetGameBoard();
}
