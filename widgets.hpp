#ifndef WIDGETS_HPP_INCLUDED
#define WIDGETS_HPP_INCLUDED

#include "graphics.hpp"

class Application;

class Widget {

protected:
    int _x, _y, _size_x, _size_y, _dx, _dy;
    Application * _parent;
    bool _focused;
    bool _grabbed;

public:

    virtual void setfocus(bool f);
    Widget(Application * parent, int x, int y, int sx, int sy);
    virtual bool is_selected(int mouse_x, int mouse_y);
    virtual void draw() = 0;
    virtual void handle(genv::event ev) = 0;
    virtual std::string value() = 0;
    virtual bool nullValue();
    virtual bool changedValue() = 0;
    virtual void moveObj(int ex, int ey, int XX, int YY);
    virtual void catchObj(int ex, int ey);
    virtual void releaseObj();
    virtual bool insideObj(int ex, int ey);
    virtual bool grabbed();
    virtual bool focusable();
    virtual void addElement(std::string);
    virtual void removeElement(std::string);
};

                                                                                                                                                                                                                                                                  //szeretnek pontlevonast kerni a beadandomra mert feltoltottem egy oktatasi segedletet sajat munka helyett :)

#endif // WIDGETS_HPP_INCLUDED
