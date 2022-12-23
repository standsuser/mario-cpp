#ifndef GEM_H
#define GEM_H
class Gem : public Map
{
private:
    int points;

public:
    Gem()
    {
        srand(time(0));
        points = rand() % (5) + 5;
    }
    int getPoints()
    {
        return this->points;
    }
    virtual void execute(Champion c)
    {
    }
};
#endif