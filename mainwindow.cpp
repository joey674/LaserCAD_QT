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

    initGraphicsView();
    initTreeWidget();
    initStatusBar();
}
MainWindow::~MainWindow()
{
    delete ui;
}

///
/// \brief MainWindow::initGraphicsView
///
void MainWindow::initGraphicsView() {
    this->Scene=new QGraphicsScene();
    ui->graphicsView->setScene(this->Scene);

    // add axis
    QPen pen(Qt::red);
    pen.setWidth(1);

    QGraphicsLineItem *xAxis=new QGraphicsLineItem(-100,0,100,0);
    QGraphicsLineItem *yAxis=new QGraphicsLineItem(0,-100,0,100);
    xAxis->setPen(pen);
    xAxis->setPos(0,0);
    yAxis->setPen(pen);
    yAxis->setPos(0,0);
    this->Scene->addItem(xAxis);
    this->Scene->addItem(yAxis);

    QGraphicsLineItem *xArrowL=new QGraphicsLineItem(90,10,100,0);
    QGraphicsLineItem *xArrowR=new QGraphicsLineItem(90,-10,100,0);
    xArrowL->setPen(pen);
    xArrowR->setPen(pen);
    this->Scene->addItem(xArrowL);
    this->Scene->addItem(xArrowR);

    QGraphicsLineItem *yArrowL=new QGraphicsLineItem(10,90,0,100);
    QGraphicsLineItem *yArrowR=new QGraphicsLineItem(-10,90,0,100);
    yArrowL->setPen(pen);
    yArrowR->setPen(pen);
    this->Scene->addItem(yArrowL);
    this->Scene->addItem(yArrowR);

    //
    ui->graphicsView->scale(1.5,1.5);
    this->Scene->setSceneRect(Scene->sceneRect()); // 锁定当前场景矩形



    // connect
    // graphicsview组件触发鼠标移动时,会通知mainwindow组件;
    connect(ui->graphicsView,SIGNAL(mousemove_event(QPoint)),
            this,SLOT(on_graphicsview_mousemove_occurred(QPoint)));
    connect(ui->graphicsView,SIGNAL(mouseleftclick_event(QPoint)),
            this,SLOT(on_graphicsview_mouseleftclick_occurred(QPoint)));
    connect(ui->graphicsView,SIGNAL(mouserightclick_event(QPoint)),
            this,SLOT(on_graphicsview_mouserightclick_occurred(QPoint)));
}

void MainWindow::initStatusBar() {
    this->LabelMouseCoordinate = new QLabel("coordinate: ");
    this->LabelMouseCoordinate->setMinimumWidth(150);
    ui->statusBar->addWidget(this->LabelMouseCoordinate);
    this->LabelOperation = new QLabel("operation: ");
    this->LabelOperation->setMinimumWidth(300);
    ui->statusBar->addWidget(this->LabelOperation);
}

void MainWindow::initTreeWidget()
{
    ui->treeWidget->setHeaderLabel("Operation List");

    QTreeWidgetItem *parentItem1 = new QTreeWidgetItem(ui->treeWidget, QStringList("Parent1"));
    QTreeWidgetItem *childItem1 = new QTreeWidgetItem(parentItem1, QStringList("Child1"));
    ui->treeWidget->addTopLevelItem(parentItem1);
    QTreeWidgetItem *parentItem2 = new QTreeWidgetItem(ui->treeWidget, QStringList("Parent1"));
    QTreeWidgetItem *childItem2 = new QTreeWidgetItem(parentItem2, QStringList("Child2"));
    ui->treeWidget->addTopLevelItem(parentItem2);
}

void MainWindow::displayOperation(QString text)
{
    this->LabelOperation->setText("operation: "+ text);
}


///
/// \brief MainWindow::resetDrawToolStatus
///
void MainWindow::resetDrawToolStatus()
{
    this->CurrentDrawTool = DrawToolType::None;
}

void MainWindow::drawLine(QPointF pointCoordScene,DrawEventType event)
{
    if (!this->TmpLine && event == DrawEventType::LeftClick) {
        TmpLine = std::make_unique<QGraphicsLineItem>(QLineF(pointCoordScene, pointCoordScene));
        TmpLine->setPen(QPen(Qt::black, 1));
        Scene->addItem(TmpLine.get());
    } else if  (this->TmpLine && event == DrawEventType::MouseMove){
        QLineF newLine(this->TmpLine->line().p1(), pointCoordScene);
        this->TmpLine->setLine(newLine);
    } else if (this->TmpLine && event == DrawEventType::LeftClick) {
        QLineF newLine(this->TmpLine->line().p1(), pointCoordScene);
        this->TmpLine->setLine(newLine);
        Container.push_back(std::move(TmpLine));
    }
}

void MainWindow::drawCircle(QPointF pointCoordScene,DrawEventType event)
{

}

///
/// \brief MainWindow::on_graphicsview_mouse_move_triggered
/// \param point
///
void MainWindow::on_graphicsview_mousemove_occurred(QPoint pointCoordView)
{
    QPointF pointCoordScene = ui->graphicsView->mapToScene(pointCoordView);

    // 显示坐标在statusbar里
    this->LabelMouseCoordinate->setText(
        QString::asprintf(
            "coordinate: x:%.0f,y:%.0f",
            pointCoordScene.x(),
            pointCoordScene.y()
        )
    );

    // 绘制控制
    switch (this->CurrentDrawTool) {
    case DrawToolType::None:{
        break;
    }
    case DrawToolType::Line:{
        this->drawLine(pointCoordScene,DrawEventType::MouseMove);
        break;
    }
    case DrawToolType::Circle:{
        this->drawCircle(pointCoordScene,DrawEventType::MouseMove);
        break;
    }
    }
}

void MainWindow::on_graphicsview_mouseleftclick_occurred(QPoint pointCoordView)
{
    displayOperation("left click");
    QPointF pointCoordScene = ui->graphicsView->mapToScene(pointCoordView);
    switch (this->CurrentDrawTool) {
        case DrawToolType::None:{
            QGraphicsItem *item = NULL;
            item = this->Scene->itemAt(pointCoordScene,ui->graphicsView->transform());
            if (item != NULL) {
                QString itemType = QString::number(item->type());
                QPointF itemCoord = item->scenePos();
                QString message = QString("Click on item type: %1, coordinate: x=%2, y=%3")
                                      .arg(itemType)
                                      .arg(itemCoord.x())
                                      .arg(itemCoord.y());
                displayOperation(message);
            }
            break;
        }
        case DrawToolType::Line:{
            this->drawLine(pointCoordScene,DrawEventType::LeftClick);
            break;
        }
        case DrawToolType::Circle:{
            this->drawCircle(pointCoordScene,DrawEventType::LeftClick);
            break;
        }
    }

}

void MainWindow::on_graphicsview_mouserightclick_occurred(QPoint)
{
    displayOperation("right click");
}

///
/// \brief MainWindow::on_drawLineButton_clicked
///
void MainWindow::on_drawLineButton_clicked()
{
    displayOperation("drawline button click");
    this->resetDrawToolStatus();
    this->CurrentDrawTool = DrawToolType::Line;
}

void MainWindow::on_drawCircleButton_clicked()
{
    displayOperation("drawcircle button click");
    this->resetDrawToolStatus();
    this->CurrentDrawTool = DrawToolType::Circle;
}

