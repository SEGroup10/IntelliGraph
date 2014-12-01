#include "algorithminterface.h"
using namespace std;

AlgorithmInterface::AlgorithmInterface(QObject *parent, QColor _color): QObject(parent)
{
    _highlightColor = _color;
}

void AlgorithmInterface::init(QList<Node *> nodes, QList<Edge *> edges)
{
    _nodes = nodes;
    _edges = edges;
    _lastNode = NULL;
}

void AlgorithmInterface::debug(QString data)
{
    qDebug() << data;
}

void AlgorithmInterface::highlightNode(QString nodeID)
{
    Node *tmp_n; Edge *tmp_e;
    int id = nodeID.toInt();
    for (int i = 0; i < _nodes.length(); i++) {
        tmp_n = _nodes.at(i);
        if (tmp_n->getID() == id) {
            tmp_n->highlight(_highlightColor);
            break;
        }
    }
    if (_lastNode != NULL) {
        for (int i = 0; i < _edges.length(); i++) {
            tmp_e = _edges.at(i);
            if (tmp_e->hasStartNode(_lastNode) && tmp_e->hasEndNode(tmp_n)) {
                tmp_e->highlight(_highlightColor);
                break;
            }
        }
    }
    _lastNode = tmp_n;
}
