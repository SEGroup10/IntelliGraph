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

using namespace std;

class Workspace
{
    public:
        Workspace( QWidget *widget, QGraphicsView *elem );
        ~Workspace();

        // Main functions
        enum Mode { selectMode, nodeMode, edgeMode };
        void handleClick( QMouseEvent *event );
        void linkTest();
        void clearSelection();

        // Data functions
        QList<Node*> getNodes();
        QList<Edge*> getEdges();
        void setMode(Workspace::Mode newMode);
        Workspace::Mode getMode();
        Node * getItem(int num);
        void setItem(Node * newItem, int num);
        void setSelectNode(Node * newSelectNode);
        Node * getSelectNode();
        void setSelectEdge(Edge * newSelectEdge);
        Edge * getSelectEdge();

        // Instance functions
        void addNode(int x, int y);
        void addNode(int x, int y, string label);
        void deleteNode(Node *target);
        void addEdge(Node *begin, Node *end);
        void deleteEdge(Edge *target);

    private:
        QWidget * parent;
        QGraphicsView * drawingArea;
        QGraphicsScene * scene;

        Mode mode;
        Node * item1;
        Node * item2;

        Node * selectNode;
        Edge * selectEdge;

        QList<Node*> nodes;
        QList<Edge*> edges;
};

#endif // WORKSPACE_H
