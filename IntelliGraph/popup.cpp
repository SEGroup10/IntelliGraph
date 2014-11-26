#include "popup.h"


Popup::Popup(QWidget *parent, Node *_caller) :
    QDialog(parent),
    ui(new Ui::Popup)
{
    ui->setupUi(this);
    this->setCaller(_caller);
    //this->setFixedSize(382, 350);
    this->fillColours();
    this->setSliders();
    ui->labelTextbox->setStyleSheet("background-color: #ecf0f1");
    this->setWindowFlags(Qt::Tool);
}

Popup::~Popup()
{
    delete ui;
}

void Popup::setLabel(string label) {
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
    updateColour(currentColor.red(), currentColor.green(), currentColor.blue());

    ui->redSlider->setMinimum(0);
    ui->redSlider->setMaximum(255);
    ui->redSlider->setValue(currentColor.red());

    ui->greenSlider->setMinimum(0);
    ui->greenSlider->setMaximum(255);
    ui->greenSlider->setValue(currentColor.green());

    ui->blueSlider->setMinimum(0);
    ui->blueSlider->setMaximum(255);
    ui->blueSlider->setValue(currentColor.blue());

    ui->redSlider->setStyleSheet("QSlider { width: 40px }"
                                  "QSlider::groove:horizontal {"
                                  "border: 1px solid #999999;"
                                   "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #95a5a6, stop:1 #95a5a6);"
                                  "height: 50px;"
                                  "margin: 0 0 0 0;}"
                                  "QSlider::handle:horizontal {"
                                  "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #e74c3c, stop:1 #e74c3c);"
                                  "border: 1px solid #5c5c5c;"
                                  "width: 15px;"
                                  "margin: -5px 0 -5px 0;"
                                  "border-radius: 3px;}");

    ui->greenSlider->setStyleSheet("QSlider { width: 40px }"
                                  "QSlider::groove:horizontal {"
                                  "border: 1px solid #999999;"
                                   "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #95a5a6, stop:1 #95a5a6);"
                                  "height: 50px;"
                                  "margin: 0 0 0 0;}"
                                  "QSlider::handle:horizontal {"
                                  "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #16a085, stop:1 #16a085);"
                                  "border: 1px solid #5c5c5c;"
                                  "width: 15px;"
                                  "margin: -5px 0 -5px 0;"
                                  "border-radius: 3px;}");

    ui->blueSlider->setStyleSheet("QSlider { width: 40px }"
                                  "QSlider::groove:horizontal {"
                                  "border: 1px solid #999999;"
                                   "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #95a5a6, stop:1 #95a5a6);"
                                  "height: 50px;"
                                  "margin: 0 0 0 0;}"
                                  "QSlider::handle:horizontal {"
                                  "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #2980b9, stop:1 #2980b9);"
                                  "border: 1px solid #5c5c5c;"
                                  "width: 15px;"
                                  "margin: -5px 0 -5px 0;"
                                  "border-radius: 3px;}");
}

void Popup::on_buttonBox_accepted() {
    if (ui->labelTextbox->toPlainText().size() != 0) {
        this->caller->setLabel(ui->labelTextbox->toPlainText().toStdString());
    }

    if (ui->colorComboBox->currentIndex() != 0) {
        QColor selected = colors[ui->colorComboBox->currentIndex() - 1];
        this->caller->setColour(selected);
    }
    else
        this->caller->setColour(newColor);

}

void Popup::updateColour(int r, int g, int b) {
    ui->colourPreview->setStyleSheet("QLabel { background-color : rgb(" +
                                     QString::number(r) + ", " +
                                     QString::number(g) + ", " +
                                     QString::number(b) + ");}");
    newColor = QColor(r, g, b);
}

void Popup::setCaller(Node *_caller) {
    caller = _caller;
}

void Popup::on_redSlider_sliderMoved(int position) {
    updateColour(position, newColor.green(), newColor.blue());
}

void Popup::on_greenSlider_sliderMoved(int position) {
    updateColour(newColor.red(), position, newColor.blue());
}

void Popup::on_blueSlider_sliderMoved(int position) {
    updateColour(newColor.red(), newColor.green(), position);
}

void Popup::on_colorComboBox_currentIndexChanged(int index) {
    if (index != 0) {
        QColor selected = (colors[ui->colorComboBox->currentIndex() - 1]);
        updateColour(selected.red(), selected.green(), selected.blue());
    }
}
