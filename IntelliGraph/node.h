#ifndef NODE_H
#define NODE_H

#define NODESIZE 80
#define FONTSIZE 18

#include <QGraphicsEllipseItem>
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
#include <QRectF>
#include <QPaintEvent>
#include <string>
#include <sstream>

#include "workspace.h"
#include "nodetype.h"

using namespace std;

class Workspace;

class Node: public QGraphicsItem
{
	public:
        // (de)Constructors
        Node(int id, QPointF position, Workspace *context);
        Node(int id, QPointF position, Workspace *context, NodeType::Type type);
        ~Node();

        // Getters
        int getID();
        string getLabel();
        NodeType::Type getType();
        QColor getColour();

        // Setters
        void setLabel(string label);
        void setType(NodeType::Type type);
        void setColour(QColor colour);
        void setColourRGB(int r, int g, int b);

        // Painting functions
        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    private:
        // Events
        void mousePressEvent(QGraphicsSceneMouseEvent *event);

        // Utility functions
        string itos(int number);

        // Data
        int _id;
        string _label;
        NodeType::Type _type;
        QColor _colour;
        Workspace *_context;
};

#endif
