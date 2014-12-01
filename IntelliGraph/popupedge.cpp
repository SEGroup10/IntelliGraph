#include "popupedge.h"


PopupEdge::PopupEdge(QWidget *parent, Edge *_caller, Workspace *workspace ) :
    QDialog(parent),
    ui(new Ui::PopupEdge)
{
    ui->setupUi(this);
    this->setCaller( _caller );
    this->setLabelLeft( _caller->getBeginNode()->getLabel() );
    this->setLabelRight( _caller->getEndNode()->getLabel() );
    this->setWeightLeftToRight( _caller->getWeightAsString(true) );
    this->setCheckedLeftToRight( true );
    if( _caller->getBidirectional() ) {
        this->setWeightRightToLeft( _caller->getWeightAsString(false) );
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
            weight = caller->getWeightAsString( false );
        } else {
            weight = this->getWeightRightToLeft();
        }

        workspace->deleteEdge( caller );

        Edge *newEdge = workspace->addEdge( end, begin );
        newEdge->setWeight( weight, true );
    } else {
        //Left to right must be checked

        if( this->getWeightLeftToRight().length() > 0 ) {
            this->caller->setWeight(this->getWeightLeftToRight(),true);
        }

        if( this->getCheckedRightToLeft() && this->getWeightRightToLeft().length() > 0 ) {
            //Optionally set the weight of the other way too.
            this->caller->setBidirectional(true);
            this->caller->setWeight(this->getWeightRightToLeft(),false);
        } else if( !this->getCheckedRightToLeft() ){
            this->caller->setBidirectional(false);
            this->caller->setWeight(0,false);
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
    workspace->deleteEdge( caller );
}

void PopupEdge::on_leftToRightWeight_textChanged(const QString &arg1)
{
    if(!is_number(arg1.toStdString())){
        int oldcursorpos = ui->leftToRightWeight->cursorPosition();
        ui->leftToRightWeight->setText( QString::fromStdString(this->onlyNumbers( arg1.toStdString() )) );
        ui->leftToRightWeight->setCursorPosition(oldcursorpos - 1);
    }
}

void PopupEdge::on_rightToLeftWeight_textChanged(const QString &arg1)
{
    if(!is_number(arg1.toStdString())){
        int oldcursorpos = ui->rightToLeftWeight->cursorPosition();
        ui->rightToLeftWeight->setText( QString::fromStdString(this->onlyNumbers( arg1.toStdString() )) );
        ui->rightToLeftWeight->setCursorPosition(oldcursorpos - 1);
    }
}

/* Filters out all characters that we do not expect
 * in a number. Works mostly the same as is_number, but
 * outputs a string that is a number
 */
string PopupEdge::onlyNumbers( const std::string& input ) {
  std::string::const_iterator it = input.begin();
  string output = "";
  bool foundcomma = false;
  if( it != input.end() && *it == '-' ) {
    output += "-";
    it++;
  }

  while (it != input.end()) {
    if( std::isdigit(*it) ) {
      output += *it;
    } else if( *it == '.' && !foundcomma ) {
      output += *it;
      foundcomma = true;
    }
    it++;
  }
  return output;
}


/* Returns true if the string is in the form of
 * regex -?[0-9]*.?[0-9]*
 * Special cases: -. -> 0, -1. -> -1, -.1 -> -0.1
 * This is correct behaviour
 */
bool PopupEdge::is_number(const std::string& s)
{
    bool foundcomma = false;
    std::string::const_iterator it = s.begin();

    //Support for negative numbers
    if( it != s.end() && *it == '-' ) ++it;

    //If we encounter a non-digit this is not a number
    while (it != s.end() ) {
      if( !foundcomma && *it == '.' ) {
        foundcomma = true;
      } else if( !std::isdigit(*it) ) {
        break;
      }
      it++;
    }
    return !s.empty() && it == s.end();
}
