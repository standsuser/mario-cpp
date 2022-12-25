#ifndef MAP_H
#define MAP_H

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
    Map();
    /*{
        c = new Champion();
        board = new Cell *[10];
        for (int i = 0; i < 10; i++)
        {
            board[i] = new Cell[10];
        }
    }*/

    ~Map();
    /*{
        for (int i = 0; i < 10; ++i)
        {
            delete (board[i]); // deletes an inner array of integer;
        }
        delete (board); // delete pointer holding array of pointers;
    }*/

    void newGame();
    /*{

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
            Map2 *m = new Map2();
            newGame();
        }
        else if (rButton == '2')
        {
            cout << "\033[2J\033[1;1H";
            cout << "print_map() called" << endl;
            newTurn();
        }
    }*/
    void print_map();
    /*{
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
    }*/
    void randomize_map();
    /*{
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
    }*/
};
#endif