#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "workspace.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Load algorithmList
    refreshAlgorithms();

    // Connect AlgorithmList signal to slot
    connect(ui->algorithmsList, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(on_item_clicked(QListWidgetItem*)));

    this->workspace = new Workspace( this, ui->graphicsView);
    this->engine = new QScriptEngine();

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
    QStringList nameFilter("*.alg");
    QDir directory("algorithms");
    QStringList fileList = directory.entryList(nameFilter);

    // Insert items to AlgorithmsList from code:
    for(int i = 0; i < fileList.count(); i++)
    {
        QListWidgetItem *itm = new QListWidgetItem;
        QString file = fileList.at(i);
        itm->setText(file.mid(0, file.length() - 4));
        itm->setStatusTip(file);
        ui->algorithmsList->addItem(itm);
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

void MainWindow::on_item_clicked(QListWidgetItem* item)
{
    // load algorithm in algorithms/item->text();
    qDebug() << item->statusTip();
}

void MainWindow::on_refreshButton_clicked()
{
    qDebug() << "refresh";
    refreshAlgorithms();
}

void MainWindow::on_nextButton_clicked()
{
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
        QFile alg_file(QString("algorithms").append(itm->statusTip()));
        qDebug() << "able to read file? " << alg_file.open(QIODevice::ReadOnly);
        engine->evaluate(alg_file.readAll());
        alg_file.close();
        ui->nextButton->setDisabled(false);
        ui->pushButton->setText(QString("Stop"));
    } else {
        workspace->stopAlgorithm();
        ui->nextButton->setDisabled(true);
        ui->pushButton->setText(QString("Start"));
    }
}
