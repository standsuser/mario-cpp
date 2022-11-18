#include <iostream>
#include <random>
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
	int gemDoneCount;
	int obstCountDone;
public:

	Map()
	{
		cout << "Constructor Map() is called" << endl;
		randomize_map();
		printshit();
	}
	
	void print_map()
	{	
		int count = 0;
		cout << "print_map() called" << endl;
		for (int i = 9; i >= 0; i--)
		{
			for (int j = 0; j < 10; j++){
				if(i == mario.getX() && j == mario.getY())
				 	board[i][j] = "⚇ ";
				else if(i == gemX[i] && j == gemY[j]){
					board[i][j] = "⦿ ";
				}else if(i == obstX[i] && j == obstY[j]){
					board[i][j] = "☁︎ ";
				}else board[i][j] = ". ";
			}
			cout << endl;
		}

		
		
	}

	// pointer that points to 7eta men el board

	void printshit(int x, int y){
		print_map();
		for(int i = 0; i < 50; i++){
			for(int j = 0; j < 50; j++){
				if(){

				}
			}
		}
		for(int i = 9; i >= 0; i--){
			for(int j = 0; j < 10; j++){
				cout<<board[i][j];
			}
			cout<<endl;
		}


	}

	

	// randomly waza3 gems and obstacles on the map
	void randomize_map()
	{
		//⚇ mario, ⦿ gem, ☁︎ obstacle
		cout << "randomize_map() called" << endl;
		int gemCount;
		int obstCount;		

		for(int i = 0; i < 50; i++){
			srand(time(0));
			gemX[i] = (rand() % 10);
			gemY[i] = (rand() % 10);
			if(gemX[i] == 0 && gemY[i] == 0){
				gemX[i] = (rand() % 9) + 1;
				gemY[i] = (rand() % 9) + 1;
			}
			gemCount++; 
		}

		for(int i = 0; i < 25; i++){
			srand(time(0));
			obstX[i] = (rand() % 10);
			obstY[i] = (rand() % 10);
			
			if((obstX[i] == 0 && obstY[i] == 0)){
				obstX[i] = (rand() % 9) + 1;
				obstY[i] = (rand() % 9) + 1;
			}
			obstCount++;
		}

		//if there are duplicate points betweeen gems and obstacles
		for(int i = 0; i < 50; i++){
			for(int j = 0; j < 25; j++){
				if((obstX[j] == gemX[i]) && (obstY[j] == gemY[i])){
					obstX[j] = (rand() % 9) + 1;
					obstY[j] = (rand() % 9) + 1;
				}
			}
		}

		// for(int i = 0; i < 50;i++){
		// 	for(int j = 0; j<50; j++){
		// 		if(i == j)
		// 			cout<<"⦿ ";
		// 	}
		// }


	}


};

// GRABY TEST LEARNER PERMITS HAHA GAY WAMEN grayb
int main()
{
	Map();
	
	return 0;
}
