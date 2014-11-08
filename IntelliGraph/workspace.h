#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QGraphicsView>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QListWidgetItem>
#include <QMouseEvent>
#include <QDebug>
#include <QScrollBar>

class Workspace
{
public:
    Workspace( QWidget *widget, QGraphicsView *elem );
    void doStuff();
    void handleClick( QMouseEvent *event );
private:
    QWidget *parent;
    QGraphicsView *drawingArea;

    QList <int>Nodes; // Hier moet <int> later aangepast worden aan de "Node" class! Int is alleen een placeholder.
    QList <int>Edges; // Hier moet <int> later aangepast worden aan de "Edge" class!

    //TODO find out if these are needed and if they need to be deleted when destroying this class
    QGraphicsEllipseItem *ellipse;
    QGraphicsScene *scene;
};

#endif // WORKSPACE_H
