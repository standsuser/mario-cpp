#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <string.h>
#include "Obstacle.h"
#include "Bomb.h"
#include "Cell.h"
#include "Coin.h"
#include "Champion.h"
#include "Gem.h"
#include "Luigi.h"
#include "Mario.h"
#include "Map.h"
#include "Potion.h"
#include "Thief.h"
using namespace std;

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
			Map2 *m = new Map2();
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

	Map *m = new Map();
	m->randomize_map();
	m->print_map();
	return 0;
}
