#include "algorithmengine.h"

AlgorithmEngine::AlgorithmEngine(Workspace *parent, QPushButton *nxt, QString appdir)
{
    _context = parent;
    _path = appdir.append("/algorithms/");
    _engine = new QScriptEngine();
    _nextButton = nxt;
    isInitiated = false;

    // expose workspace
    /*QScriptValue scriptWorkspace = _engine->newQObject(_context);
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
    qDebug() << _handler.property("init").call().toString();

    // bind algorithm next
    qScriptConnect(_nextButton, SIGNAL(clicked()), _handler, _handler.property("next"));

    isInitiated = !_handler.isError();
}
