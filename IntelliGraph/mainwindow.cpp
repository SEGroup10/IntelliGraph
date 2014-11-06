#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QListWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Insert items to AlgorithmsList from code:
    QListWidgetItem *itm = new QListWidgetItem;
    itm->setText("Algorithm 1");
    ui->algorithmsList->addItem(itm);

    // We need a Scene on the GraphicsView to draw shapes
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    // As a test we draw a purple circle.
    QBrush purpleBrush(QColor(102, 0, 102));
    QPen blackPen(Qt::black);

    blackPen.setWidth(2);

    // Here we add the circle to the scene
    ellipse = scene->addEllipse(10, 10, 100, 100, blackPen, purpleBrush);

    // And make it movable
    ellipse->setFlag(QGraphicsItem::ItemIsMovable);
}

MainWindow::~MainWindow()
{
    delete ui;
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
