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
#include <QPointF>

#include "node.h"
#include "edge.h"
#include "nodetype.h"
#include "popup.h"
#include "popupedge.h"
#include "algorithminterface.h"
#include "samplealgorithm.h"

class Node;
class Popup;
class PopupEdge;
class Edge;
class AlgorithmInterface;

class Workspace: public QGraphicsScene
{
    public:
        enum Mode {
            selectMode,
            nodeMode,
            edgeMode,
            viewMode
        };
        Workspace( QWidget *widget, QGraphicsView *elem );
        ~Workspace();

        // Main functions
        void handleClick( QMouseEvent *event);
        void handleResize();
        void handleNext();
        void clearSelection();

        // Data functions
        QList<Node*> getNodes();
        QList<Edge*> getEdges();
        void setMode(Workspace::Mode newMode);
        Workspace::Mode getMode();

        //What does this do?
        bool popupChecked;

        // Instance functions
        void updateConnectedEdges(Node *target);
        Node *addNode(int x, int y);
        Node *addNode(int x, int y, NodeType::Type type);
        void deleteNode(Node *target);
        Edge *addEdge(Node *begin, Node *end);
        void deleteEdge(Edge *target);
        void setnode(Node *target,NodeType::Type type);
        void test();

    private:
        bool clickedOnNode(Node *&node, QPointF pos);
        bool clickedOnEdge(Edge *&edge,QPointF pos);

        // events
        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);
        void mousePressEvent(QGraphicsSceneMouseEvent * event);

        Node* getNodeById( int id );

        int getNewId();

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

        AlgorithmInterface *loadedAlgorithm;

        static int IDCounter;
};

#endif // WORKSPACE_H
