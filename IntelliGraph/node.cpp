#include "node.h"
#include "workspace.h"

using namespace std;

Node::Node(int newID, int x, int y, Workspace * newParent): QGraphicsItem()
{
	ID = newID;
    special = 0;
    name = itos(newID);
    col = QColor(200, 200, 0);
    parent = newParent;

    //The first and second param of QGraphicsEllipseItem are an offset from
    //the position, which is by default 0. We set the offset to 0 in the
    //constructor and set the correct position below.
    //
    //Because logic.
    this->setPos(x, y);
    //this->setText(QString(name.c_str()));

    setFlag(QGraphicsItem::ItemIsMovable);

    //this->scene() is NULL until this node gets added to a scene.
    //So we add this label in the workspace function instead

}

Node::~Node()
{

}

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
}

int Node::getSpecial()
{
	return special;
}

void Node::setSpecial( int newSpecial )
{
    special = newSpecial;
}

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

QRectF Node::boundingRect() const
{
    return QRectF(0, 0, NODESIZE, NODESIZE);
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush(getColour());
    QPen pen(Qt::black);
    QFont font = painter->font();

    font.setPointSize(FONTSIZE);
    painter->setFont(font);
    painter->setBrush(brush);

    pen.setWidth(3);
    painter->setPen(pen);
    painter->drawEllipse(rect);

    pen.setWidth(1);
    painter->setPen(pen);
    painter->drawText(rect, Qt::AlignCenter, QString(name.c_str()));
}

string Node::itos(int number)
{
    ostringstream temp;
    temp << number;
    return temp.str();
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(parent->getMode() == Workspace::Mode::selectMode)
        parent->setSelectNode(this);

    if(parent->getMode() == Workspace::Mode::edgeMode)
    {
        if(parent->getItem(1) == NULL)
            parent->setItem(this,1);
        else if(parent->getItem(1) != this)
        {
            parent->setItem(this,2);
            parent->addEdge(parent->getItem(1),parent->getItem(2));
            parent->clearSelection();
        }
    }

    // update grpahics
    update();
    QGraphicsItem::mousePressEvent(event);
}




