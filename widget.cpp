#include "widget.h"
#include "ui_widget.h"

/*
 * For clarity, the number of each grid represents:
 * 0. No pieces
 * 1. Black piece
 * 2. White piece
 * 3. Black side can take a step here
 * 4. White side can take a step here
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
//extern const int drct[8][2];

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //QResource::registerResource("backgroundmusic.rcc");
    backgroundPlayer.setMedia(QUrl::fromLocalFile("./background.wav")); //load and play the backgroundmusic
    backgroundPlayer.play();
    connect(&backgroundPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), &backgroundPlayer, SLOT(play()));

    allowed = false;

    timer1 = new QTimer(parent);
    connect(timer1, SIGNAL(timeout()), this, SLOT(callAI()));

    timer2 = new QTimer(parent);
    connect(timer2, SIGNAL(timeout()), this, SLOT(pass()));
    ui->countBlack->setPixmap(QPixmap(":/gameBoard_1.png"));
    ui->countWhite->setPixmap(QPixmap(":/gameBoard_2.png"));
    gameBoard << ui->gameBoard_0_0 << ui->gameBoard_0_1 << ui->gameBoard_0_2 << ui->gameBoard_0_3
              << ui->gameBoard_0_4 << ui->gameBoard_0_5 << ui->gameBoard_0_6 << ui->gameBoard_0_7
              << ui->gameBoard_1_0 << ui->gameBoard_1_1 << ui->gameBoard_1_2 << ui->gameBoard_1_3
              << ui->gameBoard_1_4 << ui->gameBoard_1_5 << ui->gameBoard_1_6 << ui->gameBoard_1_7
              << ui->gameBoard_2_0 << ui->gameBoard_2_1 << ui->gameBoard_2_2 << ui->gameBoard_2_3
              << ui->gameBoard_2_4 << ui->gameBoard_2_5 << ui->gameBoard_2_6 << ui->gameBoard_2_7
              << ui->gameBoard_3_0 << ui->gameBoard_3_1 << ui->gameBoard_3_2 << ui->gameBoard_3_3
              << ui->gameBoard_3_4 << ui->gameBoard_3_5 << ui->gameBoard_3_6 << ui->gameBoard_3_7
              << ui->gameBoard_4_0 << ui->gameBoard_4_1 << ui->gameBoard_4_2 << ui->gameBoard_4_3
              << ui->gameBoard_4_4 << ui->gameBoard_4_5 << ui->gameBoard_4_6 << ui->gameBoard_4_7
              << ui->gameBoard_5_0 << ui->gameBoard_5_1 << ui->gameBoard_5_2 << ui->gameBoard_5_3
              << ui->gameBoard_5_4 << ui->gameBoard_5_5 << ui->gameBoard_5_6 << ui->gameBoard_5_7
              << ui->gameBoard_6_0 << ui->gameBoard_6_1 << ui->gameBoard_6_2 << ui->gameBoard_6_3
              << ui->gameBoard_6_4 << ui->gameBoard_6_5 << ui->gameBoard_6_6 << ui->gameBoard_6_7
              << ui->gameBoard_7_0 << ui->gameBoard_7_1 << ui->gameBoard_7_2 << ui->gameBoard_7_3
              << ui->gameBoard_7_4 << ui->gameBoard_7_5 << ui->gameBoard_7_6 << ui->gameBoard_7_7;

    connect(ui->pushButtonNewgame, SIGNAL(clicked()), this, SIGNAL(displaySettings()));
    connect(this, SIGNAL(sendChangeBoard(int,int,int)), this, SLOT(recvChangeBoard(int,int,int)));

    connect(this, SIGNAL(callForStep(QString, bool)), this, SLOT(thinking(QString, bool)));
    connect(this, SIGNAL(sendEndGame()), this, SLOT(endGame()));
    connect(this, SIGNAL(sendEmptyStep(QString)), this, SLOT(emptyStep(QString)));
    connect(this, SIGNAL(sendPlayerStep(int,int,int)), this, SLOT(takeStep(int,int,int)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setNewGameBoard()
{
    recordNum = 0;
    int i, j;
    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
        {
            if (((i == 3) && (j == 3)) || ((i == 4) && (j == 4)))
            {
                map[i][j] = 1;
            }
            else if (((i == 3) && (j == 4)) || ((i == 4) && (j == 3)))
            {
                map[i][j] = 2;
            }
            else
            {
                map[i][j] = 0;
            }
            recordBoard[i][j][recordNum] = map[i][j];
            emit sendChangeBoard(i, j, map[i][j]);
        }
    }
    ui->BlackNum->display(2);
    ui->WhiteNum->display(2);

    emit callForStep(p1, false);
}

void Widget::on_pushButtonLoad_2_clicked()                        //Display the 'About' Information
{
    QMessageBox message(QMessageBox::NoIcon, tr("ABOUT"), tr(""));
    message.setIconPixmap(QPixmap(":/Image_0.png"));
    QString str = "";
    str += tr("============About Author ============\n");
    str += tr("This Program is created by Chen Yifan.\n");
    str += tr("Contact the author by WeChat: chenyifan42\n\n");
    str += tr("============About Othello============\n");
    str += tr("Well, the rule is quite easy to understand.\n\n");
    str += tr("============About Qt     =============\n");
    str += tr("This Program is created with Qt.\n");
    str += tr("Learn more about Qt: http://www.qt.io/\n");
    message.setText(str);
    message.exec();
}

QList<Steps> Widget::possiblesteps(int color)                      //Find possible steps for the next side
{
    int i, j, k;
    int anticolor = 3 - color;
    QList<Steps> ans;

    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
        {
            if (map[i][j] == 0)
            {
                bool flag = false;
                for (k = 0; k < 8; ++k)
                {
                    if ((i + drct[k][0] >= 0) && (j + drct[k][1] >= 0) && (i + drct[k][0] < 8) && (j + drct[k][1] < 8)
                            && (map[i+drct[k][0]][j+drct[k][1]] == anticolor))
                    {
                        if (reversible(i + drct[k][0], j + drct[k][1], drct[k][0], drct[k][1], color, false))
                        {
                            flag = true;
                            break;
                        }
                    }
                }
                if (flag)
                {
                    emit sendChangeBoard(i, j, color+2);
                    Steps temp = {i, j, color};
                    ans << temp;
                }
            }
        }
    }
    return ans;
}

bool Widget::reversible(int x, int y, int dx, int dy, int color, bool rev = false)
{
    if (map[x][y] == color) return true;
    if (map[x][y] != 3-color) return false;
    if ((x + dx >= 0) && (y + dy >= 0) && (x + dx < 8) && (y + dy < 8)
            && (reversible(x + dx, y + dy, dx, dy, color, rev)))                   //if the next piece in this direction is reversible, this piece is also reversible.
    {
        if (rev)                                                                   //if we need to reverse the reversible pieces(when we are take steps), we reverse it; otherwise(when we just wanna find possible steps), no
        {
            map[x][y] = color;
            emit sendChangeBoard(x, y, color);
        }
        return true;
    }
    else
    {
        return false;
    }
}

void Widget::recvChangeBoard(int x, int y, int id)                                 //change a explicit grid
{
    QString str;
    switch(id){
    case 0:
        str = tr(":/gameBoard_0.png");
        break;
    case 1:
        str = tr(":/gameBoard_1.png");
        break;
    case 2:
        str = tr(":/gameBoard_2.png");
        break;
    case 3:
        str = tr(":/gameBoard_3.png");
        break;
    case 4:
        str = tr(":/gameBoard_4.png");
        break;
    case 5:
        str = tr(":/gameBoard_5.png");
        break;
    case 6:
        str = tr(":/gameBoard_6.png");
        break;
    default:
        break;
    }

    gameBoard[x*8+y]->setPixmap(QPixmap(str));
    gameBoard[x*8+y]->show();
}

void Widget::thinking(QString player, bool prior)                             //waiting for the human/AI to take a step. The bool 'prior' shows if the previous step is an empty step.
{
    if (player == p1)
    {
        curcolor = 1;
    }
    else if (player == p2)
    {
        curcolor = 2;
    }
    ui->labelInfo->setText(tr("It's ")+player+tr("'s turn."));
    ui->labelInfo->show();

    steps = possiblesteps(curcolor);                                            //find possible steps

    if (steps.isEmpty())
    {
        if (!prior)
        {
            emit sendEndGame();                                                 //if the previous and current side neither has legal steps, the game is over
        }
        else
        {
            emit sendEmptyStep(player);                                          //game pass settling
        }
        return;
    }
    if (player != tr("AI"))
    {
        allowed = true;
        return;
    }
    else
    {
        allowed = false;
        timer1->start(1000);
        return;
    }
}

void Widget::mousePressEvent(QMouseEvent *e)                          //using mouseEvent location to find which grid is pressed and call the changeboard slot if it's a legal step
{
    if (!allowed) return;
    if (e->button() == Qt::LeftButton)
    {
        int posX = e->x(), posY = e->y();

        if ((posX < 20) || (posX > 330) || (posY < 30) || (posY > 340))
        {
            return;
        }
        int row, col;
        if ((((posX - 20) / 40) == ((posX - 10) / 40)) && (((posY - 30) / 40) == ((posY - 20) / 40)))
        {
            row = (posY - 30) / 40;
            col = (posX - 20) / 40;

            int k;
            for (k = 0; k < steps.length(); ++k)
            {
                if ((steps.at(k).x == row) && (steps.at(k).y == col) && (steps.at(k).color == curcolor))
                {
                    emit sendPlayerStep(row, col, curcolor);
                    return;
                }
            }
            return;
        }
        else return;
    }
}

void Widget::takeStep(int r, int c, int color)                   //change board and other relative stuff after a step by human/AI is taken
{
    if (recordNum > 0)
    {
        emit sendChangeBoard(recordSteps[recordNum].x, recordSteps[recordNum].y, recordSteps[recordNum].color);
    }
    recordSteps[++recordNum].x = r;
    recordSteps[recordNum].y = c;
    recordSteps[recordNum].color = color;

    while (!steps.isEmpty())
    {
        int posX = steps.at(0).x;
        int posY = steps.at(0).y;
        emit sendChangeBoard(posX, posY, 0);
        steps.takeFirst();
    }
    int k;
    for (k = 0; k < 8; ++k)
    {
        if ((r+drct[k][0] >= 0) && (c+drct[k][1] >= 0) && (r + drct[k][0] < 8) && (c + drct[k][1] < 8)
                && (map[r+drct[k][0]][c+drct[k][1]] == 3-color))
        {
            reversible(r + drct[k][0], c + drct[k][1], drct[k][0], drct[k][1], color, true);
        }
    }
    map[r][c] = color;
    emit sendChangeBoard(r, c, color+4);

    //qDebug()<<r<<c<<color;

    int i, j;
    cnt1 = 0;
    cnt2 = 0;

    for (i = 0; i < 8; ++i)
        for (j = 0; j < 8; ++j)
        {
            if (map[i][j] == 1)
            {
                ++cnt1;
                recordBoard[i][j][recordNum] = 1;
            }
            else if (map[i][j] == 2)
            {
                ++cnt2;
                recordBoard[i][j][recordNum] = 2;
            }
            else
            {
                recordBoard[i][j][recordNum] = 0;
            }
        }

    ui->BlackNum->display(cnt1);
    ui->WhiteNum->display(cnt2);

    if (color == 1)
    {
        emit callForStep(p2, true);
    }
    else if (color == 2)
    {
        emit callForStep(p1, true);
    }
}

void Widget::endGame()                                      //show the 'game over' Info
{
    ui->labelInfo->setText(tr("The game is over"));
    QString title, text, img;
    title = tr("Game Over");
    if (mode == 0)
    {
        img = tr(":/Image_9.png");
        if (cnt1 > cnt2)
        {
            text = p1 + tr(" wins!");
        }
        else if (cnt2 > cnt1)
        {
            text = p2 + tr(" wins!");
        }
        else
        {
            text = tr("Tie!");
        }
    }
    else if (mode == 1)
    {
        if (cnt1 == cnt2)
        {
            img = tr(":/Image_7.png");
            text = tr("Tie!");
        }
        else if ((cnt1 > cnt2) == (p1 == tr("AI")))
        {
            img = tr(":/Image_4.png");
            text = tr("You lose!");
        }
        else
        {
            img = tr(":/Image_5.png");
            text = tr("You win!");
        }
    }
    QMessageBox message(QMessageBox::NoIcon, title, tr(""));
    message.setIconPixmap(QPixmap(img));
    message.setText(text);
    message.exec();
}

void Widget::emptyStep(QString player)                      //process the condition of passing a step
{
    allowed = false;
    ui->labelInfo->setText(player + " have to pass this step.");
    timer2->start(750);
}

void Widget::callAI()                                       //call the AI to take a step after waiting for some time, in order to make the AI's step seem a little longer
{
    timer1->stop();
    emit callForAI(steps, curcolor);
}

void Widget::pass()                                         //the second part of peocessing the condition of passing a step
{
    timer2->stop();
    if (curcolor == 1)
    {
        emit callForStep(p2, false);
    }
    else if (curcolor == 2)
    {
        emit callForStep(p1, false);
    }
}

void Widget::on_pushButtonLoad_3_clicked()                   //press 'UNDO' to turn back to the previous step
{
    while((recordNum > 0) && (recordSteps[recordNum].color != curcolor)) --recordNum;
    if(recordNum >0) --recordNum;
    int i, j;
    int cnt1 = 0, cnt2 = 0;
    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
        {
            map[i][j] = recordBoard[i][j][recordNum];
            emit sendChangeBoard(i, j, map[i][j]);
            if (map[i][j] == 1)
            {
                ++cnt1;
            }
            else if (map[i][j] == 2)
            {
                ++cnt2;
            }
        }
    }
    if (recordNum > 0)
    {
        emit sendChangeBoard(recordSteps[recordNum].x, recordSteps[recordNum].y, recordSteps[recordNum].color+4);
    }

    ui->BlackNum->display(cnt1);
    ui->WhiteNum->display(cnt2);

    if (curcolor == 1)
    {
        emit callForStep(p1, true);
    }
    else if (curcolor == 2)
    {
        emit callForStep(p2, true);
    }
}

void Widget::update(QString player)              //update the gameboard after loading a recorded game
{
    recordNum = 0;
    int i, j;
    int cnt1 = 0, cnt2 = 0;
    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
        {
            recordBoard[i][j][recordNum] = map[i][j];
            emit sendChangeBoard(i, j, map[i][j]);
            if (map[i][j] == 1)
            {
                ++cnt1;
            }
            else if (map[i][j] == 2)
            {
                ++cnt2;
            }
        }
    }

    ui->BlackNum->display(cnt1);
    ui->WhiteNum->display(cnt2);

    emit callForStep(player, true);

}

void Widget::on_pushButtonSave_clicked()
{
    emit pushSave();
}

void Widget::on_pushButtonLoad_clicked()
{
    emit pushLoad();
}
