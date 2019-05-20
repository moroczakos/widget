#include "figure.h"
#include "graphics.hpp"
#include <math.h>

using namespace genv;

figure::figure(Application * parent,int x, int y, int sx, int sy, int whichPlayer)
    : Widget(parent,x,y,sx,sy)
{
    _whichPlayer=whichPlayer;
}


void figure::draw()
{
    for (int i=-15;i<=15;i++)
    {
        for (int j=-15;j<=15;j++)
        {
            if ((pow(i,2)+pow(j,2))<pow(15,2))
            {
                gout << move_to(_x-i, _y-j) << color(100,100,100) << dot;
            }
            if ((pow(i,2)+pow(j,2))<pow(13,2))
            {
                gout << move_to(_x-i, _y-j) << color(255-255*_whichPlayer,255*_whichPlayer,0) << dot;
            }
        }
    }
}

void figure::handle(event ev)
{

}


std::string figure::value()
{
    return "";
}

bool figure::changedValue()
{
    return false;
}

bool figure::moveable()
{
    /*if (_x>200 && _y>100)
    {
        return false;
    }*/
    return true;
}

int figure::returnXcoord()
{
    return _x;
}

int figure::returnYcoord()
{
    return _y;
}

void figure::setXcoord(int x)
{
    _x=x;
}

void figure::setYcoord(int y)
{
    _y=y;
}

int figure::whichPlayer()
{
    return _whichPlayer;
}
