#include "workspace.h"

using namespace std;

Workspace::Workspace( QWidget *widget, QGraphicsView *elem ): QGraphicsScene( widget )
{
    this->drawingArea = elem;
    this->parent = widget;

    // We need a Scene on the GraphicsView to draw shapes
   // scene = new QGraphicsScene( parent );
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

void Workspace::linkTest()
{
    Node *edge_start;
    if (nodes.count() > 1)
    {
        edge_start = nodes.at(0);
        for (int i = 1; i < nodes.count(); i++)
        {
            addEdge(edge_start, nodes.at(i));
        }
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

/*Node * Workspace::getItem(int num)
{
    if(num == 1)
        return item1;
    else if(num == 2)
        return item2;
    else
        return NULL;
}

void Workspace::setItem(Node * newItem, int num)
{
    if(num == 1)
        item1 = newItem;
    else if(num == 2)
        item2 = newItem;
    else
        return;
}

void Workspace::setSelectNode( Node * newSelectNode )
{
    selectNode = newSelectNode;
}

Node * Workspace::getSelectNode()
{
    return selectNode;
}

void Workspace::setSelectEdge( Edge * newSelectEdge )
{
    selectEdge = newSelectEdge;
}

Edge * Workspace::getSelectEdge()
{
    return selectEdge;
}*/

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
    Node* node = new Node(nodes.count(), pos, this);
    nodes.append( node );
    this->addItem( node );
    return node;
}

Node *Workspace::addNode(int x, int y, NodeType::Type type)
{
    QPointF pos(x, y);
    Node* node = new Node(nodes.count(), pos, this, type);
    nodes.append( node );

    this->addItem( node );
    return node;
}

void Workspace::deleteNode(Node *target)
{
    this->removeItem( target );
    // remove connected edges
    for( int i = 0; i < edges.count(); i++ )
    {
        if( edges.at(i)->hasNode(target))
        {
            deleteEdge(edges.at(i));
        }
    }
    //
    nodes.removeAt(target->getID());
    delete target;
}

void Workspace::addEdge(Node *begin, Node *end)
{
    Edge* edge = new Edge(edges.count(),begin,end,this);
    edges.append(edge);

    this->addItem( edge );
}

void Workspace::deleteEdge(Edge *target)
{
    this->removeItem( target );
    edges.removeAt(target->getID());
    delete target;
}

bool Workspace::clickedOnNode(Node *&node)
{
    Node *temp;
    node = NULL;
    for (int i = 0; i < nodes.length(); i++) {
        temp = nodes.at(i);
        if (temp->isUnderMouse()) {
            node = temp;
            return true;
        }
    }
    return false;
}

bool Workspace::clickedOnEdge(Edge *&edge)
{
    Edge *temp;
    edge = NULL;
    QPoint mousepos = parent->mapFromGlobal( QCursor::pos() );
    for (int i = 0; i < edges.length(); i++) {
        temp = edges.at(i);
        if (temp->isUnderMouse(mousepos)) {
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

    if (clickedOnNode(n)) {
        //Close dialog; if we don't do this, we loose the reference
        //creating a potential memory leak
        if( popup != NULL ) {
            delete popup;
        }
        popup = new Popup();
        popup->setCaller(n);
        popup->setLabel(n->getLabel());
        popup->show();
    } else if (clickedOnEdge(e)) {
        //Close dialog; if we don't do this, we loose the reference
        //creating a potential memory leak
        if( popupedge != NULL ) {
            delete popupedge;
        }
        popupedge = new PopupEdge();
        popupedge->setCaller(e);
        popupedge->show();
    } else if(mode == Workspace::selectMode) {
        addNode( x - (NODESIZE/2), y - (NODESIZE/2) );
    }
    QGraphicsScene::mouseDoubleClickEvent(event);
}

void Workspace::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //_dragging = true;
    Node *n; Edge *e;
    if (clickedOnNode(n)) {
        if(mode == Workspace::selectMode) {
            selectedNode = n;
            selectedEdge = NULL;
        } else if(mode == Workspace::edgeMode)  {
            if(item1 == NULL) {
                item1 = n;
            } else if(item1 != n) {
                item2 = n;
                this->addEdge(item1, item2);
                this->clearSelection();
            }
        }
    } else if (clickedOnEdge(e)) {
        if(mode == Workspace::selectMode) {
            selectedEdge = e;
            selectedNode = NULL;
        }
    }

    QGraphicsScene::mousePressEvent(event);
}
