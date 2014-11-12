#include <string>
#include "node.h"

using namespace std;

Node::Node(int newID,int newSpecial,string newName, int X, int Y)
{
	ID = newID;
	special = newSpecial;
	name = newName;
	pos.X = X;
	pos.Y = Y;
}

Node::~Node()
{

};

int Node::getID()
{
	return ID;
}

string Node::getName()
{
	return name;
}

void Node::changeName(string newName)
{
	name = newName;
	return;
}

int Node::getSpecial()
{
	return special;
}

position Node::getPosition()
{
	return pos;
}

void Node::changePosition(position newPos)
{
	pos = newPos;
	return;
}

void Node::changePositionXY(int newX, int newY)
{
	pos.X = newX;
	pos.Y = newY;
	return;
}

colour Node::getColour()
{
	return col;
}

void Node::changeColour(colour newCol)
{
	col = newCol;
	return;
}

void Node::changeColourRGB(int newR, int newG, int newB)
{
	col.changeColourRGB(newR,newG,newB);
	return;
}





