#include "gameControl.h"
#include <iostream>

bool gameControl::canTakeFigure()
{
    //vizszintes es fuggoleges sorokat ellenorzi, kiveve a belso keresztet
    for (int i=0;i<7;i++)
    {
        if (i!=3 && _table[i][i]>0 && _table[i][i]==_table[3][i] && _table[i][i]==_table[6-i][i])
        {
            return true;
        }

        if (i!=3 && _table[i][i]>0 && _table[i][i]==_table[i][3] && _table[i][i]==_table[i][6-i])
        {
            return true;
        }
    }

    //belso kereszt ellenorzese
    for (int i=0;i<5;i+=4)
    {
        if (_table[i][3]>0 && _table[i][3]== _table[i+1][3] && _table[i][3]== _table[i+2][3])
        {
            return true;
        }

        if (_table[3][i]>0 && _table[3][i]== _table[3][i+1] && _table[3][i]== _table[3][i+2])
        {
            return true;
        }
    }

    return false;
}

bool gameControl::nearby(int x_from, int x_to, int y_from, int y_to)
{
    if ((x_from==x_to && abs(y_from-y_to)) || (y_from==y_to && abs(x_from-x_to)))
    {
        return true;
    }

    return false;
}
