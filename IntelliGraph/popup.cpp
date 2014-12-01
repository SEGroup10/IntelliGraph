#include "popup.h"


Popup::Popup(QWidget *parent, Node *_caller, Workspace *workspace) :
    QDialog(parent),
    ui(new Ui::Popup)
{
    ui->setupUi(this);
    this->setCaller(_caller);
    this->setLabel(caller->getLabel());
    this->fillColours();
    this->setSliders( caller->getColour() );
    this->setWindowFlags(Qt::Tool);
    this->setWorkspace( workspace );

    this->selectedNodeType = -1;

    if( this->caller->getType() == NodeType::STANDARD ) {
        selectedNodeType = 0;
        ui->radioStandard->setChecked(true);
    } else if( this->caller->getType() == NodeType::START ) {
        selectedNodeType = 1;
        ui->radioStart->setChecked(true);
    } else if( this->caller->getType() == NodeType::END ) {
        selectedNodeType = 2;
        ui->radioEnd->setChecked(true);
    }

    ui->labelTextbox->selectAll();
    ui->labelTextbox->setFocus();
}

Popup::~Popup()
{
    delete ui;
}

void Popup::setLabel(string label) {
    ui->labelTextbox->setText( QString::fromStdString(label) );
}

void Popup::fillColours() {
    ui->colorComboBox->addItem("");
    foreach (QString clr, QColor::colorNames()) {
        colors.append(clr);
        ui->colorComboBox->addItem(clr);
    }
}

void Popup::setSliders( QColor currentColor ) {
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
}

void Popup::on_buttonBox_accepted() {
    if (ui->labelTextbox->text().size() != 0) {
        this->caller->setLabel(ui->labelTextbox->text().toStdString());
    }

    //Since some of these will change the node colour, we need to do this
    //before setting the colour
    if(ui->radioEnd->isChecked()){
        workspace->setnode( this->caller,NodeType::END);
    } else if(ui->radioStandard->isChecked()) {
        workspace->setnode(this->caller,NodeType::STANDARD);
    } else if(ui->radioStart->isChecked()) {
       workspace->setnode(this->caller,NodeType::START);
    }

    if (ui->colorComboBox->currentIndex() != 0) {
        QColor selected = colors[ui->colorComboBox->currentIndex() - 1];
        this->caller->setColour(selected);
    } else {
        this->caller->setColour(newColor);
    }
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
        setSliders( selected );
    }
}

void Popup::setWorkspace( Workspace *workspace )
{
    this->workspace = workspace;
}

void Popup::on_DeleteButton_clicked()
{
    workspace->deleteNode(this->caller);
}

void Popup::on_radioStandard_clicked()
{
    if( selectedNodeType == 1 ) {
        //If used to be start node and didn't change colour
        if( newColor.red() == 0 && newColor.green() == 255 && newColor.blue() == 0 ) {
            setSliders( QColor(255,255,255) );
        }
    } else if( selectedNodeType == 2 ) {
        //If used to be end node and didn't change colour
        if( newColor.red() == 255 && newColor.green() == 0 && newColor.blue() == 0 ) {
            setSliders( QColor(255,255,255) );
        }
    }

    selectedNodeType = 0;
}

void Popup::on_radioStart_clicked()
{
  if( selectedNodeType == 0 ) {
      //If used to be standard node and didn't change colour
      if( newColor.red() == 255 && newColor.green() == 255 && newColor.blue() == 255 ) {
          setSliders( QColor(0,255,0) );
      }
  } else if( selectedNodeType == 2 ) {
      //If used to be end node and didn't change colour
      if( newColor.red() == 255 && newColor.green() == 0 && newColor.blue() == 0 ) {
          setSliders( QColor(0,255,0) );
      }
  }

  selectedNodeType = 1;
}

void Popup::on_radioEnd_clicked()
{
  if( selectedNodeType == 0 ) {
      //If used to be standard node and didn't change colour
      if( newColor.red() == 255 && newColor.green() == 255 && newColor.blue() == 255 ) {
          setSliders( QColor(255,0,0) );
      }
  } else if( selectedNodeType == 1 ) {
      //If used to be start node and didn't change colour
      if( newColor.red() == 0 && newColor.green() == 255 && newColor.blue() == 0 ) {
          setSliders( QColor(255,0,0) );
      }
  }

  selectedNodeType = 2;
}
