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
#include "nodetype.h"
#include "popup.h"
#include "popupedge.h"

class Node;
class Popup;
class PopupEdge;
class Edge;

class Workspace: public QGraphicsScene
{
    public:
        enum Mode {
            selectMode,
            nodeMode,
            edgeMode
        };
        Workspace( QWidget *widget, QGraphicsView *elem );
        ~Workspace();

        // Main functions
        void handleClick( QMouseEvent *event);
        void handleResize();
        void linkTest();
        void clearSelection();

        // Data functions
        QList<Node*> getNodes();
        QList<Edge*> getEdges();
        void setMode(Workspace::Mode newMode);
        Workspace::Mode getMode();
        //Node * getItem(int num);
        //void setItem(Node * newItem, int num);
        //void setSelectNode(Node * newSelectNode);
        //Node * getSelectNode();
        //void setSelectEdge(Edge * newSelectEdge);
        //Edge * getSelectEdge();

        // Instance functions
        void updateConnectedEdges(Node *target);
        Node *addNode(int x, int y);
        Node *addNode(int x, int y, NodeType::Type type);
        void deleteNode(Node *target);
        void addEdge(Node *begin, Node *end);
        void deleteEdge(Edge *target);
        bool popupChecked;

    private:
        bool clickedOnNode(Node *&node);
        bool clickedOnEdge(Edge *&edge);

        // events
        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);
        void mousePressEvent(QGraphicsSceneMouseEvent * event);

       // bool _dragging;
        QWidget * parent;
        QGraphicsView * drawingArea;
        //QGraphicsScene * scene;

        QGraphicsRectItem *sizeenforcer;

        Workspace::Mode mode;
        Node * item1;
        Node * item2;

        Node * selectedNode;
        Edge * selectedEdge;

        QList<Node*> nodes;
        QList<Edge*> edges;

        Popup *popup;
        PopupEdge *popupedge;
};

#endif // WORKSPACE_H
