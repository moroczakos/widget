#ifndef FIGURE_H_INCLUDED
#define FIGURE_H_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"

class figure : public Widget {
protected:
    int _whichPlayer;
public:
    figure(Application * parent,int x, int y, int sx, int sy, int whichPlayer);
    virtual void draw();
    virtual void handle(genv::event ev);
    virtual bool changedValue();
    virtual std::string value();
    virtual bool moveable();
    virtual int returnXcoord();
    virtual int returnYcoord();
    virtual void setXcoord(int x);
    virtual void setYcoord(int y);
    virtual int whichPlayer();
    virtual void setMoveable(bool setMoveable);
};


#endif // FIGURE_H_INCLUDED
