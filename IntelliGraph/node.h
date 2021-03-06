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

#include "nodetype.h"
#include "workspace.h"

using namespace std;

class Workspace;
class Popup;

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
        QPointF getCenter() const;

        // Setters
        void resetLabel();
        void setLabel(string label);
        void setAlgorithmLabel(QString label);
        void setType(NodeType::Type type);
        void setColour(QColor colour);
        void setColourRGB(int r, int g, int b);

        // Painting functions
        QRectF boundingRect() const;
        void highlight(QColor color);
        void removeHighlight();
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

        bool isUnderMouse(QPointF mousepos) const;

    private:
        // Events
        QVariant itemChange(GraphicsItemChange change, const QVariant &value);
        void update();

        // Utility functions
        string itos(int number);

        // Data
        int _id;
        QString _algorithmLabel;
        string _label;
        NodeType::Type _type;
        QColor _colour, _highlightColour;
        Workspace *_context;
        bool _isHighlighted;
        bool _useAlgorithmLabel;
};

#endif
