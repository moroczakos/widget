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
#include "graph.h"
#include <vector>
#include <set>
#include <list>
#include <sstream>

using namespace std;
using namespace genv;

int XX=800, YY=400;

struct Tetel{
    string nev;
    int ertek, nap;
};

struct TetelNapszerint{
    string nev;
    int ertek, nap;
};

bool operator<(Tetel a, Tetel b)
{
    return a.ertek>b.ertek;
}

bool operator<(TetelNapszerint a, TetelNapszerint b)
{
    return a.nap<b.nap;
}

//konverterek
int strintToIntConverter(std::string input)
{
    int temp;
    std::istringstream iss (input);
    iss >> temp;
    return temp;
}

std::string intToStringConverter(int input)
{
    std::string temp;
    std::stringstream ss;
    ss<<input;
    ss>>temp;
    return temp;
}

class MyApplication : public Application
{
protected:
    staticText * staticText1;
    dinamicText * beNev;
    dinamicText * fileNev;
    counter * beAr;
    choose * opciok;
    choose * rendezesiMod;
    button * hozzaad;
    button * visszavon;
    button * torol;
    button * modosit;
    button * betolt;
    button * kiment;
    button * rendezestValt;
    graph * graf;

    vector<Tetel> _tetelek;
    set<TetelNapszerint> _beviteli;
    set<Tetel> _ertekcsokken;
    int _egyenleg=0;
    int _index=0;
    int _nap=0;
    vector<int> nap;
    vector<int> egyenleg;

public:
    MyApplication(){
        staticText1 = new staticText(this,50,160,200,30,"Egyenleg:");
        beNev = new dinamicText(this,50,10,200,30);
        beAr = new counter(this,50,60,-100000,100000);
        hozzaad = new button(this,200,60,100,30,"Hozzaad");
        opciok = new choose(this,50,110,200,5,"");
        visszavon = new button(this,50,210,100,30,"Visszavon");
        torol = new button(this,150,210,100,30,"Torol");
        modosit = new button(this,250,210,100,30,"Modosit");
        fileNev = new dinamicText(this,50,260,200,30);
        betolt = new button(this,250,260,100,30,"Betolt");
        kiment = new button(this,350,260,100,30,"Kiment");
        rendezesiMod = new choose(this,50,310,200,2,"");
        rendezestValt = new button(this,250,310,200,30,"Rendezesi modot valt");
        graf = new graph(this,470,20,300,300);

        start();
    }

    void start()
    {
        Tetel ujtetel;
        ujtetel.nev="ProbaNev";
        ujtetel.ertek=10;
        ujtetel.nap=_nap++;
        _tetelek.push_back(ujtetel);
        ujtetel.nev="Proba2";
        ujtetel.ertek=-1110;
        ujtetel.nap=_nap++;
        _tetelek.push_back(ujtetel);
        rendezesiMod->clearElement();
        rendezesiMod->addElement("eredeti");
        rendezesiMod->addElement("ertek csokkeno");
    }

    void update()
    {
        _index=opciok->clearElement();
        string temp;
        for(Tetel a : _tetelek)
        {
            temp=a.nev;
            temp+=" (";
            temp+=intToStringConverter(a.ertek);
            temp+=")";
            opciok->addElement(temp);
        }
        opciok->getIndex(_index);

        temp="Egyenleg: ";
        temp+=intToStringConverter(_egyenleg);
        staticText1->addElement(temp);

        rendezesiMod->setElementChosen();
    }

    void hozzadElemet()
    {
        if (hozzaad->changedValue())
        {
            Tetel ujtetel;
            ujtetel.nev=beNev->value();
            ujtetel.ertek=strintToIntConverter(beAr->value());
            ujtetel.nap=_nap++;
            _tetelek.push_back(ujtetel);
        }
    }

    void visszavonElemet()
    {
        if (_tetelek.size()>0 && visszavon->changedValue())
        {
            _tetelek.pop_back();
        }
    }

    void torolMindenElemet()
    {
        if (torol->changedValue())
        {
            _tetelek.clear();
            _nap=0;
        }
    }

    void modositElemet()
    {
        if (_tetelek.size()>0 && modosit->changedValue())
        {
            _tetelek[opciok->returnIndex()].nev=beNev->value();
            _tetelek[opciok->returnIndex()].ertek=strintToIntConverter(beAr->value());
            _tetelek[opciok->returnIndex()].nap=_nap++;
        }
        else if(modosit->changedValue())
        {
            Tetel ujtetel;
            ujtetel.nev=beNev->value();
            ujtetel.ertek=strintToIntConverter(beAr->value());
            ujtetel.nap=_nap++;
            _tetelek.push_back(ujtetel);
        }
    }

    void kivalasztElemet()
    {
        if (opciok->elementChosen())
        {
            _egyenleg+=_tetelek[_index].ertek;
            opciok->setElementChosen();

            grafRajzol();
        }
    }

    void kimentFileba()
    {
        if (fileNev->value()!="" && kiment->changedValue())
        {
            ofstream kiFile(fileNev->value());
            kiFile<<_egyenleg<<endl;
            for (Tetel a : _tetelek)
            {
                kiFile<<a.nev<<";"<<a.ertek<<";"<<a.nap<<endl;
            }
            kiFile.close();
        }
    }

    void betoltFilebol()
    {
        if (betolt->changedValue())
        {
            ifstream befile(fileNev->value());
            string temp;
            if (befile.good())
            {
                befile>>ws>>_egyenleg>>ws;
                Tetel betoltTetelt;
                while(befile.good())
                {
                    getline(befile,betoltTetelt.nev,';');
                    getline(befile,temp,';');
                    betoltTetelt.ertek=strintToIntConverter(temp);
                    befile>>betoltTetelt.nap>>ws;
                    _tetelek.push_back(betoltTetelt);
                }
            }
            befile.close();
        }
    }

    void elemekRendezese()
    {
        if (rendezestValt->changedValue())
        {
            if (rendezesiMod->returnIndex()==1)
            {
                _ertekcsokken.clear();
                for (Tetel a : _tetelek)
                {
                    _ertekcsokken.insert(a);
                }

                _tetelek.clear();
                for (Tetel a : _ertekcsokken)
                {
                    _tetelek.push_back(a);
                }
            }
            else
            {
                _beviteli.clear();
                TetelNapszerint be;
                for (Tetel a : _tetelek)
                {
                    be.ertek=a.ertek;
                    be.nap=a.nap;
                    be.nev=a.nev;
                    _beviteli.insert(be);
                }

                _tetelek.clear();
                Tetel be2;
                for (TetelNapszerint a : _beviteli)
                {
                    be2.ertek=a.ertek;
                    be2.nap=a.nap;
                    be2.nev=a.nev;
                    _tetelek.push_back(be2);
                }
            }
        }
    }

    void grafRajzol()
    {
        _beviteli.clear();
        TetelNapszerint be;
        for (Tetel a : _tetelek)
        {
            be.ertek=a.ertek;
            be.nap=a.nap;
            be.nev=a.nev;
            _beviteli.insert(be);
        }

        _tetelek.clear();
        Tetel be2;
        for (TetelNapszerint a : _beviteli)
        {
            be2.ertek=a.ertek;
            be2.nap=a.nap;
            be2.nev=a.nev;
            _tetelek.push_back(be2);
        }

        nap.clear();
        for (TetelNapszerint a : _beviteli)
        {
            nap.push_back(a.nap);
        }
        egyenleg.push_back(_egyenleg);
        graf->addData(nap,egyenleg);
    }

    virtual void action()
    {
        update();
        hozzadElemet();
        visszavonElemet();
        torolMindenElemet();
        modositElemet();
        kivalasztElemet();
        kimentFileba();
        betoltFilebol();
        elemekRendezese();
    }
};

int main()
{
    gout.open(XX, YY);
    MyApplication app;
    app.event_loop(XX, YY);
    return 0;
}

