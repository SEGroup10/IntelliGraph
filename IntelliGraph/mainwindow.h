#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public slots:
    void on_nextButton_clicked();
    void on_exportButton_clicked();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;

    QGraphicsRectItem *rectangle;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
