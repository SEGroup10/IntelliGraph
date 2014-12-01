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
    explicit PopupEdge(QWidget *parent = 0, Edge *_caller = 0, Workspace *workspace = 0);
    ~PopupEdge();


private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_DeleteEdge_clicked();

    void on_leftToRightWeight_textChanged(const QString &arg1);

    void on_rightToLeftWeight_textChanged(const QString &arg1);

private:
    Ui::PopupEdge *ui;
    QList<QColor> colors;
    Edge *caller;
    Workspace *workspace;

    void setCaller(Edge* _caller);
    void setLabelLeft( string label );
    void setLabelRight( string label );
    void setWorkspace( Workspace *workspace );

    void setWeightLeftToRight( string label );
    void setWeightRightToLeft( string label );
    void setCheckedLeftToRight( bool check );
    void setCheckedRightToLeft( bool check );

    string getWeightLeftToRight();
    string getWeightRightToLeft();
    bool getCheckedLeftToRight();
    bool getCheckedRightToLeft();
    bool is_number(const std::string& s);
    string onlyNumbers( const std::string& );

};

#endif // POPUPEDGE_H
