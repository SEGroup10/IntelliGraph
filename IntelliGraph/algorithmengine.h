#ifndef ALGORITHMENGINE_H
#define ALGORITHMENGINE_H

#include <QJSEngine>
#include <QJSValue>
#include <QDir>
#include "workspace.h"
#include "node.h"
#include "edge.h"
#include "algorithminterface.h"

class Workspace;
class AlgorithmInterface;

class AlgorithmEngine
{
public:
    AlgorithmEngine(Workspace *parent, QString appdir);

    // getters
    QList<QListWidgetItem*> getAlgorithms();

    // actions
    void init(QString file);
    void reset();
    void next();

private:
    QJSValue getStartNode();
    QJSValue getEndNode();
    QByteArray getFileContents(QString path);

    int _algorithmIterator;
    bool isInitiated;
    QString _path;
    Workspace *_context;
    QJSEngine *_engine;
    QJSValue _handler;
    QList<QVariant> _algorithmPath;
};

#endif // ALGORITHM_H
