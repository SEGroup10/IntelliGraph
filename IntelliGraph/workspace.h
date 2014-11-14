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
#include <QResizeEvent>
#include <QSize>

#include "node.h"
#include "edge.h"

class Workspace
{
public:
    Workspace( QWidget *widget, QGraphicsView *elem );
    ~Workspace();
    void handleClick( QMouseEvent *event );
    void linkTest();

    void handleResize();
private:

    QWidget *parent;
    QGraphicsView *drawingArea;
    QGraphicsScene *scene;

    QList<Node*> nodes;
    QList<Edge*> edges;

    QGraphicsRectItem *sizeenforcer;

    void addNode(int x, int y);
    void addNode(int x, int y, string label);
    void deleteNode(Node *target);
    void addEdge(Node *begin, Node *end);
    void deleteEdge(Edge *target);
};

#endif // WORKSPACE_H
