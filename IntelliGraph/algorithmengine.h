#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <QScriptEngine>
#include <QScriptValueIterator>
#include <QDir>
#include "workspace.h"

class AlgorithmEngine
{
public:
    AlgorithmEngine(Workspace *parent, QString appdir);

    // getters
    QList<QListWidgetItem*> getAlgorithms();

    // actions
    void init(QString file);

private:
    QString _path;
    Workspace *_context;
    QScriptEngine *_engine;
};

#endif // ALGORITHM_H
