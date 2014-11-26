#include "popup.h"


Popup::Popup(QWidget *parent, Node *_caller) :
    QDialog(parent),
    ui(new Ui::Popup)
{
    ui->setupUi(this);
    this->setCaller(_caller);
    this->setFixedSize(382, 250);
    this->fillColours();
    this->setSliders();
}

Popup::~Popup()
{
    delete ui;
}

void Popup::setLabel(string label) {
    //QString qlabel = QString::fromStdString(label);
    //ui->label->setText(qlabel);
    ui->labelTextbox->setPlainText( QString::fromStdString(label) );
}

void Popup::fillColours() {
    ui->colorComboBox->addItem("");
    foreach (QString clr, QColor::colorNames()) {
        colors.append(clr);
        ui->colorComboBox->addItem(clr);
    }
}

void Popup::setSliders() {
    currentColor = caller->getColour();
    ui->colourPreview->setStyleSheet("QLabel { background-color : rgb(" +
                                     QString::number(currentColor.red()) + ", " +
                                     QString::number(currentColor.green()) + ", " +
                                     QString::number(currentColor.blue()) + ");}");
    ui->redSlider->setMinimum(0);
    ui->redSlider->setMaximum(255);

    ui->greenSlider->setMinimum(0);
    ui->greenSlider->setMaximum(255);
    ui->greenSlider->setValue(currentColor.green());

    ui->blueSlider->setMinimum(0);
    ui->blueSlider->setMaximum(255);
    ui->blueSlider->setValue(currentColor.blue());
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
