#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsLineItem>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QDebug>
#include <QEvent>
#include <QGraphicsTextItem>
#include <QString>
#include <QGraphicsScene>
#include <QLineF>

#include "node.h"
#include "workspace.h"

using namespace std;

class Workspace;

class Node;

class Edge: public QGraphicsLineItem
{
    public:
        Edge(int newID, Node * newBegin, Node * newEnd, Workspace * newParent);
        ~Edge();
        int getID();
        string getName();
        void setName( string newName );
        int getWeight();
        void setWeight( int newWeight );
        void paint(QPainter *painter);
        bool hasNode(Node *target);

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);

    private:
        int ID;
        string name;
        int weight;
        bool direction;
        Node * begin;
        Node * end;
        Workspace * parent;
};



#endif // EDGE_H
