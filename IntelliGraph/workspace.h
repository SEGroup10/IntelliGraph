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

using namespace std;

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

    Node *addNode(int x, int y);
    Node *addNode(int x, int y, NodeType::Type type);
    void deleteNode(Node *target);
    void addEdge(Node *begin, Node *end);
    void deleteEdge(Edge *target);
};

#endif // WORKSPACE_H
