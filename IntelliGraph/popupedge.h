#ifndef POPUPEDGE_H
#define POPUPEDGE_H

#include <QDialog>
#include <QPlainTextEdit>
#include <QString>
#include <string>

#include "workspace.h"
#include "edge.h"
#include <QList>
#include <QDebug>
#include "ui_popupedge.h"

using namespace std;

//class Popup;
class Edge;


class PopupEdge : public QDialog
{
    Q_OBJECT

public:
    explicit PopupEdge(QWidget *parent = 0);
    ~PopupEdge();
    void setLabel(string label);
    void setCaller(Edge* _caller);
    void setWorkspace(Workspace*);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_DeleteNode_clicked();

    void on_DeleteEdge_clicked();

private:
    Ui::PopupEdge *ui;
    QList<QColor> colors;
    Edge *caller;
    Workspace *wrkspc;

};

#endif // POPUPEDGE_H
