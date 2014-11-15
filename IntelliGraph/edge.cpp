#include "edge.h"
#include "workspace.h"

using namespace std;

Edge::Edge(int newID, Node * newBegin, Node * newEnd, Workspace * newParent): QGraphicsLineItem(newBegin->pos().x()+NODESIZE/2, newBegin->pos().y()+NODESIZE/2,
                                                                                                newEnd->pos().x()+NODESIZE/2, newEnd->pos().y()+NODESIZE/2, 0)
{
    ID = newID;
    begin = newBegin;
    end = newEnd;
    parent = newParent;
}

Edge::~Edge()
{

}

int Edge::getID()
{
    return ID;
}

string Edge::getName()
{
    return name;
}

void Edge::setName( string newName )
{
    name = newName;
}

int Edge::getWeight()
{
    return weight;
}

void Edge::setWeight( int newWeight )
{
    weight = newWeight;
}

void Edge::paint(QPainter *painter)
{
    QPen pen(Qt::black);
    pen.setWidth(2);

    painter->setPen(pen);
    painter->drawLine(begin->pos().x(), begin->pos().y(), end->pos().x(), end->pos().y());
}

bool Edge::hasNode(Node *target)
{
    return (begin == target || end == target);
}

void Edge::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(parent->getMode() == Workspace::selectMode)
        parent->setSelectEdge(this);

    update();
}

