#include "workspace.h"

Workspace::Workspace( QWidget *widget, QGraphicsView *elem )
{
    this->drawingArea = elem;
    this->parent = widget;
}

void Workspace::doStuff()
{
    // We need a Scene on the GraphicsView to draw shapes
    scene = new QGraphicsScene( parent );
    drawingArea->setScene(scene);

    // As a test we draw a purple circle.
    QBrush purpleBrush(QColor(102, 0, 102));
    QPen blackPen(Qt::black);

    blackPen.setWidth(2);

    // Here we add the circle to the scene
    ellipse = scene->addEllipse(10, 10, 100, 100, blackPen, purpleBrush);

    // And make it movable
    ellipse->setFlag(QGraphicsItem::ItemIsMovable);

}

void Workspace::handleClick( QMouseEvent *event ) {
    int x, y;
    x = event->x() + drawingArea->horizontalScrollBar()->value() - drawingArea->x();
    y = event->y() + drawingArea->verticalScrollBar()->value() - drawingArea->y();
    qDebug() << "Click at:" << x << "," << y << "relative to top-left of drawing area";
    //TODO fix this - values are off when scrollbar becomes visible for some reason
}
