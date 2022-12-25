#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "Champion.h"
class Obstacle
{
private:
    int takedmg;

public:
    Obstacle();
    /*{
        srand(time(0));
        takedmg = rand() % 5 + 1;
    }*/

    virtual void execute(Champion c);

    int getTakeDmg();
};
#endif