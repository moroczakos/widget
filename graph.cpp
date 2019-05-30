#include "graph.h"
#include "graphics.hpp"
#include <vector>
#include <sstream>

using namespace genv;

graph::graph(Application * parent,int x, int y, int sx, int sy)
    : Widget(parent,x,y,sx,sy)
{

}

std::string intToStringConverter2(int input)
{
    std::string temp;
    std::stringstream ss;
    ss<<input;
    ss>>temp;
    return temp;
}

void graph::draw()
{
    gout << move_to(_x, _y) << color(255,255,255) << box(_size_x, _size_y);
    gout << move_to(_x+2, _y+2) << color(0,0,0) << box(_size_x-4, _size_y-4);
    gout << move_to(_x+30, _y+_size_y-30) << color(255,255,255) << box(_size_x-60, 2);
    gout << move_to(_x+30, _y+_size_y-30) << color(255,255,255) << box(2, 60-_size_y);
    if (_day.size()>1)
    {
        gout << move_to(_x+30, _y+_size_y-10) << color(255,255,255) << text(intToStringConverter2(_day[0]));
    }

}

void graph::handle(event ev)
{

}

std::string graph::value()
{
    return 0;
}

bool graph::changedValue()
{
    return false;
}

//egerkattintasra ne legyen fokuszalva azert hamis
bool graph::is_selected(int mouse_x, int mouse_y)
{
    return false;
}

//nem fokuszalhato
bool graph::focusable()
{
    return false;
}

void graph::addData(std::vector<int> day, std::vector<int> sumOfMoney)
{
    _day=day;
    _sumOfMoney=sumOfMoney;
}
