#ifndef THIEF_H
#define THIEF_H
class Thief : public Obstacle
{
public:
    void execute(Champion c);
    /*{

        int x = c.getScore() - this->getTakeDmg();

        if (x < 0)
            x = 0;
        c.setScore(x);

        cout << "thief executed with dmg = " << this->getTakeDmg() << endl;
    }*/
};
#endif