#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <stdlib.h>
#include <unistd.h>
//-------------------------------//

using namespace std;
bool marioActive = false;
bool luigiActive = false;
int CompletedgemScore;
string currentchamp = "empty";
//------------------------------champion---------------------------------
//--------------------------------cell-------------------------------------

class Cell
{
private:
    char type;
    int x, y;
    char objType;

public:
    Cell()
    {
        this->type = '.';
        this->x = 0;
        this->y = 0;
    }

    char getObjType()
    {
        return this->objType;
    }

    void setObjType(char c)
    {
        this->objType = c;
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

class Champion : public Cell
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
        return gemScore;
    }
    void setScore(int x)
    {
        gemScore = x;
    }

    void decScore()
    {
    }
    void setHp(int k)
    {
        hp = k;
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

class Luigi : public Champion
{

public:
    void useAbility()
    {
        luigiActive = true;
        cout << "Luigi Ability is called" << endl;
    }
};

class Mario : public Champion
{
public:
    void useAbility()
    {

        cout << "Mario Ability is called" << endl;
        marioActive = true;
    }
};

//------------------------------obstacle---------------------------
class Obstacle
{
private:
    int takedmg;
    char type;

public:
    Obstacle()
    {
        // srand(time(0));
        takedmg = rand() % 5 + 1;
    }

    virtual void execute(Champion *c)
    {
        cout << "Obstacle execute called" << endl;
    }

    int getTakeDmg()
    {
        return this->takedmg;
    }
};

class Thief : public Obstacle
{
public:
    void execute(Champion *c)
    {

        int x = c->getScore() - this->getTakeDmg();

        if (x < 0)
            x = 0;
        c->setScore(x);

        cout << "thief executed with dmg = " << this->getTakeDmg() << endl;
        sleep(4);
    }
};

class Bomb : public Obstacle
{
public:
    void execute(Champion *c)
    {

        int x = c->getHp() - this->getTakeDmg();

        if (x < 0)
            x = 0;
        //   c->setHp(x);

        cout << "bomb excuted with dmg = " << this->getTakeDmg() << endl;
        sleep(4);
    }
};

//--------------------------------gem --------------------------

class Gem : public Cell
{
private:
    int amount;
    int name;

public:
    Gem()
    {
        srand(time(0));
        this->amount = rand() % 6 + 5;
    }
    int getPoints()
    {
        return this->amount;
    }

    void setPoints(int z)
    {
        this->amount = z;
    }

    virtual void execute(Champion c)
    {
    }
};

class Coin : public Gem
{

public:
    void execute(Champion *c)
    {
        if (getPoints() == 100)
        {
            setPoints(rand() % 6 + 5);
        }
        int newScore = c->getScore() + getPoints();
        CompletedgemScore += getPoints();
        c->setScore(newScore);

        cout << "Coin executed with points = " << getPoints() << endl;
        sleep(4);
    }
};

class Potion : public Gem
{
public:
    void execute(Champion *c)
    {
        c->setHp(c->getHp() + getPoints());
        if (c->getHp() >= 100)
        {
            c->setHp(100);
        }
        cout << "Potion executed with points = " << getPoints() << endl;
        sleep(4);
    }
};

//----------------------------------------------------------------------------------------NEW MAP----------------------------------------------------------------------------------

class Map
{
private:
    int rows[10];
    int col[10];
    Cell ***board;
    int gemCount, obstCount;
    int thievesX[10], thievesY[10], bombsX[10], bombsY[10], potionsX[10], potionsY[10], coinsX[10], coinsY[10];
    Obstacle *obstacles[20];

    Champion *c;

public:
    Map()
    {
        c = new Champion();
        board = new Cell **[10];
        for (int i = 0; i < 10; i++)
        {
            board[i] = new Cell*[10];
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
            currentchamp = "Mario";
            print_map();
        }
        else if (rButton == 'L')
        {
            c = new Luigi();
            cout << "\033[2J\033[1;1H";
            currentchamp = "Luigi";
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
                    board[i][j]->setType('c');

                cout << board[i][j]->getType() << " ";
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
                board[i][j] = new Cell();
                board[i][j]->setX(i);
                board[i][j]->setY(j);
                board[i][j]->setType('.');
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
            } while (board[thievesX[i]][thievesY[i]]->getType() != '.');

            board[thievesX[i]][thievesY[i]]->setType('t');
            board[thievesX[i]][thievesY[i]]->setX(thievesX[i]);
            board[thievesX[i]][thievesY[i]]->setY(thievesY[i]);
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
            } while (board[bombsX[i]][bombsY[i]]->getType() != '.');

            board[bombsX[i]][bombsY[i]]->setType('b');
            board[bombsX[i]][bombsY[i]]->setX(bombsX[i]);
            board[bombsX[i]][bombsY[i]]->setY(bombsY[i]);
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
            } while (board[coinsX[i]][coinsY[i]]->getType() != '.');

            board[coinsX[i]][coinsY[i]]->setType('$');
            board[coinsX[i]][coinsY[i]]->setX(coinsX[i]);
            board[coinsX[i]][coinsY[i]]->setY(coinsY[i]);
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
            } while (board[potionsX[i]][potionsY[i]]->getType() != '.');

            board[potionsX[i]][potionsY[i]]->setType('p');
            board[potionsX[i]][potionsY[i]]->setX(potionsX[i]);
            board[potionsX[i]][potionsY[i]]->setY(potionsY[i]);
            gemCount++;
        }

        CompletedgemScore = gemCount;
        //   Creating those Gems and Obsts
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (board[i][j]->getType() == 'o')
                {
                    if (thievesX[i] == i && thievesY[j] == j)
                    {
                        Thief *t = new Thief();
                    }

                    if (bombsX[i] == i && bombsY[j] == j)
                    {
                        Bomb *b = new Bomb();
                    }
                }

                // if (board[i][j].getType() == 'c')
                // {
                //     Champion *c = new Champion();
                // }

                if (board[i][j]->getType() == 'g')
                {
                    if (potionsX[i] == i && potionsY[j] == j)
                    {
                        Potion *p = new Potion();
                    }

                    if (coinsX[i] == i && coinsY[j] == j)
                    {
                        Coin *coin = new Coin();
                    }
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
        cout << "Total Gem count (g): " << gemCount << "\nObst count (o): " << obstCount << "\nScore: " << c->getScore() << "\nHealth: " << c->getHp() << "\nx: " << c->getX() << "\ny: " << c->getY() << "\nChampion Type: " << currentchamp << "\nRemaining Ability Moves: " << c->getRemainingAbilityMoves() << endl;
        char input;
        end();
        cout << "Enter direction: ";
        input = getch();
        if (input == 'X')
        {
            c->useAbility();
            if (c->getRemainingAbilityMoves() <= 0)
            {

                cout << "no ability moves left" << endl;
                marioActive = false;
                luigiActive = false;
                newTurn();
            }
            else
            {
                c->setRemainingAbilityMoves(c->getRemainingAbilityMoves() - 1);
            }

            move(input = getch());
        }
        else
            move(input);
    }

    void end()
    {
        if (c->getScore() >= CompletedgemScore)
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

        marioActive = false; // doesnt work globaly like outside the method i tried pointer and it didnt work
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
                board[c->getX()][c->getY()]->setType('.');
                c->setX(c->getX() + 2);
                if (board[c->getX()][c->getY()]->getType() == 't')
                {
                    Thief *tempP = (Thief *)c;
                    tempP->execute(c);
                }

                if (board[c->getX()][c->getY()]->getType() == 'b')
                {
                    Bomb *tempP = (Bomb *)c;
                    tempP->execute(c);
                }
                if (board[c->getX()][c->getY()]->getType() == 'p')
                {
                    Potion *tempP = (Potion *)c;
                    tempP->execute(c);
                }
                if (board[c->getX()][c->getY()]->getType() == '$')
                {
                    Coin *tempP = (Coin *)c;
                    tempP->execute(c);
                }
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
                board[c->getX()][c->getY()]->setType('.');
                c->setY(c->getY() + 2);
                if (board[c->getX()][c->getY()]->getType() == 't')
                {
                    Thief *tempP = (Thief *)c;
                    tempP->execute(c);
                }

                if (board[c->getX()][c->getY()]->getType() == 'b')
                {
                    Bomb *tempP = (Bomb *)c;
                    tempP->execute(c);
                }
                if (board[c->getX()][c->getY()]->getType() == 'p')
                {
                    Potion *tempP = (Potion *)c;
                    tempP->execute(c);
                }
                if (board[c->getX()][c->getY()]->getType() == '$')
                {
                    Coin *tempP = (Coin *)c;
                    tempP->execute(c);
                }

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

                board[c->getX()][c->getY()]->setType('.');
                c->setX(c->getX() - 2);
                if (board[c->getX()][c->getY()]->getType() == 't')
                {
                    Thief *tempP = (Thief *)c;
                    tempP->execute(c);
                }

                if (board[c->getX()][c->getY()]->getType() == 'b')
                {
                    Bomb *tempP = (Bomb *)c;
                    tempP->execute(c);
                }
                if (board[c->getX()][c->getY()]->getType() == 'p')
                {
                    Potion *tempP = (Potion *)c;
                    tempP->execute(c);
                }
                if (board[c->getX()][c->getY()]->getType() == '$')
                {
                    Coin *tempP = (Coin *)c;
                    tempP->execute(c);
                }
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

                board[c->getX()][c->getY()]->setType('.');
                c->setY(c->getY() - 2);
                if (board[c->getX()][c->getY()]->getType() == 't')
                {
                    Thief *tempP = (Thief *)c;
                    tempP->execute(c);
                }

                if (board[c->getX()][c->getY()]->getType() == 'b')
                {
                    Bomb *tempP = (Bomb *)c;
                    tempP->execute(c);
                }
                if (board[c->getX()][c->getY()]->getType() == 'p')
                {
                    Potion *tempP = (Potion *)c;
                    tempP->execute(c);
                }
                if (board[c->getX()][c->getY()]->getType() == '$')
                {
                    Coin *tempP = (Coin *)c;
                    tempP->execute(c);
                }
                move(4);
            }
        }
        }
    }

    void luigiAbilityHelper(int k)
    {
        luigiActive = false;
        switch (k)
        {
        case 8:
        {

            for (int i = (9 - c->getX()); i >= 0; i--)
            {
                if (board[c->getX() + i][c->getY()]->getType() == 't' || board[c->getX() + i][c->getY()]->getType() == 'b')
                    board[c->getX() + i][c->getY()]->setType('.');
            }
            break;
        case 6: // board[mario.getX()][mario.getY() + 1]
        {
            for (int i = (9 - c->getY()); i >= 0; i--)
            {
                if (board[c->getX()][c->getY() + i]->getType() == 't' || board[c->getX()][c->getY() + i]->getType() == 'b')
                    board[c->getX()][c->getY() + i]->setType('.');
            }
        }
        break;
        case 5: // board[mario.getX() - 1][mario.getY()]
        {
            for (int i = (0 - c->getX()); i <= 0; i++)
            {
                if (board[c->getX() + i][c->getY()]->getType() == 't' || board[c->getX() + i][c->getY()]->getType() == 'b')
                    board[c->getX() + i][c->getY()]->setType('.');
            }
        }
        break;
        case 4: // board[mario.getX()][mario.getY() - 1]
        {
            for (int i = (0 - c->getY()); i <= 0; i++)
            {
                if (board[c->getX()][c->getY() + i]->getType() == 't' || board[c->getX()][c->getY() + i]->getType() == 'b')
                    board[c->getX()][c->getY() + i]->setType('.');
            }
        }
        break;
        default:
            newTurn();
        }
        }
    }

    //-----------------------------------------------------------------------------move--------------------------------------------------------------------
    void move(char k)
    {

        switch (k)
        {
        case '8':
        {
            if (c->getX() == 9)
            {
                newTurn();
            }

            if (board[c->getX() + 1][c->getY()]->getType() == 't')
            {
                if (!marioActive && !luigiActive)
                {
                    Thief *tempP = (Thief *)c;
                    tempP->execute(c);
                    board[c->getX()][c->getY()]->setType('.');
                    c->setX(c->getX() + 1);
                }

                else if (marioActive)
                    marioAbilityHelper(8);
                else
                    luigiAbilityHelper(8);

                newTurn();
            }
            else if (board[c->getX() + 1][c->getY()]->getType() == 'b')
            {
                if (!marioActive && !luigiActive)
                {
                    Bomb *tempP = (Bomb *)c;
                    tempP->execute(c);
                    board[c->getX()][c->getY()]->setType('.');
                    c->setX(c->getX() + 1);
                }

                else if (marioActive)
                    marioAbilityHelper(8);
                else
                    luigiAbilityHelper(8);

                newTurn();
            }
            else if (board[c->getX() + 1][c->getY()]->getType() == '$')
            {

                if (!marioActive && !luigiActive)
                {

                    Coin *tempP = (Coin *)c;
                    tempP->execute(c);
                    board[c->getX()][c->getY()]->setType('.');
                    c->setX(c->getX() + 1);
                }
                else if (marioActive)
                    marioAbilityHelper(8);
                else
                    luigiAbilityHelper(8);
                newTurn();
            }
            else if (board[c->getX() + 1][c->getY()]->getType() == 'p')
            {
                if (!marioActive && !luigiActive)
                {

                    Potion *tempP = (Potion *)c;
                    tempP->execute(c);
                    board[c->getX()][c->getY()]->setType('.');
                    c->setX(c->getX() + 1);
                }
                else if (marioActive)
                    marioAbilityHelper(8);
                else
                    luigiAbilityHelper(8);
                newTurn();
            }
            else if (board[c->getX() + 1][c->getY()]->getType() == '.')
            {
                if (!marioActive && !luigiActive)
                {
                    board[c->getX()][c->getY()]->setType('.');

                    c->setX(c->getX() + 1);
                }
                else if (marioActive)
                    marioAbilityHelper(8);
                else
                    luigiAbilityHelper(8);

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
            if (board[c->getX()][c->getY() + 1]->getType() == 't')
            {
                if (!marioActive && !luigiActive)
                {
                    Thief *tempP = (Thief *)c;
                    tempP->execute(c);
                    board[c->getX()][c->getY()]->setType('.');
                    c->setY(c->getY() + 1);
                }
                else if (marioActive)
                    marioAbilityHelper(6);
                else
                    luigiAbilityHelper(6);

                newTurn();
            }
            else if (board[c->getX()][c->getY() + 1]->getType() == 'b')
            {
                if (!marioActive && !luigiActive)
                {
                    Thief *tempP = (Thief *)c;
                    tempP->execute(c);
                    board[c->getX()][c->getY()]->setType('.');
                    c->setY(c->getY() + 1);
                }
                else if (marioActive)
                    marioAbilityHelper(6);
                else
                    luigiAbilityHelper(6);

                newTurn();
            }
            else if (board[c->getX()][c->getY() + 1]->getType() == '$')
            {
                if (!marioActive && !luigiActive)
                {
                    Coin *tempP = (Coin *)c;
                    tempP->execute(c);
                    board[c->getX()][c->getY()]->setType('.');
                    c->setY(c->getY() + 1);
                }
                else if (marioActive)
                    marioAbilityHelper(6);
                else
                    luigiAbilityHelper(6);

                newTurn();
            }
            else if (board[c->getX()][c->getY() + 1]->getType() == 'p')
            {
                if (!marioActive && !luigiActive)
                {
                    Potion *tempP = (Potion *)c;
                    tempP->execute(c);
                    board[c->getX()][c->getY()]->setType('.');
                    c->setY(c->getY() + 1);
                }
                else if (marioActive)
                    marioAbilityHelper(6);
                else
                    luigiAbilityHelper(6);

                newTurn();
            }
            else if (board[c->getX()][c->getY() + 1]->getType() == '.')
            {
                if (!marioActive && !luigiActive)
                {
                    board[c->getX()][c->getY()]->setType('.');
                    c->setY(c->getY() + 1);
                }
                else if (marioActive)
                    marioAbilityHelper(6);
                else
                    luigiAbilityHelper(6);

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
            if (board[c->getX() - 1][c->getY()]->getType() == 't')
            {
                if (!marioActive && !luigiActive)
                {
                    Thief *tempP = (Thief *)c;
                    tempP->execute(c);
                    board[c->getX()][c->getY()]->setType('.');
                    c->setX(c->getX() - 1);
                }
                else if (marioActive)
                    marioAbilityHelper(5);
                else
                    luigiAbilityHelper(5);

                newTurn();
            }
            else if (board[c->getX() - 1][c->getY()]->getType() == 'b')
            {
                if (!marioActive && !luigiActive)
                {
                    Bomb *tempP = (Bomb *)c;
                    tempP->execute(c);
                    board[c->getX()][c->getY()]->setType('.');
                    c->setX(c->getX() - 1);
                }
                else if (marioActive)
                    marioAbilityHelper(5);
                else
                    luigiAbilityHelper(5);

                newTurn();
            }
            else if (board[c->getX() - 1][c->getY()]->getType() == '$')
            {
                if (!marioActive && !luigiActive)
                {
                    Coin *tempP = (Coin *)c;
                    tempP->execute(c);
                    board[c->getX()][c->getY()]->setType('.');
                    c->setX(c->getX() - 1);
                }
                else if (marioActive)
                    marioAbilityHelper(5);
                else
                    luigiAbilityHelper(5);

                newTurn();
            }
            else if (board[c->getX() - 1][c->getY()]->getType() == 'p')
            {
                if (!marioActive && !luigiActive)
                {
                    Potion *tempP = (Potion *)c;
                    tempP->execute(c);
                    board[c->getX()][c->getY()]->setType('.');
                    c->setX(c->getX() - 1);
                }
                else if (marioActive)
                    marioAbilityHelper(5);
                else
                    luigiAbilityHelper(5);

                newTurn();
            }
            else if (board[c->getX() - 1][c->getY()]->getType() == '.')
            {
                if (!marioActive && !luigiActive)
                {
                    board[c->getX()][c->getY()]->setType('.');
                    c->setX(c->getX() - 1);
                }
                else if (marioActive)
                    marioAbilityHelper(5);
                else
                    luigiAbilityHelper(5);

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
            if (board[c->getX()][c->getY() - 1]->getType() == 't')
            {
                if (!marioActive && !luigiActive)
                {
                    Thief *tempP = (Thief *)c;
                    tempP->execute(c);
                    board[c->getX()][c->getY()]->setType('.');
                    c->setY(c->getY() - 1);
                }
                else if (marioActive)
                    marioAbilityHelper(4);
                else
                    luigiAbilityHelper(4);

                newTurn();
            }
            else if (board[c->getX()][c->getY() - 1]->getType() == 'b')
            {
                if (!marioActive && !luigiActive)
                {
                    Bomb *tempP = (Bomb *)c;
                    tempP->execute(c);
                    board[c->getX()][c->getY()]->setType('.');
                    c->setY(c->getY() - 1);
                }
                else if (marioActive)
                    marioAbilityHelper(4);
                else
                    luigiAbilityHelper(4);

                newTurn();
            }
            else if (board[c->getX()][c->getY() - 1]->getType() == 'p')
            {
                if (!marioActive && !luigiActive)
                {
                    Potion *tempP = (Potion *)c;
                    tempP->execute(c);
                    board[c->getX()][c->getY()]->setType('.');
                    c->setY(c->getY() - 1);
                }
                else if (marioActive)
                    marioAbilityHelper(4);
                else
                    luigiAbilityHelper(4);

                newTurn();
            }
            else if (board[c->getX()][c->getY() - 1]->getType() == '$')
            {
                if (!marioActive && !luigiActive)
                {
                    Coin *tempP = (Coin *)c;
                    tempP->execute(c);
                    board[c->getX()][c->getY()]->setType('.');
                    c->setY(c->getY() - 1);
                }
                else if (marioActive)
                    marioAbilityHelper(4);
                else
                    luigiAbilityHelper(4);

                newTurn();
            }
            else if (board[c->getX()][c->getY() - 1]->getType() == '.')
            {
                if (!marioActive && !luigiActive)
                {
                    board[c->getX()][c->getY()]->setType('.');
                    c->setY(c->getY() - 1);
                }
                else if (marioActive)
                    marioAbilityHelper(4);
                else
                    luigiAbilityHelper(4);

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
    Gem();

    Map *m = new Map();
    return 0;
}