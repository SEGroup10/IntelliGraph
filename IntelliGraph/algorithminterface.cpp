#include "algorithminterface.h"
using namespace std;

AlgorithmInterface::AlgorithmInterface(Workspace *context, QJSEngine *engine, QObject *parent): QObject(parent)
{
    _context = context;
    _engine = engine;
    _name = QString("Unknown");
    _highlightColor = Qt::red;
}


void AlgorithmInterface::log(QString data)
{
    qDebug() << _name << ">" << data;
}

void AlgorithmInterface::setName(QString name)
{
    _name = name;
}

void AlgorithmInterface::setNodeLabel(QString id, QString label)
{
    Node * n = _context->getNodeById(id.toInt());
    if (n != NULL) {
        n->setAlgorithmLabel(label);
    }
}

void AlgorithmInterface::setEdgeLabel(QString a, QString b, QString label)
{

}

void AlgorithmInterface::highlightColor(QString r, QString g, QString b)
{
    _highlightColor = QColor(r.toInt(), g.toInt(), b.toInt());
}

void AlgorithmInterface::highlightNode(QString id)
{
    Node *n = _context->getNodeById(id.toInt());
    if (n != NULL) {
        n->highlight(_highlightColor);
    }
}

void AlgorithmInterface::highlightEdge(QString a, QString b)
{
    Node *na = _context->getNodeById(a.toInt()),
         *nb = _context->getNodeById(b.toInt());
    Edge *tmp = _context->findEdge(na, nb);
    if (tmp != NULL) {
        tmp->highlight(_highlightColor);
    }
}

void AlgorithmInterface::removeHighlightNode(QString id)
{
    Node *n = _context->getNodeById(id.toInt());
    if (n != NULL) {
        n->removeHighlight();
    }
}

void AlgorithmInterface::removeHighlightEdge(QString a, QString b)
{
    Node *na = _context->getNodeById(a.toInt()),
         *nb = _context->getNodeById(b.toInt());
    Edge *tmp = _context->findEdge(na, nb);
    if (tmp != NULL) {
        tmp->removeHighlight();
    }
}


QJSValue AlgorithmInterface::getNodes()
{
    QString arr("([");
    QList<Node*> nodes = _context->getNodes();
    for (int i = 0; i < nodes.length(); i++) {
        arr.append(QString::number(nodes.at(i)->getID()));
        if (i < (nodes.length() - 1)) {
            arr.append(",");
        }
    }
    return _engine->evaluate(arr.append("])"));
}

QJSValue AlgorithmInterface::getEdges()
{
    Edge *current;
    QList<Edge*> edges = _context->getEdges();
    QJSValue ret =  _engine->newArray(edges.length());
    for (int i = 0; i < edges.length(); i++) {
        current = edges.at(i);
        QJSValue tmp = _engine->newArray(2);
        tmp.setProperty(0, QJSValue(current->getBeginNode()->getID()));
        tmp.setProperty(1, QJSValue(current->getEndNode()->getID()));
        tmp.setProperty(2, QJSValue(current->getWeight(true)));
        ret.setProperty(i, tmp);
    }
    return ret;
}
