#ifndef GAMECONTROL_H_INCLUDED
#define GAMECONTROL_H_INCLUDED
#include <vector>

class gameControl{
protected:


public:
    std::vector<std::vector<int> > _table{ {0,-1,-1,0,-1,-1,0},
                                 {-1,0,-1,0,-1,0,-1},
                                 {-1,-1,0,0,0,-1,-1},
                                 {0,0,0,-1,0,0,0},
                                 {-1,-1,0,0,0,-1,-1},
                                 {-1,0,-1,0,-1,0,-1},
                                 //{1,-1,-1,1,-1,-1,1},
                                 {0,-1,-1,0,-1,-1,0} };
    virtual bool canTakeFigure();
    virtual bool nearby(int x_from, int y_from, int x_to, int y_to);



};

#endif // GAMECONTROL_H_INCLUDED
