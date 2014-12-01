#include "algorithm.h"
using namespace std;

Algorithm::Algorithm(QObject *parent, QColor _color): QObject(parent)
{
    _highlightColor = _color;
}

void Algorithm::init(QList<Node *> nodes, QList<Edge *> edges)
{
    _nodes = nodes;
    _edges = edges;
}

void Algorithm::debug(QString data)
{
    qDebug() << data;
}

void Algorithm::highlightNode(QString nodeID)
{
    Node *tmp;
    int id = nodeID.toInt();
    for (int i = 0; i < _nodes.length(); i++) {
        tmp = _nodes.at(i);
        if (tmp->getID() == id) {
            tmp->highlight(_highlightColor);
        }
    }
}
