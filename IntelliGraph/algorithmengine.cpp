#include "algorithmengine.h"
using namespace std;

AlgorithmEngine::AlgorithmEngine(Workspace *parent, QString appdir)
{
    _context = parent;
    _path = appdir.append("/algorithms/");
    _engine = new QJSEngine();
    isInitiated = false;
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
    // init script environment
    _engine->globalObject().setProperty("console", _engine->newQObject(new AlgorithmInterface()));

    // load script
    _handler = _engine->evaluate(QString(getFileContents(_path + file)));

    // check algorithm functions
    if (!_handler.hasProperty("init") || !_handler.hasProperty("run")) {
        qDebug() << "Algorithm doesn't have required functions";
        return;
    }

    // start algorithm
    _handler.property("init").call(QJSValueList() << getNodes() << getEdges());
    QJSValue bestPath = _handler.property("run").call(QJSValueList() << getStartNode() << getEndNode());
    if (bestPath.toVariant().userType() == QVariant::List) {
        _algorithmPath = bestPath.toVariant().toList();
        _algorithmIterator = 0;
        isInitiated = true;
        // highlight start node
        _context->getNodeById(_algorithmPath.at(0).toInt())->highlight(Qt::red);
    }
}

bool AlgorithmEngine::previous() {
    Node *_prev, *_curr; Edge *_e;
    if (isInitiated && _algorithmIterator > 0) {
        _prev = _context->getNodeById(_algorithmPath.at(_algorithmIterator-1).toInt());
        _curr = _context->getNodeById(_algorithmPath.at(_algorithmIterator).toInt());
        _curr->removeHighlight();
        _e = _context->findEdge(_curr, _prev);
        _e->removeHighlight();
        _algorithmIterator--;
        return true;
    }
    return false;
}

bool AlgorithmEngine::next() {
    Node *_curr, *_next; Edge *_e;
    if (isInitiated && _algorithmIterator < (_algorithmPath.length()-1)) {
        _curr = _context->getNodeById(_algorithmPath.at(_algorithmIterator).toInt());
        _next = _context->getNodeById(_algorithmPath.at(_algorithmIterator+1).toInt());
        _next->highlight(Qt::red);
        _e = _context->findEdge(_curr, _next);
        _e->highlight(Qt::red);
        _algorithmIterator++;
        return true;
    }
    return false;
}

QJSValue AlgorithmEngine::getNodes()
{
    QString arr("([");
    QList<Node*> nodes = _context->getNodes();
    for (int i = 0; i < nodes.length(); i++) {
        arr.append(QString::number(nodes.at(i)->getID()));
        if (i < (nodes.length() - 1)) {
            arr.append(",");
        }
    }
    return _engine->evaluate(arr.append("])"));
}

QJSValue AlgorithmEngine::getEdges()
{
    Edge *current;
    QList<Edge*> edges = _context->getEdges();
    QJSValue ret =  _engine->newArray(edges.length());
    for (int i = 0; i < edges.length(); i++) {
        current = edges.at(i);
        QJSValue tmp = _engine->newArray(2);
        tmp.setProperty(0, QJSValue(current->getBeginNode()->getID()));
        tmp.setProperty(1, QJSValue(current->getEndNode()->getID()));
        tmp.setProperty(2, QJSValue(current->getWeight(true)));
        ret.setProperty(i, tmp);
    }
    return ret;
}

QJSValue AlgorithmEngine::getStartNode() {
    Node * tmp;
    QList<Node*> nodes = _context->getNodes();
    for (int i = 0; i < nodes.length(); i++) {
        tmp = nodes.at(i);
        if (tmp->getType() == NodeType::START) {
            return QJSValue(tmp->getID());
        }
    }
    return QJSValue();
}

QJSValue AlgorithmEngine::getEndNode() {
    Node * tmp;
    QList<Node*> nodes = _context->getNodes();
    for (int i = 0; i < nodes.length(); i++) {
        tmp = nodes.at(i);
        if (tmp->getType() == NodeType::END) {
            return QJSValue(tmp->getID());
        }
    }
    return QJSValue();
}

QByteArray AlgorithmEngine::getFileContents(QString path) {
    QByteArray ret;
    QFile file(path);
    qDebug() << path;
    if (file.open(QIODevice::ReadOnly)) {
        qDebug() << "file could be opened!";
        ret = file.readAll();
    } else {
        qDebug() << "file could not be opened?!";
    }
    file.close();
    return ret;
}
