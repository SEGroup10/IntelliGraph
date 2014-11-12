#include "edge.h"

using namespace std;

Edge::Edge(int newID, Node * newBegin, Node * newEnd): QGraphicsLineItem(newBegin->pos().x()+NODESIZE/2, newBegin->pos().y()+NODESIZE/2,
                                                                         newEnd->pos().x()+NODESIZE/2, newEnd->pos().y()+NODESIZE/2, 0)
{
    ID = newID;
    begin = newBegin;
    end = newEnd;
}

Edge::~Edge()
{

};

int Edge::getID()
{
    return ID;
}

string Edge::getName()
{
    return name;
}

void Edge::changeName(string newName)
{
    name = newName;
    return;
}

void Edge::paint(QPainter *painter)
{
    QPen pen(Qt::black);
    pen.setWidth(2);

    painter->setPen(pen);
    painter->drawLine(begin->pos().x(), begin->pos().y(), end->pos().x(), end->pos().y());
}



