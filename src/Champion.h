#ifndef CHAMPION_H
#define CHAMPION_H
class Champion
{
private:
    int hp;
    int gemScore;
    int champX;
    int champY;

public:
    // Champion() = default;
    Champion();
    /*{

        cout << "Constructor champion() is called" << endl;
        champY = 9; // Row
        champX = 0; // Column
        hp = 100;
        gemScore = 0;
    }*/
    void print_champ_info();
    /*{
        cout << "Current hp: " << hp << "  , Score: " << gemScore << " Location: " << endl;
    }*/

    void useAbility();
    /*{
        cout << "Ability x is called" << endl;
    }*/

    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    int getHp();
    void decHp();
    /*{
        this->hp -= 40;
        if (this->hp <= 0)
        {
            this->hp = 0;
        }
    }*/
    int getScore();
    void setScore(int x);
    void setHp(int x);
};
#endif