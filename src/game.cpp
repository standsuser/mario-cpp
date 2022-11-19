#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>
using namespace std;

class Champion
{
private:
	int hp;
	int gemScore;
	int champX;
	int champY;

	
public:
	Champion()
	{
		cout << "Constructor champion() is called" << endl;
		champY = 0; //Row
		champX = 0; //Column
		hp = 100;
		gemScore = 0;
	}
	void print_champ_info()
	{
		cout << "Current hp: " << hp << "  , Score: " << gemScore << " Location: " << endl;
	}
	int getX(){
		return this->champX;
	}
	int getY(){
		return this->champY;
	}
	void setX(int x){
		this->champX = x;
	}
	void setY(int y){
		this->champY = y;
	}
	int getHp(){
		return this->hp;
	}
	void decHp(){
		this->hp-=40; 
	}
	
	
};

class Map
{
private:
	string board[10][10];
	Champion mario;
	int gemX[50];
	int gemY[50];
	int obstX[25];
	int obstY[25];
	int gemCount;
	int obstCount;
public:

	Map()
	{
		cout << "Constructor Map() is called" << endl;
		randomize_map();
		print_map();
		cout<<"Gem count: "<<gemCount<<"\nObst count: "<<obstCount<<endl;
		int* p = (int*) (mario.getX());
		mario.setX(*p++);
		cout<<mario.getX();
	}

	void move(int k){
		switch (k)
		{
		// case 8:{
		// 	if(board[mario.getX()][mario.getY()] == "☁︎ "){
		// 		mario.decHp();
		// 	}
		// 	int* p = (int*) (mario.getX());
		// 	mario.setX(*p++);
		// }break;
		// default:
		// cout<<endl;
		}
	}
	
	void print_map()
	{	
		int count = 0;
		cout << "print_map() called" << endl;
		for (int i = 9; i >= 0; i--)
		{
			for (int j = 0; j < 10; j++){
				if(i == mario.getX() && j == mario.getY())
			  		board[i][j] = "∺ ";
				
				cout<<board[i][j];
			}
			cout << endl;
		}
	}

	// randomly waza3 gems and obstacles on the map
	void randomize_map()
	{
		//⚇ mario, ⦿ gem, ☁︎ obstacle
		cout << "randomize_map() called" << endl;
			

		for (int i = 9; i >= 0; i--)
		{
			for (int j = 0; j < 10; j++){
				board[i][j] = ". ";
			}
		}	

		srand(time(0));
		for(int i = 0; i < 50; i++){
			do{
				gemX[i] = (rand() % 10);
				gemY[i] = (rand() % 10);
				if(gemX[i] == 0 && gemY[i] == 0){
					gemX[i] = (rand() % 9) + 1;
					gemY[i] = (rand() % 9) + 1;
				}
			}while(board[gemX[i]][gemY[i]] != ". ");
			
			board[gemX[i]][gemY[i]] = "⦿ "; 
				gemCount++;
		}
		
		
		for(int i = 0; i < 25; i++){
			do
			{
				obstX[i] = (rand() % 10);
				obstY[i] = (rand() % 10);
			
				if((obstX[i] == 0 && obstY[i] == 0)){
					obstX[i] = (rand() % 9) + 1;
					obstY[i] = (rand() % 9) + 1;
				}
				
			} while (board[obstX[i]][obstY[i]] != ". ");
			
			board[obstX[i]][obstY[i]] = "☁︎ ";
				obstCount++;
		}
		
		
		//if there are duplicate points betweeen gems and obstacles
		for(int i = 0; i < 50; i++){
			for(int j = 0; j < 25; j++){
				
				while((obstX[j] == gemX[i]) && (obstY[j] == gemY[i])){
					obstX[j] = (rand() % 9) + 1;
					obstY[j] = (rand() % 9) + 1;
				}
			}
		}
	}
};

// GRABY TEST LEARNER PERMITS HAHA GAY WAMEN grayb
int main()
{
	Map();
	
	return 0;
}
