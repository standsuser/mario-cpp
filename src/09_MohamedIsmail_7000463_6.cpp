#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <stdlib.h>
//-------------------------------//

using namespace std;
bool marioActive = false;

//------------------------------champion---------------------------------

class Champion
{
private:
    int hp;
    int gemScore;
    int champX;
    int champY;
    int RemaningAbilityMoves;

public:
    // Champion() = default;
    Champion()
    {

        cout << "Constructor champion() is called" << endl;
        champY = 0; // Row
        champX = 0; // Column
        hp = 100;
        gemScore = 0;
        RemaningAbilityMoves = 2;
    }
    // void print_champ_info()
    // {
    //     cout << "Current hp: " << hp << "  , Score: " << gemScore << "Remaining Ability Moves: " << RemaningAbilityMoves << endl;
    // }

   virtual void useAbility()
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
    int getRemainingAbilityMoves()
    {
        return this->RemaningAbilityMoves;
    }

    void setRemainingAbilityMoves(int x)
    {
        this->RemaningAbilityMoves = x;
    }
};

// class Luigi : public Champion
// {

//     // idea :  in whatever direction luigi moves we clean
//     //  the hypothetical place he was gonna move into ,that way we preserve the obstacles that are before him
//     //  if the ability was called, by cleaning I mean we just replace everything by dots or whatever the symbol of tile is
//     // defensive programming for luigi not to "clean himself" off the "lain" or not to clean mario as well so no cleaning
//     //  champions , also cleaning will save the point object thingies but remove obstacles
//     //  and we need to define what is front , I am guessing whateever last move he makes is the front so if he moved right
//     //  then the whole right direction will be clean
//     // IF luigi is somewhere and he moved in the another somewhere direction
//     //  useABility()
//     //  and we can use ability while in spawn as well and probably he will spawn somewhere else
//     //  and mario will be the original champion
// public:
//     void useAbility()
//     {
//         cout << "Luigi Ability is called" << endl;

//         for (int i = 0; i < 10; i++)
//         {
//             if (board[luigi->getX()][i].getType() == 'o ')
//             {
//                 board[luigi->getX()][i] = '. ';
//             }
//         }
//         for (int j = 0; j < 10; j++)
//         {
//             if (board[j][luigi->getX()].getType() == 'o ')
//             {
//                 board[j][luigi->getY()] = '. ';
//             }
//         }
//     }
// };

class Mario : public Champion
{
public:
    //  idea is putting all the move method here seems stupid , cos why the move function then to kill redundancy ?
    // so somehow we put the move function correctly and just +2 in every single direction but only one time
    // and we remove the getting damage line or something and  we make him not see obstacles aslan fa msh far2a m3ah
    // haye3mel eih

    void useAbility()
    {

        // In Class Mario the useAbility() method allows you to move 2 steps at a time allowing you to jump
        // over an obstacle without having any damage. It must print “Mario Ability is called”
        cout << "Mario Ability is called" << endl;
        marioActive = true;
        
    }
};

//------------------------------obstacle---------------------------
class Obstacle
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

class Thief : public Obstacle
{
public:
    void execute(Champion c)
    {

        int x = c.getScore() - this->getTakeDmg();

        if (x < 0)
            x = 0;
        c.setScore(x);

        cout << "thief executed with dmg = " << this->getTakeDmg() << endl;
    }
};

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

//--------------------------------gem --------------------------

class Gem
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

class Coin : public Gem
{

public:
    void execute(Champion c)
    {
        c.setScore(c.getScore() + this->getPoints());
        cout << "Coin executed with points = " << this->getPoints() << endl;
    }
};

class Potion : public Gem
{
public:
    void execute(Champion c)
    {
        c.setHp(c.getHp() + this->getPoints());
        if (c.getHp() == 100)
        {
            c.setHp(100);
        }
        cout << "Potion executed with points = " << this->getPoints() << endl;
    }
};

//--------------------------------cell-------------------------------------

class Cell
{
private:
    char type;
    int x, y;

public:
    Cell()
    {
        this->type = '.';
        this->x = 0;
        this->y = 0;
    }

    char getType()
    {
        return this->type;
    }

    void setType(char c)
    {
        this->type = c;
    }

    int getX()
    {
        return this->x;
    }

    void setX(int n)
    {
        this->x = n;
    }

    int getY()
    {
        return this->y;
    }

    void setY(int n)
    {
        this->y = n;
    }

    string toString()
    {
        return getType() + "";
    }
};

//----------------------------------------------------------------------------------------NEW MAP----------------------------------------------------------------------------------

class Map
{
private:
    int rows[10];
    int col[10];
    Cell **board;
    int gemCount, obstCount;
    int thievesX[10], thievesY[10], bombsX[10], bombsY[10], potionsX[10], potionsY[10], coinsX[10], coinsY[10];
    Obstacle *obstacles[20];
    Champion *c;

public:
    Map()
    {
        c = new Champion();
        board = new Cell *[10];
        for (int i = 0; i < 10; i++)
        {
            board[i] = new Cell[10];
        }
        newGame();
    }

    ~Map()
    {
        for (int i = 0; i < 10; ++i)
        {
            delete (board[i]); // deletes an inner array of integer;
        }
        delete (board); // delete pointer holding array of pointers;
    }

    void newGame()
    {
        randomize_map();
        cout << "print_map() called" << endl;
        print_map();
        rand_start();
    }

    void rand_start()
    {
        char mButton;

        while (mButton != '1' && mButton != '2')
        {
            cout << "Choose 1 to Randomize, Choose 2 to start the game" << endl;
            mButton = getch();
        }

        if (mButton == '1')
        {
            randomize_map();
            cout << "\033[2J\033[1;1H";
            Map *m = new Map();
            newGame();
        }
        else if (mButton == '2')
        {
            cout << "\033[2J\033[1;1H";
            cout << "print_map() called" << endl;
            choose_champ();
            newTurn();
        }
    }
    void choose_champ()
    {
        print_map();

        char rButton;

        while (rButton != 'M' && rButton != 'L')
        {
            cout << "Choose your champion! Choose M for Mario , Choose L for Luigi" << endl;
            rButton = getch();
        }

        if (rButton == 'M')
        {
            c = new Mario();
            cout << "\033[2J\033[1;1H";
            print_map();
        }
        else if (rButton == 'L')
        {
            //    c = new Luigi();
            cout << "\033[2J\033[1;1H";
            print_map();
        }
    }

    void print_map()
    {
        for (int i = 9; i >= 0; i--)
        {
            for (int j = 0; j < 10; j++)
            {
                if (i == c->getX() && j == c->getY())
                    board[i][j].setType('c');

                cout << board[i][j].getType() << " ";
            }
            cout << endl;
        }
    }
    void randomize_map()
    {
        gemCount = 0;
        obstCount = 0;

        for (int i = 9; i >= 0; i--) // what even is this
        {
            for (int j = 0; j < 10; j++)
            {
                board[i][j] = Cell();
                board[i][j].setX(i);
                board[i][j].setY(j);
                board[i][j].setType('.');
            }
        }

        srand(time(0));

        // Thieves & Bombs locations set
        for (int i = 0; obstCount < 20; i++)
        {
            do
            {
                thievesX[i] = (rand() % 10);
                thievesY[i] = (rand() % 10);
                if (thievesX[i] == 0 && thievesY[i] == 0)
                {
                    thievesX[i] = (rand() % 9) + 1;
                    thievesY[i] = (rand() % 9) + 1;
                }
            } while (board[thievesX[i]][thievesY[i]].getType() != '.');

            board[thievesX[i]][thievesY[i]].setType('o');
            board[thievesX[i]][thievesY[i]].setX(thievesX[i]);
            board[thievesX[i]][thievesY[i]].setY(thievesY[i]);
            obstCount++;

            do
            {
                bombsX[i] = (rand() % 10);
                bombsY[i] = (rand() % 10);
                if (bombsX[i] == 0 && bombsY[i] == 0)
                {
                    bombsX[i] = (rand() % 9) + 1;
                    bombsY[i] = (rand() % 9) + 1;
                }
            } while (board[bombsX[i]][bombsY[i]].getType() != '.');

            board[bombsX[i]][bombsY[i]].setType('o');
            board[bombsX[i]][bombsY[i]].setX(bombsX[i]);
            board[bombsX[i]][bombsY[i]].setY(bombsY[i]);
            obstCount++;
        }

        // Coins & potions locations set
        for (int i = 0; gemCount < 40; i++)
        {
            do
            {
                coinsX[i] = (rand() % 10); // changed to 10 cuz it can nvr be 20 it's a coordinate
                coinsY[i] = (rand() % 10);
                if (coinsX[i] == 0 && coinsY[i] == 0)
                {
                    coinsX[i] = (rand() % 9) + 1;
                    coinsY[i] = (rand() % 9) + 1;
                }
            } while (board[coinsX[i]][coinsY[i]].getType() != '.');

            board[coinsX[i]][coinsY[i]].setType('g');
            board[coinsX[i]][coinsY[i]].setX(coinsX[i]);
            board[coinsX[i]][coinsY[i]].setY(coinsY[i]);
            gemCount++;

            do
            {
                potionsX[i] = (rand() % 10);
                potionsY[i] = (rand() % 10);
                if (potionsX[i] == 0 && potionsY[i] == 0)
                {
                    potionsX[i] = (rand() % 9) + 1;
                    potionsY[i] = (rand() % 9) + 1;
                }
            } while (board[potionsX[i]][potionsY[i]].getType() != '.');

            board[potionsX[i]][potionsY[i]].setType('g');
            board[potionsX[i]][potionsY[i]].setX(potionsX[i]);
            board[potionsX[i]][potionsY[i]].setY(potionsY[i]);
            gemCount++;
        }

        //   Creating those Gems
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (board[i][j].getType() == 'o')
                {
                    if (thievesX[i] == i && thievesY[j] == j)
                        Obstacle *o = new Thief();

                    if (bombsX[i] == i && bombsY[j] == j)
                        Obstacle *o = new Bomb();
                }

                // if (board[i][j].getType() == 'c')
                // {
                //     Champion *c = new Champion();
                // }

                if (board[i][j].getType() == 'g')
                {
                    if (potionsX[i] == i && potionsY[j] == j)
                        Gem *g = new Potion();

                    if (coinsX[i] == i && coinsY[j] == j)
                        Gem *g = new Coin();
                }
            }
        }

        //   In case there are duplicates
        for (int i = 0; i < 10; i++) // unnecessary
        {
            for (int j = 0; j < 10; j++)
            {

                // relocating coins
                while ((coinsX[i] == (thievesX[i] || bombsX[i])) && (coinsY[j] == (thievesY[j] || bombsY[j])))
                {
                    coinsX[j] = (rand() % 19) + 1;
                    coinsY[j] = (rand() % 19) + 1;
                }

                // Relocating Potions
                while ((potionsX[i] == (thievesX[i] || bombsX[i])) && (potionsY[j] == (thievesY[j] || bombsY[j])))
                {
                    potionsY[j] = (rand() % 19) + 1;
                    potionsX[j] = (rand() % 19) + 1;
                }
            }
        }
    }
    void newTurn()
    {
        // clear terminal

        cout << "\033[2J\033[1;1H";
        print_map();
        cout << " 8 -> Up, 5 -> Down, 4 -> Left, 6 -> Right" << endl;
        cout << "Total Gem count (g): " << gemCount << "\nObst count (o): " << obstCount << "\nScore: " << c->getScore() << "\nHealth: " << c->getHp() << "\nx: " << c->getX() << "\ny: " << c->getY() << "\nRemaining Ability Moves: " << c->getRemainingAbilityMoves() << endl;
        char input;
        end();
        cout << "Enter direction: ";
        input = getch();
        if( input =='X'){
        c->useAbility();
        if(c->getRemainingAbilityMoves()<=0){

            cout<<"no ability moves left"<<endl;
            marioActive=false;
            newTurn();
        }
        else{
        c->setRemainingAbilityMoves(c->getRemainingAbilityMoves()-1);
        }

        move(input = getch());
        }
        else
        move(input);
    }

    void end()
    {
        if (c->getScore() == gemCount)
        {
            cout << "Congrats you won!!" << endl;
            for (int i = 0; i < 5; ++i)
            {
                delete (board[i]);
            }
            delete (board);
            exit(0);
        }

        else if (c->getHp() <= 0)
        {
            cout << "You lost :( but you can try again :D" << endl;
            for (int i = 0; i < 5; ++i)
            {
                delete (board[i]);
            }
            delete (board);
            exit(0);
        }
        else
        {
            return;
        }
    }

    void marioAbilityHelper(int k)
    {

                marioActive=false; //doesnt work globaly like outside the method i tried pointer and it didnt work
        switch (k)
        {
        case 8:
        {
            if (c->getX() == 9)
            {
                cout << "out of range!";

                newTurn();
            }
            else if (c->getX() + 1 == 9)
            {
                cout << "out of range!";
                newTurn();
            }
            else
            {
                board[c->getX()][c->getY()].setType('.');
                c->setX(c->getX() + 2);
                move(8); // move second step and pickup gem/get hit with obst
            }
        }
        case 6:
        {
            if (c->getY() == 9)
            {
                cout << "out of range!";

                newTurn();
            }
            else if (c->getY() + 1 == 9)
            {
                cout << "out of range!";
                newTurn();
            }
            else
            {

                board[c->getX()][c->getY()].setType('.');
                c->setY(c->getY() + 1);
                move(6);
            }
        }

        case 5: // board[mario.getX() - 1][mario.getY()]
        {
            if (c->getX() == 0)
            {
                cout << "out of range!";

                newTurn();
            }
            else if (c->getX() - 1 == 0)
            {
                cout << "out of range!";
                newTurn();
            }
            else
            {

                board[c->getX()][c->getY()].setType('.');
                c->setX(c->getX() - 1);
                move(5);
            }
        }

        case 4: // board[mario.getX()][mario.getY() - 1]
        {
            if (c->getY() == 0)
            {
                cout << "out of range!";

                newTurn();
            }
            else if (c->getY() - 1 == 0)
            {
                cout << "out of range!";
                newTurn();
            }
            else
            {

                board[c->getX()][c->getY()].setType('.');
                c->setY(c->getY() - 1);
                move(4);
            }
        }
        }
    }

    void move(char k)
    {

        switch (k)
        {
        case '8':
        {
            cout<<marioActive<<"";
            if (c->getX() == 9)
            {
                newTurn();
            }

            if (board[c->getX() + 1][c->getY()].getType() == 'o')
            {
                if (marioActive == false)
                {
                    c->decHp();
                    board[c->getX()][c->getY()].setType('.');
                    c->setX(c->getX() + 1);
                }
                else
                {
                    marioAbilityHelper(8);
                }

                newTurn();
            }
            else if (board[c->getX() + 1][c->getY()].getType() == 'g')
            {

                if (marioActive == false)
                {

                    c->setScore(c->getScore() + 1);
                    board[c->getX()][c->getY()].setType('.');
                    c->setX(c->getX() + 1);
                }
                else
                    marioAbilityHelper(8);

                newTurn();
            }
            else if (board[c->getX() + 1][c->getY()].getType() == '.')
            {
                if (marioActive == false)
                {
                    board[c->getX()][c->getY()].setType('.');

                    c->setX(c->getX() + 1);
                }
                else
                    marioAbilityHelper(8);

                newTurn();
            }

            else
            {
                newTurn();
            }
        }
        break;
        case '6': // board[mario.getX()][mario.getY() + 1]
        {
            if (c->getY() == 9)
            {
                newTurn();
            }
            if (board[c->getX()][c->getY() + 1].getType() == 'o')
            {
                if (!marioActive)
                {
                    c->decHp();
                    board[c->getX()][c->getY()].setType('.');
                    c->setY(c->getY() + 1);
                }
                else
                {
                    marioAbilityHelper(6);
                }

                newTurn();
            }
            else if (board[c->getX()][c->getY() + 1].getType() == 'g')
            {
                if (!marioActive)
                {
                    c->setScore(c->getScore() + 1);
                    board[c->getX()][c->getY()].setType('.');
                    c->setY(c->getY() + 1);
                }
                else
                {
                    marioAbilityHelper(6);
                }

                newTurn();
            }
            else if (board[c->getX()][c->getY() + 1].getType() == '.')
            {
                if (!marioActive)
                {
                    board[c->getX()][c->getY()].setType('.');
                    c->setY(c->getY() + 1);
                }
                else
                {
                    marioAbilityHelper(6);
                }

                newTurn();
            }

            else
            {
                newTurn();
            }
        }
        break;
        case '5': // board[mario.getX() - 1][mario.getY()]
        {
            if (c->getX() == 0)
            {
                newTurn();
            }
            if (board[c->getX() - 1][c->getY()].getType() == 'o')
            {
                if (!marioActive)
                {
                    c->decHp();
                    board[c->getX()][c->getY()].setType('.');
                    c->setX(c->getX() - 1);
                }
                else
                {
                    marioAbilityHelper(5);
                }

                newTurn();
            }
            else if (board[c->getX() - 1][c->getY()].getType() == 'g')
            {
                if (!marioActive)
                {
                    c->setScore(c->getScore() + 1);
                    board[c->getX()][c->getY()].setType('.');
                    c->setX(c->getX() - 1);
                }
                else
                {
                    marioAbilityHelper(5);
                }

                newTurn();
            }
            else if (board[c->getX() - 1][c->getY()].getType() == '.')
            {
                if (!marioActive)
                {
                    board[c->getX()][c->getY()].setType('.');
                    c->setX(c->getX() - 1);
                }
                else
                {
                    marioAbilityHelper(5);
                }

                newTurn();
            }

            else
            {
                newTurn();
            }
        }
        break;
        case '4': // board[mario.getX()][mario.getY() - 1]
        {
            if (c->getY() == 0)
            {
                newTurn();
            }
            if (board[c->getX()][c->getY() - 1].getType() == 'o')
            {
                if (!marioActive)
                {
                    c->decHp();
                    board[c->getX()][c->getY()].setType('.');
                    c->setY(c->getY() - 1);
                }
                else
                {
                    marioAbilityHelper(4);
                }

                newTurn();
            }
            else if (board[c->getX()][c->getY() - 1].getType() == 'g')
            {
                if (!marioActive)
                {
                    c->setScore(c->getScore() + 1);
                    board[c->getX()][c->getY()].setType('.');
                    c->setY(c->getY() - 1);
                }
                else
                {
                    marioAbilityHelper(4);
                }

                newTurn();
            }
            else if (board[c->getX()][c->getY() - 1].getType() == '.')
            {
                if (!marioActive)
                {
                    board[c->getX()][c->getY()].setType('.');
                    c->setY(c->getY() - 1);
                }
                else
                {
                    marioAbilityHelper(4);
                }

                newTurn();
            }

            else
            {
                newTurn();
            }
        }
        break;
        default:
            newTurn();
        }
    }

}; // END OF MAP CLASS

//----------------------------new turn and move ---------------------------

int main()
{

    // Potion x = Potion();
    // Champion a = Champion();
    // x.execute(a);

    // Map();
    Map *m = new Map();
    // m->randomize_map();
    return 0;
}