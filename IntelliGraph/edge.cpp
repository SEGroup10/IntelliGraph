#include "edge.h"
#include "node.h"
#include "workspace.h"

using namespace std;

static const double Pi = 3.14159265358979323846264338327950288419717;

// initializes the edge class
Edge::Edge(int id, Node *start, Node *end, Workspace *context): QGraphicsItem()
{
    _id = id;
    _start = start;
    _end = end;
    _flip = false;
    _margin = 50;
    _weight1 = 1;
    _weight2 = 2;
    _context = context;
    _directional = true;
    _bidirectional = false;
    _isHighlighted = false;
    arrow1Colour = QColor(52, 152, 219);
    arrow2Colour = QColor(52, 73, 94);
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

//Returns label from begin to end if true is passed
//Returns label from end to begin if false is passed
string Edge::getWeightAsString(bool weight1)
{
    return this->dtos( this->getWeight( weight1 ) );
}


//Returns weight from begin to end if true is passed
//Returns weight from end to begin if false is passed
double Edge::getWeight(bool weight1)
{
    if (weight1) return _weight1;
    else return _weight2;
}

Node *Edge::getBeginNode()
{
    return _start;
}

Node *Edge::getEndNode()
{
    return _end;
}

Node *Edge::getOtherNode(Node *tmp)
{
    if (hasStartNode(tmp)) {
        return _end;
    }
    if (hasEndNode(tmp)) {
        return _start;
    }
    return NULL;
}

// Checks if this edge is connected to target
bool Edge::hasNode(Node *target)
{
    return (_start == target || _end == target);
}

bool Edge::hasStartNode(Node *target)
{
    return (_start == target);
}

bool Edge::hasEndNode(Node *target)
{
    return (_end == target);
}

// Sets the Weight
void Edge::setWeight(double weight, bool weight1)
{
    // if label set to weight change it
    if (weight1) {
        _directional = true;
        _weight1 = weight;
    } else {
        _directional = true;
        _weight2 = weight;
    }
    this->update();
}

void Edge::setWeight(string str, bool weight1)
{
    this->setWeight( stod(str), weight1 );
}

bool Edge::getBidirectional()
{
    return _bidirectional;
}

//Makes an edge bidirectional
//Do not put any 'side-effects' in this function
void Edge::setBidirectional(bool bidirectional)
{
    _bidirectional = bidirectional;
}

// Return bounding rectangle
QRectF Edge::boundingRect() const
{
    QPointF s = _start->getCenter();
    QPointF e = _end->getCenter();
    int _practicalMargin;
    _bidirectional ? _practicalMargin = _margin : _practicalMargin = _margin;
    QPointF topleft = QPointF(min(s.x(), e.x())-_practicalMargin, min(s.y(), e.y())-_practicalMargin);
    QPointF bottomright = QPointF(max(s.x(), e.x())+_practicalMargin, max(s.y(), e.y())+_practicalMargin);

    return QRectF(topleft, bottomright);//_start->getCenter(), _end->getCenter());
}


void Edge::highlight(QColor color)
{
    _isHighlighted = true;
    _highlightColour = color;
    this->update();
}

void Edge::removeHighlight()
{
    _isHighlighted = false;
    this->update();
}

// Paint the object
void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::black);
    QFont font = painter->font();
    painter->setRenderHint(QPainter::Antialiasing);

    pen.setWidth(2);
    painter->setPen(pen);

    //I could use endPoint and startPoint here, but this way we avoid having to worry about zero-length lines.
    QLineF line(_end->getCenter(),_start->getCenter());

    //Not visible anyway, so let cut it short. Added pros:
    //if line.length() == 0 we are dividing by zero!
    if( line.length() <= NODESIZE ) return;

    // draw line
    if (_isHighlighted) {
        QPen hpen(_highlightColour);
        hpen.setWidth(6);
        painter->setPen(hpen);
        painter->drawLine(line);
    }
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawLine(line);

    //Prepare for drawing the rest
    double angle = (line.dy() >= 0) ? 2*Pi - acos(line.dx() / line.length()) : acos(line.dx() / line.length());
    QPointF endPoint = _end->getCenter() - QPointF(sin(angle - Pi/2) * NODESIZE/2, cos(angle - Pi/2) * NODESIZE/2 );
    QPointF startPoint =_start->getCenter() + QPointF(sin(angle - Pi/2) * NODESIZE/2, cos(angle - Pi/2) * NODESIZE/2 );

    font.setPointSize((line.length() >= NODESIZE * 1.6) ? FONTSIZE : max(line.length()/(NODESIZE * 1.6) * FONTSIZE, qreal(1)));
    painter->setFont(font);

    //TODO LOOK AT IT OR DELETE
    //int angleDeg = (angle*360/(2*Pi));
    //painter->drawArc(_start->getCenter().x(),_start->getCenter().y(),-line.dx()-100,-line.dy()-100,(angleDeg+45)*16, 90*16);
    //painter->drawArc(_start->getCenter().x(),_start->getCenter().y(),-line.dx()-100,-line.dy()-100,(angleDeg-45)*16, -90*16);
    //dont touch this, work in progress to make a double arch.
    if (_directional) {
        //if (line.length() >= NODESIZE) {
            //lets first check if the distance between the two is more than 20 pixels...
            //then 60 for a bigger arrow
            int ArrowSize;
            line.length() >= NODESIZE * 3 ? ArrowSize = ARROWSIZE : ArrowSize = line.length()/(NODESIZE * 3) * ARROWSIZE;
            //QPointF Point1 = _end->getCenter() - QPointF(sin(angle - Pi/2) * NODESIZE/2, cos(angle - Pi/2) * NODESIZE/2 );
            QPointF Point2 = endPoint - QPointF(sin(angle - Pi/3) * ArrowSize, cos(angle - Pi/3) * ArrowSize );
            QPointF Point3 = endPoint - QPointF(sin(angle - Pi + Pi/3) * ArrowSize, cos(angle - Pi + Pi/3) * ArrowSize );
            painter->setBrush(arrow1Colour);
            painter->drawPolygon(QPolygonF() << endPoint << Point2 << Point3);
            //qDebug() << "DrawPolygon";
            if (_bidirectional) {
                //QPointF Point4 = _start->getCenter() + QPointF(sin(angle - Pi/2) * NODESIZE/2, cos(angle - Pi/2) * NODESIZE/2 );
                QPointF Point5 = startPoint + QPointF(sin(angle - Pi/3) * ArrowSize, cos(angle - Pi/3) * ArrowSize );
                QPointF Point6 = startPoint + QPointF(sin(angle - Pi + Pi/3) * ArrowSize, cos(angle - Pi + Pi/3) * ArrowSize );
                painter->setBrush(arrow2Colour);
                painter->drawPolygon(QPolygonF() << startPoint << Point5 << Point6);
            }
        //}
    }

    if (_bidirectional) {
        pen.setColor(arrow1Colour);
        painter->setPen(pen);
        painter->drawText(boundingRect().adjusted(qSin(line.angle()*M_PI/180)*50,qCos(line.angle()*M_PI/180)*50,0,0), Qt::AlignCenter, QString::fromStdString(this->getWeightAsString(true)));
        pen.setColor(arrow2Colour);
        painter->setPen(pen);
        painter->drawText(boundingRect().adjusted(qSin(line.angle()*M_PI/180)*-50,qCos(line.angle()*M_PI/180)*-50,0,0), Qt::AlignCenter, QString::fromStdString(this->getWeightAsString(false)));
    }	else {
        if(!_flip) {
            painter->drawText(boundingRect().adjusted(qSin(line.angle()*M_PI/180)*50,qCos(line.angle()*M_PI/180)*50,0,0), Qt::AlignCenter, QString::fromStdString(this->getWeightAsString(true)));
        } else {
            painter->drawText(boundingRect().adjusted(qSin(line.angle()*M_PI/180)*-50,qCos(line.angle()*M_PI/180)*-50,0,0), Qt::AlignCenter, QString::fromStdString(this->getWeightAsString(true)));
        }
    }
}


// convert an double to a string
string Edge::dtos(double number)
{
	ostringstream temp;
	temp << number;
	return temp.str();
}

// Convert a string into a double
double Edge::stod(string str)
{
  std::istringstream i(str);
  double x;
  if (!(i >> x))
    return 0;
  return x;
}

// Custom update routine
void Edge::update()
{
	QGraphicsItem::prepareGeometryChange();
	QGraphicsItem::update(boundingRect());
}

void Edge::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	this->update();
	event->ignore();
}

bool Edge::isUnderMouse(QPointF mousepos) const
{
	qreal width = this->_end->getCenter().x() - this->_start->getCenter().x();
	qreal height = this->_end->getCenter().y() - this->_start->getCenter().y();
	qreal delta;
	qreal projection;

	//fancy way of getting a relative absolute value
	if( width*width > height*height ) {
		//Project on the x axis
		delta = height / width;
		projection = (mousepos.y() - this->_start->getCenter().y()) - ((mousepos.x() - this->_start->getCenter().x()) * delta);
	} else if( width == 0 && height == 0 ) {
		//Basically this edge does not exist
		return false;
	} else {
		//Project on the y axis
		delta = width / height;
		projection = (mousepos.x() - this->_start->getCenter().x()) - ((mousepos.y() - this->_start->getCenter().y()) * delta);
	}

	//If we ever decide to build a zoom function, this ensures that the click space stays the same as
	//the user will not become more accurate at clicking if the ui becomes smaller
	return (projection >= (-EDGECLICKSPACE*this->scale()) && projection <= (EDGECLICKSPACE*this->scale()));
}
