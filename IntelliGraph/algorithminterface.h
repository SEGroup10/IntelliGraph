#ifndef ALGORITHMINTERFACE_H
#define ALGORITHMINTERFACE_H

#include <QDebug>
#include <QObject>

class AlgorithmInterface: public QObject
{
    Q_OBJECT
    public:
        explicit AlgorithmInterface(QObject *parent = 0);

    public slots:
        Q_INVOKABLE void log(QString data);

};

#endif // ALGORITHMINTERFACE_H
