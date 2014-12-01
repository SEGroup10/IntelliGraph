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
#include <QDebug>
#include "workspace.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public slots:
    void on_refreshButton_clicked();
    void on_nextButton_clicked();
    void on_exportButton_clicked();
    void on_modeButton_clicked();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void refreshAlgorithms();
    void mousePressEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Workspace *workspace;
};

#endif // MAINWINDOW_H
