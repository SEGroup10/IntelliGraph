#include "algorithmengine.h"

AlgorithmEngine::AlgorithmEngine(Workspace *parent, QPushButton *nxt, QString appdir)
{
    _context = parent;
    _path = appdir.append("/algorithms/");
    _engine = new QScriptEngine();
    _nextButton = nxt;
    isInitiated = false;

    // expose workspace
    /*WorkspaceInterface *wi = new WorkspaceInterface(_context);
    QScriptValue scriptWorkspace = _engine->newObject();
    scriptWorkspace.setProperty("highlight", _engine->newFunction(wi->highlightNode));
    QScriptValue global = _engine->globalObject();
    global.setProperty("workspace", scriptWorkspace);*/
}

QList<QListWidgetItem *> AlgorithmEngine::getAlgorithms()
{
    QList<QListWidgetItem *> list;

    QStringList nameFilter("*.alg");
    QDir directory(_path);
    QStringList fileList = directory.entryList(nameFilter);

    for (int i = 0; i < fileList.count(); i++) {
        QListWidgetItem *itm = new QListWidgetItem();
        QString file = fileList.at(i);
        itm->setSelected(i == 0);
        itm->setText(file.mid(0, file.length() - 4));
        itm->setStatusTip(file);
        list.insert(i, itm);
    }

    return list;
}

void AlgorithmEngine::init(QString file)
{
    QFile alg(_path.append(file));
    qDebug() << "able to read file? " << alg.open(QIODevice::ReadOnly);
    _handler = _engine->evaluate(alg.readAll());
    alg.close();

    // call algorithm init
    QList<Node*> nodes = _context->getNodes();
    QString arg("[");
    for(int i = 0; i < nodes.length(); i++) {
        arg.append(nodes.at(i)->getJSON());
        if (i < (nodes.length() - 1)) {
            arg.append(QString(","));
        }
    }
    arg.append("]");
    qDebug() << _handler.property("init").call(QScriptValue(), QScriptValueList() << arg).toString();

    // bind algorithm next
    qScriptConnect(_nextButton, SIGNAL(clicked()), _handler, _handler.property("next"));

    isInitiated = !_handler.isError();
}

void AlgorithmEngine::next() {
    qint32 nextNode = _handler.property("next").call().toInt32();
    if (nextNode == -1) {
        qDebug() << "end node reached";
        return;
    } else {
        qDebug() << "highlighting: " << nextNode;
    }
    Node *n = _context->getNodeById(nextNode);
    if (n == NULL)
        return;
    n->highlight(QColor(255, 0, 0));
    _context->update();
}
