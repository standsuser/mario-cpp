#ifndef CHAMPION_H
#define CHAMPION_H
class Champion : public Map
{
private:
    int hp;
    int gemScore;
    int champX;
    int champY;

public:
    // Champion() = default;
    Champion()
    {

        cout << "Constructor champion() is called" << endl;
        champY = 9; // Row
        champX = 0; // Column
        hp = 100;
        gemScore = 0;
    }
    void print_champ_info()
    {
        cout << "Current hp: " << hp << "  , Score: " << gemScore << " Location: " << endl;
    }

    void useAbility()
    {
        cout << "Ability x is called" << endl;
    }

    int getX()
    {
        return this->champX;
    }
    int getY()
    {
        return this->champY;
    }
    void setX(int x)
    {
        this->champX = x;
    }
    void setY(int y)
    {
        this->champY = y;
    }
    int getHp()
    {
        return this->hp;
    }
    void decHp()
    {
        this->hp -= 40;
        if (this->hp <= 0)
        {
            this->hp = 0;
        }
    }
    int getScore()
    {
        return this->gemScore;
    }
    void setScore(int x)
    {
        this->gemScore = x;
    }
    void setHp(int x)
    {
        this->hp = x;
    }
};
#endif