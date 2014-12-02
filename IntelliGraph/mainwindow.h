#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QListWidgetItem>
#include <QDir>
#include <QFileDialog>
#include <QDebug>
#include "workspace.h"
#include "algorithmengine.h"

class Workspace;
class AlgorithmEngine;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public slots:
    void on_importButton_clicked();
    void on_nextButton_clicked();
    void on_exportButton_clicked();
    void on_modeButton_clicked();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setMode( Workspace::Mode );
    Workspace::Mode getMode();
    void refreshAlgorithms();
    void mousePressEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

private slots:
    void on_startStopButton_clicked();

    void on_algorithmsList_itemSelectionChanged();

private:
    Ui::MainWindow *ui;
    Workspace *workspace;
    AlgorithmEngine *algorithm;
    QListWidgetItem *selectedAlgorithmItem;
    Workspace::Mode savedMode;
};

#endif // MAINWINDOW_H
