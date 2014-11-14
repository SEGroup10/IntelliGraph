#include "workspace.h"

#include <QTransform>


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
    scene->setSceneRect(0, 0, drawingArea->width(), drawingArea->height());

    //When using a dynamic scene rect, the scene rect is the bounding box of the elements.
    //These invisible elements force the bounding box to be the size of the initial workspace
    //allowing us to dynamically add elements in it.
    scene->addRect(0,0,0,0,QPen(),QBrush());
    sizeenforcer = scene->addRect(0,0,0,0,QPen(),QBrush());
    //Position of enforcer is set as soon as the first resize event is called. See
    //http://stackoverflow.com/q/26920575/2209007 for more information

    //Scene rect back to automatic. Since we now have items in it, the bounding box will be at least the size
    //that contains these elements. Mission accomplished.
    scene->setSceneRect(QRectF());
}

Workspace::~Workspace()
{
    delete scene;
}

void Workspace::handleResize()
{
    //This enforces the scene to be at least the size of the drawingArea. If this is not the case, adding
    //elements will not work as expected.
    if( scene->width() < (drawingArea->width()-drawingArea->verticalScrollBar()->width()) ||
        scene->height() < (drawingArea->height()-drawingArea->horizontalScrollBar()->height()) ) {

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
        scene->setSceneRect(drawingArea->sceneRect().x(), drawingArea->sceneRect().y(), biggestX-3, biggestY-3);

        //Move the enforcer to it's new position.
        sizeenforcer->setPos(biggestX-3, biggestY-3);

        //The scene rect is now dynamic again and will automatically expand if you move something
        //outside the screen
        scene->setSceneRect(QRectF());
    }
}

void Workspace::handleClick( QMouseEvent *event )
{
    int x, y;
    x = event->x() - drawingArea->x() - drawingArea->horizontalScrollBar()->minimum() + drawingArea->horizontalScrollBar()->value() + drawingArea->sceneRect().x();
    y = event->y() - drawingArea->y() - drawingArea->verticalScrollBar()->minimum() + drawingArea->verticalScrollBar()->value() + drawingArea->sceneRect().y();
    if( event->type() == QEvent::MouseButtonDblClick ) {
      addNode( x - (NODESIZE/2), y - (NODESIZE/2) );
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

void Workspace::addNode(int x, int y)
{
    Node* node = new Node(nodes.count(),x,y);
    nodes.append( node );
    scene->addItem( node );
    //scene->addItem( node->getLabel() );
}
void Workspace::addNode(int x, int y, string label)
{
    Node* node = new Node(nodes.count(),x,y);
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
    Edge* edge = new Edge(edges.count(),begin,end);
    edges.append(edge);

    scene->addItem( edge );
}

void Workspace::deleteEdge(Edge *target)
{
    scene->removeItem( target );
    edges.removeAt(target->getID());
    delete target;
}
