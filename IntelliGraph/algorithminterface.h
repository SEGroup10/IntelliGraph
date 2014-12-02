#ifndef ALGORITHMINTERFACE_H
#define ALGORITHMINTERFACE_H

#include <QDebug>
#include <QObject>
#include "node.h"
#include "edge.h"

class Node;
class Edge;

class AlgorithmInterface: public QObject
{
    Q_OBJECT
    public:
        explicit AlgorithmInterface(QObject *parent = 0, QColor _color = Qt::red);
        void init(QList<Node*> nodes, QList<Edge*> edges);

    public slots:
        Q_INVOKABLE void debug(QString data);
        Q_INVOKABLE void highlightNode(QString nodeID);

    private:
        Node *_lastNode;
        QList<Node*> _nodes;
        QList<Edge*> _edges;
        QColor _highlightColor;
};

#endif // ALGORITHMINTERFACE_H
