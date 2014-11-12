#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "workspace.h"
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QListWidgetItem>
#include <QMouseEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Insert items to AlgorithmsList from code:
    QListWidgetItem *itm = new QListWidgetItem;
    itm->setText("Algorithm 1");
    ui->algorithmsList->addItem(itm);

    this->workspace = new Workspace( this, ui->graphicsView );
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

void MainWindow::on_nextButton_clicked()
{
    // Some test messagebox for the nextButton
     QMessageBox msgBox;
     msgBox.setText("nextButton works");
     msgBox.setStandardButtons(QMessageBox::Cancel);
     msgBox.setDefaultButton(QMessageBox::Cancel);
     msgBox.exec();
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
