#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLabel>
#include "graphicsview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setGraphicsView();
    void setStatusBar();

private slots:
    void on_graphicsview_mousemove_triggered(QPoint);
    // void on_graphicsview_mouseLeftClick_triggered(QPoint);
    // void on_graphicsview_mouseRightClick_triggered(QPoint);
    void on_drawLineButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *Scene;

    QLabel *LabelMouseCoordinate;

};
#endif // MAINWINDOW_H

