#include "ai.h"

extern int map[8][8];
//extern const int w[8][8];
extern int testBoard[8][8][64];
extern int testNum;
extern int maxDepth;
//extern const int drct[8][2];

AI::AI(QObject *parent) : QObject(parent)
{

}

/*
 * It takes time to explain the minimax search.
 * In general, it's a searching strategy.
 * There is a reckon-grade(or estimated grade) for the current gameboard
 * The AI is the Max side and try to have the highest grade, while the
 * opposite side(supposing it's also an AI as clever/stupid as this one
 * is the Min side trying to get the lowest grade.
 * Then the searching-progress can be explained as
 *             | EVAL(s)              s is the situation where we interrupt the search
 * Minimax(s)= | max{Minimax(next(s)) the max side is taking the step of current situation
 *             | min(Minimax(next(s)) the min side is taking the step of current situation
 *
 * The alpha is the current up-bound of the Maxside grade,
 * the beta is the current down-bound of the Minside grade.
 * If one minside-step's beta is no larger than the previous step's alpha, it can no longer
 * update the maxvalue and we have to cease searching down this step.
 * If one maxside-step's alpha is no  smaller than the previous step's beta, it can also no
 * longer update the minvalue and searching will be ceased too.
 * In this way, the number of searching steps will be largely cut down.
 */

void AI::recvCall(QList<Steps> steps, int color)         //receive the call and set the testboard for searching
{
    int i, j;
    testNum = 0;
    for (i = 0; i < 8; ++i)
        for (j = 0; j < 8; ++j)
        {
            if (map[i][j] == color)                      //on testboard, 1 for a piece of the AI's color
            {
                testBoard[i][j][0] = 1;
            }
            else if (map[i][j] == (3 - color))           //-1 for a piece of the AI's opposite color
            {
                testBoard[i][j][0] = -1;
            }
            else                                         //0 for no pieces
            {
                testBoard[i][j][0] = 0;
            }
        }
    double maxvalue = -Max;
    double alpha = Max;
    Steps ans;
    for (i = 0; i < steps.length(); ++i)
    {
        TakeMoves(steps.at(i).x, steps.at(i).y, 1);       //try to take a step and search down
        int curValue = MinSearch(1, alpha);
        if (curValue >= maxvalue)
        {
            ans = steps.at(i);
            maxvalue = curValue;
        }
        if (curValue < alpha) alpha = curValue;
        testNum--;
    }
    emit sendAIStep(ans.x, ans.y, color);
}

void AI::TakeMoves(int x, int y, int color)
{
    ++testNum;

    int i, j;
    for (i = 0; i < 8; ++i)
        for (j = 0; j < 8; ++j)
            testBoard[x][y][testNum] = 0;                       //save the situation in the testBoard array;

    testBoard[x][y][testNum] = color;
    int k;
    for (k = 0; k < 8; ++k)                                     //find and reverse the reversible pieces
    {
        Reverse(x+drct[k][0], y+drct[k][1], drct[k][0], drct[k][1], color, true);
    }

    for (i = 0; i < 8; ++i)
        for (j = 0; j < 8; ++j)
            if (testBoard[x][y][testNum] == 0)                   //fill up the rest part of the gameboard
            {
                testBoard[x][y][testNum] = testBoard[x][y][testNum-1];
            }
}

bool AI::Reverse(int x, int y, int dx, int dy, int color, bool rev = false)
{
    if (testBoard[x][y][testNum-rev] == color) return true;
    if (testBoard[x][y][testNum-rev] != -color) return false;
    if ((x + dx >= 0) && (y + dy >= 0) && (x + dx < 8) && (y + dy < 8)
            && (Reverse(x + dx, y + dy, dx, dy, color, rev)))      //if the next piece in this direction is reversible, this piece is also reversible.
    {
        if (rev)                                                   //if we need to reverse the reversible pieces(when we are take steps), we reverse it; otherwise(when we just wanna find possible steps), no
        {
            testBoard[x][y][testNum] = color;
        }
        return true;
    }
    else
    {
        return false;
    }
}

QList<Steps> AI::FindPossible(int color)                          //find possible steps where some of the opposite pieces will be reversed if we take this step.
{
    int i, j, k;
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
                    if ((i+drct[k][0] >= 0) && (j+drct[k][1] >= 0) && (i + drct[k][0] < 8) && (j + drct[k][1] < 8)
                            && (testBoard[i+drct[k][0]][j+drct[k][1]][testNum] == color))
                    {
                        if (Reverse(i + drct[k][0], j + drct[k][1], drct[k][0], drct[k][1], color, false))
                        {
                            flag = true;
                            break;
                        }
                    }
                }
                if (flag)
                {
                    Steps temp = {i, j, color};
                    ans << temp;
                }
            }
        }
    }
    return ans;
}

double AI::MinSearch(int depth,double &alpha)
{
    if (depth > maxDepth) return Reckon();

    QList<Steps> tries;
    tries = FindPossible(-1);
    int i;
    double beta = -Max;
    double minValue = Max;
    if (tries.isEmpty())                                  //if there is no legal steps, then the Minside has to pass.
    {
        QList<Steps> tries1;
        tries1 = FindPossible(1);
        if (tries1.isEmpty()) return EndGame();           //if the opposite side has no legal steps either, the game is over.
        else
        {
            int curValue = MaxSearch(depth + 1, beta);
            if (curValue < minValue) minValue = curValue;
            if (curValue > beta) beta = curValue;
            if (beta < alpha) return minValue;
        }
    }
    for (i = 0; i < tries.length(); ++i)
    {
        TakeMoves(tries[i].x, tries[i].y, -1);            //the Min side try to take a step and let the Max side continue.
        int curValue = MaxSearch(depth + 1, beta);
        if (curValue < minValue) minValue = curValue;
        if (curValue > beta) beta = curValue;
        testNum--;
        if (beta < alpha) return minValue;
    }
    return minValue;
}

double AI::MaxSearch(int depth, double &beta)             //It's similar to minsearch.
{
    if (depth > maxDepth) return Reckon();
    QList<Steps> tries;
    tries = FindPossible(1);
    int i;
    double alpha = Max;
    double maxValue = -Max;
    if (tries.isEmpty())
    {
        QList<Steps> tries1;
        tries1 = FindPossible(-1);
        if (tries1.isEmpty()) return EndGame();
        else
        {
            int curValue = MaxSearch(depth + 1, beta);
            if (curValue > maxValue) maxValue = curValue;
            if (curValue < alpha) alpha = curValue;
            if (beta < alpha) return maxValue;
        }
    }
    for (i = 0; i < tries.length(); ++i)
    {
        TakeMoves(tries[i].x, tries[i].y, 1);
        int curValue = MinSearch(depth + 1, alpha);
        if (curValue > maxValue) maxValue = curValue;
        if (curValue < alpha) alpha = curValue;
        testNum--;
        if (beta < alpha) return maxValue;
    }
    return maxValue;
}

double AI::Reckon()                                     //reckon/estimate the grade of a gameboard which hasn't been over.
{
    double ans = 0.0;
    int i, j;
    for (i = 0; i < 8; ++i)
        for (j = 0; j < 8; ++j)
        {
            ans += w[i][j] * testBoard[i][j][testNum];
        }
    return ans;
}

double AI::EndGame()                                    //judge which side is the winner and return the grade if a gameboard is over.
{
    int i, j;
    int p = 0, q = 0;
    for (i = 0; i < 8; ++i)
        for (j = 0; j < 8; ++j)
        {
            if (testBoard[i][j][testNum] == 1)
            {
                ++p;
            }
            else if (testBoard[i][j][testNum] == -1)
            {
                ++q;
            }
        }
    if (p > q) return Max;
    else return -Max;
}
