#include "node.h"

using namespace std;

Node::Node(int newID, int x, int y): QGraphicsEllipseItem(0, 0, NODESIZE, NODESIZE, 0)
{
	ID = newID;
    special = 0;
    name = "";
    col = QColor(200, 200, 0);
    label = new QGraphicsSimpleTextItem();

    //The first and second param of QGraphicsEllipseItem are an offset from
    //the position, which is by default 0. We set the offset to 0 in the
    //constructor and set the correct position below.
    //
    //Because logic.
    this->setPos(x, y);

    setFlag(QGraphicsItem::ItemIsMovable);

    //this->scene() is NULL until this node gets added to a scene.
    //So we add this label in the workspace function instead
}

Node::~Node()
{

};

int Node::getID()
{
	return ID;
}

string Node::getName()
{
	return name;
}

void Node::changeName(string newName)
{
	name = newName;
    label->setText(QString(newName.c_str()));
    label->setPos(x()+(NODESIZE/2)-(label->boundingRect().width()/2),this->y()+(NODESIZE/2)-(label->boundingRect().height()/2));
}

int Node::getSpecial()
{
	return special;
}

void Node::setSpecial( int newSpecial )
{
    special = newSpecial;
}

/*position Node::getPosition()
{
	return pos;
}

void Node::changePosition(position newPos)
{
	pos = newPos;
	return;
}

void Node::changePositionXY(int newX, int newY)
{
	pos.X = newX;
	pos.Y = newY;
	return;
}*/

QColor Node::getColour()
{
    return col;
}

void Node::changeColour(QColor newCol)
{
	col = newCol;
	return;
}

void Node::changeColourRGB(int newR, int newG, int newB)
{
    col.setRgb(newR,newG,newB);
	return;
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Type of event:" << event->type();
    if( event->type() == QEvent::GraphicsSceneMouseDoubleClick ) {
        qDebug() << "Poof! A dialog box for the element with ID" << this->ID << "appears.";
    }
}


void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush(getColour());
    QPen pen(Qt::black);
    pen.setWidth(2);

    painter->setBrush(brush);
    painter->setPen(pen);
    painter->drawEllipse(boundingRect());
}

QGraphicsSimpleTextItem* Node::getLabel()
{
    return label;
}




