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
#include <set>
#include <sstream>

using namespace std;
using namespace genv;

int XX=800, YY=400;

std::string intToStringConverter(int input)
{
    std::string temp;
    std::stringstream ss;
    ss<<input;
    ss>>temp;
    return temp;
}

struct Musor{
    string cim;
    int ora, perc, hossz;
};

bool operator < (Musor a, Musor b)
{
    if (a.ora==b.ora)
    {
        return a.perc<b.perc;
    }
    return a.ora<b.ora;
}

class MyApplication : public Application
{
protected:
    staticText * cim;
    staticText * kezdes;
    staticText * hossz;
    dinamicText * nev;
    counter * h;
    counter * m;
    counter * l;
    button * hozzaad;
    choose * opciok;
    button * torol;
    button * szerkeszt;
    button * zene;

    set<Musor> musor;
    int _index=0;
    int idorend[1440]={0};


public:
    MyApplication(){
        cim = new staticText(this,20,50,80,30,"cim");
        kezdes = new staticText(this,20,100,80,30,"kezdes");
        hossz = new staticText(this,20,150,80,30,"hossz");
        nev = new dinamicText(this,100,50,200,30);
        h = new counter(this,100,100,0,23);
        m = new counter(this,200,100,0,59);
        l = new counter(this,100,150,0,1000);
        hozzaad = new button(this,200,150,100,30,"Hozzaad");
        opciok = new choose(this,100,200,200,5,"");
        torol = new button(this,100,250,80,30,"Torol");
        szerkeszt = new button(this,200,250,80,30,"Szerkeszt");
        zene = new button(this,300,250,80,30,"Zene");

        start();
    }

    void start()
    {
        Musor ujmusor;
        ujmusor.cim="a";
        ujmusor.ora=1;
        ujmusor.perc=0;
        ujmusor.hossz=10;
        musor.insert(ujmusor);
        ujmusor.cim="b";
        ujmusor.ora=2;
        ujmusor.perc=0;
        ujmusor.hossz=10;
        musor.insert(ujmusor);
        ujmusor.cim="c";
        ujmusor.ora=3;
        ujmusor.perc=0;
        ujmusor.hossz=100;
        musor.insert(ujmusor);
    }

    void update()
    {
        _index=opciok->clearElement();
        idorend[1440]={0};
        for (Musor a : musor)
        {
            opciok->addElement(a.cim);
            for (int i=a.ora*60+a.perc;i<=a.ora*60+a.perc+a.hossz;i++)
            {
                idorend[i%1440]=1;
            }
        }
        opciok->getIndex(_index);
    }

    void hozzaadMusort()
    {
        if (hozzaad->changedValue())
        {
            int kezdetPercben, vegPercben;
            bool berakhato=true;

            Musor ujmusor;
            ujmusor.cim=nev->value();
            ujmusor.ora=h->intValue();
            ujmusor.perc=m->intValue();
            ujmusor.hossz=l->intValue();

            kezdetPercben=h->intValue()*60+m->intValue();
            vegPercben=kezdetPercben+l->intValue();

            for (int i=kezdetPercben;i<=vegPercben;i++)
            {
                if (idorend[i%1440]!=0)
                {
                    berakhato=false;
                }
            }

            if(berakhato)
            {
                musor.insert(ujmusor);
                /*for (int i=kezdetPercben;i<=vegPercben;i++)
                {
                    idorend[i%1440]=1;
                }*/
            }
        }
    }

    void torolElemet()
    {
        if (torol->changedValue() && musor.size()>0)
        {
            set<Musor>::iterator it=musor.begin();
            for (int i=0;i<_index;i++)
            {
                it++;
            }
            musor.erase(it);
        }
    }

    void szerkesztElemet()
    {
        if (szerkeszt->changedValue() && musor.size()>0)
        {
            Musor regi;
            set<Musor>::iterator it=musor.begin();
            for (int i=0;i<_index;i++)
            {
                it++;
            }
            regi=*it;
            musor.erase(it);
            for (int i=regi.ora*60+regi.perc;i<=regi.ora*60+regi.perc+regi.hossz;i++)
            {
                idorend[i%1440]=0;
            }

            int kezdetPercben, vegPercben;
            bool berakhato=true;

            Musor ujmusor;
            ujmusor.cim=nev->value();
            ujmusor.ora=h->intValue();
            ujmusor.perc=m->intValue();
            ujmusor.hossz=l->intValue();

            kezdetPercben=h->intValue()*60+m->intValue();
            vegPercben=kezdetPercben+l->intValue();

            for (int i=kezdetPercben;i<=vegPercben;i++)
            {
                if (idorend[i%1440]!=0)
                {
                    berakhato=false;
                }
            }

            if(berakhato)
            {
                musor.insert(ujmusor);
            }
            else
            {
                musor.insert(regi);
            }
        }
    }

    void zenetBetolt()
    {
        int szabadKezdet=0, szabadVeg=0;
        if (zene->changedValue())
        {
            for (int i=1;i<1440;i++)
            {
                if (idorend[i]=0 && idorend[i-1]==1)
                {
                    szabadKezdet=i;
                }

                if (idorend[i]=1 && idorend[i-1]==0 && szabadKezdet!=0)
                {
                    szabadVeg=i;

                    Musor ujmusor;
                    ujmusor.cim="Zene"+intToStringConverter(i);
                    ujmusor.ora=szabadKezdet/60;
                    ujmusor.perc=szabadKezdet%60;
                    ujmusor.hossz=szabadVeg-szabadKezdet;
                    cout<<szabadVeg-szabadKezdet<<endl;

                    musor.insert(ujmusor);
                }
            }
        }
    }

    virtual void action()
    {
        update();
        hozzaadMusort();
        torolElemet();
        szerkesztElemet();
        zenetBetolt();
    }
};

int main()
{
    gout.open(XX, YY);
    MyApplication app;
    app.event_loop(XX, YY);
    return 0;
}

