#include <iostream>
using namespace std;

class Point{
	private:
		int X, Y;
	public:
		void setPoint(int a, int b){
			X = a;
			Y = b;
		}
		int getX(){
			return X;
		}
		int getY(){
			return Y;
		}
		string toString(){
			string s;
			s = getX() + ", " + getY();
			return s;
		}
};

class Champion{
	private:
		int hp;
		int gemScore;
		Point loc;
		
	
	public:
		Champion(){
			loc = Point();
			cout<<"Constructor champion() is called"<<endl;
		}
		void print_champ_info(){
			cout<<"Current hp: "<<hp<<"  , Score: "<<gemScore << " Location: " <<loc.toString()<<endl;
		}


};

class Map{
	private:
		int board[10][10];


	public:
		Map(){
			cout<<"Constructor Map() is called"<<endl;
		}
		void print_map(){
			cout<<"print_map() called"<<endl;
		}
		void randomize_map(){
			cout<<"randomize_map() called"<<endl;
		}

};




int main()
{	char c = (char) 196;
	cout<<c<<endl;
	return 0;
}
