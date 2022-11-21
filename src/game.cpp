#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

class Champion
{
private:
	int hp;
	int gemScore;
	int champX;
	int champY;

public:
	//Champion() = default;
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
		if(this->hp <= 0){
			this->hp = 0;
		}
	}
	int getScore()
	{
		return this->gemScore;
	}
	void setGemScore(int x)
	{
		this->gemScore = x;
	}
	void setHp(int x){
		this->hp = x;
	}
};

class Map
{
private:
	string** board;
	Champion* mario = new Champion();
	int gemX[50];
	int gemY[50];
	int obstX[25];
	int obstY[25];
	int gemCount;
	int obstCount;
	int flag = 0;

public:
	Map()
	{	
		 board = new string*[10];
		 for(int i = 0; i < 10;i++){
			board[i] = new string[10];
		}
		randomize_map();
		if(flag == 0){
			cout << "Constructor Map() is called" << endl;
			cout << "randomize_map() called" << endl;
		}
		flag++;
	}
	void end(){
		if(mario->getScore() == gemCount){
			cout<<"Congrats you won!!"<<endl;
			for(int i = 0; i < 5; ++i){
    			delete[] board[i];//deletes an inner array of integer;
			}
			delete[] board;//delete pointer holding array of pointers;
		exit(0);
		}

		else if(mario->getHp() <= 0){
			cout<<"You lost :( but you can go again :D"<<endl;
			for(int i = 0; i < 5; ++i){
    			delete[] board[i];//deletes an inner array of integer;
			}
			delete[] board;//delete pointer holding array of pointers;
			
		exit(0);
		}else{
			return;
		}
	}


	void newTurn()
	{
		// clear terminal
		
		cout << "\033[2J\033[1;1H";
		print_map();
		cout<<" 8 -> up, 4 -> Left, 2 -> Down, 6 -> Right"<<endl;
		cout << "Total Gem count: " << gemCount << "\nObst count: " << obstCount << "\nScore: " << mario->getScore() << "\nHealth: " << mario->getHp() << "\nx: " << mario->getX() << "\ny: " << mario->getY() << endl;
		char input;
		end();
		cout<< "Enter direction: ";
		input = getch();
		move(input);
		
	}

	void move(char k)
	{
		
		switch (k)
		{
		case '8':
		{	if (mario->getX() == 9){
				newTurn();
		}
			if (board[mario->getX() + 1][mario->getY()] == "☁︎ ")
			{
				mario->decHp();
				board[mario->getX()][mario->getY()]= ". ";
				mario->setX(mario->getX() + 1);
				
				newTurn();
			}
			else if (board[mario->getX() + 1][mario->getY()] == "⦿ ")
			{
				mario->setGemScore(mario->getScore() + 1);
				board[mario->getX()][mario->getY()]= ". ";
				mario->setX(mario->getX() + 1);
				
				newTurn();
			}else if (board[mario->getX() + 1][mario->getY()] == ". ")
			{
				board[mario->getX()][mario->getY()]= ". ";
				mario->setX(mario->getX() + 1);
				
				newTurn();
			}
			
			else{
				newTurn();
			}
			
			
		}
		break;
		case '6': //board[mario.getX()][mario.getY() + 1]
		{	if (mario->getY() == 9){
				newTurn();
		}
			if (board[mario->getX() ][mario->getY() + 1] == "☁︎ ")
			{
				mario->decHp();
				board[mario->getX()][mario->getY()]= ". ";
				mario->setY(mario->getY() + 1);
				
				newTurn();
			}
			else if (board[mario->getX()][mario->getY() + 1] == "⦿ ")
			{
				mario->setGemScore(mario->getScore() + 1);
				board[mario->getX()][mario->getY()]= ". ";
				mario->setY(mario->getY() + 1);
				
				newTurn();
			}else if (board[mario->getX()][mario->getY() + 1] == ". ")
			{
				board[mario->getX()][mario->getY()]= ". ";
				mario->setY(mario->getY() + 1);
				
				newTurn();
			}
			
			else{
				newTurn();
			}
			
			
		}
		break;
		case '2': //board[mario.getX() - 1][mario.getY()]
		{	if (mario->getX() == 0){
				newTurn();
		}
			if (board[mario->getX() - 1][mario->getY()] == "☁︎ ")
			{
				mario->decHp();
				board[mario->getX()][mario->getY()]= ". ";
				mario->setX(mario->getX() - 1);
				
				newTurn();
			}
			else if (board[mario->getX() - 1][mario->getY()] == "⦿ ")
			{
				mario->setGemScore(mario->getScore() + 1);
				board[mario->getX()][mario->getY()]= ". ";
				mario->setX(mario->getX() - 1);
				
				newTurn();
			}else if (board[mario->getX() - 1][mario->getY()] == ". ")
			{
				board[mario->getX()][mario->getY()]= ". ";
				mario->setX(mario->getX() - 1);
				
				newTurn();
			}
			
			else{
				newTurn();
			}
			
			
		}
		break;
		case '4': //board[mario.getX()][mario.getY() - 1]
		{	if (mario->getY() == 0){
				newTurn();
		}
			if (board[mario->getX() ][mario->getY() - 1] == "☁︎ ")
			{
				mario->decHp();
				board[mario->getX()][mario->getY()]= ". ";
				mario->setY(mario->getY() - 1);
				
				newTurn();
			}
			else if (board[mario->getX()][mario->getY() - 1] == "⦿ ")
			{
				mario->setGemScore(mario->getScore() + 1);
				board[mario->getX()][mario->getY()]= ". ";
				mario->setY(mario->getY() - 1);
				
				newTurn();
			}else if (board[mario->getX()][mario->getY() - 1] == ". ")
			{
				board[mario->getX()][mario->getY()]= ". ";
				mario->setY(mario->getY() - 1);
				
				newTurn();
			}
			
			else{
				newTurn();
			}
			
			
		}break;
		default:
			newTurn();
		}	
	}

	void newGame(){
		
		print_map();
		char rButton = 0;
	
		while (rButton != '1' && rButton != '2'){
			cout<<"Choose 1 to Randomize again, Choose 2 to start the game"<<endl;
			rButton=getch();
		}
		
		if(rButton == '1'){
			//cout << "\033[2J\033[1;1H";
			randomize_map();
			cout << "\033[2J\033[1;1H";
			newGame();
			
		}else if(rButton == '2') {
			cout << "\033[2J\033[1;1H";
			cout << "print_map() called" << endl;
			newTurn();
		}
	}

	void print_map()
	{
		int count = 0;	
		cout<<"print_map() called"<<endl;
		
		for (int i = 9; i >= 0; i--)
		{
			for (int j = 0; j < 10; j++)
			{
				if (i == mario->getX() && j == mario->getY())
					board[i][j] = "∺ ";

				cout << board[i][j];
			}
			cout << endl;
		}
	}

	// randomly distribute gems and obstacles on the map
	void randomize_map()
	{	gemCount = 0;
		obstCount = 0;
		
		//⚇ mario, ⦿ gem, ☁︎ obstacle
		

		for (int i = 9; i >= 0; i--)
		{
			for (int j = 0; j < 10; j++)
			{
				board[i][j] = ". ";
			}
		}

		srand(time(0));
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
			} while (board[gemX[i]][gemY[i]] != ". ");

			board[gemX[i]][gemY[i]] = "⦿ ";
			gemCount++;
		}

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

			} while (board[obstX[i]][obstY[i]] != ". ");

			board[obstX[i]][obstY[i]] = "☁︎ ";
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
	Map* m = new Map();
	m->newGame();
// cout<<"WAAAAAA";
// 	int x;
// 	cin>>x;
	
// 	if(x==1)
// 		cout << "\033[2J\033[1;1H";

// 	cout << "The screen has been cleared!";
//  std::string word;
//     char c = getch();
//     //while (mario->hp !=0 || mario->getScore() == Map->gemCount) //  game not ended
// 	int x=0;
// 	while(x=0)
//     {
//         word.push_back(c);
//         std::cout << c;
//         c = getch();
//     }
//     std::cout << c;

	return 0;
}



