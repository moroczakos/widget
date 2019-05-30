#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"
#include <vector>

class graph : public Widget {
protected:
    std::vector<int> _day;
    std::vector<int> _sumOfMoney;
public:
    graph(Application * parent,int x, int y, int sx, int sy);
    virtual void draw();
    virtual bool is_selected(int mouse_x, int mouse_y);
    virtual bool focusable();
    virtual void handle(genv::event ev);
    virtual bool changedValue();
    virtual std::string value();
    virtual void addData(std::vector<int> day, std::vector<int> sumOfMoney);
};

#endif // GRAPH_H_INCLUDED
