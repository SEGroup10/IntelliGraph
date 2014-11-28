#include "workspaceinterface.h"

WorkspaceInterface::WorkspaceInterface(Workspace *workspace): QObject()
{
    _context = workspace;
}

QScriptValue WorkspaceInterface::highlightNode(QScriptContext *context , QScriptEngine *engine) {
    qDebug() << context->toString();
    return QScriptValue();
    /**/
}
