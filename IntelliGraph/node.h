#ifndef NODE_H
#define NODE_H

#define NODESIZE 100

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

#include <string>
#include "colour.h"
using namespace std;

class Node: public QGraphicsEllipseItem
{


	public:
        Node(int newID,int newSpecial,string newName, int x, int y);
        ~Node();
		int getID();
		string getName();
		void changeName(string newName);
		int getSpecial();
        //position getPosition();
        //void changePosition(position newPos);
        //void changePositionXY(int newX,int newY);
        QColor getColour();
        void changeColour(QColor newCol);
		void changeColourRGB(int newR,int newG, int newB);

        QGraphicsSimpleTextItem* getLabel();
	private:
		int ID;
		string name;
		int special;
        //position pos; //Information already available through inheritance
        QColor col;
        QGraphicsSimpleTextItem* label;

        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif
