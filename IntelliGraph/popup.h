#ifndef POPUP_H
#define POPUP_H

#include <QDialog>
#include <QPlainTextEdit>
#include <QString>
#include <string>

#include "workspace.h"
#include "node.h"
#include <QList>
#include <QDebug>
#include "ui_popup.h"

using namespace std;

class Node;
class Workspace;

class Popup : public QDialog
{
    Q_OBJECT

public:
    explicit Popup(QWidget *parent = 0, Node *_caller = 0, Workspace *workspace = 0);
    ~Popup();
    void setLabel(string label);
    void setCaller(Node *_caller);
    void updateColour(int r, int g, int b);

private slots:
    void on_buttonBox_accepted();

    void on_redSlider_sliderMoved(int position);

    void on_greenSlider_sliderMoved(int position);

    void on_blueSlider_sliderMoved(int position);

    void on_colorComboBox_currentIndexChanged(int index);

    void on_DeleteButton_clicked();

    void on_radioStandard_clicked();

    void on_radioStart_clicked();

    void on_radioEnd_clicked();

private:
    Ui::Popup *ui;
    QList<QColor> colors;
    Node *caller;
    Workspace *workspace;
    QColor currentColor;
    QColor newColor;
    int selectedNodeType;

    void fillColours();
    void setSliders(QColor currentColor);
    void setWorkspace( Workspace* );
};

#endif // POPUP_H
