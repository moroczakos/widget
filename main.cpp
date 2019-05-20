#include "graphics.hpp"
#include "widgets.hpp"
#include <vector>
#include <sstream>
#include "application.hpp"
#include <iostream>
#include <fstream>
#include "counter.h"
#include "choose.h"
#include "button.h"
#include "scroll.hpp"
#include "staticText.hpp"
#include "dinamicText.hpp"
#include "figure.h"
#include <math.h>
#include "gameControl.h"




using namespace std;
using namespace genv;

int XX=800, YY=400;

class MyApplication : public Application
{
protected:
    staticText * staticText1;
    figure * figures;
    vector<figure*> _figureVectorFirstPlayer, _figureVectorSecondPlayer, _allFigure;
    int _sizeOfField = 50;
    gameControl * rules;

public:
    MyApplication(){
        staticText1 = new staticText(this,520,15,160,30,"Nine men's Morris");
        rules = new gameControl();
        for (int i=0;i<9;i++)
        {
            figure * figureFirstPlayer=new figure(this,420+i*40,60,30,30,0);
            _figureVectorFirstPlayer.push_back(figureFirstPlayer);
        }

        _allFigure=_figureVectorFirstPlayer;

        for (int i=0;i<9;i++)
        {
            figure * figureSecondPlayer=new figure(this,420+i*40,100,30,30,1);
            _figureVectorSecondPlayer.push_back(figureSecondPlayer);
            _allFigure.push_back(figureSecondPlayer);
        }
    }

    virtual void fieldDraw()
    {
        for (int i=0;i<3;i++)
        {
            gout<<move_to(_sizeOfField-5+i*_sizeOfField,_sizeOfField-5+i*_sizeOfField)<<color(255,255,255)<<box_to(_sizeOfField*7+5-i*_sizeOfField,_sizeOfField*7+5-i*_sizeOfField);
            gout<<move_to(_sizeOfField+5+i*_sizeOfField,_sizeOfField+5+i*_sizeOfField)<<color(0,0,0)<<box_to(_sizeOfField*7-5-i*_sizeOfField,_sizeOfField*7-5-i*_sizeOfField);
        }

        gout<<move_to(_sizeOfField,_sizeOfField-5+3*_sizeOfField)<<color(255,255,255)<<box_to(_sizeOfField+2*_sizeOfField,_sizeOfField+5+3*_sizeOfField);
        gout<<move_to(_sizeOfField+4*_sizeOfField,_sizeOfField-5+3*_sizeOfField)<<color(255,255,255)<<box_to(_sizeOfField+6*_sizeOfField,_sizeOfField+5+3*_sizeOfField);

        gout<<move_to(_sizeOfField-5+3*_sizeOfField,_sizeOfField)<<color(255,255,255)<<box_to(_sizeOfField+5+3*_sizeOfField,_sizeOfField+2*_sizeOfField);
        gout<<move_to(_sizeOfField-5+3*_sizeOfField,_sizeOfField+4*_sizeOfField)<<color(255,255,255)<<box_to(_sizeOfField+5+3*_sizeOfField,_sizeOfField+6*_sizeOfField);

    }

    virtual void setCoord()
    {
        int xCoord, yCoord;
        bool positionReserved;

        //fokuszalt babut helyere ugrasztja
        for (figure* f : _allFigure)
        {
            xCoord=round(f->returnXcoord()/_sizeOfField);
            yCoord=round(f->returnYcoord()/_sizeOfField);
            if (f->is_focused())
            {
                if (xCoord>0 && xCoord<8 && yCoord>0 && yCoord<8 && !(xCoord==4 && yCoord==4))
                {
                    /*if (rules->_table[xCoord-1][yCoord-1]==0)
                    {
                        f->setXcoord(xCoord*_sizeOfField);
                        f->setYcoord(yCoord*_sizeOfField);
                    }*/

                    if (xCoord==yCoord || xCoord+yCoord==8 || xCoord==4 || yCoord==4)// && rules->_table[xCoord-1][yCoord-1]==0)
                    {
                        f->setXcoord(xCoord*_sizeOfField);
                        f->setYcoord(yCoord*_sizeOfField);

                        if (f->whichPlayer()==0 && rules->_table[xCoord-1][yCoord-1]==0)
                        {
                            rules->_table[xCoord-1][yCoord-1]=1;
                        }
                        else if (f->whichPlayer()==1 && rules->_table[xCoord-1][yCoord-1]==0)
                        {
                            rules->_table[xCoord-1][yCoord-1]=2;
                        }

                        ///kijavitani, hogy egymasra ne lehessen tenni

                        /*else if (!f->grabbed())
                        {
                            f->setXcoord(xCoord*_sizeOfField+20);
                            f->setYcoord(yCoord*_sizeOfField+20);
                        }*/
                    }

                }
            }
        }

        //ha nincs az adott helyen babu akkor kinullazza az adott vektorbeli elemet
        for (int i=0;i<7;i++)
        {
            for (int j=0;j<7;j++)
            {
                positionReserved=false;

                if (!(i==3 && j==3) && (i==j || i+j==6 || i==3 || j==3))
                {
                    for (figure* f : _allFigure)
                    {
                        xCoord=f->returnXcoord()/_sizeOfField-1;
                        yCoord=f->returnYcoord()/_sizeOfField-1;

                        if (i==xCoord && j==yCoord)
                        {
                            positionReserved=true;
                        }
                    }
                    if (!positionReserved)
                    {
                        rules->_table[i][j]=0;
                    }
                }
            }
        }
    }

    virtual void action()
    {
        fieldDraw();
        setCoord();
        //std::cout<<rules->canTakeFigure();
        std::cout<<rules->nearby(0,0,0,1);

    }
};

int main()
{
    gout.open(XX, YY);
    MyApplication app;
    app.event_loop(XX, YY);
    return 0;
}


///hf mukodjon a mozgatas - kell javitani a 0 elemu vektort
