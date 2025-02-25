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
#include "titlebar.h"
#include "header/CavalierContours/polyline.hpp"
// #include "header/CavalierContours/polylineoffset.hpp"
// #include "utils.h";

///
/// \brief MainWindow::MainWindow
/// \param parent
///
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showMaximized();

    initTitleBar();
    initGraphicsView();
    initButton();
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
    for (auto &item : Manager::getIns().getContainer()) {
        if (item) {
            item->setFlag(QGraphicsItem::ItemIsMovable, movable);
        }
    }
}

void MainWindow::setAllDrawButtonChecked(bool isChecked)
{
    ui->drawArcButton->setChecked(isChecked);
    ui->drawCircleButton->setChecked(isChecked);
    ui->drawEllipseButton->setChecked(isChecked);
    ui->drawPolylineButton->setChecked(isChecked);
    ui->drawPolygonButton->setChecked(isChecked);
    ui->drawRectButton->setChecked(isChecked);
    ui->drawSpiralButton->setChecked(isChecked);
}

void MainWindow::setAllToolButtonChecked(bool isChecked)
{
    ui->resetButton->setChecked(isChecked);
    ui->dragSceneButton->setChecked(isChecked);
    ui->centerButton->setChecked(isChecked);
    ui->createOffsetButton->setChecked(isChecked);
    ui->deleteButton->setChecked(isChecked);
    ui->rotateButton->setChecked(isChecked);
    ui->drawTestLineButton->setChecked(isChecked);
}

///
/// \brief MainWindow::initGraphicsView
///

void MainWindow::initTitleBar()
{
    // this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    // setAttribute(Qt::WA_TranslucentBackground);
    // setAttribute(Qt::WA_DeleteOnClose);

    // this->titleBar = new TitleBar(this);
    // this->titleBar->move(0, 0);

    // connect(m_titleBar, SIGNAL(signalButtonMinClicked()), this, SLOT(onButtonMinClicked()));
    // connect(m_titleBar, SIGNAL(signalButtonRestoreClicked()), this, SLOT(onButtonRestoreClicked()));
    // connect(m_titleBar, SIGNAL(signalButtonMaxClicked()), this, SLOT(onButtonMaxClicked()));
    // connect(m_titleBar, SIGNAL(signalButtonCloseClicked()), this, SLOT(onButtonCloseClicked()));

}

void MainWindow::initGraphicsView()
{
    this->scene=new QGraphicsScene();
    ui->graphicsView->setScene(this->scene);

    // 初始化manager
    Manager::init(this->scene);

    // add axis
    QPen pen(Qt::red);
    pen.setWidth(1);

    QGraphicsLineItem *xAxis=new QGraphicsLineItem(-100,0,100,0);
    QGraphicsLineItem *yAxis=new QGraphicsLineItem(0,-100,0,100);
    xAxis->setPen(pen);
    xAxis->setPos(0,0);
    yAxis->setPen(pen);
    yAxis->setPos(0,0);
    this->scene->addItem(xAxis);
    this->scene->addItem(yAxis);

    QGraphicsLineItem *xArrowL=new QGraphicsLineItem(90,10,100,0);
    QGraphicsLineItem *xArrowR=new QGraphicsLineItem(90,-10,100,0);
    xArrowL->setPen(pen);
    xArrowR->setPen(pen);
    this->scene->addItem(xArrowL);
    this->scene->addItem(xArrowR);

    QGraphicsLineItem *yArrowL=new QGraphicsLineItem(10,90,0,100);
    QGraphicsLineItem *yArrowR=new QGraphicsLineItem(-10,90,0,100);
    yArrowL->setPen(pen);
    yArrowR->setPen(pen);
    this->scene->addItem(yArrowL);
    this->scene->addItem(yArrowR);

    // 锁定当前场景矩形
    this->setSceneScale(1.5,1.5);
    this->scene->setSceneRect(scene->sceneRect());

    // 设置初始为没有选框
    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);

    // connect
    // graphicsview组件触发鼠标移动时,会通知mainwindow组件;
    connect(ui->graphicsView,SIGNAL(mousemove_event(QPoint)),
            this,SLOT(on_graphicsview_mousemove_occurred(QPoint)));
    connect(ui->graphicsView,SIGNAL(mouseleftpress_event(QPoint)),
            this,SLOT(on_graphicsview_mouseleftpress_occurred(QPoint)));
    connect(ui->graphicsView,SIGNAL(mouserightpress_event(QPoint)),
            this,SLOT(on_graphicsview_mouserightpress_occurred(QPoint)));
    connect(ui->graphicsView,SIGNAL(mouseleftrelease_event(QPoint)),
            this,SLOT(on_graphicsview_mouseleftrelease_occurred(QPoint)));
    connect(ui->graphicsView,SIGNAL(mouserightrelease_event(QPoint)),
            this,SLOT(on_graphicsview_mouserightrelease_occurred(QPoint)));
    connect(ui->graphicsView,SIGNAL(mousedoubleclick_event(QPoint)),
            this,SLOT(on_graphicsview_mousedoubleclick_occurred(QPoint)));
    connect(ui->graphicsView,SIGNAL(mousewheel_event(QWheelEvent*)),
            this,SLOT(on_graphicsview_mousewheel_occurred(QWheelEvent*)));
}

void MainWindow::initButton()
{
    QString buttonStyle = R"(
        QToolButton {
            border-radius: 15px;
            background-color: #d0d0d0;
            color: black;
            padding: 5px;
        }
        QToolButton:hover {
            background-color: #c0c0c0;
        }
        QToolButton:pressed {
            background-color: #b0b0b0;
        }
        QToolButton:checked {
            background-color: #b0b0b0;
        }
    )";

    QToolButton *dragsceneButton = ui->dragSceneButton;
    dragsceneButton->setIcon(QIcon(":/button/dragSceneButton.svg"));
    dragsceneButton->setIconSize(QSize(30, 30));
    dragsceneButton->setStyleSheet(buttonStyle);
    dragsceneButton->setCheckable(true);
    dragsceneButton->setAutoExclusive(false);
    dragsceneButton->setToolTip("拖动画布；左键拖拽");

    QToolButton *resetButton = ui->resetButton;
    resetButton->setIcon(QIcon(":/button/resetButton.svg"));
    resetButton->setIconSize(QSize(30, 30));
    resetButton->setStyleSheet(buttonStyle);
    resetButton->setCheckable(true);
    resetButton->setAutoExclusive(false);
    resetButton->setToolTip("移动对象");

    QToolButton *rotateButton = ui->rotateButton;
    rotateButton->setIcon(QIcon(":/button/rotateButton.svg"));
    rotateButton->setIconSize(QSize(30, 30));
    rotateButton->setStyleSheet(buttonStyle);
    rotateButton->setCheckable(true);
    rotateButton->setAutoExclusive(false);
    rotateButton->setToolTip("旋转对象");

    QToolButton *deleteButton = ui->deleteButton;
    deleteButton->setIcon(QIcon(":/button/deleteButton.svg"));
    deleteButton->setIconSize(QSize(30, 30));
    deleteButton->setStyleSheet(buttonStyle);
    deleteButton->setCheckable(true);
    deleteButton->setAutoExclusive(false);
    deleteButton->setToolTip("删除对象");

    QToolButton *drawTestLineButton = ui->drawTestLineButton;
    drawTestLineButton->setIcon(QIcon(":/button/drawTestLineButton.svg"));
    drawTestLineButton->setIconSize(QSize(30, 30));
    drawTestLineButton->setStyleSheet(buttonStyle);
    drawTestLineButton->setCheckable(true);
    drawTestLineButton->setAutoExclusive(false);
    drawTestLineButton->setToolTip("测试按钮");

    QToolButton *createOffsetButton = ui->createOffsetButton;
    createOffsetButton->setIcon(QIcon(":/button/createOffsetButton.svg"));
    createOffsetButton->setIconSize(QSize(30, 30));
    createOffsetButton->setStyleSheet(buttonStyle);
    createOffsetButton->setCheckable(true);
    createOffsetButton->setAutoExclusive(false);
    createOffsetButton->setToolTip("添加填充/offset");

    QToolButton *centerButton = ui->centerButton;
    centerButton->setIcon(QIcon(":/button/centerButton.svg"));
    centerButton->setIconSize(QSize(30, 30));
    centerButton->setStyleSheet(buttonStyle);
    centerButton->setCheckable(true);
    centerButton->setAutoExclusive(false);
    centerButton->setToolTip("移动对象到中心点");

    QToolButton *redoButton = ui->redoButton;
    redoButton->setIcon(QIcon(":/button/redoButton.svg"));
    redoButton->setIconSize(QSize(30, 30));
    redoButton->setStyleSheet(buttonStyle);
    redoButton->setCheckable(true);
    redoButton->setAutoExclusive(false);
    redoButton->setToolTip("移动对象到中心点");

    QToolButton *undoButton = ui->undoButton;
    undoButton->setIcon(QIcon(":/button/undoButton.svg"));
    undoButton->setIconSize(QSize(30, 30));
    undoButton->setStyleSheet(buttonStyle);
    undoButton->setCheckable(true);
    undoButton->setAutoExclusive(false);
    undoButton->setToolTip("移动对象到中心点");



    // 绘制工具
    QToolButton *drawPolylineButton = ui->drawPolylineButton;
    drawPolylineButton->setIcon(QIcon(":/button/drawPolylineButton.svg"));
    drawPolylineButton->setIconSize(QSize(30, 30));
    drawPolylineButton->setStyleSheet(buttonStyle);
    drawPolylineButton->setCheckable(true);
    drawPolylineButton->setAutoExclusive(false);
    drawPolylineButton->setToolTip(
        "<html><head/>"
        "<body>"
         "<p><span style=\" font-weight:700;\">多段线工具</span></p>"
        "<p>绘制多段线</p>"
        "<p>长按ctrl切换绘制直线/圆弧；"
        "</p><p>按下capslock切换圆弧方向；"
        "</p><p>长按x/y锁定绘制方向</p></body></html>"
        "</body></html>"
        );


    QToolButton *drawArcButton = ui->drawArcButton;
    drawArcButton->setIcon(QIcon(":/button/drawArcButton.svg"));
    drawArcButton->setIconSize(QSize(30, 30));
    drawArcButton->setStyleSheet(buttonStyle);
    drawArcButton->setCheckable(true);
    drawArcButton->setAutoExclusive(false);
    drawArcButton->setToolTip(
        "<html><head/>"
        "<body>"
        "<p><span style=\"font-weight:700;\">弧形工具</span></p>"
        "<p>绘制半弧</p>"
        "<p>左键点击设置初始点；左键再次点击设置结束点</p>"
        "</body></html>"
        );



    QToolButton *drawCircleButton = ui->drawCircleButton;
    drawCircleButton->setIcon(QIcon(":/button/drawCircleButton.svg"));
    drawCircleButton->setIconSize(QSize(30, 30));
    drawCircleButton->setStyleSheet(buttonStyle);
    drawCircleButton->setCheckable(true);
    drawCircleButton->setAutoExclusive(false);
    drawCircleButton->setToolTip(
        "<html><head/>"
        "<body>"
        "<p><span style=\"font-weight:700;\">圆形工具</span></p>"
        "<p>绘制圆</p>"
        "<p>左键点击设置圆心；左键再次点击设置圆弧大小</p>"
        "</body></html>"
        );

    QToolButton *drawEllipseButton = ui->drawEllipseButton;
    drawEllipseButton->setIcon(QIcon(":/button/drawEllipseButton.svg"));
    drawEllipseButton->setIconSize(QSize(30, 30));
    drawEllipseButton->setStyleSheet(buttonStyle);
    drawEllipseButton->setCheckable(true);
    drawEllipseButton->setAutoExclusive(false);
    drawEllipseButton->setToolTip(
        "<html><head/>"
        "<body>"
        "<p><span style=\"font-weight:700;\">椭圆工具</span></p>"
        "<p>绘制椭圆</p>"
        "<p>左键点击设置圆心；左键再次点击确定一个方向上的椭圆半径；再次拉动鼠标点击确定垂直方向上的另一个椭圆半径</p>"
        "</body></html>"
        );

    QToolButton *drawRectButton = ui->drawRectButton;
    drawRectButton->setIcon(QIcon(":/button/drawRectButton.svg"));
    drawRectButton->setIconSize(QSize(30, 30));
    drawRectButton->setStyleSheet(buttonStyle);
    drawRectButton->setCheckable(true);
    drawRectButton->setAutoExclusive(false);
    drawRectButton->setToolTip(
        "<html><head/>"
        "<body>"
        "<p><span style=\"font-weight:700;\">矩形工具</span></p>"
        "<p>绘制矩形</p>"
        "<p>左键点击设置矩形左上顶点，左键再次点击设置矩形右下顶点</p>"
        "</body></html>"
        );

    QToolButton *drawPolygonButton = ui->drawPolygonButton;
    drawPolygonButton->setIcon(QIcon(":/button/drawPolygonButton.svg"));
    drawPolygonButton->setIconSize(QSize(30, 30));
    drawPolygonButton->setStyleSheet(buttonStyle);
    drawPolygonButton->setCheckable(true);
    drawPolygonButton->setAutoExclusive(false);
    drawPolygonButton->setToolTip(
        "<html><head/>"
        "<body>"
        "<p><span style=\"font-weight:700;\">正多边形工具</span></p>"
        "<p>绘制正多边形</p>"
        "<p>按w添加多边形边数；按s减少多边形变数（最小为3）</p>"
        "</body></html>"
        );

    QToolButton *drawSpiralButton = ui->drawSpiralButton;
    drawSpiralButton->setIcon(QIcon(":/button/drawSpiralButton.svg"));
    drawSpiralButton->setIconSize(QSize(30, 30));
    drawSpiralButton->setStyleSheet(buttonStyle);
    drawSpiralButton->setCheckable(true);
    drawSpiralButton->setAutoExclusive(false);
    drawSpiralButton->setToolTip(
        "<html><head/>"
        "<body>"
        "<p><span style=\"font-weight:700;\">螺旋线工具</span></p>"
        "<p>绘制螺旋线</p>"
        "<p>左键点击设置多边形中心；左键再次点击设置多边形大小</p>"
        "<p>按w添加多边形边数；按s减少多边形变数（最小为3）</p>"
        "</body></html>"
        );
}

void MainWindow::initStatusBar()
{
    this->labelMouseCoordinate = new QLabel("coordinate: ");
    this->labelMouseCoordinate->setMinimumWidth(150);
    ui->statusBar->addWidget(this->labelMouseCoordinate);
    this->labelOperation = new QLabel("operation: ");
    this->labelOperation->setMinimumWidth(300);
    ui->statusBar->addWidget(this->labelOperation);
}

void MainWindow::initOperationTreeWidget()
{
    ui->operationTreeWidget->setHeaderLabel("Operation List");

    // QTreeWidgetItem *parentItem1 = new QTreeWidgetItem(ui->operationTreeWidget, QStringList("Parent1"));
    // QTreeWidgetItem *childItem1 = new QTreeWidgetItem(parentItem1, QStringList("Child1"));
    // ui->operationTreeWidget->addTopLevelItem(parentItem1);
    // QTreeWidgetItem *parentItem2 = new QTreeWidgetItem(ui->operationTreeWidget, QStringList("Parent1"));
    // QTreeWidgetItem *childItem2 = new QTreeWidgetItem(parentItem2, QStringList("Child2"));
    // ui->operationTreeWidget->addTopLevelItem(parentItem2);
}

void MainWindow::initPropertyTableWidget()
{
    ui->propertyTableWidget->setColumnCount(2);
    ui->propertyTableWidget->setHorizontalHeaderLabels(
        QStringList() << "property" << "value" );
}

void MainWindow::displayOperation(QString text)
{
    this->labelOperation->setText("operation: "+ text);
}

void MainWindow::dragScene(QPointF pointCoordscene, DrawEventType event)
{
    if (event == DrawEventType::LeftPress)
    {
        displayOperation("drag scene right press");
        auto pointCoordView = ui->graphicsView->mapFromScene(pointCoordscene);
        this->dragScenePoint = pointCoordView;
    }
    else if (event == DrawEventType::MouseMove)
    {
        displayOperation("drag scene mouse move");
        auto pointCoordView = ui->graphicsView->mapFromScene(pointCoordscene);

        QPointF delta =  this->dragScenePoint - pointCoordView;
        delta = QPointF(delta.x()/getSceneScale().first, delta.y()/getSceneScale().second);
        qDebug() << pointCoordView  << this->dragScenePoint <<delta;
        this->dragScenePoint = pointCoordView;

        auto newRect = this->scene->sceneRect().adjusted(delta.x(),delta.y(),delta.x(),delta.y());
        this->scene->setSceneRect(newRect);
    }
    else if (event == DrawEventType::LeftRelease)
    {
        displayOperation("drag scene right release");
        this->dragScenePoint = QPointF(0,0);
    }
}

void MainWindow::copyItem()
{

}

void MainWindow::deleteItem()
{

}

void MainWindow::setSceneScale(double x, double y)
{
    if (x <=0 || y<=0)
    {
        displayOperation("error scene scale");
        return;
    }

    ui->graphicsView->scale(x,y);
    this->sceneScale.first *= x;
    this->sceneScale.second *= y;
}

std::pair<double, double> MainWindow::getSceneScale()
{
    return this->sceneScale;
}

///
/// \brief MainWindow::editItem
/// \param pointCoordscene
///
void MainWindow::editItem(QPointF pointCoordscene,DrawEventType event)
{
    if (this->scene->selectedItems().empty())
        return;

    this->currentEditItem = this->scene->selectedItems()[0];
    switch (this->currentEditItem->type()) {
        case QGraphicsEllipseItem::Type:
        {
            QGraphicsEllipseItem *CircleItem = static_cast<QGraphicsEllipseItem*>(this->currentEditItem);
            this->editCircle(CircleItem,event);
            break;
        }
        case PolylineItem::Type:
        {
            PolylineItem *polylineItem = static_cast<PolylineItem*>(this->currentEditItem);
            this->editPolyline(pointCoordscene,polylineItem,event);
            break;
        }
        default:
        {
            displayOperation("undefine object");
        }
    };
}

void MainWindow::editLine(QGraphicsLineItem *lineItem,DrawEventType event)
{
    if (event == DrawEventType::LeftRelease)
    {
        // 先初始化
        ui->propertyTableWidget->clearContents();
        ui->propertyTableWidget->setRowCount(0);

        // 起始点和结束点是属性 不会随着拖拽改变;只用scenePos会在拖拽时记录与起始点的偏移量;
        QLineF line = lineItem->line();
        QPointF offset = lineItem->scenePos();
        QPointF startPoint = line.p1() + offset;
        QPointF endPoint = line.p2() + offset;
        QPointF centerPoint = (startPoint + endPoint)/2;

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
}

void MainWindow::editCircle(QGraphicsEllipseItem * circleItem, DrawEventType event)
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


    // // 把对象的属性映射到属性修改面板
    // // 先blocksignal,不然会频繁触发修改属性table的回调
    // ui->propertyTableWidget->blockSignals(true);

    // // 映射属性
    // int row = ui->propertyTableWidget->rowCount();
    // ui->propertyTableWidget->insertRow(row);
    // QTableWidgetItem *centerPointXName = new QTableWidgetItem("centerPoint.x");
    // QTableWidgetItem *centerPointXValue = new QTableWidgetItem(QString::number(centerPoint.x()));
    // centerPointXName->setFlags(centerPointXName->flags() & ~Qt::ItemIsEditable);
    // centerPointXValue->setFlags(centerPointXValue->flags() | Qt::ItemIsEditable);
    // ui->propertyTableWidget->setItem(row, 0, centerPointXName);
    // ui->propertyTableWidget->setItem(row, 1, centerPointXValue);

    // row = ui->propertyTableWidget->rowCount();
    // ui->propertyTableWidget->insertRow(row);
    // QTableWidgetItem *centerPointYName = new QTableWidgetItem("centerPoint.y");
    // QTableWidgetItem *centerPointYValue = new QTableWidgetItem(QString::number(centerPoint.y()));
    // centerPointYName->setFlags(centerPointYName->flags() & ~Qt::ItemIsEditable);
    // centerPointYValue->setFlags(centerPointYValue->flags() | Qt::ItemIsEditable);
    // ui->propertyTableWidget->setItem(row, 0, centerPointYName);
    // ui->propertyTableWidget->setItem(row, 1, centerPointYValue);

    // row = ui->propertyTableWidget->rowCount();
    // ui->propertyTableWidget->insertRow(row);
    // QTableWidgetItem *radiusName = new QTableWidgetItem("radius");
    // QTableWidgetItem *radiusValue = new QTableWidgetItem(QString::number(circleItem->rect().width()));
    // radiusName->setFlags(radiusName->flags() & ~Qt::ItemIsEditable);
    // radiusValue->setFlags(radiusValue->flags() | Qt::ItemIsEditable);
    // ui->propertyTableWidget->setItem(row, 0, radiusName);
    // ui->propertyTableWidget->setItem(row, 1, radiusValue);

    // ui->propertyTableWidget->blockSignals(false);
}

void MainWindow::editPolyline(QPointF pointCoordscene, PolylineItem* polylineItem,DrawEventType event)
{
    if (!polylineItem) return;
    displayOperation("edit polyline, center: " +
                     QString::number(polylineItem->getCenterPos().x())  +
                     " " +
                     QString::number(polylineItem->getCenterPos().y()));
    // qDebug() << "edit Polyline: current edit vertex " << this->CurrentEditPolylineVertexIndex;

    // 图形上直接编辑操作点；
    if (this->currentEditPolylineVertexIndex == -1 && event == DrawEventType::LeftRelease)
    {
        double minDistance = 100;

        for (int i = 0; i < polylineItem->getSize(); ++i) {
            double distance = QLineF(pointCoordscene, polylineItem->getVertexPos(i)).length();
            qDebug() << "distance ?<10: " << distance ;
            if (distance <= 10.0 && distance < minDistance) {
                minDistance = distance;
                this->currentEditPolylineVertexIndex = i;
                qDebug() << "setindex to" << this->currentEditPolylineVertexIndex;
            }
        }
    }
    else if (this->currentEditPolylineVertexIndex != -1 && event == DrawEventType::MouseMove)
    {
        double bulge = polylineItem->getVertex(this->currentEditPolylineVertexIndex).bulge;
        polylineItem->editVertex(this->currentEditPolylineVertexIndex,pointCoordscene ,bulge);
        // 注意这里输入的是绝对坐标 所以要减去相对坐标！
    }
    else if (this->currentEditPolylineVertexIndex != -1 && event == DrawEventType::LeftRelease)
    {
        this->currentEditPolylineVertexIndex = -1;
        this->currentEditItem =NULL;
    }
    else
    {
        displayOperation("unknow edit polyline event");
    }


    // 在左侧区域操作参数
    if (event == DrawEventType::LeftRelease)
    {
        // 先初始化属性栏
        ui->propertyTableWidget->clearContents();
        ui->propertyTableWidget->setRowCount(0);

        // 把对象的属性映射到属性修改面板
        // 先blocksignal,不然会频繁触发修改属性table的回调
        ui->propertyTableWidget->blockSignals(true);

        // 映射属性
        int row = ui->propertyTableWidget->rowCount();
        ui->propertyTableWidget->insertRow(row);
        QTableWidgetItem *offsetName = new QTableWidgetItem("offset");
        QTableWidgetItem *offsetValue = new QTableWidgetItem(polylineItem->getOffset());
        offsetName->setFlags(offsetName->flags() & ~Qt::ItemIsEditable);
        offsetValue->setFlags(offsetValue->flags() | Qt::ItemIsEditable);
        ui->propertyTableWidget->setItem(row, 0,offsetName);
        ui->propertyTableWidget->setItem(row, 1, offsetValue);

        ui->propertyTableWidget->insertRow(row);
        QTableWidgetItem *offsetNumName = new QTableWidgetItem("offsetNum");
        QTableWidgetItem *offsetNumValue = new QTableWidgetItem(polylineItem->getOffset());
        offsetNumName->setFlags(offsetNumName->flags() & ~Qt::ItemIsEditable);
        offsetNumValue->setFlags(offsetNumValue->flags() | Qt::ItemIsEditable);
        ui->propertyTableWidget->setItem(row, 0,offsetNumName);
        ui->propertyTableWidget->setItem(row, 1, offsetNumValue);

        ui->propertyTableWidget->blockSignals(false);
    }
}

///
/// \brief MainWindow::resetDrawToolStatus
///
void MainWindow::resetDrawToolStatus()
{
    this->currentDrawTool = DrawToolType::None;
    this->polygonEdgeNum = 3;
    this->tmpCircle = NULL;
    this->tmpPolyline = NULL;
    this->tmpArc = NULL;
    this->tmpRect = NULL;
    this->tmpSpiral = NULL;
    this->tmpPolygon = NULL;
    this->tmpEllipse = NULL;
}

/*void MainWindow::drawLine(QPointF pointCoordscene,DrawEventType event)
{
    this->setAllItemsMovable(false);

    if (!this->tmpLine && event == DrawEventType::LeftRelease)
    {
        this->tmpLine = std::make_shared<QGraphicsLineItem>(QLineF(pointCoordscene, pointCoordscene));
        this->tmpLine->setPen(QPen(Qt::black, 1));
        this->scene->addItem(this->tmpLine.get());
    }
    else if  (this->tmpLine && event == DrawEventType::MouseMove)
    {
        QLineF newLine;
        QPointF endPoint = pointCoordscene;
        if (Manager::getIns().IsXHold)
            endPoint = QPointF(pointCoordscene.x(), this->tmpLine->line().p1().y());
        else if (Manager::getIns().IsYHold)
                    endPoint = QPointF(this->tmpLine->line().p1().x(), pointCoordscene.y());
        newLine = QLineF(this->tmpLine->line().p1(), endPoint);
        this->tmpLine->setLine(newLine);
        this->tmpLine->setTransformOriginPoint(newLine.center());
    }
    else if (this->tmpLine && event == DrawEventType::LeftRelease) {
        this->tmpLine->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        Manager::getIns().addItem(std::move(this->tmpLine));
    }
}*/

void MainWindow::drawCircle(QPointF pointCoordscene,DrawEventType event)
{
    this->setAllItemsMovable(false);

    if (!this->tmpCircle && event == DrawEventType::LeftRelease)
    {
        QRectF initialRect(pointCoordscene.x(), pointCoordscene.y(), 0, 0);
        this->tmpCircle = std::make_shared<QGraphicsEllipseItem>(initialRect);
        this->tmpCircle->setPen(QPen(Qt::black, 1));
        scene->addItem(this->tmpCircle.get());
    }
    else if  (this->tmpCircle && event == DrawEventType::MouseMove)
    {
        QRectF currentRect = this->tmpCircle->rect();
        QPointF center = currentRect.center();
        double radius = QLineF(center, pointCoordscene).length();
        QRectF newRect(center.x() - radius,
                       center.y() - radius,
                       2 * radius,
                       2 * radius);
        this->tmpCircle->setRect(newRect);
        this->tmpCircle->setTransformOriginPoint(center);
    }
    else if (this->tmpCircle && event == DrawEventType::LeftRelease)
    {
        this->tmpCircle->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
         Manager::getIns().addItem(std::move(this->tmpCircle));
    }
}

void MainWindow::drawPolyline(QPointF pointCoordscene, DrawEventType event)
{
    this->setAllItemsMovable(false);

    if (!this->tmpPolyline && event == DrawEventType::LeftRelease)
    {
        this->tmpPolyline = std::make_shared<PolylineItem>();
        this->scene->addItem(this->tmpPolyline.get());

        this->tmpPolyline->addVertex(pointCoordscene,0);
        this->tmpPolyline->addVertex(pointCoordscene,0);
    }
    else if  (this->tmpPolyline && event == DrawEventType::MouseMove)
    {
        int index = this->tmpPolyline->getSize()-1;
        if (!Manager::getIns().IsControlHold)
        {
            QPointF lastPoint = this->tmpPolyline->getVertex(index - 1).point;
            if (Manager::getIns().IsXHold)
                this->tmpPolyline->editVertex(index,QPointF(pointCoordscene.x(),lastPoint.y()),0);
            else if (Manager::getIns().IsYHold)
                this->tmpPolyline->editVertex(index,QPointF(lastPoint.x(),pointCoordscene.y()),0);
            else
                this->tmpPolyline->editVertex(index,pointCoordscene,0);
        }
        else
        {
            if (!Manager::getIns().IsCapsLocked)
                this->tmpPolyline->editVertex(index, pointCoordscene,1);
            else
                 this->tmpPolyline->editVertex(index, pointCoordscene,-1);
        }
    }
    else if (this->tmpPolyline && event == DrawEventType::LeftRelease)
    {
        this->tmpPolyline->addVertex(pointCoordscene,0);
    }
    else if (this->tmpPolyline && event == DrawEventType::RightRelease)
    {
        this->tmpPolyline->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        Manager::getIns().addItem(std::move(this->tmpPolyline));
    }
}

void MainWindow::drawArc(QPointF pointCoordscene, DrawEventType event)
{
    this->setAllItemsMovable(false);

    if (!this->tmpArc && event == DrawEventType::LeftRelease)
    {
        this->tmpArc = std::make_shared<ArcItem>();
        scene->addItem(this->tmpArc.get());

        this->tmpArc->editVertex(0,pointCoordscene,0);
        this->tmpArc->editVertex(1,pointCoordscene,0);
         qDebug() << "1";
    }
    else if  (this->tmpArc && event == DrawEventType::MouseMove)
    {
        this->tmpArc->editVertex(1,pointCoordscene,1);
    }
    else if (this->tmpArc && event == DrawEventType::LeftRelease)
    {
        this->tmpArc->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        Manager::getIns().addItem(std::move(this->tmpArc));
    }
}

/*void MainWindow::drawVariantLine(QPointF pointCoordscene, DrawEventType event)
{
    this->setAllItemsMovable(false);
    if (!this->tmpVariantLine && event == DrawEventType::LeftRelease)
    {
        this->tmpVariantLine = std::make_shared<VariantLineItem>(QPointF(pointCoordscene));
        this->scene->addItem(this->tmpVariantLine.get());

        this->tmpVariantLine->setLine(pointCoordscene,true,VariantLineItem::Line);
    }
    else if  (this->tmpVariantLine && event == DrawEventType::MouseMove)
    {
        if (!Manager::getIns().IsControlHold)
            this->tmpVariantLine->setLine(pointCoordscene,false,VariantLineItem::Line);
        else
            this->tmpVariantLine->setLine(pointCoordscene,false,VariantLineItem::Arc);
    }
    else if (this->tmpVariantLine && event == DrawEventType::LeftRelease)
    {
        if (!Manager::getIns().IsControlHold)
            this->tmpVariantLine->setLine(pointCoordscene,true,VariantLineItem::Line);
        else
            this->tmpVariantLine->setLine(pointCoordscene,true,VariantLineItem::Arc);
    }
    else if (this->tmpVariantLine && event == DrawEventType::RightRelease)
    {
        this->tmpVariantLine->setTransformOriginPoint(this->tmpVariantLine->getCenter());
        this->tmpVariantLine->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
         Manager::getIns().addItem(std::move(this->tmpVariantLine));
    }
}*/

void MainWindow::drawRect(QPointF pointCoordscene, DrawEventType event)
{
    this->setAllItemsMovable(false);

    if (!this->tmpRect && event == DrawEventType::LeftRelease)
    {
        this->tmpRect = std::make_shared<QGraphicsRectItem>(pointCoordscene.x(), pointCoordscene.y(),0,0);
        this->tmpRect->setPen(QPen(Qt::black, 1));
        this->scene->addItem(this->tmpRect.get());
    }
    else if  (this->tmpRect && event == DrawEventType::MouseMove)
    {
        qreal width = pointCoordscene.x() - this->tmpRect->rect().topLeft().x();
        qreal height = pointCoordscene.y() - this->tmpRect->rect().topLeft().y();
        QRectF newRect(this->tmpRect->rect().topLeft().x(),this->tmpRect->rect().topLeft().y(),width,height);
        this->tmpRect->setRect(newRect);
    }
    else if (this->tmpRect && event == DrawEventType::LeftRelease) {
        this->tmpRect->setTransformOriginPoint(this->tmpRect->rect().center());
        this->tmpRect->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
         Manager::getIns().addItem(std::move(this->tmpRect));
    }
}

void MainWindow::drawSpiral(QPointF pointCoordscene, DrawEventType event)
{
    this->setAllItemsMovable(false);
    /* center：螺旋的中心点
        radius：螺旋的初始半径
        spacing：每圈的间距
        turns：螺旋的圈数*/

    if (!this->tmpSpiral && event == DrawEventType::LeftRelease)
    {
        QPointF centerPoint  = pointCoordscene;
        this->tmpSpiral =  std::make_shared<QGraphicsPathItem>();
        this->tmpSpiral->setData(0,pointCoordscene);
        this->tmpSpiral->setPen(QPen(Qt::black, 1));
        scene->addItem(this->tmpSpiral.get());
    }
    else if  (this->tmpSpiral && event == DrawEventType::MouseMove)
    {
        // 这里都是设置了一个演示默认值；
        QPointF centerPoint = this->tmpSpiral->data(0).toPointF();
        QPointF endPoint = pointCoordscene;
        int turns = 3;
        double radius = QLineF(centerPoint,endPoint).length()/2;
        double spacing = QLineF(centerPoint,endPoint).length()/6;
        double dx = endPoint.x() - centerPoint.x();
        double dy = endPoint.y() - centerPoint.y();

        QPainterPath path;
        bool start = true;
        for (double theta = 0; theta < turns * 2 * M_PI; theta += 0.1)
        {
            double r = radius + spacing * theta / (2 * M_PI);
            double x = centerPoint.x() + r * cos(theta);
            double y = centerPoint.y() + r * sin(theta);

            if (start == true)
            {
                path.moveTo(centerPoint.x() + r * cos(theta),centerPoint.y()+r* sin(theta));
                start = false;
            } else
            {
                path.lineTo(x, y);
            }
        }
        this->tmpSpiral->setTransformOriginPoint(centerPoint);
        this->tmpSpiral->setRotation(atan2(dy, dx)* 180 / M_PI);

        this->tmpSpiral->setPath(path);
    }
    else if (this->tmpSpiral && event == DrawEventType::LeftRelease)
    {
        this->tmpSpiral->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
         Manager::getIns().addItem(std::move(this->tmpSpiral));
    }
}

void MainWindow::drawPolygon(QPointF pointCoordscene, DrawEventType event)
{
    this->setAllItemsMovable(false);

    if (!this->tmpPolygon && event == DrawEventType::LeftRelease)
    {
        this->tmpPolygon = std::make_shared<QGraphicsPolygonItem>();
        this->tmpPolygon->setData(0,pointCoordscene);
        this->tmpPolygon->setPen(QPen(Qt::black, 1));
        this->scene->addItem(this->tmpPolygon.get());
    }
    else if  (this->tmpPolygon && event == DrawEventType::MouseMove)
    {
        QPolygonF newPolygon;

        QPointF centerPoint = this->tmpPolygon->data(0).toPointF();
        double radius = QLineF(centerPoint,pointCoordscene).length();
        int edgeNum = polygonEdgeNum;

        double angleStep = 2 * M_PI / edgeNum;
        for (int i =0;i<edgeNum;i++) {
            double angle = i * angleStep - M_PI/2;
            QPointF Vertex(centerPoint.x()+radius*cos(angle),centerPoint.y()+radius*sin(angle));
            newPolygon << Vertex;
        }

        this->tmpPolygon->setPolygon(newPolygon);
        this->tmpPolygon->setTransformOriginPoint(centerPoint);
    }
    else if (this->tmpPolygon && event == DrawEventType::LeftRelease) {
        this->tmpPolygon->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        Manager::getIns().addItem(std::move(this->tmpPolygon));
    }
}

void MainWindow::drawEllipse(QPointF pointCoordscene, DrawEventType event)
{
    this->setAllItemsMovable(false);

    if (!this->tmpEllipse && event == DrawEventType::LeftRelease)
    {
        QRectF initialRect(pointCoordscene.x(), pointCoordscene.y(), 0, 0);
        this->tmpEllipse = std::make_shared<QGraphicsEllipseItem>(initialRect);
        this->tmpEllipse->setPen(QPen(Qt::black, 1));
        scene->addItem(this->tmpEllipse.get());
    }
    else if  (this->tmpEllipse && event == DrawEventType::MouseMove)
    {
        if (!this->tmpEllipse->data(0).isValid()) {
            QRectF currentRect = this->tmpEllipse->rect();
            QPointF center = currentRect.center();
            double radius = QLineF(center, pointCoordscene).length();
            QRectF newRect(center.x() - radius,
                           center.y() - radius,
                           2 * radius,
                           2 * radius);
            this->tmpEllipse->setRect(newRect);
        } else {
            QPointF firstAxisPoint = this->tmpEllipse->data(0).toPointF();
            QRectF currentRect = this->tmpEllipse->rect();
            QPointF center = currentRect.center();

            double majorAxis = QLineF(center, firstAxisPoint).length();

            double dx = firstAxisPoint.x() - center.x();
            double dy = firstAxisPoint.y() - center.y();
            double theta = atan2(dy, dx);

            QLineF axisLine(center, firstAxisPoint);
            QLineF perpendicularLine = axisLine.normalVector();
            QPointF perpendicularPoint = perpendicularLine.p2();
            double minorAxis = QLineF(center, pointCoordscene).length();

            QRectF finalRect(center.x() - majorAxis, center.y() - minorAxis,
                             2 * majorAxis, 2 * minorAxis);

            this->tmpEllipse->setRect(finalRect);

            this->tmpEllipse->setTransformOriginPoint(center);
            this->tmpEllipse->setRotation(theta * 180 / M_PI);
        }

    }
    else if (this->tmpEllipse && event == DrawEventType::LeftRelease)
    {
        if (!this->tmpEllipse->data(0).isValid()) {
            this->tmpEllipse->setData(0,pointCoordscene);
        } else {
            this->tmpEllipse->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
         Manager::getIns().addItem(std::move(this->tmpEllipse));
        }
    }
}

///
/// \brief MainWindow::keyPressEvent
/// \param event
///
void MainWindow::keyPressEvent(QKeyEvent * event)
{
    switch(event->key())
    {
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
        break;
    }

    case Qt::Key_W:
    {
        this->polygonEdgeNum +=1;
        break;
    }
    case Qt::Key_S:
    {
        if (this->polygonEdgeNum>3){
            this->polygonEdgeNum -=1;
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
        break;
    }
    case Qt::Key_2:
    {
        break;
    }
    case Qt::Key_3:
    {
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
    QPointF pointCoordscene = ui->graphicsView->mapToScene(pointCoordView);

    // 显示坐标在statusbar里
    this->labelMouseCoordinate->setText(
        QString::asprintf(
            "coordinate: x:%.0f,y:%.0f",
            pointCoordscene.x(),
            pointCoordscene.y()
        )
    );

    // 非拖拽行为
    if (Manager::getIns().IsMouseLeftButtonHold == false && Manager::getIns().IsMouseRightButtonHold == false)
    {
        switch (this->currentDrawTool)
        {
            case DrawToolType::None:
            {
                this->editItem(pointCoordscene,DrawEventType::MouseMove);
                break;
            }
            case DrawToolType::Circle:
            {
                this->drawCircle(pointCoordscene,DrawEventType::MouseMove);
                break;
            }
            case DrawToolType::Polyline:
            {
                this->drawPolyline(pointCoordscene,DrawEventType::MouseMove);
                break;
            }
            case DrawToolType::Arc:
            {
                this->drawArc(pointCoordscene,DrawEventType::MouseMove);
                break;
            }
            case DrawToolType::Spiral:
            {
                this->drawSpiral(pointCoordscene,DrawEventType::MouseMove);
                break;
            }
            case DrawToolType::Rect:
            {
                this->drawRect(pointCoordscene,DrawEventType::MouseMove);
                break;
            }
            case DrawToolType::Polygon:
            {
                this->drawPolygon(pointCoordscene,DrawEventType::MouseMove);
                break;
            }
            case DrawToolType::Ellipse:
            {
                this->drawEllipse(pointCoordscene,DrawEventType::MouseMove);
                break;
            }

            default:
        {}
        }
    }
    // 左键拖拽
    else if (Manager::getIns().IsMouseLeftButtonHold == true && Manager::getIns().IsMouseRightButtonHold == false)
    {
        switch (this->currentDrawTool)
        {
        case DrawToolType::DragScene:
        {
            this->dragScene(pointCoordscene,DrawEventType::MouseMove);
            break;
        }
        default:
        {}
        }
    }
    // 右键拖拽
    else if (Manager::getIns().IsMouseLeftButtonHold == false && Manager::getIns().IsMouseRightButtonHold == true)
    {
        switch (this->currentDrawTool)
        {
        default:
        {}
        }
    }

}

void MainWindow::on_graphicsview_mouseleftpress_occurred(QPoint pointCoordView)
{
    displayOperation("mouse left press");
    Manager::getIns().IsMouseLeftButtonHold = true;

    QPointF pointCoordscene = ui->graphicsView->mapToScene(pointCoordView);
    switch (this->currentDrawTool)
    {
    case DrawToolType::DragScene:
    {
        this->dragScene(pointCoordscene,DrawEventType::LeftPress);
        break;
    }
    default:
    {}
    }
}

void MainWindow::on_graphicsview_mouserightpress_occurred(QPoint pointCoordView)
{
    displayOperation("mouse right press");
    Manager::getIns().IsMouseRightButtonHold = true;

    QPointF pointCoordscene = ui->graphicsView->mapToScene(pointCoordView);
    switch (this->currentDrawTool)
    {
    case DrawToolType::None:
    {
        break;
    }
    default:
    {}
    }
}

void MainWindow::on_graphicsview_mouseleftrelease_occurred(QPoint pointCoordView)
{
    displayOperation("mouse left release");
    Manager::getIns().IsMouseLeftButtonHold = false;

    QPointF pointCoordscene = ui->graphicsView->mapToScene(pointCoordView);
    switch (this->currentDrawTool)
    {
    case DrawToolType::DragScene:
    {
        this->dragScene(pointCoordscene,DrawEventType::LeftRelease);
        break;
    }

    case DrawToolType::None:
    {
        this->editItem(pointCoordscene,DrawEventType::LeftRelease);
        break;
    }
    case DrawToolType::Circle:
    {
        this->drawCircle(pointCoordscene,DrawEventType::LeftRelease);
        break;
    }
    case DrawToolType::Polyline:
    {
        this->drawPolyline(pointCoordscene,DrawEventType::LeftRelease);
        break;
    }
    case DrawToolType::Arc:
    {
        this->drawArc(pointCoordscene,DrawEventType::LeftRelease);
        break;
    }
    case DrawToolType::Spiral:
    {
        this->drawSpiral(pointCoordscene,DrawEventType::LeftRelease);
        break;
    }
    case DrawToolType::Rect:
    {
        this->drawRect(pointCoordscene,DrawEventType::LeftRelease);
        break;
    }
    case DrawToolType::Polygon:
    {
        this->drawPolygon(pointCoordscene,DrawEventType::LeftRelease);
        break;
    }
    case DrawToolType::Ellipse:
    {
        this->drawEllipse(pointCoordscene,DrawEventType::LeftRelease);
        break;
    }

    default:
    {}
    }
}

void MainWindow::on_graphicsview_mouserightrelease_occurred(QPoint pointCoordView)
{
    displayOperation("mouse right release");
    Manager::getIns().IsMouseRightButtonHold = false;

    QPointF pointCoordscene = ui->graphicsView->mapToScene(pointCoordView);
    switch (this->currentDrawTool) {
    case DrawToolType::None:
    {
        this->editItem(pointCoordscene,DrawEventType::RightRelease);
        break;
    }
    case DrawToolType::Polyline:
    {
        this->drawPolyline(pointCoordscene,DrawEventType::RightRelease);
        break;
    }
    case DrawToolType::Ellipse:
    {
        this->drawEllipse(pointCoordscene,DrawEventType::RightRelease);
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

void MainWindow::on_graphicsview_mousewheel_occurred(QWheelEvent * event)
{
    displayOperation("mouse wheel occourred");
    if (event->angleDelta().y() > 0)
    {
        this->setSceneScale(1.2, 1.2);
    } else {
        this->setSceneScale(0.8, 0.8);
    }
}

///
/// \brief MainWindow::on_drawLineButton_clicked
///
void MainWindow::on_drawCircleButton_clicked()
{
    displayOperation("drawCircle button click");
    this->resetDrawToolStatus();

    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);

    this->setAllDrawButtonChecked(false);
    this->setAllToolButtonChecked(false);
    ui->drawCircleButton->setChecked(true);

    this->currentDrawTool = DrawToolType::Circle;
}

void MainWindow::on_drawPolylineButton_clicked()
{
    displayOperation("drawPolyline button click");
    this->resetDrawToolStatus();

    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);

    this->setAllDrawButtonChecked(false);
    this->setAllToolButtonChecked(false);
    ui->drawPolylineButton->setChecked(true);

    this->currentDrawTool = DrawToolType::Polyline;
}

void MainWindow::on_drawArcButton_clicked()
{
    displayOperation("drawArc button click");
    this->resetDrawToolStatus();

    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);

    this->setAllDrawButtonChecked(false);
    this->setAllToolButtonChecked(false);
    ui->drawArcButton->setChecked(true);

    this->currentDrawTool = DrawToolType::Arc;
}

void MainWindow::on_drawSpiralButton_clicked()
{
    displayOperation("drawSpiral button click");
    this->resetDrawToolStatus();

    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);

    this->setAllDrawButtonChecked(false);
    this->setAllToolButtonChecked(false);
    ui->drawSpiralButton->setChecked(true);

    this->currentDrawTool = DrawToolType::Spiral;
}

void MainWindow::on_drawRectButton_clicked()
{
    displayOperation("drawRect button click");
    this->resetDrawToolStatus();

    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);

    this->setAllDrawButtonChecked(false);
    this->setAllToolButtonChecked(false);
    ui->drawRectButton->setChecked(true);

    this->currentDrawTool = DrawToolType::Rect;
}

void MainWindow::on_drawPolygonButton_clicked()
{
    displayOperation("drawPolygon button click");
    this->resetDrawToolStatus();

    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);

    this->setAllDrawButtonChecked(false);
    this->setAllToolButtonChecked(false);
    ui->drawPolygonButton->setChecked(true);

    this->currentDrawTool = DrawToolType::Polygon;
}

void MainWindow::on_drawEllipseButton_clicked()
{
    displayOperation("drawEllipse button click");
    this->resetDrawToolStatus();

    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);

    this->setAllDrawButtonChecked(false);
    this->setAllToolButtonChecked(false);
    ui->drawEllipseButton->setChecked(true);

    this->currentDrawTool = DrawToolType::Ellipse;
}

///
///  编辑工具
///
void MainWindow::on_resetButton_clicked()
{
    displayOperation("reset button click");

    this->resetDrawToolStatus();

    ui->propertyTableWidget->clearContents();
    ui->propertyTableWidget->setRowCount(0);

    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);

    this->setAllItemsMovable(true);

    this->setAllDrawButtonChecked(false);
    this->setAllToolButtonChecked(false);
    ui->resetButton->setChecked(true);

    this->currentEditItem = NULL;
}

void MainWindow::on_dragSceneButton_clicked()
{
    displayOperation("dragscene button click");

    this->resetDrawToolStatus();

    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);

    this->setAllDrawButtonChecked(false);
    this->setAllToolButtonChecked(false);
    ui->dragSceneButton->setChecked(true);

    this->currentDrawTool = DrawToolType::DragScene;
}

///
/// \brief MainWindow::on_propertyTableWidget_cellChanged
///
void MainWindow::on_propertyTableWidget_cellChanged(int row, int column)
{
    if (this->currentEditItem != NULL) {
        switch (this->currentEditItem->type()) {
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

                QGraphicsLineItem *lineItem = static_cast<QGraphicsLineItem*>(this->currentEditItem);
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

                QGraphicsEllipseItem *circleItem = static_cast<QGraphicsEllipseItem*>(this->currentEditItem);
                QRectF newRect( centerX - radius,
                               centerY - radius,
                               radius,
                               radius);
                circleItem->setPos(QPointF(0,0));
                circleItem->setRect(newRect);
            }
            break;
        }
        case PolylineItem::Type:
        {

            double offset = 0, offsetNum = 0;
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

                if (propertyName == "offset")
                    offset = value;
                else if (propertyName == "offsetNum")
                    offsetNum = value;

                // update
                PolylineItem *polyline = static_cast<PolylineItem*>(this->currentEditItem);
                polyline->createParallelOffset(offset,offsetNum);
                qDebug() << "finish";
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
    displayOperation("rotate button click");
    this->resetDrawToolStatus();
    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    this->setAllDrawButtonChecked(false);
    this->setAllToolButtonChecked(false);
    ui->rotateButton->setChecked(true);

    QList<QGraphicsItem*> selectedItems = this->scene->selectedItems();
    if (selectedItems.empty())
        return;
    for (auto item = selectedItems.cbegin(); item != selectedItems.cend(); ++item)
    {
        auto angle =(*item)->rotation();
        (*item)->setRotation(angle + 90);
    }
}

void MainWindow::on_centerButton_clicked()
{
    displayOperation("center button click");

    this->resetDrawToolStatus();

    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);

    this->setAllDrawButtonChecked(false);
    this->setAllToolButtonChecked(false);
    ui->centerButton->setChecked(true);


    if (!this->currentEditItem) return;

    this->currentEditItem->setPos(QPointF(0,0) - this->currentEditItem->scenePos());
}

void MainWindow::on_createOffsetButton_clicked()
{
    displayOperation("createOffset button click");

    this->resetDrawToolStatus();

    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);

    this->setAllDrawButtonChecked(false);
    this->setAllToolButtonChecked(false);
    ui->createOffsetButton->setChecked(true);


    if (!this->currentEditItem) return;

    switch (this->currentEditItem->type())
    {
    case PolylineItem::Type:
    {
        PolylineItem *polylineItem = static_cast<PolylineItem*>(this->currentEditItem);

        polylineItem->createParallelOffset(20,6);
        break;
    }
    case ArcItem::Type:
    {
        ArcItem *arcItem = static_cast<ArcItem*>(this->currentEditItem);

        arcItem->createParallelOffset(20,6);
        break;
    }
    default:{}
    }
}

void MainWindow::on_deleteButton_clicked()
{
    displayOperation("delete button click");
    this->resetDrawToolStatus();
    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    this->setAllDrawButtonChecked(false);
    this->setAllToolButtonChecked(false);
    ui->deleteButton->setChecked(true);

    QList<QGraphicsItem*> selectedItems = this->scene->selectedItems();
    if (selectedItems.empty())
        return;
    for (auto item = selectedItems.cbegin(); item != selectedItems.cend(); ++item)
    {
       this->scene ->removeItem(*item);
        auto it = std::find_if(Manager::getIns().getContainer().begin(), Manager::getIns().getContainer().end(),
                       [item](const std::shared_ptr<QGraphicsItem>& ptr) {
                           return ptr.get() == *item;
                       });

        if (it != Manager::getIns().getContainer().end()) {
            Manager::getIns().getContainer().erase(it);
        }
    }
}

///
/// test function
///
void printResults(const std::vector<cavc::Polyline<double>>& results) {
for (size_t i = 0; i < results.size(); ++i) {
    const cavc::Polyline<double>& polyline = results[i];
    qDebug() << "Polyline " << i << " (size = " << polyline.size() << "):\n";

    for (size_t j = 0; j < polyline.size(); ++j) {
        double x = polyline.vertexes()[j].x();
        double y = polyline.vertexes()[j].y();
        double bulge = polyline.vertexes()[j].bulge();
        qDebug() << "  Vertex " << j << ": (" << x << ", " << y << "), bulge: " << bulge << "\n";
    }

    qDebug() << "  Closed: " << (polyline.isClosed() ? "Yes" : "No") << "\n";
}
}
void MainWindow::on_drawTestLineButton_clicked()
{
    ///
    ///
    ///



    ///
    /// polyline test
    ///
    /*
    this->tmpPolyline = std::make_shared<PolylineItem>();
    this->scene->addItem(this->tmpPolyline.get());

    this->tmpPolyline->addVertex(QPointF(50,50),0);
    this->tmpPolyline->addVertex(QPointF(50,100),0);
    this->tmpPolyline->addVertex(QPointF(100,100),0);
    // this->tmpPolyline->addVertex(QPointF(100,50),0);
    this->tmpPolyline->createParallelOffset(10,3);
    */


    ///
    /// CC  test
    ///
    // /*
    // cavc::Polyline<double> input;
    // // add vertexes as (x, y, bulge)
    // input.addVertex(0, 0, 0);
    // input.addVertex(0,100,0);
    // input.addVertex(100,100,0);
    // input.addVertex(100,0,0);
    // input.isClosed() = true;

    // std::vector<cavc::Polyline<double>> results = cavc::parallelOffset(input, 10.0);
    // printResults(results);
    // */

    ///
    ///
    ///
    /*QPolygonF newPolygon;
    newPolygon << QPointF(0,0) << QPointF(100,0) << QPointF(100,100) << QPointF(0,100);
    this->tmpPolygon->setPolygon(newPolygon);

    this->tmpPolygon->setTransformOriginPoint(QPointF(50,50));
    this->tmpPolygon->setRotation(180);*/

    ///
    /// rect test
    ///
    /*
    this->tmpRect = std::make_shared<QGraphicsRectItem>(100, 100,50,50);
    this->tmpRect->setPen(QPen(Qt::black, 1));
    this->scene->addItem(this->tmpRect.get());

     QRectF newRect(this->tmpRect->rect().topLeft().x(),this->tmpRect->rect().topLeft().y(),100, 100);
    this->tmpRect->setRect(newRect);
    */

    ///
    /// variant test
    ///
    /*this->tmpVariantLine = std::make_shared<VariantLineItem>(QPointF(1,1));
    this->scene->addItem(this->tmpVariantLine.get());
    this->tmpVariantLine->setLine(QPointF(10,10),true,VariantLineItem::LineType::Line);
    this->tmpVariantLine->setLine(QPointF(20,10),false,VariantLineItem::LineType::Line);
    this->tmpVariantLine->setLine(QPointF(0,20),true,VariantLineItem::LineType::Arc);

     this->tmpVariantLine->setLine(QPointF(10,20),true,VariantLineItem::LineType::Arc);*/

    ///
    /// arc test
    ///
    /*QPoint startPoint(10,10);
    QPoint endPoint(100,100);

    this->tmpArc = std::make_shared<QGraphicsPathItem>();
    this->tmpArc->setData(0,QPointF(startPoint));
    this->tmpArc->setPen(QPen(Qt::black, 1));
    scene->addItem(this->tmpArc.get());


    if(startPoint != this->tmpArc->data(0))
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
    this->tmpArc->setPath(path1);*/

    ///
    /// polyline test
    ///
    /*QLineF line(QPointF(0,0),QPointF(100,100));
    this->tmpPolyline = std::make_shared<PolylineItem>(line);
    this->scene->addItem(this->tmpPolyline.get());

    QLineF line1(QPointF(0,0),QPointF(-100,100));
    this->tmpPolyline->setLine(line1,false);

    QLineF line2(QPointF(-100,100),QPointF(100,100));
    this->tmpPolyline->setLine(line2,true);*/
}








void MainWindow::on_undoButton_clicked()
{

}


void MainWindow::on_redoButton_clicked()
{

}

