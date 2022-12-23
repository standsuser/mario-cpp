#ifndef BOMB_H
#define BOMB_H
class Bomb : public Obstacle
{
public:
    void execute(Champion c)
    {

        int x = c.getHp() - this->getTakeDmg();

        if (x < 0)
            x = 0;
        c.setHp(x);

        cout << "bomb excuted with dmg = " << this->getTakeDmg() << endl;
    }
};
#endif