#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QList <int>Nodes; // Hier moet <int> later aangepast worden aan de "Node" class! Int is alleen een placeholder.
    QList <int>Edges; // Hier moet <int> later aangepast worden aan de "Edge" class!


    return a.exec();
}
