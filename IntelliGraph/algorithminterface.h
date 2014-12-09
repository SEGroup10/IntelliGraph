#ifndef ALGORITHMINTERFACE_H
#define ALGORITHMINTERFACE_H

#include <QDebug>
#include <QJSEngine>
#include <QJSValue>
#include <QObject>
#include "edge.h"
#include "node.h"
#include "workspace.h"

class AlgorithmInterface: public QObject
{
    Q_OBJECT
    public:
        explicit AlgorithmInterface(Workspace *context, QJSEngine *engine, QObject *parent = 0);

    public slots:
        Q_INVOKABLE void log(QString data);
        Q_INVOKABLE void setName(QString name);
        Q_INVOKABLE void setLabel(QString id, QString label);
        Q_INVOKABLE void highlightColor(QString r, QString g, QString b);
        Q_INVOKABLE void highlightNode(QString id);
        Q_INVOKABLE void highlightEdge(QString a, QString b);
        Q_INVOKABLE void removeHighlightNode(QString id);
        Q_INVOKABLE void removeHighlightEdge(QString a, QString b);
        Q_INVOKABLE QJSValue getNodes();
        Q_INVOKABLE QJSValue getEdges();

    private:
        QString _name;
        QColor _highlightColor;
        Workspace *_context;
        QJSEngine *_engine;
};

#endif // ALGORITHMINTERFACE_H
