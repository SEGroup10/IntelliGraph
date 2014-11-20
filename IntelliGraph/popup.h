#ifndef POPUP_H
#define POPUP_H

#include <QDialog>
#include <string>

#include "workspace.h"
#include <QList>
#include <QDebug>
#include "ui_popup.h"

using namespace std;

//class Popup;
class Node;


class Popup : public QDialog
{
    Q_OBJECT

public:
    explicit Popup(QWidget *parent = 0);
    ~Popup();
    void setLabel(string label);
    void setCaller(Node* _caller);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Popup *ui;
    QList<QColor> colors;
    void fillColours();
    Node *caller;
};

#endif // POPUP_H
