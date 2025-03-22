#include "mainwindow.h"
// #include "ui_mainwindow.h"
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
#include <QButtonGroup>
#include <QMenu>
#include "css.h"
// #include "utils.h"
#include "logger.h"
// #include "titlebar.h"
#include "CavalierContours/polyline.hpp"
#include "manager.h"
#include "treeviewmodel.h"
#include "keyboardmanager.h"
#include "uimanager.h"
#include "scenestates.h"


///
/// \brief MainWindow::MainWindow
/// \param parent
///
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    auto ui = std::make_unique<Ui::MainWindow>();
    ui->setupUi(this);
    UiManager::getIns().setUI(std::move(ui));
    // showMaximized();

    initTitleBar();
    initGraphicsView();
    initToolButton();
    initLayerButton();
    initTreeViewModel();
    initPropertyTableWidget();
    initStatusBar();
}

MainWindow::~MainWindow()
{
    // 不用delete,由unique ptr管理内存
    // delete UiManager::getIns().UI();
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
    SceneStates::getIns().scene=new QGraphicsScene();
    UiManager::getIns().UiManager::getIns().UI()->graphicsView->setScene(SceneStates::getIns().scene);

    // add axis
    QPen pen(Qt::red);
    pen.setWidth(1);

    QGraphicsLineItem *xAxis=new QGraphicsLineItem(-100,0,100,0);
    QGraphicsLineItem *yAxis=new QGraphicsLineItem(0,-100,0,100);
    xAxis->setPen(pen);
    xAxis->setPos(0,0);
    yAxis->setPen(pen);
    yAxis->setPos(0,0);
    SceneStates::getIns().scene->addItem(xAxis);
    SceneStates::getIns().scene->addItem(yAxis);

    QGraphicsLineItem *xArrowL=new QGraphicsLineItem(90,10,100,0);
    QGraphicsLineItem *xArrowR=new QGraphicsLineItem(90,-10,100,0);
    xArrowL->setPen(pen);
    xArrowR->setPen(pen);
    SceneStates::getIns().scene->addItem(xArrowL);
    SceneStates::getIns().scene->addItem(xArrowR);

    QGraphicsLineItem *yArrowL=new QGraphicsLineItem(10,90,0,100);
    QGraphicsLineItem *yArrowR=new QGraphicsLineItem(-10,90,0,100);
    yArrowL->setPen(pen);
    yArrowR->setPen(pen);
    SceneStates::getIns().scene->addItem(yArrowL);
    SceneStates::getIns().scene->addItem(yArrowR);

    // 锁定当前场景矩形
    SceneStates::getIns().setSceneScale(1,1);
    SceneStates::getIns().scene->setSceneRect(SceneStates::getIns().scene->sceneRect());

    // 设置初始为没有选框
    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::NoDrag);

    // connect
    // graphicsview组件触发鼠标移动时,会通知mainwindow组件;
    connect(UiManager::getIns().UI()->graphicsView,SIGNAL(mouseMoved(QPoint)),
            this,SLOT(onGraphicsviewMouseMoved(QPoint)));
    connect(UiManager::getIns().UI()->graphicsView,SIGNAL(mouseLeftPressed(QPoint)),
            this,SLOT(onGraphicsviewMouseLeftPressed(QPoint)));
    connect(UiManager::getIns().UI()->graphicsView,SIGNAL(mouseRightPressed(QPoint)),
            this,SLOT(onGraphicsviewMouseRightPressed(QPoint)));
    connect(UiManager::getIns().UI()->graphicsView,SIGNAL(mouseLeftReleased(QPoint)),
            this,SLOT(onGraphicsviewMouseLeftReleased(QPoint)));
    connect(UiManager::getIns().UI()->graphicsView,SIGNAL(mouseRightReleased(QPoint)),
            this,SLOT(onGraphicsviewMouseRightReleased(QPoint)));
    connect(UiManager::getIns().UI()->graphicsView,SIGNAL(mouseDoubleClicked(QPoint)),
            this,SLOT(onGraphicsviewMouseDoubleClicked(QPoint)));
    connect(UiManager::getIns().UI()->graphicsView,SIGNAL(mouseWheelTriggered(QWheelEvent*)),
            this,SLOT(onGraphicsviewMouseWheelTriggered(QWheelEvent*)));
}

void MainWindow::initToolButton()
{
    QString buttonStyle = buttonStyle1;

    QToolButton *dragsceneButton = UiManager::getIns().UI()->dragSceneButton;
    dragsceneButton->setIcon(QIcon(":/button/dragSceneButton.svg"));
    dragsceneButton->setIconSize(QSize(30, 30));
    dragsceneButton->setStyleSheet(buttonStyle);
    dragsceneButton->setCheckable(true);
    dragsceneButton->setAutoExclusive(false);
    dragsceneButton->setToolTip("拖动画布；左键拖拽");

    QToolButton *resetButton = UiManager::getIns().UI()->editButton;
    resetButton->setIcon(QIcon(":/button/resetButton.svg"));
    resetButton->setIconSize(QSize(30, 30));
    resetButton->setStyleSheet(buttonStyle);
    resetButton->setCheckable(true);
    resetButton->setAutoExclusive(false);
    resetButton->setToolTip("移动对象");

    QToolButton *rotateButton = UiManager::getIns().UI()->rotateButton;
    rotateButton->setIcon(QIcon(":/button/rotateButton.svg"));
    rotateButton->setIconSize(QSize(30, 30));
    rotateButton->setStyleSheet(buttonStyle);
    rotateButton->setCheckable(true);
    rotateButton->setAutoExclusive(false);
    rotateButton->setToolTip("旋转对象");

    QToolButton *deleteButton = UiManager::getIns().UI()->deleteButton;
    deleteButton->setIcon(QIcon(":/button/deleteButton.svg"));
    deleteButton->setIconSize(QSize(30, 30));
    deleteButton->setStyleSheet(buttonStyle);
    deleteButton->setCheckable(true);
    deleteButton->setAutoExclusive(false);
    deleteButton->setToolTip("删除对象");

    QToolButton *drawTestLineButton = UiManager::getIns().UI()->drawTestLineButton;
    drawTestLineButton->setIcon(QIcon(":/button/drawTestLineButton.svg"));
    drawTestLineButton->setIconSize(QSize(30, 30));
    drawTestLineButton->setStyleSheet(buttonStyle);
    drawTestLineButton->setCheckable(true);
    drawTestLineButton->setAutoExclusive(false);
    drawTestLineButton->setToolTip("测试按钮");

    QToolButton *createOffsetButton = UiManager::getIns().UI()->createOffsetButton;
    createOffsetButton->setIcon(QIcon(":/button/createOffsetButton.svg"));
    createOffsetButton->setIconSize(QSize(30, 30));
    createOffsetButton->setStyleSheet(buttonStyle);
    createOffsetButton->setCheckable(true);
    createOffsetButton->setAutoExclusive(false);
    createOffsetButton->setToolTip("添加填充/offset");

    QToolButton *centerButton = UiManager::getIns().UI()->centerButton;
    centerButton->setIcon(QIcon(":/button/centerButton.svg"));
    centerButton->setIconSize(QSize(30, 30));
    centerButton->setStyleSheet(buttonStyle);
    centerButton->setCheckable(true);
    centerButton->setAutoExclusive(false);
    centerButton->setToolTip("移动对象到中心点");

    QToolButton *redoButton = UiManager::getIns().UI()->redoButton;
    redoButton->setIcon(QIcon(":/button/redoButton.svg"));
    redoButton->setIconSize(QSize(30, 30));
    redoButton->setStyleSheet(buttonStyle);
    redoButton->setCheckable(true);
    redoButton->setAutoExclusive(false);
    redoButton->setToolTip("移动对象到中心点");

    QToolButton *undoButton = UiManager::getIns().UI()->undoButton;
    undoButton->setIcon(QIcon(":/button/undoButton.svg"));
    undoButton->setIconSize(QSize(30, 30));
    undoButton->setStyleSheet(buttonStyle);
    undoButton->setCheckable(true);
    undoButton->setAutoExclusive(false);
    undoButton->setToolTip("移动对象到中心点");



    // 绘制工具
    QToolButton *drawPolylineButton = UiManager::getIns().UI()->drawPolylineButton;
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


    QToolButton *drawArcButton = UiManager::getIns().UI()->drawArcButton;
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



    QToolButton *drawCircleButton = UiManager::getIns().UI()->drawCircleButton;
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

    QToolButton *drawEllipseButton = UiManager::getIns().UI()->drawEllipseButton;
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

    QToolButton *drawRectButton = UiManager::getIns().UI()->drawRectButton;
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

    QToolButton *drawPolygonButton = UiManager::getIns().UI()->drawPolygonButton;
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

    QToolButton *drawSpiralButton = UiManager::getIns().UI()->drawSpiralButton;
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

///
/// \brief MainWindow::initLayerButton
///
void MainWindow::initLayerButton()
{
    // QLayout *graphicsViewLayout = UiManager::getIns().UI()->mainLayout->findChild<QLayout*>("graphicsViewLayout");
    // QLayout *layerButtonLayout = graphicsViewLayout->findChild<QLayout*>("layerButtonLayout");
    // if (!layerButtonLayout)
    //     FATAL_MSG("layerButtonLayout can not be init");

    // // layout style
    // layerButtonLayout->setAlignment(Qt::AlignLeft);
    // layerButtonLayout->setSpacing(0);

    // //button style
    // auto buttonStyle = buttonStyle1;

    // //button
    // QPushButton *layer1Button = new QPushButton("layer 1");
    // layer1Button->setStyleSheet(buttonStyle);
    // layer1Button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // QPushButton *addLayerButton = new QPushButton("add Layer");
    // addLayerButton->setStyleSheet(buttonStyle);
    // addLayerButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // //
    // layerButtonLayout->addWidget(layer1Button);
    // layerButtonLayout->addWidget(addLayerButton);
    // connect(layer1Button, &QPushButton::clicked, this, [=]() {MainWindow::onLayerButtonClicked(1);} );
    // connect(addLayerButton, &QPushButton::clicked, this, &MainWindow::onAddLayerButtonClicked);

    // // 初始化layer1选中 并存在layerbuttons里
    // layer1Button->setCheckable(true);
    // layer1Button->setChecked(true);
    // // DEBUG_VAR(layer1Button->isCheckable());
    // // DEBUG_VAR(layer1Button->isChecked());
    // this->layerButtons.append(layer1Button);
}

void MainWindow::initStatusBar()
{
    this->labelMouseCoordinate = new QLabel("coordinate: ");
    this->labelMouseCoordinate->setMinimumWidth(150);
    UiManager::getIns().UI()->statusBar->addWidget(this->labelMouseCoordinate);

    this->labelCurrentLayer = new QLabel("layer: ");
    this->labelCurrentLayer->setMinimumWidth(150);
    UiManager::getIns().UI()->statusBar->addWidget(this->labelCurrentLayer);

    this->labelCurrentGroup = new QLabel("layer: ");
    this->labelCurrentGroup->setMinimumWidth(150);
    UiManager::getIns().UI()->statusBar->addWidget(this->labelCurrentGroup);

    this->labelOperation = new QLabel("operation: ");
    this->labelOperation->setMinimumWidth(300);
    UiManager::getIns().UI()->statusBar->addWidget(this->labelOperation);
}

void MainWindow::initPropertyTableWidget()
{
    UiManager::getIns().UI()->propertyTableWidget->setColumnCount(2);
    UiManager::getIns().UI()->propertyTableWidget->setHorizontalHeaderLabels(QStringList() << "property" << "value");
}

void MainWindow::initTreeViewModel()
{
    auto *model = new TreeViewModel("testTreeViewModel", this);

    UiManager::getIns().UI()->treeView->setStyleSheet(treeViewModelStyle1);
    UiManager::getIns().UI()->treeView->setModel(model);
    UiManager::getIns().UI()->treeView->expandAll();

    UiManager::getIns().UI()->treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    UiManager::getIns().UI()->treeView->setDragEnabled(true);
    UiManager::getIns().UI()->treeView->setAcceptDrops(true);
    UiManager::getIns().UI()->treeView->setDropIndicatorShown(true);
    UiManager::getIns().UI()->treeView->setDragDropMode(QAbstractItemView::InternalMove);

    UiManager::getIns().UI()->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(UiManager::getIns().UI()->treeView, &QWidget::customContextMenuRequested, this, &MainWindow::onTreeViewModelShowContextMenu);
    // connect(UiManager::getIns().UI()->treeView, &QTreeView::clicked, this, &MainWindow::onItemClicked);
}

void MainWindow::displayOperation(QString text)
{
    this->labelOperation->setText("operation: "+ text);
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
        KeyboardManager::getIns().IsShiftHold = true;
        break;
    }
    case Qt::Key_Control:
    {
        KeyboardManager::getIns().IsControlHold = true;
        break;
    }

    case Qt::Key_X:
    {
        KeyboardManager::getIns().IsXHold = true;
        break;
    }
    case Qt::Key_Y:
    {
        KeyboardManager::getIns().IsYHold = true;
        break;
    }
    case Qt::Key_Z:
    {
        KeyboardManager::getIns().IsZHold = true;
        break;
    }

    case Qt::Key_CapsLock:
    {
        KeyboardManager::getIns().IsCapsLocked = !KeyboardManager::getIns().IsCapsLocked;
        break;
    }

    case Qt::Key_W:
    {
        // ->polygonEdgeNum +=1;
        break;
    }
    case Qt::Key_S:
    {
        // if (this->polygonEdgeNum>3){
        //     this->polygonEdgeNum -=1;
        // }
        // break;
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
        KeyboardManager::getIns().IsShiftHold = false;
        break;
    }
    case Qt::Key_Control:
    {
        KeyboardManager::getIns().IsControlHold = false;
        break;
    }
    case Qt::Key_X:
    {
        KeyboardManager::getIns().IsXHold = false;
        break;
    }
    case Qt::Key_Y:
    {
        KeyboardManager::getIns().IsYHold = false;
        break;
    }
    case Qt::Key_Z:
    {
        KeyboardManager::getIns().IsZHold = false;
        break;
    }
    }
    displayOperation("keyrelease");
}

///
/// \brief MainWindow::on_graphicsview_mouse_move_triggered
///
void MainWindow::onGraphicsviewMouseMoved(QPoint pointCoordView)
{
    QPointF pointCoordscene = UiManager::getIns().UI()->graphicsView->mapToScene(pointCoordView);

    // 显示坐标在statusbar里
    this->labelMouseCoordinate->setText(
        QString::asprintf(
            "coordinate: x:%.0f,y:%.0f",
            pointCoordscene.x(),
            pointCoordscene.y()
        )
    );
    this->labelCurrentLayer->setText(
        QString::asprintf(
            "layer: %i",
            SceneStates::getIns().currentLayer
            )
        );

    // 非拖拽行为
    if (KeyboardManager::getIns().IsMouseLeftButtonHold == false && KeyboardManager::getIns().IsMouseRightButtonHold == false)
    {
        switch (this->currentDrawTool)
        {
            case DrawToolType::EditProperty:
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
    else if (KeyboardManager::getIns().IsMouseLeftButtonHold == true && KeyboardManager::getIns().IsMouseRightButtonHold == false)
    {
        switch (this->currentDrawTool)
        {
        case DrawToolType::DragScene:
        {
            this->dragScene(pointCoordView,DrawEventType::MouseMove);
            break;
        }
        default:
        {}
        }
    }
    // 右键拖拽
    else if (KeyboardManager::getIns().IsMouseLeftButtonHold == false && KeyboardManager::getIns().IsMouseRightButtonHold == true)
    {
        switch (this->currentDrawTool)
        {
        default:
        {}
        }
    }

}

void MainWindow::onGraphicsviewMouseLeftPressed(QPoint pointCoordView)
{
    displayOperation("mouse left press");
    KeyboardManager::getIns().IsMouseLeftButtonHold = true;

    QPointF pointCoordscene = UiManager::getIns().UI()->graphicsView->mapToScene(pointCoordView);
    switch (this->currentDrawTool)
    {
    case DrawToolType::DragScene:
    {
        this->dragScene(pointCoordView,DrawEventType::LeftPress);
        break;
    }
    default:
    {}
    }
}

void MainWindow::onGraphicsviewMouseRightPressed(QPoint pointCoordView)
{
    displayOperation("mouse right press");
    KeyboardManager::getIns().IsMouseRightButtonHold = true;

    QPointF pointCoordscene = UiManager::getIns().UI()->graphicsView->mapToScene(pointCoordView);
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

void MainWindow::onGraphicsviewMouseLeftReleased(QPoint pointCoordView)
{
    displayOperation("mouse left release");
    KeyboardManager::getIns().IsMouseLeftButtonHold = false;

    QPointF pointCoordscene = UiManager::getIns().UI()->graphicsView->mapToScene(pointCoordView);
    switch (this->currentDrawTool)
    {
    case DrawToolType::DragScene:
    {
        this->dragScene(pointCoordView,DrawEventType::LeftRelease);
        break;
    }
    case DrawToolType:: EditProperty:
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

void MainWindow::onGraphicsviewMouseRightReleased(QPoint pointCoordView)
{
    displayOperation("mouse right release");
    KeyboardManager::getIns().IsMouseRightButtonHold = false;

    QPointF pointCoordscene = UiManager::getIns().UI()->graphicsView->mapToScene(pointCoordView);
    switch (this->currentDrawTool) {
    case DrawToolType:: EditProperty:
    {
        this->editItem(pointCoordscene,DrawEventType::RightRelease);
        break;
    }
    case DrawToolType::Polyline:
    {
        this->drawPolyline(pointCoordscene,DrawEventType::RightRelease);
        break;
    }
    case DrawToolType::Arc:
    {
        this->drawArc(pointCoordscene,DrawEventType::RightRelease);
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

void MainWindow::onGraphicsviewMouseDoubleClicked(QPoint pointCoordView)
{
    UiManager::getIns().UI()->editButton->setChecked(true);
    this->on_editButton_clicked();
}

void MainWindow::onGraphicsviewMouseWheelTriggered(QWheelEvent * event)
{
    displayOperation("mouse wheel occourred");
    if (event->angleDelta().y() > 0)
    {
        SceneStates::getIns().setSceneScale(1.2, 1.2);
    }
    else
    {
        SceneStates::getIns().setSceneScale(0.8, 0.8);
    }
}

///
/// \brief MainWindow::on_drawLineButton_clicked
///
void MainWindow::on_drawCircleButton_clicked()
{
    displayOperation("drawCircle button click");
    this->currentDrawTool = DrawToolType::None;
    this->resetDrawToolStatus();

    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::NoDrag);

    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->drawCircleButton->setChecked(true);

    this->currentDrawTool = DrawToolType::Circle;
}

void MainWindow::on_drawPolylineButton_clicked()
{
    displayOperation("drawPolyline button click");
    this->currentDrawTool = DrawToolType::None;
    this->resetDrawToolStatus();

    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::NoDrag);

    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->drawPolylineButton->setChecked(true);

    this->currentDrawTool = DrawToolType::Polyline;
}

void MainWindow::on_drawArcButton_clicked()
{
    displayOperation("drawArc button click");
     this->currentDrawTool = DrawToolType::None;
    this->resetDrawToolStatus();

    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::NoDrag);

    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->drawArcButton->setChecked(true);

    this->currentDrawTool = DrawToolType::Arc;
}

void MainWindow::on_drawSpiralButton_clicked()
{
    displayOperation("drawSpiral button click");
     this->currentDrawTool = DrawToolType::None;
    this->resetDrawToolStatus();

    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::NoDrag);

    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->drawSpiralButton->setChecked(true);

    this->currentDrawTool = DrawToolType::Spiral;
}

void MainWindow::on_drawRectButton_clicked()
{
    displayOperation("drawRect button click");
     this->currentDrawTool = DrawToolType::None;
    this->resetDrawToolStatus();

    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::NoDrag);

    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->drawRectButton->setChecked(true);

    this->currentDrawTool = DrawToolType::Rect;
}

void MainWindow::on_drawPolygonButton_clicked()
{
    displayOperation("drawPolygon button click");
     this->currentDrawTool = DrawToolType::None;
    this->resetDrawToolStatus();

    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::NoDrag);

    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->drawPolygonButton->setChecked(true);

    this->currentDrawTool = DrawToolType::Polygon;
}

void MainWindow::on_drawEllipseButton_clicked()
{
    displayOperation("drawEllipse button click");
     this->currentDrawTool = DrawToolType::None;
    this->resetDrawToolStatus();

    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::NoDrag);

    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->drawEllipseButton->setChecked(true);

    this->currentDrawTool = DrawToolType::Ellipse;
}

///
///  编辑工具
///
void MainWindow::on_editButton_clicked()
{
    displayOperation("edit button click");

     // tool status
    this->currentDrawTool = DrawToolType::EditProperty;
    this->resetDrawToolStatus();
    this->currentEditItem = NULL;

    // clean table
    UiManager::getIns().UI()->propertyTableWidget->clearContents();
    UiManager::getIns().UI()->propertyTableWidget->setRowCount(0);

    // drag mode
    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    // 设置当前图层内物体可动
    auto inLayerItems = Manager::getIns().getItems(SceneStates::getIns().currentLayer);
    auto allItems = Manager::getIns().getItems(0);
    this->setItemsStatus(false,false,false,allItems);
    this->setItemsStatus(true,true,true,inLayerItems);
    // DEBUG_VAR(this->currentLayer);
    DEBUG_VAR(inLayerItems.size());
    DEBUG_VAR(allItems.size());

    // button check
    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->editButton->setChecked(true);
}

void MainWindow::on_dragSceneButton_clicked()
{
    displayOperation("dragscene button click");

    // tool status
    this->currentDrawTool = DrawToolType::DragScene;
    this->resetDrawToolStatus();

    // drag mode
    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::NoDrag);

    //button check
    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->dragSceneButton->setChecked(true);
}

///
/// \brief
///
void MainWindow::on_propertyTableWidget_cellChanged(int row, int column)
{
    if (this->currentEditItem != NULL) {
        switch (this->currentEditItem->type())
        {
        case ArcItem::Type:
        {
            ///
            ArcItem *item = dynamic_cast<ArcItem*>(this->currentEditItem);
             if (!item) FATAL_MSG("ptr cast fail");

            double startPointX = item->getVertex(0).point.x();
            double startPointY = item->getVertex(0).point.y();
            double endPointX = item->getVertex(1).point.x();
            double endPointY = item->getVertex(1).point.y();
            double angle = item->getVertex(1).angle;
            ///

            int rowCount = UiManager::getIns().UI()->propertyTableWidget->rowCount();

            for (int r = 0; r < rowCount; ++r)
            {
                QTableWidgetItem *nameItem  = UiManager::getIns().UI()->propertyTableWidget->item(r, 0);
                QTableWidgetItem *valueItem = UiManager::getIns().UI()->propertyTableWidget->item(r, 1);
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

                ///
                ///
                if (propertyName == "startPoint.x")
                {
                    startPointX = value;
                    DEBUG_VAR(startPointX);
                }
                else if (propertyName == "startPoint.y")
                {
                    startPointY = value;
                    DEBUG_VAR(startPointY);
                }
                else if (propertyName == "endPoint.x")
                {
                    endPointX = value;
                    DEBUG_VAR(endPointX);
                }
                else if (propertyName == "endPoint.y")
                {
                    endPointY = value;
                    DEBUG_VAR(endPointY);
                }
                    else if (propertyName == "angle")
                {
                    angle = value;
                    DEBUG_VAR(angle);
                }
                item->editVertex(0,QPointF{startPointX,startPointY},0);
                item->editVertex(1,QPointF{endPointX,endPointY},angle);
                ///
                ///
            }
            break;
        }
        case PolylineItem::Type:
        {

            double offset = 0, offsetNum = 0;
            int rowCount = UiManager::getIns().UI()->propertyTableWidget->rowCount();

            for (int r = 0; r < rowCount; ++r)
            {
                QTableWidgetItem *nameItem  = UiManager::getIns().UI()->propertyTableWidget->item(r, 0);
                QTableWidgetItem *valueItem = UiManager::getIns().UI()->propertyTableWidget->item(r, 1);
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
            }
            break;
        }

        default:
        {
            WARN_MSG("unknown cell change");
        }
        };
    }
}

///
/// \brief edit toolButton
///
void MainWindow::on_rotateButton_clicked()
{
    displayOperation("rotate button click");
    this->currentDrawTool = DrawToolType::None;
    this->resetDrawToolStatus();
    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->rotateButton->setChecked(true);

    QList<QGraphicsItem*> selectedItems = SceneStates::getIns().scene->selectedItems();
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

     this->currentDrawTool = DrawToolType::None;
    this->resetDrawToolStatus();

    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);

    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->centerButton->setChecked(true);


    if (!this->currentEditItem) return;

    this->currentEditItem->setPos(QPointF(0,0) - this->currentEditItem->scenePos());
}

void MainWindow::on_createOffsetButton_clicked()
{
    displayOperation("createOffset button click");

     this->currentDrawTool = DrawToolType::None;
    this->resetDrawToolStatus();

    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::NoDrag);

    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->createOffsetButton->setChecked(true);


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
     this->currentDrawTool = DrawToolType::None;
    this->resetDrawToolStatus();
    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->deleteButton->setChecked(true);

    QList<QGraphicsItem*> selectedItems = SceneStates::getIns().scene->selectedItems();
    if (selectedItems.empty())
        return;
    for (auto it = selectedItems.cbegin(); it != selectedItems.cend(); ++it)
    {
        QGraphicsItem* graphicsItem = *it;
        LaserItem* laserItem = dynamic_cast<LaserItem*>(graphicsItem);


        SceneStates::getIns().scene ->removeItem(graphicsItem);
        if(!laserItem)
            FATAL_MSG("fail pointer convertion");
        Manager::getIns().deleteItem(laserItem);
    }
}

void MainWindow::on_undoButton_clicked()
{

}

void MainWindow::on_redoButton_clicked()
{

}

///
/// \brief onLayerButton
///
void MainWindow::onLayerButtonClicked(int index)
{
    // this->resetDrawToolStatus();

    // this->currentLayer = index;
    // DEBUG_VAR(this->currentLayer);

    // //设置按钮选中
    // this->setAllLayerButtonChecked(false);
    // layerButtons[this->currentLayer-1]->setChecked(true);

    // //显示对应layer的元素
    // auto inLayerItems = Manager::getIns().getItemsByLayer(this->currentLayer);
    // auto allItems = Manager::getIns().getItems();
    // this->setItemsStatus(false,false,false,allItems);
    // this->setItemsStatus(true,true,true,inLayerItems);
}

void MainWindow::onAddLayerButtonClicked()
{
    // QLayout *graphicsViewLayout = UiManager::getIns().UI()->mainLayout->findChild<QLayout*>("graphicsViewLayout");
    // QLayout *layerButtonLayout = graphicsViewLayout->findChild<QLayout*>("layerButtonLayout");
    // if (!layerButtonLayout) {
    //     FATAL_MSG("layerButtonLayout can not be found");
    //     return;
    // }

    // layerCount++;
    // QString buttonName = QString("Layer %1").arg(layerCount);

    // QPushButton *newLayerButton = new QPushButton(buttonName);
    // newLayerButton->setStyleSheet(buttonStyle1);
    // newLayerButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // newLayerButton->setCheckable(true);

    // QPushButton *addLayerButton = qobject_cast<QPushButton*>(layerButtonLayout->itemAt(layerButtonLayout->count() - 1)->widget());
    // if (!addLayerButton)
    // {
    //     FATAL_MSG("addLayerButton not found");
    //     return;
    // }
    // layerButtonLayout->removeWidget(addLayerButton);

    // layerButtonLayout->addWidget(newLayerButton);
    // layerButtons.append(newLayerButton);

    // layerButtonLayout->addWidget(addLayerButton);

    // auto tmpLayerCount = layerCount;
    // connect(newLayerButton, &QPushButton::clicked, this, [=](){ onLayerButtonClicked(tmpLayerCount); });

    // INFO_MSG("newLayerButton added");
}


///
/// \brief MainWindow::onTreeViewModelShowContextMenu
/// \param pos
///
void MainWindow::onTreeViewModelShowContextMenu(const QPoint &pos)
{
    // 获取鼠标点击的位置
    QModelIndex index = UiManager::getIns().UI()->treeView->indexAt(pos);
    if (!index.isValid())
        return;

    QMenu contextMenu(this);
    this->addNodeAction = new QAction("Add Node", &contextMenu);
    this->removeNodeAction = new QAction("Remove Node", &contextMenu);
    this->insertChildNodeAction = new QAction("Insert Child Node", &contextMenu);

    contextMenu.addAction(addNodeAction);
    contextMenu.addAction(removeNodeAction);
    contextMenu.addAction(insertChildNodeAction);

    connect(addNodeAction, &QAction::triggered, this,&MainWindow::onTreeViewModelAddNode);
    connect(removeNodeAction, &QAction::triggered, this,&MainWindow::onTreeViewModelRemoveNode);
    connect(insertChildNodeAction, &QAction::triggered, this,&MainWindow::onTreeViewModelInsertChild);

    contextMenu.exec(UiManager::getIns().UI()->treeView->viewport()->mapToGlobal(pos));
}

void MainWindow::onTreeViewModelInsertChild()
{
    const QModelIndex index = UiManager::getIns().UI()->treeView->selectionModel()->currentIndex();
    QAbstractItemModel *model = UiManager::getIns().UI()->treeView->model();

    if (model->columnCount(index) == 0) {
        if (!model->insertColumn(0, index))
            return;
    }

    if (!model->insertRow(0, index))
        return;

    for (int column = 0; column < model->columnCount(index); ++column) {
        const QModelIndex child = model->index(0, column, index);
        model->setData(child, QVariant(tr("[No data]")), Qt::EditRole);
    }

    UiManager::getIns().UI()->treeView->selectionModel()->setCurrentIndex(model->index(0, 0, index),
                                            QItemSelectionModel::ClearAndSelect);
    onTreeViewModelUpdateActions();
}

void MainWindow::onTreeViewModelAddNode(){
    const QModelIndex index = UiManager::getIns().UI()->treeView->selectionModel()->currentIndex();

    QAbstractItemModel *model =  UiManager::getIns().UI()->treeView->model();

    if (!model->insertRow(index.row()+1, index.parent()))
        return;

    onTreeViewModelUpdateActions();

    for (int column = 0; column < model->columnCount(index.parent()); ++column) {
        const QModelIndex child = model->index(index.row() + 1, column, index.parent());
        model->setData(child, QVariant(tr("[No data]")), Qt::EditRole);
    }
}

void MainWindow::onTreeViewModelRemoveNode()
{
    const QModelIndex index = UiManager::getIns().UI()->treeView->selectionModel()->currentIndex();
    TreeViewModel *model = qobject_cast<TreeViewModel *>(UiManager::getIns().UI()->treeView->model());
    auto UUID = model->getNode(index)->property(NodePropertyIndex::UUID).toString();

    // 删除manager内的laseritem
    auto laserItem = Manager::getIns().ItemMap.find(UUID)->second.get();
    Manager::getIns().deleteItem(laserItem);

    // 删除scene内的laserItem; 但是要先进行指针转换 要更具体一些
    if (laserItem->getName() ==  "PolylineItem")
    {
        PolylineItem *item = static_cast<PolylineItem*>(laserItem);
        SceneStates::getIns().scene->removeItem(laserItem);
    }else if (laserItem->getName() =="ArcItem"){
        ArcItem *item = static_cast<ArcItem*>(laserItem);
        SceneStates::getIns().scene->removeItem(laserItem);
    }
    ///TODO


    onTreeViewModelUpdateActions();
}

void MainWindow::onTreeViewModelUpdateActions()
{
    // 暂时禁用添加节点; 因为现在都是图形节点,先按照现有图形后有节点来操作
    this->addNodeAction->setEnabled(false);

    const bool hasSelection = !UiManager::getIns().UI()->treeView->selectionModel()->selection().isEmpty();
    this->removeNodeAction->setEnabled(hasSelection);

    const bool hasCurrent = UiManager::getIns().UI()->treeView->selectionModel()->currentIndex().isValid();

    if (hasCurrent) {
        UiManager::getIns().UI()->treeView->closePersistentEditor(UiManager::getIns().UI()->treeView->selectionModel()->currentIndex());

        TreeViewModel *treeModel = qobject_cast<TreeViewModel *>(UiManager::getIns().UI()->treeView->model());
        const QModelIndex index = UiManager::getIns().UI()->treeView->selectionModel()->currentIndex();
        const auto name = treeModel->getNode(index)->property(NodePropertyIndex::Name).toString();
        const auto type = treeModel->getNode(index)->property(NodePropertyIndex::Type).toString();
        const auto uuid = treeModel->getNode(index)->property(NodePropertyIndex::UUID).toString();

        statusBar()->showMessage(tr("%3,%4,%5")
                                     .arg(name)
                                     .arg(type)
                                     .arg(uuid)
                                 );
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

static bool flag = false;
void MainWindow::on_drawTestLineButton_clicked()
{
    qDebug() << "";
    qDebug() << "------test------";
    ///
    /// test template
    ///
    // /*
    // */

    ///
    /// test template
    ///
    // /*
    this->tmpPolyline = std::make_shared<PolylineItem>();
    this->tmpPolyline->setLayer(SceneStates::getIns().currentLayer);
    SceneStates::getIns().scene->addItem(this->tmpPolyline.get());
    SceneStates::getIns().scene->removeItem(this->tmpPolyline.get());
    // */


    ///
    /// uuid
    ///
    /*
    auto uid = GenerateUUID();
    DEBUG_VAR(uid);
    */

    ///
    /// cavc2
    ///
    /*
    // QPointF p1 = QPointF{100,0};
    // QPointF p2 = QPointF{};
    // QPointF p3 = QPointF{0,100};
    // double p1p3Angle = -90;
    // double sweepAngle = 45;
    // getIntersectPoint(p1,p3,p1p3Angle,sweepAngle,p2);
    // DEBUG_VAR(p2);

    QPointF p1 = QPointF{100,0};
    QPointF p2 = QPointF{};
    QPointF p3 = QPointF{0,-100};
    double p1p3Angle = 90;
    double sweepAngle = 45;
    getIntersectPoint(p1,p3,p1p3Angle,sweepAngle,p2);
    DEBUG_VAR(p2);
     */

    ///
    /// cavc
    ///
    /*

    double angle0 = 90;
    double angle1 = 270;
    double angle2 = -90;
    double angle3 = -270;

    double bulge = 0;
    double angle = 0;
    getBulgeFromAngle(angle0,bulge);
    DEBUG_VAR(bulge);
    getAngleFromBulge(bulge,angle);
    DEBUG_VAR(angle);

    getBulgeFromAngle(angle1,bulge);
    DEBUG_VAR(bulge);
    getAngleFromBulge(bulge,angle);
    DEBUG_VAR(angle);

    getBulgeFromAngle(angle2,bulge);
    DEBUG_VAR(bulge);
    getAngleFromBulge(bulge,angle);
    DEBUG_VAR(angle);

    getBulgeFromAngle(angle3,bulge);
    DEBUG_VAR(bulge);
    getAngleFromBulge(bulge,angle);
    DEBUG_VAR(angle);

    */

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
    /// arc
    ///
    /*
     QPointF p1 = QPointF{-100,0};
    QPointF p2 = QPointF{100,0};
    QPointF p3 = QPointF{200,-173.20508};
    double  radius = 0;
    auto center = QPointF{};
    double  angle = 0;
    getCircleFromThreePoints(p1,p2,p3,center,radius);
    getAngleFromThreePoints(p1,p2,p3,center,radius,angle);

    this->tmpArc = std::make_shared<ArcItem>();
    scene->addItem(this->tmpArc.get());
    this->tmpArc->editVertex(0,p1,0);
    this->tmpArc->editVertex(1,p3,angle);
    DEBUG_VAR(center);

    double  radius1 = 0;
    auto center1 = QPointF{};
    getCircleFromAngle(p1,p3,angle,center1,radius1);
    INFO_VAR(center);

    // this->tmpArc = std::make_shared<ArcItem>();
    // scene->addItem( this->tmpArc.get());
    // this->tmpArc->editVertex(0,QPointF{0,0},0);
    //  this->tmpArc->editVertex(1,QPointF{-100,0},0.5);

    //  this->tmpArc = std::make_shared<ArcItem>();
    // scene->addItem( this->tmpArc.get());
    // this->tmpArc->editVertex(0,QPointF{0,0},0);
    //  this->tmpArc->editVertex(1,QPointF{0,100},1.5);

    //  this->tmpArc = std::make_shared<ArcItem>();
    // scene->addItem( this->tmpArc.get());
    //  this->tmpArc->editVertex(0,QPointF{0,0},0);
    //  this->tmpArc->editVertex(1,QPointF{0,-100},0.5);

*/
    ///
    /// CC  test
    ///
    /*
    cavc::Polyline<double> input;
    // add vertexes as (x, y, bulge)
    input.addVertex(0, 0, 0);
    input.addVertex(0,100,0);
    input.addVertex(100,100,0);
    input.addVertex(100,0,0);
    input.isClosed() = true;

    std::vector<cavc::Polyline<double>> results = cavc::parallelOffset(input, 10.0);
    printResults(results);
    */

    ///
    ///
    ///
    /*
     QPolygonF newPolygon;
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
    /*
     this->tmpVariantLine = std::make_shared<VariantLineItem>(QPointF(1,1));
    this->scene->addItem(this->tmpVariantLine.get());
    this->tmpVariantLine->setLine(QPointF(10,10),true,VariantLineItem::LineType::Line);
    this->tmpVariantLine->setLine(QPointF(20,10),false,VariantLineItem::LineType::Line);
    this->tmpVariantLine->setLine(QPointF(0,20),true,VariantLineItem::LineType::Arc);

     this->tmpVariantLine->setLine(QPointF(10,20),true,VariantLineItem::LineType::Arc);*/

    ///
    /// arc test
    ///
    /*
     QPoint startPoint(10,10);
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
    /*
     QLineF line(QPointF(0,0),QPointF(100,100));
    this->tmpPolyline = std::make_shared<PolylineItem>(line);
    this->scene->addItem(this->tmpPolyline.get());

    QLineF line1(QPointF(0,0),QPointF(-100,100));
    this->tmpPolyline->setLine(line1,false);

    QLineF line2(QPointF(-100,100),QPointF(100,100));
    this->tmpPolyline->setLine(line2,true);*/
}









