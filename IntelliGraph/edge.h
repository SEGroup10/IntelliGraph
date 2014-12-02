#ifndef EDGE_H
#define EDGE_H

#define EDGECLICKSPACE 8
#define ARROWSIZE 30
#define SMALLARROWSIZE 10

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
#include <QRectF>
#include <QtMath>
#include <QPointF>

#include "node.h"
#include "workspace.h"

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
		double getWeight(bool weight1);
        string getWeightAsString(bool weight1);
		bool getBidirectional();
        Node *getBeginNode();
        Node *getEndNode();

        // Comparators
        bool hasNode(Node *target);
        bool hasStartNode(Node *target);
        bool hasEndNode(Node *target);

		// Setters
        void setWeight(double weight, bool weight1);
        void setWeight(string str, bool weight1);
		void setBidirectional(bool bidirectional);

		// Painting functions
		void update();
        void highlight(QColor color);
        void removeHighlight();
		QRectF boundingRect() const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

		bool isUnderMouse( QPointF ) const;
	private:
		// Events
		void mousePressEvent(QGraphicsSceneMouseEvent *event);

		// Utility functions
		string dtos(double number);
        double stod(string str);

		// Data
		int _id;
		double _weight1;
		double _weight2;
		bool _flip;
		int _margin;
		bool _directional;
		bool _bidirectional;
		Node *_start;
		Node *_end;
        bool _isHighlighted;
        QColor _highlightColour;
		Workspace *_context;
        QColor arrow1Colour;
        QColor arrow2Colour;
};

#endif // EDGE_H
