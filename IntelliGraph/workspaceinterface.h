#ifndef WORKSPACEINTERFACE_H
#define WORKSPACEINTERFACE_H

#include <QObject>
#include <QScriptEngine>
#include "workspace.h"

class WorkspaceInterface : public QObject
{
    Q_OBJECT
public:
    WorkspaceInterface(Workspace *workspace);

signals:

public slots:
    QScriptValue highlightNode(QScriptContext *context , QScriptEngine *engine);

private:
    Workspace *_context;
};

#endif // WORKSPACEINTERFACE_H
