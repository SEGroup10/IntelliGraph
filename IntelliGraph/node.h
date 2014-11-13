#ifndef NODE_H
#define NODE_H

#define NODESIZE 100
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
//#include "colour.h"
using namespace std;

class Node: public QGraphicsItem
{
	public:
        Node(int newID,int x,int y);
        ~Node();

		int getID();
		string getName();
		void changeName(string newName);
		int getSpecial();
        void setSpecial(int newSpecial);
        QColor getColour();
        void changeColour(QColor newCol);
		void changeColourRGB(int newR,int newG, int newB);

        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
        //QGraphicsSimpleTextItem* getLabel();
    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
	private:
		int ID;
		string name;
        int special;
        QColor col;
        //QGraphicsSimpleTextItem* label;

        string itos(int number);
};

#endif
