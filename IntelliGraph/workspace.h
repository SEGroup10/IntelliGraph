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
#include <QFileDialog>

#include "node.h"
#include "edge.h"
#include "nodetype.h"
#include "popup.h"
#include "popupedge.h"
#include "algorithminterface.h"

class Node;
class Popup;
class PopupEdge;
class Edge;
//class AlgorithmInterface;

class Workspace: public QGraphicsScene
{
    public:
        enum Mode {
            selectMode,
            nodeMode,
            edgeMode,
            algorithmMode
        };
        Workspace( QWidget *widget, QGraphicsView *elem );
        ~Workspace();

        // Main functions
        void handleClick( QMouseEvent *event);
        void handleResize();
        void handleNext();
        void clearSelection();
        void removeHighlight();
        void removeAlgorithmLabels();
        bool nodesConnected();

        // Data functions
        Node* getNodeById( int id );
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
        Edge *findEdge(Node *a, Node *b);
        void deleteNode(Node *target);
        Edge *addEdge(Node *begin, Node *end);
        void deleteEdge(Edge *target);
        void exportGraph();
        void setnode(Node *target, NodeType::Type type);
private:
        QList<Node *> getConnectedNodes(Node *node);
        bool clickedOnNode(Node *&node, QPointF pos);
        bool clickedOnEdge(Edge *&edge,QPointF pos);

        // events
        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);
        void mousePressEvent(QGraphicsSceneMouseEvent * event);

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

        static int IDCounter;
};

#endif // WORKSPACE_H
