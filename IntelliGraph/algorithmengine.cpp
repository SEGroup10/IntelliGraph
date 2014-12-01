#include "algorithmengine.h"
using namespace std;

AlgorithmEngine::AlgorithmEngine(Workspace *parent, QPushButton *nxt, QString appdir)
{
    _context = parent;
    _path = appdir.append("/algorithms/");
    _engine = new QJSEngine();
    _nextButton = nxt;
    isInitiated = false;
    _interface = new Algorithm();


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
    _interface->init(_context->getNodes(), _context->getEdges());
    _engine->globalObject().setProperty("algorithm", _engine->newQObject(_interface));

    // load script
    _handler = _engine->evaluate(getFileContents(_path.append(file)));

    // start algorithm
    _handler.property("init").call(QJSValueList() << getNodes() << getEdges());
    _handler.property("start").call(QJSValueList() << getStartNode() << getEndNode());

}

void AlgorithmEngine::next() {
    qDebug() << "algorithm engine next";
    if (!_handler.property("next").call().toBool()) {
        qDebug() << "last node reached";
    }
}

void AlgorithmEngine::stop() {
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

QByteArray getFileContents(QString path) {
    QByteArray ret;
    QFile file(path);
    if (file.open(QIODevice::ReadOnly)) {
        ret = file.readAll();
    }
    file.close();
    return ret;
}
