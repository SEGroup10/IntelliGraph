#ifndef POPUP_H
#define POPUP_H

#include <QDialog>
#include <QPlainTextEdit>
#include <QString>
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
    explicit Popup(QWidget *parent = 0, Node *_caller = 0);
    ~Popup();
    void setLabel(string label);
    void setCaller(Node *_caller);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Popup *ui;
    QList<QColor> colors;
    void fillColours();
    void setSliders();
    Node *caller;
    QColor currentColor;
};

#endif // POPUP_H
