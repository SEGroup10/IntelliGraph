#include "algorithminterface.h"
using namespace std;

AlgorithmInterface::AlgorithmInterface(QObject *parent): QObject(parent)
{
}


void AlgorithmInterface::log(QString data)
{
    qDebug() << data;
}
