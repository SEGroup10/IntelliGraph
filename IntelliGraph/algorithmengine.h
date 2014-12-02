#ifndef ALGORITHMENGINE_H
#define ALGORITHMENGINE_H

#include <QJSEngine>
#include <QJSValue>
#include <QDir>
#include "workspace.h"
#include "algorithminterface.h"

class Workspace;
class AlgorithmInterface;

class AlgorithmEngine
{
public:
    AlgorithmEngine(Workspace *parent, QPushButton *nxt, QString appdir);

    // getters
    QList<QListWidgetItem*> getAlgorithms();

    // actions
    void init(QString file);
    bool next();
    void stop();

private:
    QJSValue getNodes();
    QJSValue getEdges();
    QJSValue getStartNode();
    QJSValue getEndNode();
    QByteArray getFileContents(QString path);

    bool isInitiated;
    QString _path;
    Workspace *_context;
    QJSEngine *_engine;
    QJSValue _handler;
    QPushButton *_nextButton;
    AlgorithmInterface *_interface;
};

#endif // ALGORITHM_H
