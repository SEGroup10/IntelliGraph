#include "workspace.h"

using namespace std;

Workspace::Workspace( QWidget *widget, QGraphicsView *elem )
{
    this->drawingArea = elem;
    this->parent = widget;

    // We need a Scene on the GraphicsView to draw shapes
    scene = new QGraphicsScene( parent );
    drawingArea->setScene(scene);

    //We can only add elements *inside* the bounding box of the scene, but by default this bounding box has
    //no width or height, so we can't add anything...
    //We set this bounding box to be a fixed value here so we can add something.
    scene->setSceneRect(drawingArea->x(), drawingArea->y(), drawingArea->width()-10, drawingArea->height()-10);

    //When using a dynamic scene rect, the scene rect is the bounding box of the elements.
    //These invisible elements force the bounding box to be the size of the initial workspace
    //allowing us to dynamically add elements in it.
    scene->addRect(0,0,0,0,QPen(),QBrush());
    scene->addRect(drawingArea->width(),drawingArea->height(),0,0,QPen(),QBrush());

    //Scene rect back to automatic. Since we now have items in it, the bounding box will be at least the size
    //that contains these elements. Mission accomplished.
    scene->setSceneRect(QRectF());
    mode = selectMode;
}

Workspace::~Workspace()
{
    delete scene;
}

void Workspace::handleClick( QMouseEvent *event )
{
    int x, y;
    x = event->x() - drawingArea->x() - drawingArea->horizontalScrollBar()->minimum() + drawingArea->horizontalScrollBar()->value() + scene->sceneRect().x();
    y = event->y() - drawingArea->y() - drawingArea->verticalScrollBar()->minimum() + drawingArea->verticalScrollBar()->value() + scene->sceneRect().y();

    qDebug() << drawingArea->horizontalScrollBar()->value() << drawingArea->horizontalScrollBar()->minimum();

    qDebug() << scene->sceneRect().x();

    if(mode == selectMode)
        if( event->type() == QEvent::MouseButtonDblClick )
            addNode( x - (NODESIZE/2), y - (NODESIZE/2) );
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
    selectNode = NULL;
    selectEdge = NULL;
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

Node * Workspace::getItem(int num)
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
}

void Workspace::addNode(int x, int y)
{
    Node* node = new Node(nodes.count(),x,y,this);
    nodes.append( node );
    scene->addItem( node );
    //scene->addItem( node->getLabel() );
}

void Workspace::addNode(int x, int y, string label)
{
    Node* node = new Node(nodes.count(),x,y,this);
    nodes.append( node );

    node->changeName( label );

    scene->addItem( node );
    //scene->addItem( node->getLabel() );
}

void Workspace::deleteNode(Node *target)
{
    scene->removeItem( target );
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

    scene->addItem( edge );
}

void Workspace::deleteEdge(Edge *target)
{
    scene->removeItem( target );
    edges.removeAt(target->getID());
    delete target;
}
