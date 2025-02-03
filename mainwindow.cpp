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
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showMaximized();

    initGraphicsView();
    initOperationTreeWidget();
    initPropertyTableWidget();
    initStatusBar();
}
MainWindow::~MainWindow()
{
    delete ui;
}

///
/// \brief MainWindow::initGraphicsView
///
void MainWindow::initGraphicsView()
{
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

void MainWindow::initStatusBar()
{
    this->LabelMouseCoordinate = new QLabel("coordinate: ");
    this->LabelMouseCoordinate->setMinimumWidth(150);
    ui->statusBar->addWidget(this->LabelMouseCoordinate);
    this->LabelOperation = new QLabel("operation: ");
    this->LabelOperation->setMinimumWidth(300);
    ui->statusBar->addWidget(this->LabelOperation);
}

void MainWindow::initOperationTreeWidget()
{
    ui->operationTreeWidget->setHeaderLabel("Operation List");

    QTreeWidgetItem *parentItem1 = new QTreeWidgetItem(ui->operationTreeWidget, QStringList("Parent1"));
    QTreeWidgetItem *childItem1 = new QTreeWidgetItem(parentItem1, QStringList("Child1"));
    ui->operationTreeWidget->addTopLevelItem(parentItem1);
    QTreeWidgetItem *parentItem2 = new QTreeWidgetItem(ui->operationTreeWidget, QStringList("Parent1"));
    QTreeWidgetItem *childItem2 = new QTreeWidgetItem(parentItem2, QStringList("Child2"));
    ui->operationTreeWidget->addTopLevelItem(parentItem2);
}

void MainWindow::initPropertyTableWidget()
{
    ui->propertyTableWidget->setColumnCount(2);
    ui->propertyTableWidget->setHorizontalHeaderLabels(
        QStringList() << "property" << "value" );
}

void MainWindow::displayOperation(QString text)
{
    this->LabelOperation->setText("operation: "+ text);
}

///
/// \brief MainWindow::editItem
/// \param pointCoordScene
///
void MainWindow::editItem(QPointF pointCoordScene)
{
    // 初始化一下 如果没有选中对象时, 设置当前对象为空 且属性栏清空
    this->CurrentEditItem = NULL;
    ui->propertyTableWidget->clearContents();
    ui->propertyTableWidget->setRowCount(0);

    this->CurrentEditItem = this->Scene->itemAt(pointCoordScene,ui->graphicsView->transform());
    if (this->CurrentEditItem != NULL) {
        switch (this->CurrentEditItem->type()) {
            case QGraphicsLineItem::Type:{
                ///
                /// 先显示对象信息到状态栏
                ///
                QGraphicsLineItem *lineItem = static_cast<QGraphicsLineItem*>(this->CurrentEditItem);
                QLineF line = lineItem->line();

                // 起始点和结束点是属性 不会随着拖拽改变;只用scenePos会在拖拽时记录与起始点的偏移量;
                QPointF offset = this->CurrentEditItem->scenePos();
                QPointF startPoint = line.p1() + offset;
                QPointF endPoint = line.p2() + offset;
                QPointF centerPoint = (startPoint + endPoint)/2;

                QString msg = QString("click on line: "
                                        "centerPoint:(%1, %2), "
                                        "startPoint:(%3, %4), "
                                        "endPoint:(%5, %6)")
                                  .arg(qRound(centerPoint.x()))
                                  .arg(qRound(centerPoint.y()))
                                  .arg(qRound(startPoint.x()))
                                  .arg(qRound(startPoint.y()))
                                  .arg(qRound(endPoint.x()))
                                  .arg(qRound(endPoint.y()));
                displayOperation(msg);

                ///
                /// 把对象的属性映射到属性修改面板
                ///

                // 映射属性
                int row = ui->propertyTableWidget->rowCount();
                ui->propertyTableWidget->insertRow(row);
                QTableWidgetItem *startPointXName = new QTableWidgetItem("startPoint.x");
                QTableWidgetItem *startPointXValue = new QTableWidgetItem(QString::number(startPoint.x()));
                startPointXName->setFlags(startPointXName->flags() & ~Qt::ItemIsEditable);
                startPointXValue->setFlags(startPointXValue->flags() | Qt::ItemIsEditable);
                ui->propertyTableWidget->setItem(row, 0, startPointXName);
                ui->propertyTableWidget->setItem(row, 1, startPointXValue);

                row = ui->propertyTableWidget->rowCount();
                ui->propertyTableWidget->insertRow(row);
                QTableWidgetItem *startPointYName = new QTableWidgetItem("startPoint.y");
                QTableWidgetItem *startPointYValue = new QTableWidgetItem(QString::number(startPoint.y()));
                startPointYName->setFlags(startPointYName->flags() & ~Qt::ItemIsEditable);
                startPointYValue->setFlags(startPointYValue->flags() | Qt::ItemIsEditable);
                ui->propertyTableWidget->setItem(row, 0, startPointYName);
                ui->propertyTableWidget->setItem(row, 1, startPointYValue);

                row = ui->propertyTableWidget->rowCount();
                ui->propertyTableWidget->insertRow(row);
                QTableWidgetItem *endPointXName = new QTableWidgetItem("endPoint.x");
                QTableWidgetItem *endPointXValue = new QTableWidgetItem(QString::number(endPoint.x()));
                endPointXName->setFlags(endPointXName->flags() & ~Qt::ItemIsEditable);
                endPointXValue->setFlags(endPointXValue->flags() | Qt::ItemIsEditable);
                ui->propertyTableWidget->setItem(row, 0, endPointXName);
                ui->propertyTableWidget->setItem(row, 1, endPointXValue);

                row = ui->propertyTableWidget->rowCount();
                ui->propertyTableWidget->insertRow(row);
                QTableWidgetItem *endPointYName = new QTableWidgetItem("endPoint.y");
                QTableWidgetItem *endPointYValue = new QTableWidgetItem(QString::number(endPoint.y()));
                endPointYName->setFlags(endPointYName->flags() & ~Qt::ItemIsEditable);
                endPointYValue->setFlags(endPointYValue->flags() | Qt::ItemIsEditable);
                ui->propertyTableWidget->setItem(row, 0, endPointYName);
                ui->propertyTableWidget->setItem(row, 1, endPointYValue);

                break;
            }
            case QGraphicsEllipseItem::Type:
            {
                // QGraphicsEllipseItem *ellipseItem = static_cast<QGraphicsEllipseItem*>(item);
                break;
            }
            default:
            {
                displayOperation("00");
            }
        };
    }
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

        this->TmpLine->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        Container.push_back(std::move(this->TmpLine));
        this->CurrentDrawTool = DrawToolType::None;
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
        // this->editItem(pointCoordScene);
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
    displayOperation("mouse left click");
    QPointF pointCoordScene = ui->graphicsView->mapToScene(pointCoordView);
    switch (this->CurrentDrawTool) {
        case DrawToolType::None:{
            this->editItem(pointCoordScene);
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
    displayOperation("mouse right click");
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

void MainWindow::on_testButton_clicked()
{
    ui->propertyTableWidget->clearContents();
    ui->propertyTableWidget->setRowCount(0);
}


void MainWindow::on_propertyTableWidget_cellChanged(int row, int column)
{
    if (this->CurrentEditItem != NULL) {
        switch (this->CurrentEditItem->type()) {
            case QGraphicsLineItem::Type:{

                double startX = 0.0, startY = 0.0, endX = 0.0, endY = 0.0;
                int rowCount = ui->propertyTableWidget->rowCount();

                for (int r = 0; r < rowCount; ++r) {
                    QTableWidgetItem *nameItem  = ui->propertyTableWidget->item(r, 0);
                    QTableWidgetItem *valueItem = ui->propertyTableWidget->item(r, 1);
                    if (!nameItem || !valueItem)
                        continue;

                    QString propertyName  = nameItem->text();
                    QString propertyValue = valueItem->text();

                    bool transformIsOk = false;
                    double value = propertyValue.toDouble(&transformIsOk);
                    if (!transformIsOk)
                    {
                        displayOperation("error, input right form");
                        continue;
                    }

                    if (propertyName == "startPoint.x")
                        startX = value;
                    else if (propertyName == "startPoint.y")
                        startY = value;
                    else if (propertyName == "endPoint.x")
                        endX = value;
                    else if (propertyName == "endPoint.y")
                        endY = value;

                    QGraphicsLineItem *lineItem = static_cast<QGraphicsLineItem*>(this->CurrentEditItem);
                    QPointF newStart = QPointF(startX, startY);
                    QPointF newEnd   = QPointF(endX, endY);
                    QLineF newLine(newStart, newEnd);
                    lineItem->setPos(QPointF(0,0));
                    lineItem->setLine(newLine);
                }
                break;
            }
            case QGraphicsEllipseItem::Type:{
                break;
            }
            default: {
                displayOperation("00");
            }
        };
    }
}

