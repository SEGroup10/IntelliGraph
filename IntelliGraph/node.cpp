#include <string>
#include "node.h"
//#include "position.h"
//#include "colour.h"
using namespace std;

node::node(int newID,int newSpecial,string newName, int X, int Y)
{
	ID = newID;
	special = newSpecial;
	name = newName;
	pos.X = X;
	pos.Y = Y;
}

node::~node()
{

};

int node::getID()
{
	return ID;
}

string node::getName()
{
	return name;
}

void node::changeName(string newName)
{
	name = newName;
	return;
}

int node::getSpecial()
{
	return special;
}

position node::getPosition()
{
	return pos;
}

void node::changePosition(position newPos)
{
	pos = newPos;
	return;
}

void node::changePositionXY(int newX, int newY)
{
	pos.X = newX;
	pos.Y = newY;
	return;
}

colour node::getColour()
{
	return col;
}

void node::changeColour(colour newCol)
{
	col = newCol;
	return;
}

void node::changeColourRGB(int newR, int newG, int newB)
{
	col.changeColourRGB(newR,newG,newB);
	return;
}





