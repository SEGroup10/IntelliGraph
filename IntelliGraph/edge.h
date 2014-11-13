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

using namespace std;

class Edge: public QGraphicsLineItem
{
    public:
        Edge(int newID, Node * newBegin, Node * newEnd);
        ~Edge();
        int getID();
        string getName();
        void changeName(string newName);
        void paint(QPainter *painter);
        bool hasNode(Node *target);
    private:
        int ID;
        string name;
        Node * begin;
        Node * end;
        bool direction;
};



#endif // EDGE_H
