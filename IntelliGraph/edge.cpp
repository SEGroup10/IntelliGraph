#include "edge.h"
#include "node.h"
#include "workspace.h"

using namespace std;

// initializes the edge class
Edge::Edge(int id, Node *start, Node *end, Workspace *context): QGraphicsItem()
{
    _id = id;
    _start = start;
    _end = end;
    _label = "";
    _weight = 1.0;
    _context = context;
    this->setZValue(1);
}

// Deconstructs the edge class instance
Edge::~Edge()
{

}

// Gets the Id
int Edge::getID()
{
    return _id;
}

// Gets the Label
string Edge::getLabel()
{
    return _label;
}

// Gets the path weight
double Edge::getWeight()
{
    return _weight;
}

// Checks if this edge is connected to target
bool Edge::hasNode(Node *target)
{
    return (_start == target || _end == target);
}

// Sets the Label
void Edge::setLabel(string label)
{
    _label = label;
    this->update();
}

// Sets the Weight
void Edge::setWeight(double weight)
{
    // if label set to weight change it
    if (dtos(_weight) == _label)
    {
        _label = dtos(weight);
    }
    _weight = weight;
    this->update();
}

// Return bounding rectangle
QRectF Edge::boundingRect() const
{
    QPointF s = _start->getCenter();
    QPointF e = _end->getCenter();
    QPointF topleft = QPointF(min(s.x(), e.x()), min(s.y(), e.y()));
    QPointF bottomright = QPointF(max(s.x(), e.x()), max(s.y(), e.y()));

    return QRectF(topleft, bottomright);//_start->getCenter(), _end->getCenter());
}

// Paint the object
void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::black);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawLine(_start->getCenter(), _end->getCenter());
}


// convert an double to a string
string Edge::dtos(double number)
{
    ostringstream temp;
    temp << number;
    return temp.str();
}

// Custom update routine
void Edge::update()
{
    QGraphicsItem::prepareGeometryChange();
    QGraphicsItem::update(boundingRect());
}

void Edge::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(_context->getMode() == Workspace::selectMode)
       _context->setSelectEdge(this);

    this->update();
}
