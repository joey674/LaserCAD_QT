#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include <QInputDialog>
#include <QFontDialog>
#include <QKeyEvent>
#include <QColorDialog>
#include <QTime>
#include <QString>

///
/// \brief MainWindow::MainWindow
/// \param parent
///
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showMaximized();

    setGraphicsView();
    setStatusBar();
}
MainWindow::~MainWindow()
{
    delete ui;
}

///
/// \brief MainWindow::setGraphicsView
///
void MainWindow::setGraphicsView() {
    this->Scene=new QGraphicsScene();
    ui->graphicsView->setScene(Scene);

    // add axis
    QPen pen(Qt::red);
    pen.setWidth(1);

    QGraphicsLineItem *xAxis=new QGraphicsLineItem(-100,0,100,0);
    QGraphicsLineItem *yAxis=new QGraphicsLineItem(0,-100,0,100);
    xAxis->setPen(pen);
    xAxis->setPos(0,0);
    yAxis->setPen(pen);
    yAxis->setPos(0,0);
    Scene->addItem(xAxis);
    Scene->addItem(yAxis);

    QGraphicsLineItem *xArrowL=new QGraphicsLineItem(90,10,100,0);
    QGraphicsLineItem *xArrowR=new QGraphicsLineItem(90,-10,100,0);
    xArrowL->setPen(pen);
    xArrowR->setPen(pen);
    Scene->addItem(xArrowL);
    Scene->addItem(xArrowR);

    QGraphicsLineItem *yArrowL=new QGraphicsLineItem(10,90,0,100);
    QGraphicsLineItem *yArrowR=new QGraphicsLineItem(-10,90,0,100);
    yArrowL->setPen(pen);
    yArrowR->setPen(pen);
    Scene->addItem(yArrowL);
    Scene->addItem(yArrowR);

    // connect
    // graphicsview组件触发鼠标移动时,会通知mainwindow组件;
    connect(ui->graphicsView,SIGNAL(mouseMove(QPoint)),
            this,SLOT(on_graphicsview_mousemove_triggered(QPoint)));

}

///
/// \brief MainWindow::setStatusBar
///
void MainWindow::setStatusBar() {
    this->LabelMouseCoordinate = new QLabel("coordinate:");
    this->LabelMouseCoordinate->setMinimumWidth(150);
    ui->statusBar->addWidget(this->LabelMouseCoordinate);
}

void MainWindow::on_graphicsview_mousemove_triggered(QPoint point)
{
    QPointF sceneCoordinate = ui->graphicsView->mapToScene(point);
    this->LabelMouseCoordinate->setText(
        QString::asprintf(
            "coordinate:x:%.0f,y:%.0f",
            sceneCoordinate.x(),
            sceneCoordinate.y()
        )
    );
}

///
/// \brief MainWindow::on_drawLineButton_clicked
///
void MainWindow::on_drawLineButton_clicked()
{
    qDebug() << "drawline button click";
}



