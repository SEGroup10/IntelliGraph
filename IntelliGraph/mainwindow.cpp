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
        QString txt = QString("%1").arg(fileList.at(i));
        itm->setText(txt);
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
    qDebug() << item->text();
}

void MainWindow::on_refreshButton_clicked()
{
    qDebug() << "refresh";
    refreshAlgorithms();
}

void MainWindow::on_nextButton_clicked()
{
    workspace->handleNext();
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

void MainWindow::on_pushButton_clicked()
{
    workspace->test();
}
