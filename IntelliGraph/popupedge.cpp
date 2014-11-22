#include "popupedge.h"


PopupEdge::PopupEdge(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PopupEdge)
{
    ui->setupUi(this);
    this->setFixedSize(382, 180);

}

PopupEdge::~PopupEdge()
{
    delete ui;
}

void PopupEdge::setLabel(string label) {
    //QString qlabel = QString::fromStdString(label);
    //ui->label->setText(qlabel);
    ui->labelTextbox->setPlainText( QString::fromStdString(label) );
}

void PopupEdge::on_buttonBox_accepted() {
    if (ui->labelTextbox->toPlainText().size() != 0) {
        this->caller->setLabel(ui->labelTextbox->toPlainText().toStdString());
    }
}

void PopupEdge::setCaller(Edge *_caller) {
    caller = _caller;
}

void PopupEdge::on_buttonBox_rejected()
{

}
