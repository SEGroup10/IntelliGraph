#include "workspace.h"

Workspace::Workspace( QWidget *widget, QGraphicsView *elem )
{
    this->drawingArea = elem;
    this->parent = widget;
}

Workspace::~Workspace()
{
    delete scene;
}

void Workspace::doStuff()
{
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
    scene->addRect(scene->width(),scene->height(),0,0,QPen(),QBrush());

    //Scene rect back to automatic. Since we now have items in it, the bounding box will be at least the size
    //of these elements. Mission accomplished.
    scene->setSceneRect(QRectF());

    // As a test we draw a purple circle.
    QBrush purpleBrush(QColor(102, 0, 102));
    QPen blackPen(Qt::black);

    blackPen.setWidth(2);

    // Here we add the circle to the scene
    QGraphicsEllipseItem* ellipse = scene->addEllipse(150, 150, 100, 100, blackPen, purpleBrush);

    // And make it movable
    ellipse->setFlag(QGraphicsItem::ItemIsMovable);

}

void Workspace::handleClick( QMouseEvent *event ) {
    int x, y;
    x = event->x() - drawingArea->x() - drawingArea->horizontalScrollBar()->minimum() + drawingArea->horizontalScrollBar()->value();
    y = event->y() - drawingArea->y() - drawingArea->verticalScrollBar()->minimum() + drawingArea->verticalScrollBar()->value();
    qDebug() << "Click at:" << x << "," << y << "relative to top-left of drawing area";

    qDebug() << drawingArea->horizontalScrollBar()->minimum() << ":" << drawingArea->horizontalScrollBar()->maximum();
    //TODO fix this - values are off when scrollbar becomes visible for some reason
}
