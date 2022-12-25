#ifndef POTION_H
#define POTION_H
class Potion : public Gem
{
public:
    void execute(Champion c);
    /*{
        c.setHp(c.getHp() + this->getPoints());
        if (c.getHp() == 100)
        {
            c.setHp(100);
        }
        cout << "Potion executed with points = " << this->getPoints() << endl;
    }*/
};
#endif