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

#include "node.h"
#include "edge.h"

class Workspace
{
public:
    Workspace( QWidget *widget, QGraphicsView *elem );
    ~Workspace();
    void handleClick( QMouseEvent *event );
private:
    QWidget *parent;
    QGraphicsView *drawingArea;
    QGraphicsScene *scene;

    QList<Node*> nodes; // Hier moet <int> later aangepast worden aan de "Node" class! Int is alleen een placeholder.
    QList<Edge*> edges; // Hier moet <int> later aangepast worden aan de "Edge" class!

    void addNode(int x,int y);
    void addEdge(Node *begin, Node *end);
};

#endif // WORKSPACE_H
