#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "workspace.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->workspace = new Workspace( this, ui->graphicsView);
    this->algorithm = new AlgorithmEngine(this->workspace, qApp->applicationDirPath());
    this->selectedAlgorithmItem = NULL;

    // Load algorithmList
    refreshAlgorithms();

    // disable buttons
    ui->nextButton->setDisabled(true);
    ui->prevButton->setDisabled(true);
    ui->startStopButton->setDisabled(true);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete workspace;
}

void MainWindow::refreshAlgorithms()
{
    ui->algorithmsList->clear();

    // Search for algorithm files

    QList<QListWidgetItem*> alg_list = this->algorithm->getAlgorithms();

    // Insert items to AlgorithmsList from code:
    for(int i = 0; i < alg_list.count(); i++)
    {
        ui->algorithmsList->addItem(alg_list.at(i));
    }
}


/* This function handles the ui-related things for a mode change then passes
 * the request to the workspace.
 */
void MainWindow::setMode( Workspace::Mode newmode ) {
    ui->modeButton->setDisabled(false);
    ui->nextButton->setDisabled(true);
    ui->prevButton->setDisabled(true);

    if( newmode == Workspace::selectMode ) {

    } else if( newmode == Workspace::edgeMode ) {

    } else if( newmode == Workspace::algorithmMode ) {
        ui->modeButton->setDisabled(true);
        ui->nextButton->setDisabled(false);
    } else {
        Q_ASSERT_X( false, "MainWindow::setMode", "unhandled mode!");
    }

    //Do workspace-related things with a mode change
    this->workspace->setMode( newmode );
}

Workspace::Mode MainWindow::getMode() {
    return this->workspace->getMode();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if( (event->x() >= ui->graphicsView->x()) &&
        (event->x() <= (ui->graphicsView->x() + ui->graphicsView->width())) &&
        (event->y() >= ui->graphicsView->y()) &&
        (event->y() <= (ui->graphicsView->y() + ui->graphicsView->height()))) {
        workspace->handleClick( event );

    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    workspace->handleResize();
}

void MainWindow::on_importButton_clicked()
{
    QFile sourceFile(QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("Files (*.alg)")));
    QFileInfo fileInfo(sourceFile.fileName());
    QString destination("algorithms/" + fileInfo.fileName());
    QFile destinationFile(destination);

    qDebug() << sourceFile.fileName();
    qDebug() << destination;

    if(sourceFile.fileName() != "")
    {
        if(destinationFile.exists())
        {
            QMessageBox::StandardButton choiceDialog;
            choiceDialog = QMessageBox::question(this, "Warning", "Algorithm already exists, overwrite?",QMessageBox::Yes|QMessageBox::No);

            if (choiceDialog == QMessageBox::Yes)
            {
                destinationFile.remove();
                sourceFile.copy(destination);
            }
        }
        else
        {
          sourceFile.copy(destination);
        }
    }

    refreshAlgorithms();
}

void MainWindow::on_nextButton_clicked()
{
    if (algorithm->next()) {
        ui->prevButton->setDisabled(false);
    } else {
        qDebug() << "failed to select next state";
        ui->nextButton->setDisabled(true);
    }
}

void MainWindow::on_modeButton_clicked()
{
    workspace->clearSelection();
    if (this->getMode() == Workspace::selectMode) {
        this->setMode(Workspace::edgeMode);
        ui->modeButton->setText(QString("Edge Mode"));
    } else {
        this->setMode(Workspace::selectMode);
        ui->modeButton->setText(QString("Select Mode"));
    }
}

void MainWindow::on_exportButton_clicked()
{
    workspace->exportGraph();
}

void MainWindow::on_startStopButton_clicked()
{
    Q_ASSERT_X( ui->algorithmsList->selectedItems().length() == 1, "MainWndow::on_startStopButton_clicked()", "Either 0 or more than 1 items have been selected");
    QListWidgetItem *itm = ui->algorithmsList->selectedItems().at(0);
    if (ui->startStopButton->text() == QString("Start")) {
        if (workspace->getEdges().length() > 0) {
            qDebug() << "start algorithm: " << itm->statusTip();
            savedMode = this->getMode();
            this->setMode(Workspace::algorithmMode);
            algorithm->init(itm->statusTip());
            ui->startStopButton->setText(QString("Stop"));
        } else {
            QMessageBox msgBox;
            msgBox.setText("At least 1 edge is required");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
        }
    } else {
        qDebug() << "stopping algorithm";
        this->setMode(savedMode);
        workspace->removeHighlight();
        ui->startStopButton->setText(QString("Start"));
    }
}

void MainWindow::on_algorithmsList_itemSelectionChanged()
{
    if( this->getMode() == Workspace::algorithmMode ) {
        //Prevent someone from deselecting or changing our algorithm during execution of an algorithm
        if( !(ui->algorithmsList->selectedItems().length() == 1) ||
            !(ui->algorithmsList->selectedItems().at(0) == selectedAlgorithmItem)) {
            ui->algorithmsList->setCurrentItem(selectedAlgorithmItem,QItemSelectionModel::SelectCurrent);
        }
    } else {
        if( ui->algorithmsList->selectedItems().length() == 1 ) {
            ui->startStopButton->setDisabled(false);
            this->selectedAlgorithmItem = ui->algorithmsList->selectedItems().at(0);
        } else {
            ui->startStopButton->setDisabled(true);
            this->selectedAlgorithmItem = NULL;
        }
    }
}

void MainWindow::on_prevButton_clicked()
{
    if (algorithm->previous()) {
        ui->nextButton->setDisabled(false);
    } else {
        qDebug() << "failed to select previous state";
        ui->prevButton->setDisabled(true);
    }

}
