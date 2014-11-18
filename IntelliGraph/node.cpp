#include "node.h"

using namespace std;

// Initializes the node class
Node::Node(int id, QPointF position, Workspace *context): QGraphicsItem()
{
    _id = id;
    _label = itos(id);
    _context = context;
    this->setType(NodeType::STANDARD);

    //The first and second param of QGraphicsEllipseItem are an offset from
    //the position, which is by default 0. We set the offset to 0 in the
    //constructor and set the correct position below.
    //
    //Because logic.
    this->setPos(position);
    setFlag(QGraphicsItem::ItemIsMovable);
}
Node::Node(int id, QPointF position, Workspace *context, NodeType::Type type): QGraphicsItem()
{
    _id = id;
    _label = itos(id);
    _context = context;
    this->setType(type);

    //The first and second param of QGraphicsEllipseItem are an offset from
    //the position, which is by default 0. We set the offset to 0 in the
    //constructor and set the correct position below.
    //
    //Because logic.
    this->setPos(position);
    setFlag(QGraphicsItem::ItemIsMovable);
}

// Deconstructs the node class instance
Node::~Node()
{

}

// Gets the ID
int Node::getID()
{
    return _id;
}

// Gets the Label
string Node::getLabel()
{
    return _label;
}

// Gets the Type
NodeType::Type Node::getType() {
    return _type;
}

// Gets the Colour
QColor Node::getColour() {
    return _colour;
}

// Sets the Label
void Node::setLabel(string label) {
    _label = label;
    this->update();
}

// Sets the Type
void Node::setType(NodeType::Type type)
{
    _type = type;
    switch (type)
    {
        case NodeType::START:
            _colour = QColor(0, 255, 0);
            break;
        case NodeType::END:
            _colour = QColor(255, 0, 0);
            break;
        case NodeType::STANDARD:
            _colour = QColor(255, 255, 255);
            break;
    }
    this->update();
}

// Sets the Colour
void Node::setColour(QColor colour)
{
    _colour = colour;
    this->update();
}
void Node::setColourRGB(int r, int g, int b)
{
    this->setColour(QColor(r, g, b));
}

// Return bounding rectangle
QRectF Node::boundingRect() const
{
    return QRectF(0, 0, NODESIZE, NODESIZE);
}

// Paints the node
void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush(_colour);
    QPen pen(Qt::black);
    QFont font = painter->font();
    font.setPointSize(FONTSIZE);
    pen.setWidth(2);

    painter->setFont(font);
    painter->setBrush(brush);
    painter->setPen(pen);

    painter->drawEllipse(rect);
    painter->drawText(rect, Qt::AlignCenter, QString(_label.c_str()));
}

// convert an int to a string
string Node::itos(int number)
{
    ostringstream temp;
    temp << number;
    return temp.str();
}

// Mouse press event
void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Node:" << this->_label.c_str();
    qDebug() << "Type of event:" << event;
    if( event->type() == QEvent::GraphicsSceneMouseDoubleClick ) {
        qDebug() << "Poof! A dialog box for the element with ID" << _id << "appears.";
    }
    // update grpahics
    QGraphicsItem::mousePressEvent(event);
    this->update();
}




