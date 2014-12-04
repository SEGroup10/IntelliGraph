#include "workspace.h"

using namespace std;

//Init static variable
int Workspace::IDCounter = 0;

Workspace::Workspace( QWidget *widget, QGraphicsView *elem ): QGraphicsScene( widget )
{
    this->drawingArea = elem;
    this->parent = widget;

    this->item1 = NULL;
    this->item2 = NULL;

    // We need a Scene on the GraphicsView to draw shapes
    drawingArea->setScene(this);

    //We can only add elements *inside* the bounding box of the scene, but by default this bounding box has
    //no width or height, so we can't add anything...
    //We set this bounding box to be a fixed value here so we can add something.
    this->setSceneRect(0, 0, drawingArea->width(), drawingArea->height());

    //When using a dynamic scene rect, the scene rect is the bounding box of the elements.
    //These invisible elements force the bounding box to be the size of the initial workspace
    //allowing us to dynamically add elements in it.
    this->addRect(0,0,0,0,QPen(),QBrush());
    sizeenforcer = this->addRect(0,0,0,0,QPen(),QBrush());
    //Position of enforcer is set as soon as the first resize event is called. See
    //http://stackoverflow.com/q/26920575/2209007 for more information

    //Scene rect back to automatic. Since we now have items in it, the bounding box will be at least the size
    //that contains these elements. Mission accomplished.
    this->setSceneRect(QRectF());

    //A toolbar will manipulate these modes
    mode = Workspace::selectMode;

    //Adding initial nodes.
    Node *start = addNode(100, 100, NodeType::START);
    Node *end = addNode(400, 100, NodeType::END);
    //addEdge(start, end);

    //Init popup and popupedge for systems that do not automatically initialize it with null
    popup = NULL;
    popupedge = NULL;

}

Workspace::~Workspace()
{
    //delete scene;
}

void Workspace::handleClick( QMouseEvent *event )
{
    /*int x, y;
    x = event->x() - drawingArea->x() - drawingArea->horizontalScrollBar()->minimum() + drawingArea->horizontalScrollBar()->value() + this->sceneRect().x();
    y = event->y() - drawingArea->y() - drawingArea->verticalScrollBar()->minimum() + drawingArea->verticalScrollBar()->value() + this->sceneRect().y();

    qDebug() << drawingArea->horizontalScrollBar()->value() << drawingArea->horizontalScrollBar()->minimum();

    qDebug() << this->sceneRect().x();

    if(mode == Workspace::selectMode)
        if( event->type() == QEvent::MouseButtonDblClick )
            addNode( x - (NODESIZE/2), y - (NODESIZE/2) );*/
}

void Workspace::handleResize()
{
    //This enforces the scene to be at least the size of the drawingArea. If this is not the case, adding
    //elements will not work as expected.
    if( this->width() < (drawingArea->width()-drawingArea->verticalScrollBar()->width()) ||
        this->height() < (drawingArea->height()-drawingArea->horizontalScrollBar()->height()) ) {

        //If the drawingarea is bigger than the scene, biggestX will be the new x coordinate
        //of the enforcer, otherwise it will be it's current x coordinate
        int biggestX = sizeenforcer->x() > (drawingArea->width() + drawingArea->sceneRect().x()) ?
                       sizeenforcer->x() : (drawingArea->width() + drawingArea->sceneRect().x());
        int biggestY = sizeenforcer->y() > (drawingArea->height() + drawingArea->sceneRect().y()) ?
                       sizeenforcer->y() : (drawingArea->height() + drawingArea->sceneRect().y());

        //We want the scene to be inside the scrollbars if possible
        biggestX -= drawingArea->verticalScrollBar()->width();
        biggestY -= drawingArea->horizontalScrollBar()->height();

        //Static size of scene rect so we can move the enforcer outside the current area
        this->setSceneRect(drawingArea->sceneRect().x(), drawingArea->sceneRect().y(), biggestX-3, biggestY-3);

        //Move the enforcer to it's new position.
        sizeenforcer->setPos(biggestX-3, biggestY-3);

        //The scene rect is now dynamic again and will automatically expand if you move something
        //outside the screen
        this->setSceneRect(QRectF());
    }
}

void Workspace::clearSelection()
{
    if(item1 != NULL)
        item1->removeHighlight();
    if(item2 != NULL)
        item2->removeHighlight();

    item1 = NULL;
    item2 = NULL;
    selectedNode = NULL;
    selectedEdge = NULL;
}

void Workspace::removeHighlight() {
    for (int i = 0; i < nodes.length(); i++) {
        nodes.at(i)->removeHighlight();
    }
    for (int i = 0; i < edges.length(); i++) {
        edges.at(i)->removeHighlight();
    }
}

QList<Node*> Workspace::getNodes()
{
    return nodes;
}

QList<Edge*> Workspace::getEdges()
{
    return edges;
}

/* This function handles workspace-related changes for a mode change. This should not be called
 * on it's own. Let ui elements call MainWindow::setMode instead, which will invoke this function
 * when the time is right.
 */
void Workspace::setMode(Workspace::Mode newMode)
{
    if( newMode == Workspace::edgeMode ) {
        foreach( Node* i, this->getNodes() ) {
            i->setFlag(QGraphicsItem::ItemIsMovable, false);
        }
    } else if( newMode == Workspace::selectMode ) {
        foreach( Node* i, this->getNodes() ) {
            i->setFlag(QGraphicsItem::ItemIsMovable, true);
        }
    } else if( newMode == Workspace::algorithmMode ) {
        foreach( Node* i, this->getNodes() ) {
            i->setFlag(QGraphicsItem::ItemIsMovable, false);
        }
    } else {
        Q_ASSERT_X( false, "Workspace::setMode", "unhandled mode!" );
    }
    mode = newMode;
}

Workspace::Mode Workspace::getMode()
{
    return mode;
}

void Workspace::updateConnectedEdges(Node *target)
{
    Edge *temp = NULL;
    for (int i = 0; i < edges.length(); i++)
    {
        temp = edges.at(i);
        if (temp != NULL && temp->hasNode(target))
        {
            temp->update();
        }
    }
}

Node *Workspace::addNode(int x, int y)
{
    QPointF pos(x, y);
    Node* node = new Node(getNewId(), pos, this);
    nodes.append( node );
    this->addItem( node );
    return node;
}

Node *Workspace::addNode(int x, int y, NodeType::Type type)
{
    QPointF pos(x, y);
    Node* node = new Node(getNewId(), pos, this, type);
    nodes.append( node );

    this->addItem( node );
    return node;
}

Edge *Workspace::findEdge(Node *a, Node *b)
{
    Edge *tmp;
    for (int i = 0; i < edges.length(); i++) {
        tmp = edges.at(i);
        if ((tmp->hasStartNode(a) && tmp->hasEndNode(b)) ||
            (tmp->hasStartNode(b) && tmp->hasEndNode(a))) {
            return tmp;
        }
    }
    return NULL;
}

void Workspace::deleteNode(Node *target)
{
    Edge *temp = NULL;
    for (int i = 0; i < edges.length(); i++)
    {
        temp = edges.at(i);
        if (temp != NULL && temp->hasNode(target))
        {
            deleteEdge(temp);
        }
    }

    nodes.removeAt(nodes.indexOf(target));
    this->removeItem( target );
    delete target;
}

Edge* Workspace::addEdge(Node *begin, Node *end)
{
    Edge* edge = new Edge(getNewId(),begin,end,this);
    edges.append(edge);

    this->addItem( edge );

    return edge;
}

//Removes a directional or bidirectional edge
//Do not use this if you want to only delete one way
void Workspace::deleteEdge(Edge *target)
{
    edges.removeAt(edges.indexOf(target));
    this->removeItem( target );
    delete target;
}

//Will return true and change the passed variable node if
//a node is found at the position of the click
//otherwise returns false and changes the reference to NULL
bool Workspace::clickedOnNode(Node *&node, QPointF pos)
{
    Node *temp;
    node = NULL;
    for (int i = nodes.length() - 1; i >= 0; i--) {
        temp = nodes.at(i);
        if (temp->isUnderMouse(pos)) {
            node = temp;
            return true;
        }
    }
    return false;
}

//Will return true and change the passed variable edge if
//an edge is found at the position of the click
//otherwise returns false and changes the reference to NULL
bool Workspace::clickedOnEdge(Edge *&edge, QPointF pos)
{
    Edge *temp;
    edge = NULL;
    for (int i = edges.length() - 1; i >= 0; i--) {
        temp = edges.at(i);
        if (temp->isUnderMouse(pos)) {
            edge = temp;
            return true;
        }
    }
    return false;
}

void Workspace::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Node *n; Edge *e;
    int x = event->scenePos().x(),  y = event->scenePos().y();

    if( mode == Workspace::selectMode) {
        if (clickedOnNode(n,event->scenePos())) {
            //Close dialog; if we don't do this, we loose the reference
            //creating a potential memory leak
            if( popup != NULL ) {
                delete popup;
            }
            popup = new Popup(this->parent, n, this);
            popup->show();
            popup->activateWindow();
        } else if (clickedOnEdge(e,event->scenePos())) {
            //Close dialog; if we don't do this, we loose the reference
            //creating a potential memory leak
            if( popupedge != NULL ) {
                delete popupedge;
            }
            popupedge = new PopupEdge(this->parent, e, this);
            popupedge->show();
        } else {
            addNode( x - (NODESIZE/2), y - (NODESIZE/2) );
        }
    } else if( mode == Workspace::edgeMode ) {
        if( clickedOnNode(n,event->scenePos()) ) {
            if( item1 == NULL ) {
                item1 = n;
                item1->highlight(QColor(255,0,0));
            } else if(item1 == n) {
                this->clearSelection();
            }
        }
    }
    QGraphicsScene::mouseDoubleClickEvent(event);
}

void Workspace::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //_dragging = true;
    Node *n; Edge *e;
    if (clickedOnNode(n,event->scenePos())) {
        if(mode == Workspace::selectMode) {
            selectedNode = n;
            selectedEdge = NULL;
        } else if(mode == Workspace::edgeMode)  {
            if(item1 == NULL) {
                item1 = n;
                item1->highlight(QColor(255,0,0));
            } else if(item1 == n) {
                this->clearSelection();
            }
            else if(item1 != n) {
                item2 = n;
				bool didWefindsomething = false;
				foreach (Edge *edge, edges)
				{
					if (edge->hasStartNode(item1) && edge->hasEndNode(item2))
					{
                        //this edge already exists
                        didWefindsomething = true;
					}
					else if (edge->hasStartNode(item2) && edge->hasEndNode(item1))
					{
                        //lets make the existing one bidirectional
                        //even if it is already bidirectional
                        edge->setBidirectional(true);
						didWefindsomething = true;
					}
				}
				if (!didWefindsomething) {
					this->addEdge(item1, item2);
				}
                this->clearSelection();
            }
        }
    } else if (clickedOnEdge(e,event->scenePos())) {
        if(mode == Workspace::selectMode) {
            selectedEdge = e;
            selectedNode = NULL;
        }
    }

    QGraphicsScene::mousePressEvent(event);
}

//Returns a guaranteed unique id until we run out of ints. If this happens, close the application. Seriously...
int Workspace::getNewId()
{
    return IDCounter++;
}

//Returns a Node with this id; if no such node exists returns null
Node *Workspace::getNodeById( int id )
{
    foreach( Node *node, nodes ) {
        if( node->getID() == id ) {
            return node;
        }
    }
    return NULL;
}

void Workspace::setnode(Node *target,NodeType::Type type){
    int i;

    if( type == NodeType::END || type == NodeType::START ) {
        for( i = 0; i < Workspace::nodes.count(); i++ ) {
            if( (target!=Workspace::nodes.at(i)) && (Workspace::nodes.at(i)->getType()==type) ) {
                QColor color = Workspace::nodes.at(i)->getColour();
                Workspace::nodes.at(i)->setType(NodeType::STANDARD);
                if( type == NodeType::START && (color.red() != 0 || color.green() != 255 || color.blue() != 0) ) {
                    //Used to be start node with non-standard color
                    Workspace::nodes.at(i)->setColour( color );
                } else if( type == NodeType::END && (color.red() != 255 || color.green() != 0 || color.blue() != 0) ) {
                    //Used to be end node with non-standard color
                    Workspace::nodes.at(i)->setColour( color );
                }
            }
        }
    }

    target->setType(type);
}
