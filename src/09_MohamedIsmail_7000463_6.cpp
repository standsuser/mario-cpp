#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <string.h>
//-------------------------------//

using namespace std;

//------------------------------champion---------------------------------

class Champion 
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

class Luigi : public Champion
{

    // idea :  in whatever direction luigi moves we clean
    //  the hypothetical place he was gonna move into ,that way we preserve the obstacles that are before him
    //  if the ability was called, by cleaning I mean we just replace everything by dots or whatever the symbol of tile is
    // defensive programming for luigi not to "clean himself" off the "lain" or not to clean mario as well so no cleaning
    //  champions , also cleaning will save the point object thingies but remove obstacles
    //  and we need to define what is front , I am guessing whateever last move he makes is the front so if he moved right
    //  then the whole right direction will be clean
    // IF luigi is somewhere and he moved in the another somewhere direction
    //  useABility()
    //  and we can use ability while in spawn as well and probably he will spawn somewhere else
    //  and mario will be the original champion
public:
    void useAbility()
    {
        cout << "Luigi Ability is called" << endl;

        for (int i = 0; i < 10; i++)
        {
            if (board[luigi->getX()][i].getType() == 'O ')
            {
                board[luigi->getX()][i] = '. ';
            }
        }
        for (int j = 0; j < 10; j++)
        {
            if (board[j][luigi->getX()].getType() == 'O ')
            {
                board[j][luigi->getY()] = '. ';
            }
        }
    }
};

class Mario : public Champion
{
public:
    //  idea is putting all the move method here seems stupid , cos why the move function then to kill redundancy ?
    // so somehow we put the move function correctly and just +2 in every single direction but only one time
    // and we remove the getting damage line or something and  we make him not see obstacles aslan fa msh far2a m3ah
    // haye3mel eih

    void useAbility(char c)
    {
        cout << "Mario Ability is called" << endl;
    }
};

//dont forget REMAINING ABILITY COUNTER//







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
        this->type = '. ';
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
        return "" + this->type;
    }
};

//-----------------old map---------------

// class Map2
// {
// private:
// 	char **board;
// 	Champion *mario = new Champion();
// 	int gemX[50];
// 	int gemY[50];
// 	int obstX[25];
// 	int obstY[25];
// 	int gemCount;
// 	int obstCount;

// public:
// 	Map2()
// 	{
// 		board = new char *[10];
// 		for (int i = 0; i < 10; i++)
// 		{
// 			board[i] = new char[10];
// 		}
// 		randomize_map();
// 		cout << "Constructor Map() is called" << endl;
// 		cout << "randomize_map() is called" << endl;
// 	}
// 	void end()
// 	{
// 		if (mario->getScore() == gemCount)
// 		{
// 			cout << "Congrats you won!!" << endl;

// 			exit(0);
// 		}

// 		else if (mario->getHp() <= 0)
// 		{
// 			cout << "You lost :( but you can go again :D" << endl;

// 			exit(0);
// 		}
// 		else
// 		{
// 			return;
// 		}
// 	}

// 	~Map2()
// 	{
// 		for (int i = 0; i < 10; ++i)
// 		{
// 			delete (board[i]); // deletes an inner array of integer;
// 		}
// 		delete (board); // delete pointer holding array of pointers;
// 		delete (mario);
// 	}


//--------------------------NEW MAP-----------------------------

class Map
{
private:
    int rows[10];
    int col[10];
    Cell **board;
    int gemCount, obstCount;
    int thievesX[10], thievesY[10], bombsX[10], bombsY[10], potionsX[20], potionsY[20], coinsX[20], coinsY[20];
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

        cout << "print_map() called" << endl;
        print_map();
        char rButton = 0;
        if (rButton == 'M')
            c = new Mario();
        else if (rButton == 'L')
            c = new Luigi();

        while ((rButton != '1' && rButton != '2') || (rButton != 'M' && rButton != 'L'))
        {
            cout << "Choose 1 to Randomize again, Choose 2 to start the game" << endl;
            rButton = getch();
        }

        if (rButton == '1')
        {
            randomize_map();
            cout << "\033[2J\033[1;1H";
            Map *m = new Map();
            newGame();
        }
        else if (rButton == '2')
        {
            cout << "\033[2J\033[1;1H";
            cout << "print_map() called" << endl;
            newTurn();
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

                cout << board[i][j].toString() << " ";
            }
            cout << endl;
        }
    }
    void randomize_map()
    {
        gemCount = 0;
        obstCount = 0;

        for (int i = 9; i >= 0; i--)
        {
            for (int j = 0; j < 10; j++)
            {
                board[i][j] = Cell();
                board[i][j].setX(i);
                board[i][j].setY(j);
            }
        }

        srand(time(0));

        // Thieves & Bombs locations set
        for (int i = 0; i < 10; i++)
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
            } while (board[thievesX[i]][thievesY[i]].getType() != '. ');

            board[thievesX[i]][thievesY[i]].setType('O ');
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
            } while (board[bombsX[i]][bombsY[i]].getType() != '. ');

            board[bombsX[i]][bombsY[i]].setType('O ');
            board[bombsX[i]][bombsY[i]].setX(bombsX[i]);
            board[bombsX[i]][bombsY[i]].setY(bombsY[i]);
            obstCount++;
        }

        // Coins & potions locations set
        for (int i = 0; i < 40; i++)
        {
            do
            {
                coinsX[i] = (rand() % 20);
                coinsY[i] = (rand() % 20);
                if (coinsX[i] == 0 && coinsY[i] == 0)
                {
                    coinsX[i] = (rand() % 19) + 1;
                    coinsY[i] = (rand() % 19) + 1;
                }
            } while (board[coinsX[i]][coinsY[i]].getType() != '. ');

            board[coinsX[i]][coinsY[i]].setType('G ');
            board[coinsX[i]][coinsY[i]].setX(coinsX[i]);
            board[coinsX[i]][coinsY[i]].setY(coinsY[i]);
            gemCount++;

            do
            {
                potionsX[i] = (rand() % 20);
                potionsY[i] = (rand() % 20);
                if (potionsX[i] == 0 && potionsY[i] == 0)
                {
                    potionsX[i] = (rand() % 19) + 1;
                    potionsY[i] = (rand() % 19) + 1;
                }
            } while (board[potionsX[i]][potionsY[i]].getType() != '. ');

            board[potionsX[i]][potionsY[i]].setType('G ');
            board[potionsX[i]][potionsY[i]].setX(potionsX[i]);
            board[potionsX[i]][potionsY[i]].setY(potionsY[i]);
            gemCount++;
        }

        // Creating those Gems
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (board[i][j].getType() == 'O ')
                {
                    if (thievesX[i] == i && thievesY[j] == j)
                        Obstacle *o = new Thief();

                    if (bombsX[i] == i && bombsY[j] == j)
                        Obstacle *o = new Bomb();
                }

                if (board[i][j].getType() == 'C ')
                {
                    Champion *c = new Champion();
                }

                if (board[i][j].getType() == 'G ')
                {
                    if (potionsX[i] == i && potionsY[j] == j)
                        Gem *g = new Potion();

                    if (coinsX[i] == i && coinsY[j] == j)
                        Gem *g = new Coin();
                }
            }
        }

        // In case there are duplicates
        for (int i = 0; i < 10; i++)
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
};





	//----------------------------new turn and move ---------------------------

	void newTurn()
	{
		// clear terminal

		cout << "\033[2J\033[1;1H";
		print_map();
		cout << " 8 -> Up, 5 -> Down, 4 -> Left, 6 -> Right" << endl;
		cout << "Total Gem count (G): " << gemCount << "\nObst count (O): " << obstCount << "\nScore: " << mario->getScore() << "\nHealth: " << mario->getHp() << "\nx: " << mario->getX() << "\ny: " << mario->getY() << endl;
		char input;
		end();
		cout << "Enter direction: ";
		input = getch();
		move(input);
	}

	void move(char k)
	{

		switch (k)
		{
		case '8':
		{
			if (mario->getX() == 9)
			{
				newTurn();
			}
			if (board[mario->getX() + 1][mario->getY()] == 'O')
			{
				mario->decHp();
				board[mario->getX()][mario->getY()] = '.';
				mario->setX(mario->getX() + 1);

				newTurn();
			}
			else if (board[mario->getX() + 1][mario->getY()] == 'G')
			{
				mario->setScore(mario->getScore() + 1);
				board[mario->getX()][mario->getY()] = '.';
				mario->setX(mario->getX() + 1);

				newTurn();
			}
			else if (board[mario->getX() + 1][mario->getY()] == '.')
			{
				board[mario->getX()][mario->getY()] = '.';
				mario->setX(mario->getX() + 1);

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
			if (mario->getY() == 9)
			{
				newTurn();
			}
			if (board[mario->getX()][mario->getY() + 1] == 'O')
			{
				mario->decHp();
				board[mario->getX()][mario->getY()] = '.';
				mario->setY(mario->getY() + 1);

				newTurn();
			}
			else if (board[mario->getX()][mario->getY() + 1] == 'G')
			{
				mario->setScore(mario->getScore() + 1);
				board[mario->getX()][mario->getY()] = '.';
				mario->setY(mario->getY() + 1);

				newTurn();
			}
			else if (board[mario->getX()][mario->getY() + 1] == '.')
			{
				board[mario->getX()][mario->getY()] = '.';
				mario->setY(mario->getY() + 1);

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
			if (mario->getX() == 0)
			{
				newTurn();
			}
			if (board[mario->getX() - 1][mario->getY()] == 'O')
			{
				mario->decHp();
				board[mario->getX()][mario->getY()] = '.';
				mario->setX(mario->getX() - 1);

				newTurn();
			}
			else if (board[mario->getX() - 1][mario->getY()] == 'G')
			{
				mario->setScore(mario->getScore() + 1);
				board[mario->getX()][mario->getY()] = '.';
				mario->setX(mario->getX() - 1);

				newTurn();
			}
			else if (board[mario->getX() - 1][mario->getY()] == '.')
			{
				board[mario->getX()][mario->getY()] = '.';
				mario->setX(mario->getX() - 1);

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
			if (mario->getY() == 0)
			{
				newTurn();
			}
			if (board[mario->getX()][mario->getY() - 1] == 'O')
			{
				mario->decHp();
				board[mario->getX()][mario->getY()] = '.';
				mario->setY(mario->getY() - 1);

				newTurn();
			}
			else if (board[mario->getX()][mario->getY() - 1] == 'G')
			{
				mario->setScore(mario->getScore() + 1);
				board[mario->getX()][mario->getY()] = '.';
				mario->setY(mario->getY() - 1);

				newTurn();
			}
			else if (board[mario->getX()][mario->getY() - 1] == '.')
			{
				board[mario->getX()][mario->getY()] = '.';
				mario->setY(mario->getY() - 1);

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
//----------------------------------new game---------------------
	void newGame()
	{

		cout << "print_map() called" << endl;
		print_map();
		char rButton = 0;

		while (rButton != '1' && rButton != '2')
		{
			cout << "Choose 1 to Randomize again, Choose 2 to start the game" << endl;
			rButton = getch();
		}

		if (rButton == '1')
		{
			randomize_map();
			cout << "\033[2J\033[1;1H";
			Map *m = new Map();
			newGame();
		}
		else if (rButton == '2')
		{
			cout << "\033[2J\033[1;1H";
			cout << "print_map() called" << endl;
			newTurn();
		}
	}

	void print_map()
	{
		for (int i = 9; i >= 0; i--)
		{
			for (int j = 0; j < 10; j++)
			{
				if (i == mario->getX() && j == mario->getY())
					board[i][j] = 'c';

				cout << board[i][j];
			}
			cout << endl;
		}
	}

	// randomly distribute gems and obstacles on the map
	void randomize_map()
	{
		gemCount = 0;
		obstCount = 0;

		// ∺ mario, ⦿ gem, ☁︎ obstacle

		for (int i = 9; i >= 0; i--)
		{
			for (int j = 0; j < 10; j++)
			{
				board[i][j] = '.';
			}
		}

		// Generate Gems
		for (int i = 0; i < 50; i++)
		{
			do
			{
				gemX[i] = (rand() % 10);
				gemY[i] = (rand() % 10);
				if (gemX[i] == 0 && gemY[i] == 0)
				{
					gemX[i] = (rand() % 9) + 1;
					gemY[i] = (rand() % 9) + 1;
				}
			} while (board[gemX[i]][gemY[i]] != '.');

			board[gemX[i]][gemY[i]] = 'G';
			gemCount++;
		}

		// Generate Obstacles
		for (int i = 0; i < 25; i++)
		{
			do
			{
				obstX[i] = (rand() % 10);
				obstY[i] = (rand() % 10);

				if ((obstX[i] == 0 && obstY[i] == 0))
				{
					obstX[i] = (rand() % 9) + 1;
					obstY[i] = (rand() % 9) + 1;
				}

			} while (board[obstX[i]][obstY[i]] != '.');

			board[obstX[i]][obstY[i]] = 'O';
			obstCount++;
		}

		// if there are duplicate points betweeen gems and obstacles
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 25; j++)
			{

				while ((obstX[j] == gemX[i]) && (obstY[j] == gemY[i]))
				{
					obstX[j] = (rand() % 9) + 1;
					obstY[j] = (rand() % 9) + 1;
				}
			}
		}
	}
};

int main()
{

	// Potion x = Potion();
	// Champion a = Champion();
	// x.execute(a);




	Map();
//	Map *m = new Map();
//	m->randomize_map();
//	m->print_map();
	return 0;
}
