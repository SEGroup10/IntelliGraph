#include "popup.h"


Popup::Popup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Popup)
{
    ui->setupUi(this);
    this->setWindowTitle("Node settings");
    this->fillColors();

}

Popup::~Popup()
{
    delete ui;
}

void Popup::setLabel(string label) {
    QString qlabel = QString::fromStdString(label);
    ui->label->setText(qlabel);
}

void Popup::fillColors() {
    ui->colorComboBox->addItem("");
    foreach (QString clr, QColor::colorNames()) {
        colors.append(clr);
        ui->colorComboBox->addItem(clr);
    }
}

void Popup::on_buttonBox_accepted() {
    if (ui->labelTextbox->toPlainText().size() != 0) {
        this->caller->setLabel(ui->labelTextbox->toPlainText().toStdString());
    }

    if (ui->colorComboBox->currentIndex() != 0) {
        QColor selected = colors[ui->colorComboBox->currentIndex() - 1];
        this->caller->setColour(selected);
    }

}

void Popup::setCaller(Node *_caller) {
    caller = _caller;
}
