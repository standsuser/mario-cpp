#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <string.h>
using namespace std;
srand(time(0));

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
		champY = 0; // Row
		champX = 0; // Column
		hp = 100;
		gemScore = 0;
	}
	void print_champ_info()
	{
		cout << "Current hp: " << hp << "  , Score: " << gemScore << " Location: " << endl;
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

class Map2
{
private:
	char **board;
	Champion *mario = new Champion();
	int gemX[50];
	int gemY[50];
	int obstX[25];
	int obstY[25];
	int gemCount;
	int obstCount;

public:
	Map2()
	{
		board = new char *[10];
		for (int i = 0; i < 10; i++)
		{
			board[i] = new char[10];
		}
		randomize_map();
		cout << "Constructor Map() is called" << endl;
		cout << "randomize_map() is called" << endl;
	}
	void end()
	{
		if (mario->getScore() == gemCount)
		{
			cout << "Congrats you won!!" << endl;

			exit(0);
		}

		else if (mario->getHp() <= 0)
		{
			cout << "You lost :( but you can go again :D" << endl;

			exit(0);
		}
		else
		{
			return;
		}
	}

	~Map2()
	{
		for (int i = 0; i < 10; ++i)
		{
			delete (board[i]); // deletes an inner array of integer;
		}
		delete (board); // delete pointer holding array of pointers;
		delete (mario);
	}

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
			if (board[mario->getX() + 1][mario->getY()] == 'O ')
			{
				mario->decHp();
				board[mario->getX()][mario->getY()] = '. ';
				mario->setX(mario->getX() + 1);

				newTurn();
			}
			else if (board[mario->getX() + 1][mario->getY()] == 'G ')
			{
				mario->setGemScore(mario->getScore() + 1);
				board[mario->getX()][mario->getY()] = '. ';
				mario->setX(mario->getX() + 1);

				newTurn();
			}
			else if (board[mario->getX() + 1][mario->getY()] == '. ')
			{
				board[mario->getX()][mario->getY()] = '. ';
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
			if (board[mario->getX()][mario->getY() + 1] == 'O ')
			{
				mario->decHp();
				board[mario->getX()][mario->getY()] = '. ';
				mario->setY(mario->getY() + 1);

				newTurn();
			}
			else if (board[mario->getX()][mario->getY() + 1] == 'G ')
			{
				mario->setGemScore(mario->getScore() + 1);
				board[mario->getX()][mario->getY()] = '. ';
				mario->setY(mario->getY() + 1);

				newTurn();
			}
			else if (board[mario->getX()][mario->getY() + 1] == '. ')
			{
				board[mario->getX()][mario->getY()] = '. ';
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
			if (board[mario->getX() - 1][mario->getY()] == 'O ')
			{
				mario->decHp();
				board[mario->getX()][mario->getY()] = '. ';
				mario->setX(mario->getX() - 1);

				newTurn();
			}
			else if (board[mario->getX() - 1][mario->getY()] == 'G ')
			{
				mario->setGemScore(mario->getScore() + 1);
				board[mario->getX()][mario->getY()] = '. ';
				mario->setX(mario->getX() - 1);

				newTurn();
			}
			else if (board[mario->getX() - 1][mario->getY()] == '. ')
			{
				board[mario->getX()][mario->getY()] = '. ';
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
			if (board[mario->getX()][mario->getY() - 1] == 'O ')
			{
				mario->decHp();
				board[mario->getX()][mario->getY()] = '. ';
				mario->setY(mario->getY() - 1);

				newTurn();
			}
			else if (board[mario->getX()][mario->getY() - 1] == 'G ')
			{
				mario->setGemScore(mario->getScore() + 1);
				board[mario->getX()][mario->getY()] = '. ';
				mario->setY(mario->getY() - 1);

				newTurn();
			}
			else if (board[mario->getX()][mario->getY() - 1] == '. ')
			{
				board[mario->getX()][mario->getY()] = '. ';
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
					board[i][j] = 'c ';

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
				board[i][j] = '. ';
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
			} while (board[gemX[i]][gemY[i]] != '. ');

			board[gemX[i]][gemY[i]] = 'G ';
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

			} while (board[obstX[i]][obstY[i]] != '. ');

			board[obstX[i]][obstY[i]] = 'O ';
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

class Map
{
private:
	int rows[10];
	int col[10];
	Cell **board;
	int gemCount, obstCount;
	// The declaration down there is for when the gem class and the obstacle class is created;
	//  Gem gems[40];
	//  Obstacle obst[20];

public:
	Map()
	{
		board = new Cell *[10];
		for (int i = 0; i < 10; i++)
		{
			board[i] = new Cell[10];
		}
	}

	void randomize_map()
	{
		gemCount = 0;
		obstCount = 0;

		// ∺ mario, ⦿ gem, ☁︎ obstacle

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
	}
};
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
};

class Map
{
private:
	int rows[10];
	int col[10];
	Cell **board;
	int gemCount, obstCount;
	// The declaration down there is for when the gem class and the obstacle class is created;
	//  Gem gems[40];
	//  Obstacle obst[20];

public:
	Map()
	{
		board = new Cell *[10];
		for (int i = 0; i < 10; i++)
		{
			board[i] = new Cell[10];
		}
	}

	void randomize_map()
	{
		gemCount = 0;
		obstCount = 0;

		// ∺ mario, ⦿ gem, ☁︎ obstacle

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
	}
};
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
};

class Obstacle
{
private:
	int takedmg;

public:
	Obstacle()
	{
		takedmg = rand() % 5 + 1
	}

	virtual void execute(Champion c){};
};

class Bomb : public Obstacle
{
public:
	void execute(Champion c)
	{

		int x = c.getHp() - takedmg;

		if (x < 0)
			x = 0;
		c.setHp(x);

		cout << "bomb excuted with dmg = " << takedmg << endl;
	}
};

class Thief() : public Obstacle{
					public :
						execute(Champion c){

							int x = c.getScore - takedmg;

if (x < 0)
	x = 0;
c.setScore(x);

cout << "thief executed with dmg = " << takedmg << endl;
}
}
;

int main()
{
	Map2 *m = new Map2();
	m->newGame();
	return 0;
}
