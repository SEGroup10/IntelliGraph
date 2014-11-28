#include "popupedge.h"


PopupEdge::PopupEdge(QWidget *parent, Edge *_caller, Workspace *workspace ) :
    QDialog(parent),
    ui(new Ui::PopupEdge)
{
    ui->setupUi(this);
    this->setCaller( _caller );
    this->setLabelLeft( _caller->getBeginNode()->getLabel() );
    this->setLabelRight( _caller->getEndNode()->getLabel() );
    this->setWeightLeftToRight( _caller->getLabel(true) );
    this->setCheckedLeftToRight( true );
    if( _caller->getBidirectional() ) {
        this->setWeightRightToLeft( _caller->getLabel(false) );
        this->setCheckedRightToLeft( true );
    } else {
        this->setCheckedRightToLeft( false );
    }
    this->setWorkspace(workspace);
    this->setFixedSize(499, 398);

}

PopupEdge::~PopupEdge()
{
    delete ui;
}

void PopupEdge::setLabelLeft( string label )
{
    ui->leftNodeLabel->setText( QString::fromStdString(label) );
}

void PopupEdge::setLabelRight( string label )
{
    ui->rightNodeLabel->setText( QString::fromStdString(label) );
}

void PopupEdge::setWeightLeftToRight( string label )
{
    ui->leftToRightWeight->setText( QString::fromStdString(label) );
}

void PopupEdge::setWeightRightToLeft( string label )
{
    ui->rightToLeftWeight->setText( QString::fromStdString(label) );
}

void PopupEdge::setCheckedLeftToRight( bool check )
{
    ui->leftToRightCheckbox->setChecked( check );
}

void PopupEdge::setCheckedRightToLeft( bool check )
{
    ui->rightToLeftCheckbox->setChecked( check );
}

string PopupEdge::getWeightLeftToRight()
{
    return ui->leftToRightWeight->text().toStdString();
}

string PopupEdge::getWeightRightToLeft()
{
    return ui->rightToLeftWeight->text().toStdString();
}

bool PopupEdge::getCheckedLeftToRight()
{
    return ui->leftToRightCheckbox->isChecked();
}

bool PopupEdge::getCheckedRightToLeft()
{
    return ui->rightToLeftCheckbox->isChecked();
}

void PopupEdge::on_buttonBox_accepted() {
    if( !this->getCheckedLeftToRight() && !this->getCheckedRightToLeft() ) {
        //Neither edge is checked. This means that this edge no longer exists

        workspace->deleteEdge( caller );
    } else if( !this->getCheckedLeftToRight() ) {
        //The edge left to right must be deleted, and the other edge exists.
        //This means that we have to delete the current edge, then need to make a
        //new edge from right to left as primary
        Node *begin = caller->getBeginNode();
        Node *end = caller->getEndNode();
        string weight;
        if( this->getWeightRightToLeft().length() == 0 ) {
            weight = caller->getLabel( false );
        } else {
            weight = this->getWeightRightToLeft();
        }

        workspace->deleteEdge( caller );

        Edge *newEdge = workspace->addEdge( end, begin );
        newEdge->setLabel( weight, true );
    } else {
        //Left to right must be checked

        if( this->getWeightLeftToRight().length() > 0 ) {
            this->caller->setLabel(this->getWeightLeftToRight(),true);
        }

        if( this->getCheckedRightToLeft() && this->getWeightRightToLeft().length() > 0 ) {
            //Optionally set the weight of the other way too.
            this->caller->setBidirectional(true);
            this->caller->setLabel(this->getWeightRightToLeft(),false);
        }
    }
}

void PopupEdge::setCaller(Edge *_caller) {
    caller = _caller;
}

void PopupEdge::on_buttonBox_rejected()
{

}

void PopupEdge::setWorkspace( Workspace *workspace )
{
    this->workspace = workspace;
}

void PopupEdge::on_DeleteEdge_clicked()
{
    workspace->deleteEdge( this->caller );
}
