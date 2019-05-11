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



using namespace std;
using namespace genv;

int XX=800, YY=400;

class MyApplication : public Application
{
protected:
    int memory=0, number=0;
    counter * count1;
    counter * count2;
    choose * choose1;
    choose * choose2;
    button * button1;
    button * button2;
    button * button3;
    button * buttonPlus;
    button * buttonDelete;
    button * buttonEqual;
    scroll * scroll1;
    staticText * staticText1;
   // staticText * staticText2;
    dinamicText * dinamicText1;

public:
    MyApplication(){

        ///elemek atpakolasahoz innentol
        /*choose1 = new choose(this,30,80,200,12,"befile.txt");
        choose2 = new choose(this,300,80,150,12,"befile2.txt");
        button1 = new button(this,500,80,30,30,"+");
        button2 = new button(this,500,120,30,30,"->");
        button3 = new button(this,500,160,30,30,"<-");
        dinamicText1 = new dinamicText(this,600,80,100,30);*/
        ///idaig

        buttonPlus = new button(this,400,80,30,30,"+");
        buttonDelete = new button(this,400,120,30,30,"Delete");
        buttonEqual = new button(this,400,160,30,30,"=");
        button1 = new button(this,500,80,30,30,"1");
        button2 = new button(this,500,120,30,30,"2");
        button3 = new button(this,500,160,30,30,"3");
        staticText1 = new staticText(this,40,20,100,30,"");


        //count1 = new counter(this,30,30,-10,100);
        //count2 = new counter(this,300,30,25,75);

        //scroll1 = new scroll(this,50,200,200,100,"beolvas.txt");
        //staticText1 = new staticText(this,80,150,100,80,"Ez egy statikus szovegdoboz adbbdsssbbsavaavava");

    }
    void moveElement()
    {
        if (button1->changedValue())
        {
            choose1->addElement(dinamicText1->value());
        }
        if (button2->changedValue())
        {
            std::string temp=choose1->value();
            if (!choose1->nullValue()){
                choose2->addElement(choose1->value());
                choose1->removeElement(temp);
            }
        }
        if (button3->changedValue())
        {
            std::string temp=choose2->value();
            if (!choose2->nullValue()){
                choose1->addElement(choose2->value());
                choose2->removeElement(temp);
            }
        }
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


    enum class operation{ADD, SUBSTRACT, DIVIDE, EQUAL};
    operation o;

    //if(m==muvelet::ADD)

    void calculator()
    {
        //osszeadas gomb lenyomasa elmenti a staticText erteket
        if (buttonPlus->changedValue())
        {
            memory=number;
            number=0;
        }

        if (buttonDelete->changedValue())
        {
            memory/=10;
            number=memory;
        }

        if (buttonEqual->changedValue())
        {
            memory+=number;
            number=memory;
        }

        if (button1->changedValue())
        {
            if (number==0){
                number=strintToIntConverter(button1->value());
            }
            else{
                number*=10;
                number+=strintToIntConverter(button1->value());
            }
        }

        if (button2->changedValue())
        {
            if (number==0){
                number=strintToIntConverter(button2->value());
            }
            else{
                number*=10;
                number+=strintToIntConverter(button2->value());
            }
        }
        staticText1->addElement(intToStringConverter(number));
    }

    virtual void action()
    {
        //moveElement();
        calculator();
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
