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
class Workspace;
class Node;

using namespace std;

class Edge: public QGraphicsItem
{
    public:
        // (de)Constructors
        Edge(int id, Node *start, Node *end, Workspace *context);
        ~Edge();

        // Getters
        int getID();
        string getLabel();
        double getWeight();
        bool hasNode(Node *target);

        // Setters
        void setLabel(string label);
        void setWeight(double weight);

        // Painting functions
        void update();
        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    private:
        // Events
        void mousePressEvent(QGraphicsSceneMouseEvent *event);

        // Utility functions
        string dtos(double number);

        // Data
        int _id;
        double _weight;
        string _label;
        Node *_start;
        Node *_end;
        Workspace *_context;
};

#endif // EDGE_H
