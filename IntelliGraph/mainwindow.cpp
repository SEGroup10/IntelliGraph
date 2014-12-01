#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "workspace.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->workspace = new Workspace( this, ui->graphicsView);
    this->algorithm = new AlgorithmEngine(this->workspace, ui->nextButton, qApp->applicationDirPath());

    // Load algorithmList
    refreshAlgorithms();

    // disable next button
    ui->nextButton->setDisabled(true);
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

    // prevent errors when no algorithms found
    if (alg_list.count() == 0) {
        ui->pushButton->setDisabled(true);
    } else {
        ui->pushButton->setDisabled(false);
    }

    // Insert items to AlgorithmsList from code:
    for(int i = 0; i < alg_list.count(); i++)
    {
        ui->algorithmsList->addItem(alg_list.at(i));
    }
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

/*void MainWindow::on_item_clicked(QListWidgetItem* item)
{
    // load algorithm in algorithms/item->text();
    qDebug() << item->statusTip();
}*/

void MainWindow::on_refreshButton_clicked()
{
    qDebug() << "refresh";
    refreshAlgorithms();
}

void MainWindow::on_nextButton_clicked()
{
    qDebug() << "form next";
    algorithm->next();
    /*QScriptValue next = this->algorithm.property("next");
    qDebug() << this->algorithm.call(next, QScriptValueList()).toString();*/
    //workspace->handleNext();
}

void MainWindow::on_modeButton_clicked()
{
    workspace->clearSelection();
    if (workspace->getMode() == Workspace::selectMode) {
        workspace->setMode(Workspace::edgeMode);
        ui->modeButton->setText(QString("Edge Mode"));
        foreach(Node* i, workspace->getNodes())
            i->setFlag(QGraphicsItem::ItemIsMovable, false);
    } else if (workspace->getMode() == Workspace::edgeMode) {
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

void MainWindow::on_pushButton_clicked()
{
    //workspace->test();
    QListWidgetItem *itm = ui->algorithmsList->selectedItems().at(0);
    if (ui->pushButton->text() == QString("Start")) {
        qDebug() << "start algorithm: " << itm->statusTip();
        workspace->startAlgorithm();
        algorithm->init(itm->statusTip());
        /*QString path = qApp->applicationDirPath().append("/algorithms/").append(itm->statusTip());
        qDebug() << "full path: " << path;
        QFile alg_file(path);
        qDebug() << "able to read file? " << alg_file.open(QIODevice::ReadOnly);
        QScriptValue obj = engine->evaluate(alg_file.readAll());
        alg_file.close();
        this->algorithm = obj.property("algorithm");*/
        ui->nextButton->setDisabled(false);
        ui->pushButton->setText(QString("Stop"));
    } else {
        qDebug() << "stopping algorithm";
        workspace->stopAlgorithm();
        algorithm->stop();
        ui->nextButton->setDisabled(true);
        ui->pushButton->setText(QString("Start"));
    }
}
