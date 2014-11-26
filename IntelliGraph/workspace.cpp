#include "workspace.h"

using namespace std;

//Init static variable
int Workspace::IDCounter = 0;

Workspace::Workspace( QWidget *widget, QGraphicsView *elem ): QGraphicsScene( widget )
{
    this->drawingArea = elem;
    this->parent = widget;

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
    addEdge(start, end);

    //Init popup and popupedge for systems that do not automatically initialize it with null
    popup = NULL;
    popupedge = NULL;

    //Init loadedAlgorithm for systems that do not automatically initialize it with null
    //loadedAlgorithm = NULL;
    //TODO Remove this and uncomment above!
    loadedAlgorithm = new SampleAlgorithm( this );
    //This should happen in the algorithm initializer
    loadedAlgorithm->processNodes( nodes );
    loadedAlgorithm->processEdges( edges );
    loadedAlgorithm->init();
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
    item1 = NULL;
    item2 = NULL;
    selectedNode = NULL;
    selectedEdge = NULL;
}

QList<Node*> Workspace::getNodes()
{
    return nodes;
}

QList<Edge*> Workspace::getEdges()
{
    return edges;
}

void Workspace::setMode(Workspace::Mode newMode)
{
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

void Workspace::deleteNode(Node *target)
{
    bool repeat = true;
    while( repeat ) {
        //If no edges had to be deleted, repeat will be false at the end of the while loop
        repeat = false;

        //Delete any edge that connects to the deleted node
        for( int i = 0; i < edges.count(); i++ )
        {
            if( edges.at(i)->hasNode(target))
            {
                deleteEdge(edges.at(i));
                //Continueing with this loop will result in undefined behaviour
                //break out of for loop and start all over again
                repeat = true;
                break;
            }
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
            item1 = n;
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
            } else if(item1 != n) {
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

//Handles a click on the next button
void Workspace::handleNext()
{
    //You should not be able to click the next button if no algorithm is loaded
    Q_ASSERT_X( (loadedAlgorithm != NULL), "Workspace::handleNext()", "loadedAlgorithm is NULL");

    Node *oldNode = getNodeById( loadedAlgorithm->getHighlightedNode() );
    Q_ASSERT_X( (oldNode != NULL ), "Workspace::handleNext()", "old Node is NULL");
    oldNode->removeHighlight();

    if( loadedAlgorithm->next() ) {
        qDebug() << "loaded Next: " << loadedAlgorithm->getHighlightedNode();
        Node *node = this->getNodeById( loadedAlgorithm->getHighlightedNode() );
        Q_ASSERT_X( (node != NULL), "Workspace::handleNext()", "id returned by algorithm does not exist");
        node->highlight(QColor(255,0,0));
    }

    //nodes.at(0)->highlight(QColor(255, 0, 0));
}

//Test function to test functionality of algorithms
void Workspace::test() {
    qDebug() << "resetting algorithm";
    delete loadedAlgorithm;

    foreach( Node *node, nodes ) {
        node->removeHighlight();
    }

    loadedAlgorithm = new SampleAlgorithm( this );
    loadedAlgorithm->processNodes( nodes );
    loadedAlgorithm->processEdges( edges );
    loadedAlgorithm->init();
    Node *node = this->getNodeById( loadedAlgorithm->getHighlightedNode() );
    Q_ASSERT_X( (node != NULL), "Workspace::test()", "id returned by algorithm does not exist");
    node->highlight(QColor(255,0,0));
}
