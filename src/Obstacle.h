#ifndef OBSTACLE_H
#define OBSTACLE_H
class Obstacle : public Map
{
private:
    int takedmg;

public:
    Obstacle()
    {
        srand(time(0));
        takedmg = rand() % 5 + 1;
    }

    virtual void execute(Champion c){};

    int getTakeDmg()
    {
        return this->takedmg;
    }
};
#endif