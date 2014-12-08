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
    _engine->globalObject().setProperty("console", _engine->newQObject(new AlgorithmInterface(_context, _engine)));

    // load script
    _handler = _engine->evaluate(QString(getFileContents(_path + file)));

    // check algorithm functions
    if (!_handler.hasProperty("init")) { qDebug() << "missing init function"; return; }
    if (!_handler.hasProperty("next")) { qDebug() << "missing next function"; return; }
    // start algorithm
    _handler.property("init").call(QJSValueList() << getStartNode() << getEndNode());
}

void AlgorithmEngine::reset() {
    _context->removeHighlight();
    _handler.property("init").call(QJSValueList() << getStartNode() << getEndNode());
}

void AlgorithmEngine::next() {
    _handler.property("next").call();
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
