#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "workspace.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Insert items to AlgorithmsList from code:
    QListWidgetItem *itm = new QListWidgetItem;
    itm->setText("Algorithm 1");
    ui->algorithmsList->addItem(itm);

    this->workspace = new Workspace( this, ui->graphicsView);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete workspace;
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

void MainWindow::on_nextButton_clicked()
{
    workspace->getNodes().at(0)->highlight(QColor(255, 0, 0));
    // Some test messagebox for the nextButton
     QMessageBox msgBox;
     msgBox.setText("nextButton works");
     msgBox.setStandardButtons(QMessageBox::Cancel);
     msgBox.setDefaultButton(QMessageBox::Cancel);
     msgBox.exec();
}

void MainWindow::on_modeButton_clicked()
{
    workspace->clearSelection();
    if (workspace->getMode() == Workspace::selectMode) {
        workspace->setMode(Workspace::edgeMode);
        ui->modeButton->setText(QString("Edge Mode"));
        foreach(Node* i, workspace->getNodes())
            i->setFlag(QGraphicsItem::ItemIsMovable, false);
    } else {
        workspace->setMode(Workspace::selectMode);
        ui->modeButton->setText(QString("Select Mode"));
        foreach(Node* i, workspace->getNodes())
            i->setFlag(QGraphicsItem::ItemIsMovable, true);
    }
}

void MainWindow::on_exportButton_clicked()
{
    // Some test messagebox for the exportButton
    QMessageBox msgBox;
    msgBox.setText("exportButton works");
    msgBox.setStandardButtons(QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBox.exec();
}

void MainWindow::on_testLinks_clicked()
{
    workspace->linkTest();
}
