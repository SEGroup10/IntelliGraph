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
		string getLabel(bool label1);
		double getWeight(bool weight1);
		bool getBidirectional();
        Node *getBeginNode();
        Node *getEndNode();

        // Comparators
        bool hasNode(Node *target);
        bool hasStartNode(Node *target);
        bool hasEndNode(Node *target);

		// Setters
		void setLabel(string label, bool label1);
		void setWeight(double weight, bool weight1);
		void setBidirectional(bool bidirectional);

		// Painting functions
		void update();
		QRectF boundingRect() const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

		bool isUnderMouse( QPointF ) const;
	private:
		// Events
		void mousePressEvent(QGraphicsSceneMouseEvent *event);

		// Utility functions
		string dtos(double number);

		// Data
		int _id;
		double _weight1;
		double _weight2;
		string _label1;
		string _label2;
		bool _flip;
		int _margin;
		bool _directional;
		bool _bidirectional;
		Node *_start;
		Node *_end;
		Workspace *_context;
};

#endif // EDGE_H
