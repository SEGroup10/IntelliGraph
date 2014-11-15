#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "workspace.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public slots:
        void on_nextButton_clicked();
        void on_exportButton_clicked();
        void on_testLinks_clicked();
        void on_selectButton_clicked();
        void on_edgeButton_clicked();

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

        void mousePressEvent(QMouseEvent *event);
    private:
        Ui::MainWindow *ui;
        Workspace *workspace;
};

#endif // MAINWINDOW_H
