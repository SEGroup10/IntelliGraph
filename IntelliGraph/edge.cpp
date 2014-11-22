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
	_label = "1";
	_flip = false;
	_margin = 50;
	_weight = 1.0;
	_context = context;
	_direction = true;
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
	}_direction = true;
	_weight = weight;
	this->update();
}

// Return bounding rectangle
QRectF Edge::boundingRect() const
{
	QPointF s = _start->getCenter();
	QPointF e = _end->getCenter();
	QPointF topleft = QPointF(min(s.x(), e.x())-_margin, min(s.y(), e.y())-_margin);
	QPointF bottomright = QPointF(max(s.x(), e.x())+_margin, max(s.y(), e.y())+_margin);

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

	QFont font = painter->font();
	font.setPointSize(FONTSIZE);
	painter->setFont(font);

	QLineF line(_end->getCenter(),_start->getCenter());

	if (line.length() >= NODESIZE) {
		//lets first check if the distance between the two is more than 20 pixels...
		//then 60 for a bigger arrow
		int ArrowSize;
		line.length() >= NODESIZE*2 ? ArrowSize = ARROWSIZE : ArrowSize = SMALLARROWSIZE;

		double angle = ::acos(line.dx() / line.length());
		if (line.dy() >= 0) {
			angle = 2*Pi - angle;
		}
		QPointF Point1 = _end->getCenter() - QPointF(sin(angle - Pi/2) * NODESIZE/2, cos(angle - Pi/2) * NODESIZE/2 );
		if (_direction) {
			QPointF Point2 = Point1 - QPointF(sin(angle - Pi/3) * ArrowSize, cos(angle - Pi/3) * ArrowSize );
			QPointF Point3 = Point1 - QPointF(sin(angle - Pi + Pi/3) * ArrowSize, cos(angle - Pi + Pi/3) * ArrowSize );
			painter->setBrush(Qt::magenta);
			//een beetje gay is oke? lol!
			painter->drawPolygon(QPolygonF() << Point1 << Point2 << Point3);
			//qDebug() << "DrawPolygon";
		}
	}

	if(!_flip)
		painter->drawText(boundingRect().adjusted(qSin(line.angle()*M_PI/180)*50,qCos(line.angle()*M_PI/180)*50,0,0), Qt::AlignCenter, QString(_label.c_str()));
	else
		painter->drawText(boundingRect().adjusted(qSin(line.angle()*M_PI/180)*-50,qCos(line.angle()*M_PI/180)*-50,0,0), Qt::AlignCenter, QString(_label.c_str()));

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
