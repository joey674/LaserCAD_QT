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
#include <QtMath>
#include "header/CavalierContours/polyline.hpp"
#include "header/CavalierContours/polylineoffset.hpp"

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

void MainWindow::setAllItemsMovable(bool movable )
{
    for (auto &item : this->Container) {
        if (item) {
            item->setFlag(QGraphicsItem::ItemIsMovable, movable);
        }
    }
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

    // 锁定当前场景矩形
    ui->graphicsView->scale(1.5,1.5);
    this->Scene->setSceneRect(Scene->sceneRect());

    // connect
    // graphicsview组件触发鼠标移动时,会通知mainwindow组件;
    connect(ui->graphicsView,SIGNAL(mousemove_event(QPoint)),
            this,SLOT(on_graphicsview_mousemove_occurred(QPoint)));
    connect(ui->graphicsView,SIGNAL(mouseleftclick_event(QPoint)),
            this,SLOT(on_graphicsview_mouseleftclick_occurred(QPoint)));
    connect(ui->graphicsView,SIGNAL(mouserightclick_event(QPoint)),
            this,SLOT(on_graphicsview_mouserightclick_occurred(QPoint)));
    connect(ui->graphicsView,SIGNAL(mouserelease_event(QPoint)),
            this,SLOT(on_graphicsview_mouserelease_occurred(QPoint)));
    connect(ui->graphicsView,SIGNAL(mousedoubleclick_event(QPoint)),
            this,SLOT(on_graphicsview_mousedoubleclick_occurred(QPoint)));
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

    if (! this->Scene->selectedItems().empty())
    {
        this->CurrentEditItem = this->Scene->selectedItems()[0];
        switch (this->CurrentEditItem->type()) {
            case QGraphicsLineItem::Type:{
                QGraphicsLineItem *lineItem = static_cast<QGraphicsLineItem*>(this->CurrentEditItem);
                this->editLine(lineItem);
                break;
            }
            case QGraphicsEllipseItem::Type:
            {
                QGraphicsEllipseItem *CircleItem = static_cast<QGraphicsEllipseItem*>(this->CurrentEditItem);
                this->editCircle(CircleItem);
                break;
            }
            default:
            {
                displayOperation("undefine object");
            }
        };
    }
}

void MainWindow::editLine(QGraphicsLineItem *lineItem)
{
    // 先显示对象信息到状态栏
    // 起始点和结束点是属性 不会随着拖拽改变;只用scenePos会在拖拽时记录与起始点的偏移量;
    QLineF line = lineItem->line();
    QPointF offset = lineItem->scenePos();
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


    // 把对象的属性映射到属性修改面板
    // 先blocksignal,不然会频繁触发修改属性table的回调
    ui->propertyTableWidget->blockSignals(true);

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

    ui->propertyTableWidget->blockSignals(false);
}

void MainWindow::editCircle(QGraphicsEllipseItem * circleItem)
{
    // 先显示对象信息到状态栏
    QPointF offset = circleItem->scenePos();
    QPointF centerPoint = QPointF(
        circleItem->rect().center().x() + offset.x(),
        circleItem->rect().center().y() + offset.y()
        );

    QString msg = QString("click on circle: "
                          "centerPoint:(%1, %2), "
                          "radius:%3")
                      .arg(qRound(centerPoint.x()))
                      .arg(qRound(centerPoint.y()))
                      .arg(qRound(circleItem->rect().width()));
    displayOperation(msg);


    // 把对象的属性映射到属性修改面板
    // 先blocksignal,不然会频繁触发修改属性table的回调
    ui->propertyTableWidget->blockSignals(true);

    // 映射属性
    int row = ui->propertyTableWidget->rowCount();
    ui->propertyTableWidget->insertRow(row);
    QTableWidgetItem *centerPointXName = new QTableWidgetItem("centerPoint.x");
    QTableWidgetItem *centerPointXValue = new QTableWidgetItem(QString::number(centerPoint.x()));
    centerPointXName->setFlags(centerPointXName->flags() & ~Qt::ItemIsEditable);
    centerPointXValue->setFlags(centerPointXValue->flags() | Qt::ItemIsEditable);
    ui->propertyTableWidget->setItem(row, 0, centerPointXName);
    ui->propertyTableWidget->setItem(row, 1, centerPointXValue);

    row = ui->propertyTableWidget->rowCount();
    ui->propertyTableWidget->insertRow(row);
    QTableWidgetItem *centerPointYName = new QTableWidgetItem("centerPoint.y");
    QTableWidgetItem *centerPointYValue = new QTableWidgetItem(QString::number(centerPoint.y()));
    centerPointYName->setFlags(centerPointYName->flags() & ~Qt::ItemIsEditable);
    centerPointYValue->setFlags(centerPointYValue->flags() | Qt::ItemIsEditable);
    ui->propertyTableWidget->setItem(row, 0, centerPointYName);
    ui->propertyTableWidget->setItem(row, 1, centerPointYValue);

    row = ui->propertyTableWidget->rowCount();
    ui->propertyTableWidget->insertRow(row);
    QTableWidgetItem *radiusName = new QTableWidgetItem("radius");
    QTableWidgetItem *radiusValue = new QTableWidgetItem(QString::number(circleItem->rect().width()));
    radiusName->setFlags(radiusName->flags() & ~Qt::ItemIsEditable);
    radiusValue->setFlags(radiusValue->flags() | Qt::ItemIsEditable);
    ui->propertyTableWidget->setItem(row, 0, radiusName);
    ui->propertyTableWidget->setItem(row, 1, radiusValue);

    ui->propertyTableWidget->blockSignals(false);
}

void MainWindow::editVariantLine()
{

}

///
/// \brief MainWindow::resetDrawToolStatus
///
void MainWindow::resetDrawToolStatus()
{
    this->CurrentDrawTool = DrawToolType::None;
    this->PolygonEdgeNum = 3;
    this->TmpLine = NULL;
    this->TmpCircle = NULL;
    this->TmpPolyline = NULL;
    this->TmpArc = NULL;
    this->TmpVariantLine = NULL;
    this->TmpRect = NULL;
    this->TmpSpiral = NULL;
    this->TmpPolygon = NULL;
    this->TmpEllipse = NULL;
}

void MainWindow::drawLine(QPointF pointCoordScene,DrawEventType event)
{
    this->setAllItemsMovable(false);

    if (!this->TmpLine && event == DrawEventType::LeftClick)
    {
        this->TmpLine = std::make_unique<QGraphicsLineItem>(QLineF(pointCoordScene, pointCoordScene));
        this->TmpLine->setPen(QPen(Qt::black, 1));
        this->Scene->addItem(this->TmpLine.get());
    }
    else if  (this->TmpLine && event == DrawEventType::MouseMove)
    {
        QLineF newLine;
        QPointF endPoint = pointCoordScene;
        if (Manager::getIns().IsXHold)
            endPoint = QPointF(pointCoordScene.x(), this->TmpLine->line().p1().y());
        else if (Manager::getIns().IsYHold)
                    endPoint = QPointF(this->TmpLine->line().p1().x(), pointCoordScene.y());
        newLine = QLineF(this->TmpLine->line().p1(), endPoint);
        this->TmpLine->setLine(newLine);
        this->TmpLine->setTransformOriginPoint(newLine.center());
    }
    else if (this->TmpLine && event == DrawEventType::LeftClick) {
        this->TmpLine->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        this->Container.push_back(std::move(this->TmpLine));
    }
}

void MainWindow::drawCircle(QPointF pointCoordScene,DrawEventType event)
{
    this->setAllItemsMovable(false);

    if (!this->TmpCircle && event == DrawEventType::LeftClick)
    {
        QRectF initialRect(pointCoordScene.x(), pointCoordScene.y(), 0, 0);
        this->TmpCircle = std::make_unique<QGraphicsEllipseItem>(initialRect);
        this->TmpCircle->setPen(QPen(Qt::black, 1));
        Scene->addItem(this->TmpCircle.get());
    }
    else if  (this->TmpCircle && event == DrawEventType::MouseMove)
    {
        QRectF currentRect = this->TmpCircle->rect();
        QPointF center = currentRect.center();
        double radius = QLineF(center, pointCoordScene).length();
        QRectF newRect(center.x() - radius,
                       center.y() - radius,
                       2 * radius,
                       2 * radius);
        this->TmpCircle->setRect(newRect);
        this->TmpCircle->setTransformOriginPoint(center);
    }
    else if (this->TmpCircle && event == DrawEventType::LeftClick)
    {
        this->TmpCircle->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        Container.push_back(std::move(this->TmpCircle));
    }
}

void MainWindow::drawPolyline(QPointF pointCoordScene, DrawEventType event)
{
    this->setAllItemsMovable(false);

    if (!this->TmpPolyline && event == DrawEventType::LeftClick)
    {
        this->TmpPolyline = std::make_unique<PolylineItem>();
        this->Scene->addItem(this->TmpPolyline.get());

        this->TmpPolyline->addVertex(pointCoordScene,0);
        this->TmpPolyline->addVertex(pointCoordScene,0);
    }
    else if  (this->TmpPolyline && event == DrawEventType::MouseMove)
    {
        int index = this->TmpPolyline->getSize()-1;
        if (!Manager::getIns().IsControlHold)
        {
            QPointF lastPoint = this->TmpPolyline->getPoint(index - 1);
            if (Manager::getIns().IsXHold)
                this->TmpPolyline->editVertex(index,QPointF(pointCoordScene.x(),lastPoint.y()),0);
            else if (Manager::getIns().IsYHold)
                this->TmpPolyline->editVertex(index,QPointF(lastPoint.x(),pointCoordScene.y()),0);
            else
                this->TmpPolyline->editVertex(index,pointCoordScene,0);
        }
        else
        {
            if (!Manager::getIns().IsCapsLocked)
                this->TmpPolyline->editVertex(index, pointCoordScene,1);
            else
                 this->TmpPolyline->editVertex(index, pointCoordScene,-1);
        }
    }
    else if (this->TmpPolyline && event == DrawEventType::LeftClick)
    {
        this->TmpPolyline->addVertex(pointCoordScene,0);
    }
    else if (this->TmpPolyline && event == DrawEventType::RightClick)
    {
        this->TmpPolyline->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        this->Container.push_back(std::move(this->TmpPolyline));
    }
}

void MainWindow::drawArc(QPointF pointCoordScene, DrawEventType event)
{
    this->setAllItemsMovable(false);

    if (!this->TmpArc && event == DrawEventType::LeftClick)
    {
        this->TmpArc = std::make_unique<QGraphicsPathItem>();
        this->TmpArc->setData(0,pointCoordScene);
        this->TmpArc->setPen(QPen(Qt::black, 1));
        Scene->addItem(this->TmpArc.get());
    }
    else if  (this->TmpArc && event == DrawEventType::MouseMove)
    {
        QPointF startPoint =this->TmpArc->data(0).toPointF();
        QPointF endPoint = pointCoordScene;

        double radius = QLineF(startPoint, endPoint).length()/2;
        QPointF centerPoint((startPoint.x()+endPoint.x())/2, (startPoint.y()+endPoint.y())/2);

        QRectF newRect(QPointF(centerPoint.x() - radius, centerPoint.y() - radius),
                       QPointF(centerPoint.x() + radius, centerPoint.y() + radius));

        QLineF diameterLine(startPoint, endPoint);
        double angle = diameterLine.angle();

        QPainterPath path;
        path.arcMoveTo(newRect, angle);
        path.arcTo(newRect, angle, 180);
        this->TmpArc->setPath(path);
    }
    else if (this->TmpArc && event == DrawEventType::LeftClick)
    {
        this->TmpArc->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        Container.push_back(std::move(this->TmpArc));
    }
}

void MainWindow::drawVariantLine(QPointF pointCoordScene, DrawEventType event)
{
    this->setAllItemsMovable(false);
    if (!this->TmpVariantLine && event == DrawEventType::LeftClick)
    {
        this->TmpVariantLine = std::make_unique<VariantLineItem>(QPointF(pointCoordScene));
        this->Scene->addItem(this->TmpVariantLine.get());

        this->TmpVariantLine->setLine(pointCoordScene,true,VariantLineItem::Line);
    }
    else if  (this->TmpVariantLine && event == DrawEventType::MouseMove)
    {
        if (!Manager::getIns().IsControlHold)
            this->TmpVariantLine->setLine(pointCoordScene,false,VariantLineItem::Line);
        else
            this->TmpVariantLine->setLine(pointCoordScene,false,VariantLineItem::Arc);
    }
    else if (this->TmpVariantLine && event == DrawEventType::LeftClick)
    {
        if (!Manager::getIns().IsControlHold)
            this->TmpVariantLine->setLine(pointCoordScene,true,VariantLineItem::Line);
        else
            this->TmpVariantLine->setLine(pointCoordScene,true,VariantLineItem::Arc);
    }
    else if (this->TmpVariantLine && event == DrawEventType::RightClick)
    {
        this->TmpVariantLine->setTransformOriginPoint(this->TmpVariantLine->getCenter());
        this->TmpVariantLine->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        this->Container.push_back(std::move(this->TmpVariantLine));
    }
}

void MainWindow::drawRect(QPointF pointCoordScene, DrawEventType event)
{
    this->setAllItemsMovable(false);

    if (!this->TmpRect && event == DrawEventType::LeftClick)
    {
        this->TmpRect = std::make_unique<QGraphicsRectItem>(pointCoordScene.x(), pointCoordScene.y(),0,0);
        this->TmpRect->setPen(QPen(Qt::black, 1));
        this->Scene->addItem(this->TmpRect.get());
    }
    else if  (this->TmpRect && event == DrawEventType::MouseMove)
    {
        qreal width = pointCoordScene.x() - this->TmpRect->rect().topLeft().x();
        qreal height = pointCoordScene.y() - this->TmpRect->rect().topLeft().y();
        QRectF newRect(this->TmpRect->rect().topLeft().x(),this->TmpRect->rect().topLeft().y(),width,height);
        this->TmpRect->setRect(newRect);
    }
    else if (this->TmpRect && event == DrawEventType::LeftClick) {
        this->TmpRect->setTransformOriginPoint(this->TmpRect->rect().center());
        this->TmpRect->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        this->Container.push_back(std::move(this->TmpRect));
    }
}

void MainWindow::drawSpiral(QPointF pointCoordScene, DrawEventType event)
{
    this->setAllItemsMovable(false);
    /* center：螺旋的中心点
        radius：螺旋的初始半径
        spacing：每圈的间距
        turns：螺旋的圈数*/

    if (!this->TmpSpiral && event == DrawEventType::LeftClick)
    {
        QPointF centerPoint  = pointCoordScene;
        this->TmpSpiral =  std::make_unique<QGraphicsPathItem>();
        this->TmpSpiral->setData(0,pointCoordScene);
        this->TmpSpiral->setPen(QPen(Qt::black, 1));
        Scene->addItem(this->TmpSpiral.get());
    }
    else if  (this->TmpSpiral && event == DrawEventType::MouseMove)
    {
        // 这里都是设置了一个演示默认值；
        QPointF centerPoint = this->TmpSpiral->data(0).toPointF();
        QPointF endPoint = pointCoordScene;
        int turns = 3;
        double radius = QLineF(centerPoint,endPoint).length()/2;
        double spacing = QLineF(centerPoint,endPoint).length()/6;
        double dx = endPoint.x() - centerPoint.x();
        double dy = endPoint.y() - centerPoint.y();

        QPainterPath path;
        bool start = true;
        for (double theta = 0; theta < turns * 2 * M_PI; theta += 0.1) {
            double r = radius + spacing * theta / (2 * M_PI);
            double x = centerPoint.x() + r * cos(theta);
            double y = centerPoint.y() + r * sin(theta);

            if (start == true) {
                path.moveTo(centerPoint.x() + r * cos(theta),centerPoint.y()+r* sin(theta));
                start = false;
            } else {
                path.lineTo(x, y);
            }
        }
        this->TmpSpiral->setTransformOriginPoint(centerPoint);
        this->TmpSpiral->setRotation(atan2(dy, dx)* 180 / M_PI);

        this->TmpSpiral->setPath(path);
    }
    else if (this->TmpSpiral && event == DrawEventType::LeftClick)
    {
        this->TmpSpiral->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        Container.push_back(std::move(this->TmpSpiral));
    }
}

void MainWindow::drawPolygon(QPointF pointCoordScene, DrawEventType event)
{
    this->setAllItemsMovable(false);

    if (!this->TmpPolygon && event == DrawEventType::LeftClick)
    {
        this->TmpPolygon = std::make_unique<QGraphicsPolygonItem>();
        this->TmpPolygon->setData(0,pointCoordScene);
        this->TmpPolygon->setPen(QPen(Qt::black, 1));
        this->Scene->addItem(this->TmpPolygon.get());
    }
    else if  (this->TmpPolygon && event == DrawEventType::MouseMove)
    {
        QPolygonF newPolygon;

        QPointF centerPoint = this->TmpPolygon->data(0).toPointF();
        double radius = QLineF(centerPoint,pointCoordScene).length();
        int edgeNum = PolygonEdgeNum;

        double angleStep = 2 * M_PI / edgeNum;
        for (int i =0;i<edgeNum;i++) {
            double angle = i * angleStep - M_PI/2;
            QPointF Vertex(centerPoint.x()+radius*cos(angle),centerPoint.y()+radius*sin(angle));
            newPolygon << Vertex;
        }

        this->TmpPolygon->setPolygon(newPolygon);
        this->TmpPolygon->setTransformOriginPoint(centerPoint);
    }
    else if (this->TmpPolygon && event == DrawEventType::LeftClick) {
        this->TmpPolygon->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        this->Container.push_back(std::move(this->TmpPolygon));
    }
}

void MainWindow::drawEllipse(QPointF pointCoordScene, DrawEventType event)
{
    this->setAllItemsMovable(false);

    if (!this->TmpEllipse && event == DrawEventType::LeftClick)
    {
        QRectF initialRect(pointCoordScene.x(), pointCoordScene.y(), 0, 0);
        this->TmpEllipse = std::make_unique<QGraphicsEllipseItem>(initialRect);
        this->TmpEllipse->setPen(QPen(Qt::black, 1));
        Scene->addItem(this->TmpEllipse.get());
    }
    else if  (this->TmpEllipse && event == DrawEventType::MouseMove)
    {
        if (!this->TmpEllipse->data(0).isValid()) {
            QRectF currentRect = this->TmpEllipse->rect();
            QPointF center = currentRect.center();
            double radius = QLineF(center, pointCoordScene).length();
            QRectF newRect(center.x() - radius,
                           center.y() - radius,
                           2 * radius,
                           2 * radius);
            this->TmpEllipse->setRect(newRect);
        } else {
            QPointF firstAxisPoint = this->TmpEllipse->data(0).toPointF();
            QRectF currentRect = this->TmpEllipse->rect();
            QPointF center = currentRect.center();

            double majorAxis = QLineF(center, firstAxisPoint).length();

            double dx = firstAxisPoint.x() - center.x();
            double dy = firstAxisPoint.y() - center.y();
            double theta = atan2(dy, dx);

            QLineF axisLine(center, firstAxisPoint);
            QLineF perpendicularLine = axisLine.normalVector();
            QPointF perpendicularPoint = perpendicularLine.p2();
            double minorAxis = QLineF(center, pointCoordScene).length();

            QRectF finalRect(center.x() - majorAxis, center.y() - minorAxis,
                             2 * majorAxis, 2 * minorAxis);

            this->TmpEllipse->setRect(finalRect);

            this->TmpEllipse->setTransformOriginPoint(center);
            this->TmpEllipse->setRotation(theta * 180 / M_PI);
        }

    }
    else if (this->TmpEllipse && event == DrawEventType::LeftClick)
    {
        if (!this->TmpEllipse->data(0).isValid()) {
            this->TmpEllipse->setData(0,pointCoordScene);
        } else {
            this->TmpEllipse->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
            Container.push_back(std::move(this->TmpEllipse));
        }
    }
}

///
/// \brief MainWindow::keyPressEvent
/// \param event
///
void MainWindow::keyPressEvent(QKeyEvent * event)
{
    switch(event->key()) {
    case Qt::Key_Shift:
    {
        Manager::getIns().IsShiftHold = true;
        break;
    }
    case Qt::Key_Control:
    {
        Manager::getIns().IsControlHold = true;
        break;
    }

    case Qt::Key_X:
    {
        Manager::getIns().IsXHold = true;
        break;
    }
    case Qt::Key_Y:
    {
        Manager::getIns().IsYHold = true;
        break;
    }
    case Qt::Key_Z:
    {
        Manager::getIns().IsZHold = true;
        break;
    }

    case Qt::Key_CapsLock:
    {
        Manager::getIns().IsCapsLocked = !Manager::getIns().IsCapsLocked;
        VariantLineItem::arcDirectionIsClockwise = !VariantLineItem::arcDirectionIsClockwise;
        break;
    }

    case Qt::Key_W:
    {
        this->PolygonEdgeNum +=1;
        break;
    }
    case Qt::Key_S:
    {
        if (this->PolygonEdgeNum>3){
            this->PolygonEdgeNum -=1;
        }
        break;
    }
    case Qt::Key_A:
    {

        break;
    }
    case Qt::Key_D:
    {

        break;
    }

    case Qt::Key_1:
    {
        ui->resetButton->setChecked(true);
        this->on_resetButton_clicked();
        break;
    }
    case Qt::Key_2:
    {
        ui->drawVariantLineButton->setChecked(true);
        this->on_drawVariantLineButton_clicked();
        break;
    }
    case Qt::Key_3:
    {
        ui->drawCircleButton->setChecked(true);
        this->on_drawCircleButton_clicked();
        break;
    }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent * event)
{
    switch(event->key()) {
    case Qt::Key_Shift:
    {
        Manager::getIns().IsShiftHold = false;
        break;
    }
    case Qt::Key_Control:
    {
        Manager::getIns().IsControlHold = false;
        break;
    }
    case Qt::Key_X:
    {
        Manager::getIns().IsXHold = false;
        break;
    }
    case Qt::Key_Y:
    {
        Manager::getIns().IsYHold = false;
        break;
    }
    case Qt::Key_Z:
    {
        Manager::getIns().IsZHold = false;
        break;
    }
    }
    displayOperation("keyrelease");
}

///
/// \brief MainWindow::on_graphicsview_mouse_move_triggered
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
        case DrawToolType::None:
        {
            // this->editItem(pointCoordScene);
            break;
        }
        case DrawToolType::Line:
        {
            this->drawLine(pointCoordScene,DrawEventType::MouseMove);
            break;
        }
        case DrawToolType::Circle:
        {
            this->drawCircle(pointCoordScene,DrawEventType::MouseMove);
            break;
        }
        case DrawToolType::Polyline:
        {
            this->drawPolyline(pointCoordScene,DrawEventType::MouseMove);
            break;
        }
        case DrawToolType::Arc:
        {
            this->drawArc(pointCoordScene,DrawEventType::MouseMove);
            break;
        }
        case DrawToolType::Spiral:
        {
            this->drawSpiral(pointCoordScene,DrawEventType::MouseMove);
            break;
        }
        case DrawToolType::VariantLine:
        {
            this->drawVariantLine(pointCoordScene,DrawEventType::MouseMove);
            break;
        }
        case DrawToolType::Rect:
        {
            this->drawRect(pointCoordScene,DrawEventType::MouseMove);
            break;
        }
        case DrawToolType::Polygon:
        {
            this->drawPolygon(pointCoordScene,DrawEventType::MouseMove);
            break;
        }
        case DrawToolType::Ellipse:
        {
            this->drawEllipse(pointCoordScene,DrawEventType::MouseMove);
            break;
        }

        default:
        {}
    }
}

void MainWindow::on_graphicsview_mouseleftclick_occurred(QPoint pointCoordView)
{
    displayOperation("mouse left click");
    QPointF pointCoordScene = ui->graphicsView->mapToScene(pointCoordView);
    switch (this->CurrentDrawTool) {
        case DrawToolType::None:
    {
            this->editItem(pointCoordScene);
            break;
        }
        case DrawToolType::Line:
        {
            this->drawLine(pointCoordScene,DrawEventType::LeftClick);
            break;
        }
        case DrawToolType::Circle:
        {
            this->drawCircle(pointCoordScene,DrawEventType::LeftClick);
            break;
        }
        case DrawToolType::Polyline:
        {
            this->drawPolyline(pointCoordScene,DrawEventType::LeftClick);
            break;
        }
        case DrawToolType::Arc:
        {
            this->drawArc(pointCoordScene,DrawEventType::LeftClick);
            break;
        }
        case DrawToolType::Spiral:
        {
            this->drawSpiral(pointCoordScene,DrawEventType::LeftClick);
            break;
        }
        case DrawToolType::VariantLine:
        {
            this->drawVariantLine(pointCoordScene,DrawEventType::LeftClick);
            break;
        }
        case DrawToolType::Rect:
        {
            this->drawRect(pointCoordScene,DrawEventType::LeftClick);
            break;
        }
        case DrawToolType::Polygon:
        {
            this->drawPolygon(pointCoordScene,DrawEventType::LeftClick);
            break;
        }
        case DrawToolType::Ellipse:
        {
            this->drawEllipse(pointCoordScene,DrawEventType::LeftClick);
            break;
        }

        default:
        {}
    }
}

void MainWindow::on_graphicsview_mouserightclick_occurred(QPoint pointCoordView)
{
    displayOperation("mouse right click");
    QPointF pointCoordScene = ui->graphicsView->mapToScene(pointCoordView);
    switch (this->CurrentDrawTool) {
        case DrawToolType::Polyline:
        {
            this->drawPolyline(pointCoordScene,DrawEventType::RightClick);
            break;
        }
        case DrawToolType::VariantLine:
        {
            this->drawVariantLine(pointCoordScene,DrawEventType::RightClick);
            break;
        }
        case DrawToolType::Ellipse:
        {
            this->drawEllipse(pointCoordScene,DrawEventType::RightClick);
            break;
        }
        default:
        {}
    }
}

void MainWindow::on_graphicsview_mouserelease_occurred(QPoint pointCoordView)
{
    QPointF pointCoordScene = ui->graphicsView->mapToScene(pointCoordView);
    switch (this->CurrentDrawTool) {
        case DrawToolType::None:
        {
            this->editItem(pointCoordScene);
            break;
        }
        default:
        {}
    }
}

void MainWindow::on_graphicsview_mousedoubleclick_occurred(QPoint pointCoordView)
{
    ui->resetButton->setChecked(true);
    this->on_resetButton_clicked();
}

///
/// \brief MainWindow::on_drawLineButton_clicked
///
void MainWindow::on_drawLineButton_clicked()
{
    displayOperation("drawLine button click");
    this->resetDrawToolStatus();
    this->CurrentDrawTool = DrawToolType::Line;
}

void MainWindow::on_drawCircleButton_clicked()
{
    displayOperation("drawCircle button click");
    this->resetDrawToolStatus();
    this->CurrentDrawTool = DrawToolType::Circle;
}

void MainWindow::on_resetButton_clicked()
{
    displayOperation("reset button click");
    this->resetDrawToolStatus();
    ui->propertyTableWidget->clearContents();
    ui->propertyTableWidget->setRowCount(0);

    this->setAllItemsMovable(true);
}

void MainWindow::on_drawPolylineButton_clicked()
{
    displayOperation("drawPolyline button click");
    this->resetDrawToolStatus();
    this->CurrentDrawTool = DrawToolType::Polyline;
}

void MainWindow::on_drawArcButton_clicked()
{
    displayOperation("drawArc button click");
    this->resetDrawToolStatus();
    this->CurrentDrawTool = DrawToolType::Arc;
}

void MainWindow::on_drawSpiralButton_clicked()
{
    displayOperation("drawSpiral button click");
    this->resetDrawToolStatus();
    this->CurrentDrawTool = DrawToolType::Spiral;
}

void MainWindow::on_drawVariantLineButton_clicked()
{
    displayOperation("drawVariantLine button click");
    this->resetDrawToolStatus();
    this->CurrentDrawTool = DrawToolType::VariantLine;
}

void MainWindow::on_drawRectButton_clicked()
{
    displayOperation("drawRect button click");
    this->resetDrawToolStatus();
    this->CurrentDrawTool = DrawToolType::Rect;
}

void MainWindow::on_drawPolygonButton_clicked()
{
    displayOperation("drawPolygon button click");
    this->resetDrawToolStatus();
    this->CurrentDrawTool = DrawToolType::Polygon;
}

void MainWindow::on_drawEllipseButton_clicked()
{
    displayOperation("drawEllipse button click");
    this->resetDrawToolStatus();
    this->CurrentDrawTool = DrawToolType::Ellipse;
}


///
/// \brief MainWindow::on_propertyTableWidget_cellChanged
///
void MainWindow::on_propertyTableWidget_cellChanged(int row, int column)
{
    if (this->CurrentEditItem != NULL) {
        switch (this->CurrentEditItem->type()) {
        case QGraphicsLineItem::Type:
        {

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
        case QGraphicsEllipseItem::Type:
        {

            double centerX = 0.0, centerY = 0.0,radius = 0.0;
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

                if (propertyName == "centerPoint.x")
                    centerX = value;
                else if (propertyName == "centerPoint.y")
                    centerY = value;
                else if (propertyName == "radius")
                    radius = value;

                QGraphicsEllipseItem *circleItem = static_cast<QGraphicsEllipseItem*>(this->CurrentEditItem);
                QRectF newRect( centerX - radius,
                               centerY - radius,
                               radius,
                               radius);
                circleItem->setPos(QPointF(0,0));
                circleItem->setRect(newRect);
            }
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
/// \brief MainWindow::on_rotateButton_clicked
///
void MainWindow::on_rotateButton_clicked()
{
    if (!this->CurrentEditItem) return;

    auto angle = this->CurrentEditItem->rotation();
    this->CurrentEditItem->setRotation(angle + 90);
}

void MainWindow::on_centerButton_clicked()
{

}

///
/// 测试专用
///
void MainWindow::on_drawTestLineButton_clicked()
{
    ///
    /// polyline test
    ///
    this->TmpPolyline = std::make_unique<PolylineItem>();
    this->Scene->addItem(this->TmpPolyline.get());

    this->TmpPolyline->addVertex(QPointF(0,0),0);
    this->TmpPolyline->addVertex(QPointF(100,100),0);
    this->TmpPolyline->addVertex(QPointF(200,100),0);
    this->TmpPolyline->addVertex(QPointF(200,200),1);
    this->TmpPolyline->addVertex(QPointF(200,300),-1);

    ///
    /// polygon  test
    ///
    /*
    using namespace cavc;

    cavc::Polyline<double> input;
    // add vertexes as (x, y, bulge)
    input.addVertex(0, 25, 1);
    input.addVertex(0, 0, 0);
    input.addVertex(2, 0, 1);
    input.addVertex(10, 0, -0.5);
    input.addVertex(8, 9, 0.374794619217547);
    input.addVertex(21, 0, 0);
    input.addVertex(23, 0, 1);
    input.addVertex(32, 0, -0.5);
    input.addVertex(28, 0, 0.5);
    input.addVertex(39, 21, 0);
    input.addVertex(28, 12, 0);
    input.isClosed() = true;

    // compute the resulting offset polylines, offset = 3
    std::vector<cavc::Polyline<double>> results = cavc::parallelOffset(input, 3.0);

    this->TmpPolygon = std::make_unique<QGraphicsPolygonItem>();
    this->TmpPolygon->setPen(QPen(Qt::black, 1));
    this->Scene->addItem(this->TmpPolygon.get());
    // closed polyline representing a circle going counter clockwise
    double radius = 10.0;
    cavc::Polyline<double> ccwCircle;
    ccwCircle.addVertex(0, 0, 1);
    ccwCircle.addVertex(2.0 * radius, 0, 1);
    ccwCircle.isClosed() = true;

    // closed polyline representing a circle going clockwise
    cavc::Polyline<double> cwCircle;
    cwCircle.addVertex(0, 0, -1);
    cwCircle.addVertex(2.0 * radius, 0, -1);
    cwCircle.isClosed() = true;

    // path length of polyline
    double length = getPathLength(ccwCircle);
    assert(utils::fuzzyEqual(length, 2.0 * utils::pi<double>() * radius));

    // signed area of closed polyline (area is positive if counter clockwise, negative if clockwise)
    double area = getArea(ccwCircle);
    assert(utils::fuzzyEqual(area, utils::pi<double>() * radius * radius));
    assert(utils::fuzzyEqual(getArea(cwCircle), -area));

    // polyline extents
    AABB<double> extents = getExtents(ccwCircle);
    assert(utils::fuzzyEqual(extents.xMin, 0.0));
    assert(utils::fuzzyEqual(extents.yMin, -radius));
    assert(utils::fuzzyEqual(extents.xMax, 2.0 * radius));
    assert(utils::fuzzyEqual(extents.yMax, radius));

    // Closest point on polyline to a point given
    ClosestPoint<double> closestPoint(ccwCircle, Vector2<double>(radius, 10.0 * radius));
    // index is the starting vertex index of the closest segment (going clockwise so arc starting at
    // the second vertex is closest)
    assert(closestPoint.index() == 1);
    assert(fuzzyEqual(closestPoint.point(), Vector2<double>(radius, radius)));
    assert(utils::fuzzyEqual(closestPoint.distance(), 9.0 * radius));*/

    ///
    ///
    ///
    /*QPolygonF newPolygon;
    newPolygon << QPointF(0,0) << QPointF(100,0) << QPointF(100,100) << QPointF(0,100);
    this->TmpPolygon->setPolygon(newPolygon);

    this->TmpPolygon->setTransformOriginPoint(QPointF(50,50));
    this->TmpPolygon->setRotation(180);*/

    ///
    /// rect test
    ///
    /*this->TmpRect = std::make_unique<QGraphicsRectItem>(100, 100,50,50);
    this->TmpRect->setPen(QPen(Qt::black, 1));
    this->Scene->addItem(this->TmpRect.get());

     QRectF newRect(this->TmpRect->rect().topLeft().x(),this->TmpRect->rect().topLeft().y(),100, 100);
    this->TmpRect->setRect(newRect);*/

    ///
    /// variant test
    ///
    /*this->TmpVariantLine = std::make_unique<VariantLineItem>(QPointF(1,1));
    this->Scene->addItem(this->TmpVariantLine.get());
    this->TmpVariantLine->setLine(QPointF(10,10),true,VariantLineItem::LineType::Line);
    this->TmpVariantLine->setLine(QPointF(20,10),false,VariantLineItem::LineType::Line);
    this->TmpVariantLine->setLine(QPointF(0,20),true,VariantLineItem::LineType::Arc);

     this->TmpVariantLine->setLine(QPointF(10,20),true,VariantLineItem::LineType::Arc);*/

    ///
    /// arc test
    ///
    /*QPoint startPoint(10,10);
    QPoint endPoint(100,100);

    this->TmpArc = std::make_unique<QGraphicsPathItem>();
    this->TmpArc->setData(0,QPointF(startPoint));
    this->TmpArc->setPen(QPen(Qt::black, 1));
    Scene->addItem(this->TmpArc.get());


    if(startPoint != this->TmpArc->data(0))
    {
        displayOperation("error");
    }


    double radius = QLineF(startPoint, endPoint).length()/2;
    QPointF centerPoint((startPoint.x()+endPoint.x())/2, (startPoint.y()+endPoint.y())/2);

    QRectF newRect(QPointF(centerPoint.x() - radius, centerPoint.y() - radius),
                   QPointF(centerPoint.x() + radius, centerPoint.y() + radius));

    QLineF diameterLine(startPoint, endPoint);
    double angle = diameterLine.angle();

    QPainterPath path1;
    path1.arcMoveTo(newRect, angle);
    path1.arcTo(newRect, angle, 180);
    this->TmpArc->setPath(path1);*/

    ///
    /// polyline test
    ///
    /*QLineF line(QPointF(0,0),QPointF(100,100));
    this->TmpPolyline = std::make_unique<PolylineItem>(line);
    this->Scene->addItem(this->TmpPolyline.get());

    QLineF line1(QPointF(0,0),QPointF(-100,100));
    this->TmpPolyline->setLine(line1,false);

    QLineF line2(QPointF(-100,100),QPointF(100,100));
    this->TmpPolyline->setLine(line2,true);*/
}
