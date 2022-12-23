#ifndef COIN_H
#define COIN_H
class Coin : public Gem
{

public:
    void execute(Champion c)
    {
        c.setScore(c.getScore() + this->getPoints());
        cout << "Coin executed with points = " << this->getPoints() << endl;
    }
};
#endif