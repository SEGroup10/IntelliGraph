#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <QDebug>
#include <QObject>
#include "node.h"
#include "edge.h"

class Algorithm : public QObject
{
    Q_OBJECT
public:
    explicit Algorithm(QObject *parent = 0, QColor _color = Qt::red);
    void init(QList<Node*> nodes, QList<Edge*> edges);

public slots:
    Q_INVOKABLE void debug(QString data);
    Q_INVOKABLE void highlightNode(QString nodeID);

private:
    QList<Node*> _nodes;
    QList<Edge*> _edges;
    QColor _highlightColor;
};

#endif // ALGORITHM_H
