#ifndef ALGORITHMENGINE_H
#define ALGORITHMENGINE_H

#include <QJSEngine>
#include <QJSValue>
#include <QDir>
#include "workspace.h"
#include "algorithm.h"

class AlgorithmEngine
{
public:
    AlgorithmEngine(Workspace *parent, QPushButton *nxt, QString appdir);

    // getters
    QList<QListWidgetItem*> getAlgorithms();

    // actions
    void init(QString file);
    void next();
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
    Algorithm *_interface;
};

#endif // ALGORITHM_H
