#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <QScriptEngine>
#include <QScriptValueIterator>
#include <QDir>
#include "workspace.h"
#include "workspaceinterface.h"

class AlgorithmEngine
{
public:
    AlgorithmEngine(Workspace *parent, QPushButton *nxt, QString appdir);

    // getters
    QList<QListWidgetItem*> getAlgorithms();

    // actions
    void init(QString file);
    void next();

private:
    bool isInitiated;
    QString _path;
    Workspace *_context;
    QScriptEngine *_engine;
    QScriptValue _handler;
    QPushButton *_nextButton;
};

#endif // ALGORITHM_H
