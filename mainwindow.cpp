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
    connect(ui->graphicsView,SIGNAL(mouserelease_event(QPoint)),
            this,SLOT(on_graphicsview_mouserelease_occurred(QPoint)));
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

///
/// \brief MainWindow::resetDrawToolStatus
///
void MainWindow::resetDrawToolStatus()
{
    this->CurrentDrawTool = DrawToolType::None;
    this->TmpLine = NULL;
    this->TmpCircle = NULL;
    this->TmpPolyline = NULL;
    this->TmpArc = NULL;
    // this->TmpSpiral = NULL;
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
        QLineF newLine(this->TmpLine->line().p1(), pointCoordScene);
        this->TmpLine->setLine(newLine);
    }
    else if (this->TmpLine && event == DrawEventType::LeftClick) {
        QLineF newLine(this->TmpLine->line().p1(), pointCoordScene);
        this->TmpLine->setLine(newLine);

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
    }
    else if (this->TmpCircle && event == DrawEventType::LeftClick)
    {
        QRectF currentRect = this->TmpCircle->rect();
        QPointF center = currentRect.center();
        double radius = QLineF(center, pointCoordScene).length();
        QRectF newRect(center.x() - radius,
                       center.y() - radius,
                       2 * radius,
                       2 * radius);
        this->TmpCircle->setRect(newRect);

        this->TmpCircle->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        Container.push_back(std::move(this->TmpCircle));
    }
}

void MainWindow::drawPolyline(QPointF pointCoordScene, DrawEventType event)
{
    this->setAllItemsMovable(false);

    if (!this->TmpPolyline && event == DrawEventType::LeftClick)
    {
        this->TmpPolyline = std::make_unique<PolylineItem>(QLineF(pointCoordScene, pointCoordScene));
        this->Scene->addItem(this->TmpPolyline.get());
    }
    else if  (this->TmpPolyline && event == DrawEventType::MouseMove)
    {
        QLineF newLine(this->TmpPolyline->tmpline().p1(), pointCoordScene);
        this->TmpPolyline->setLine(newLine,false);
    }
    else if (this->TmpPolyline && event == DrawEventType::LeftClick)
    {
        QLineF confirmLine(this->TmpPolyline->tmpline().p1(), pointCoordScene);
        this->TmpPolyline->setLine(confirmLine,false);

        this->TmpPolyline->setLine(QLineF(pointCoordScene, pointCoordScene),true);
    }
    else if (this->TmpPolyline && event == DrawEventType::RightClick)
    {
        QLineF newLine(this->TmpPolyline->tmpline().p1(), pointCoordScene);
        this->TmpPolyline->setLine(newLine,false);

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
        this->TmpArc->setData(0,QPointF(pointCoordScene));
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

void MainWindow::drawSpiral(QPointF pointCoordScene, DrawEventType event)
{
    this->setAllItemsMovable(false);

    if (!this->TmpLine && event == DrawEventType::LeftClick)
    {
    }
    else if  (this->TmpLine && event == DrawEventType::MouseMove)
    {

    }
    else if (this->TmpLine && event == DrawEventType::LeftClick)
    {

    }
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

///
/// \brief MainWindow::on_drawLineButton_clicked
///
void MainWindow::on_drawTestLineButton_clicked()
{


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

