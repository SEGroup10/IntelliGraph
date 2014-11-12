#include <string>
#include "colour.h"
using namespace std;

class Node
{
	public:
        Node(int newID,int newSpecial,string newName, int X, int Y);
        ~Node();
		int getID();
		string getName();
		void changeName(string newName);
		int getSpecial();
		position getPosition();
		void changePosition(position newPos);
		void changePositionXY(int newX,int newY);
		colour getColour();
		void changeColour(colour newCol);
		void changeColourRGB(int newR,int newG, int newB);
	private:
		int ID;
		string name;
		int special;
		position pos;
		colour col;
};


