#include "node.h"

using namespace std;

// Initializes the node class
Node::Node(int id, QPointF position, Workspace *context): QGraphicsItem()
{
    _id = id;
    _label = itos(id);
    _context = context;
    _isHighlighted = false;
    this->setZValue(2);
    this->setType(NodeType::STANDARD);

    //The first and second param of QGraphicsEllipseItem are an offset from
    //the position, which is by default 0. We set the offset to 0 in the
    //constructor and set the correct position below.
    //
    //Because logic.
    this->setPos(position);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}
Node::Node(int id, QPointF position, Workspace *context, NodeType::Type type): QGraphicsItem()
{
    _id = id;
    _label = itos(id);
    _context = context;
    _isHighlighted = false;
    this->setZValue(2);
    this->setType(type);

    //The first and second param of QGraphicsEllipseItem are an offset from
    //the position, which is by default 0. We set the offset to 0 in the
    //constructor and set the correct position below.
    //
    //Because logic.
    this->setPos(position);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
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

// Gets the center position of this object
QPointF Node::getCenter() const {
    double x = this->pos().x(), y = this->pos().y();
    x += NODESIZE / 2;
    y += NODESIZE / 2;
    return QPointF(x, y);
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
        default:
            Q_ASSERT_X(false, "Node::setType", "unrecognized nodetype");
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

// highlights current node
void Node::highlight(QColor color) {
    _isHighlighted = true;
    _highlightColour = color;
    this->update();
}

void Node::removeHighlight() {
    _isHighlighted = false;
    this->update();
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
    painter->setRenderHint(QPainter::Antialiasing);

    if (_isHighlighted) {
        painter->setPen(Qt::NoPen);
        painter->setBrush(QBrush(_highlightColour));
        painter->drawEllipse(QRectF(-4, -4, NODESIZE+8, NODESIZE+8));
    }

    painter->setPen(pen);
    painter->setBrush(brush);
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
QVariant Node::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemScenePositionHasChanged) {
        this->update();
    }
    return QGraphicsItem::itemChange(change, value);
}

// Custom update routine
void Node::update()
{
    // update edges attached to node
    _context->updateConnectedEdges(this);
    // update this item
    QGraphicsItem::update(boundingRect());
}

bool Node::isUnderMouse( QPointF mousepos ) const
{
    //Pythagoras
    qreal a = mousepos.x() - this->getCenter().x();
    qreal b = mousepos.y() - this->getCenter().y();
    qreal c = qSqrt( qPow(a,2) + qPow(b,2) );

    return c < (NODESIZE/2);
}
