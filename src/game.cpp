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
			cout<<"Constructor champion() is called"<<endl;
			loc = Point(); // will we alloc since Point is an object or ?
			loc.setPoint(0,0); // i initialized the origin here tho m not sure if this the right place
			hp = 100;
			gemScore = 0;
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
			randomize_map();
			print_map();
		}
		void print_map(){
			cout<<"print_map() called"<<endl;
			for(int i=0; i<10; i++){
				for(int j=0; j<10; j++){

					// if(loc.getY==j && loc.getX()==i) // how can i reference the champ's point location hena i googled it it went on abt dynamic mem alloc w keda or maybe theres a diff way google the sentence i sent on discord
					// cout<<"O"<<" ";
					// else
					cout<<"E"<< " ";

				


				}
				cout<<endl;
			}
		}
		void randomize_map(){
			cout<<"randomize_map() called"<<endl;
			//randomly waza3 gems and obstacles on the map
		}

};




int main()
{	
	Map();
	return 0;
}
