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
#include <polyline.hpp>
#include "manager.h"
#include "treemodel.h"
#include "keyboardmanager.h"
#include "uimanager.h"
#include "scenecontroller.h"
#include "editcontroller.h"
#include "drawcontroller.h"
#include "tablemodel.h"


///
/// \brief MainWindow::MainWindow
/// \param parent
///
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    auto ui = std::make_shared < Ui::MainWindow > ();
    ui->setupUi(this);
    UiManager::getIns().setUI(std::move(ui));
    showMaximized();
    initTitleBar();
    initGraphicsView();
    initDrawToolButton();
    initEditToolButton();
    initLayerButton();
    initHardwareButton();
    initTreeViewModel();
    // initTableViewModel();
    initStatusBar();
    initTabWidget();
    //
    connect(SceneController::getIns().scene, &QGraphicsScene::selectionChanged, [ = ]() {
        EditController::getIns().onSceneSelectionChanged();
    });
    //
    test();
}

MainWindow::~MainWindow() {
    // 不用delete,由unique ptr管理内存
    // delete UiManager::getIns().UI();
}

void MainWindow::initTitleBar() {
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

void MainWindow::initGraphicsView() {
    SceneController::getIns().scene = new QGraphicsScene();
    UiManager::getIns().UI()->graphicsView->setScene(SceneController::getIns().scene);
    UiManager::getIns().UI()->graphicsView->setRenderHint(QPainter::Antialiasing, true); //设置抗锯齿
    UiManager::getIns().UI()->graphicsView->setRenderHint(QPainter::SmoothPixmapTransform, true);
    UiManager::getIns().UI()->graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    UiManager::getIns().UI()->graphicsView->setTransformationAnchor(QGraphicsView::NoAnchor);
    UiManager::getIns().UI()->graphicsView->setResizeAnchor(QGraphicsView::NoAnchor);
    UiManager::getIns().UI()->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    UiManager::getIns().UI()->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    UiManager::getIns().UI()->graphicsView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored); // 设置画面缩放时不调整view大小
    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::NoDrag); // 设置初始为没有选框
    UiManager::getIns().UI()->graphicsView->viewport()->setCursor(Qt::ArrowCursor);
    SceneController::getIns().setSceneScale(0.1, 0.1);
    QTimer::singleShot(100, this, []() {
        SceneController::getIns().setSceneScale(10, 10);
    });
    QGraphicsLineItem *xAxis = new QGraphicsLineItem(-100, 0, 100, 0);
    QGraphicsLineItem *yAxis = new QGraphicsLineItem(0, -100, 0, 100);
    xAxis->setPen(AXIS_PEN);
    xAxis->setPos(0, 0);
    yAxis->setPen(AXIS_PEN);
    yAxis->setPos(0, 0);
    SceneController::getIns().scene->addItem(xAxis);
    SceneController::getIns().scene->addItem(yAxis);
    QGraphicsLineItem *xArrowL = new QGraphicsLineItem(90, 10, 100, 0);
    QGraphicsLineItem *xArrowR = new QGraphicsLineItem(90, -10, 100, 0);
    xArrowL->setPen(AXIS_PEN);
    xArrowR->setPen(AXIS_PEN);
    SceneController::getIns().scene->addItem(xArrowL);
    SceneController::getIns().scene->addItem(xArrowR);
    QGraphicsLineItem *yArrowL = new QGraphicsLineItem(10, 90, 0, 100);
    QGraphicsLineItem *yArrowR = new QGraphicsLineItem(-10, 90, 0, 100);
    yArrowL->setPen(AXIS_PEN);
    yArrowR->setPen(AXIS_PEN);
    SceneController::getIns().scene->addItem(yArrowL);
    SceneController::getIns().scene->addItem(yArrowR);
    QGraphicsLineItem *bound1 = new QGraphicsLineItem(900, 900, 1000, 1000);
    QGraphicsLineItem *bound2 = new QGraphicsLineItem(-1000, -1000, -900, -900);
    QGraphicsLineItem *bound3 = new QGraphicsLineItem(-900, 900, -1000, 1000);
    QGraphicsLineItem *bound4 = new QGraphicsLineItem(1000, -1000, 900, -900);
    bound1->setPen(AXIS_PEN);
    bound2->setPen(AXIS_PEN);
    bound3->setPen(AXIS_PEN);
    bound4->setPen(AXIS_PEN);
    SceneController::getIns().scene->addItem(bound1);
    SceneController::getIns().scene->addItem(bound2);
    SceneController::getIns().scene->addItem(bound3);
    SceneController::getIns().scene->addItem(bound4);
    // connect
    // graphicsview组件触发鼠标移动时,会通知mainwindow组件;
    connect(UiManager::getIns().UI()->graphicsView, SIGNAL(mouseMoved(QPoint)),
            this, SLOT(onGraphicsviewMouseMoved(QPoint)));
    connect(UiManager::getIns().UI()->graphicsView, SIGNAL(mouseLeftPressed(QPoint)),
            this, SLOT(onGraphicsviewMouseLeftPressed(QPoint)));
    connect(UiManager::getIns().UI()->graphicsView, SIGNAL(mouseRightPressed(QPoint)),
            this, SLOT(onGraphicsviewMouseRightPressed(QPoint)));
    connect(UiManager::getIns().UI()->graphicsView, SIGNAL(mouseLeftReleased(QPoint)),
            this, SLOT(onGraphicsviewMouseLeftReleased(QPoint)));
    connect(UiManager::getIns().UI()->graphicsView, SIGNAL(mouseRightReleased(QPoint)),
            this, SLOT(onGraphicsviewMouseRightReleased(QPoint)));
    connect(UiManager::getIns().UI()->graphicsView, SIGNAL(mouseDoubleClicked(QPoint)),
            this, SLOT(onGraphicsviewMouseRightDoubleClicked(QPoint)));
    connect(UiManager::getIns().UI()->graphicsView, SIGNAL(mouseWheelTriggered(QWheelEvent*)),
            this, SLOT(onGraphicsviewMouseWheelTriggered(QWheelEvent*)));
}


void MainWindow::initDrawToolButton() {
    QString buttonStyle = buttonStyle1;
    // 绘制工具
    QToolButton *drawPolylineButton = UiManager::getIns().UI()->drawPolylineButton;
    drawPolylineButton->setIcon(QIcon(":/button/drawPolylineButton.svg"));
    drawPolylineButton->setIconSize(QSize(30, 30));
    drawPolylineButton->setStyleSheet(buttonStyle);
    drawPolylineButton->setCheckable(true);
    drawPolylineButton->setAutoExclusive(false);
    drawPolylineButton->setToolTip(drawPolylineButtonToolTip);
    UiManager::getIns().registerDrawButton(drawPolylineButton);
    connect(drawPolylineButton, &QToolButton::clicked, this, &MainWindow::onDrawPolylineButtonClicked);
    //
    QToolButton *drawLineButton = UiManager::getIns().UI()->drawLineButton;
    drawLineButton->setIcon(QIcon(":/button/drawLineButton.svg"));
    drawLineButton->setIconSize(QSize(30, 30));
    drawLineButton->setStyleSheet(buttonStyle);
    drawLineButton->setCheckable(true);
    drawLineButton->setAutoExclusive(false);
    drawLineButton->setToolTip(drawLineButtonToolTip);
    UiManager::getIns().registerDrawButton(drawLineButton);
    connect(drawLineButton, &QToolButton::clicked, this, &MainWindow::onDrawLineButtonClicked);
    //
    QToolButton *drawArcButton = UiManager::getIns().UI()->drawArcButton;
    drawArcButton->setIcon(QIcon(":/button/drawArcButton.svg"));
    drawArcButton->setIconSize(QSize(30, 30));
    drawArcButton->setStyleSheet(buttonStyle);
    drawArcButton->setCheckable(true);
    drawArcButton->setAutoExclusive(false);
    drawArcButton->setToolTip(drawArcButtonToolTip);
    UiManager::getIns().registerDrawButton(drawArcButton);
    connect(drawArcButton, &QToolButton::clicked, this, &MainWindow::onDrawArcButtonClicked);
    //
    QToolButton *drawPointButton = UiManager::getIns().UI()->drawPointButton;
    drawPointButton->setIcon(QIcon(":/button/drawPointButton.svg"));
    drawPointButton->setIconSize(QSize(30, 30));
    drawPointButton->setStyleSheet(buttonStyle);
    drawPointButton->setCheckable(true);
    drawPointButton->setAutoExclusive(false);
    UiManager::getIns().registerDrawButton(drawPointButton);
    connect(drawPointButton, &QToolButton::clicked, this, &MainWindow::onDrawPointButtonClicked);
    //
    QToolButton *drawCircleButton = UiManager::getIns().UI()->drawCircleButton;
    drawCircleButton->setIcon(QIcon(":/button/drawCircleButton.svg"));
    drawCircleButton->setIconSize(QSize(30, 30));
    drawCircleButton->setStyleSheet(buttonStyle);
    drawCircleButton->setCheckable(true);
    drawCircleButton->setAutoExclusive(false);
    drawCircleButton->setToolTip(drawCircleButtonToolTip);
    UiManager::getIns().registerDrawButton(drawCircleButton);
    connect(drawCircleButton, &QToolButton::clicked, this, &MainWindow::onDrawCircleButtonClicked);
    //
    QToolButton *drawEllipseButton = UiManager::getIns().UI()->drawEllipseButton;
    drawEllipseButton->setIcon(QIcon(":/button/drawEllipseButton.svg"));
    drawEllipseButton->setIconSize(QSize(30, 30));
    drawEllipseButton->setStyleSheet(buttonStyle);
    drawEllipseButton->setCheckable(true);
    drawEllipseButton->setAutoExclusive(false);
    drawEllipseButton->setToolTip(drawEllipseButtonToolTip);
    UiManager::getIns().registerDrawButton(drawEllipseButton);
    connect(drawEllipseButton, &QToolButton::clicked, this, &MainWindow::onDrawEllipseButtonClicked);
    //
    QToolButton *drawRectButton = UiManager::getIns().UI()->drawRectButton;
    drawRectButton->setIcon(QIcon(":/button/drawRectButton.svg"));
    drawRectButton->setIconSize(QSize(30, 30));
    drawRectButton->setStyleSheet(buttonStyle);
    drawRectButton->setCheckable(true);
    drawRectButton->setAutoExclusive(false);
    drawRectButton->setToolTip(drawRectButtonToolTip);
    UiManager::getIns().registerDrawButton(drawRectButton);
    connect(drawRectButton, &QToolButton::clicked, this, &MainWindow::onDrawRectButtonClicked);
    //
    QToolButton *drawPolygonButton = UiManager::getIns().UI()->drawPolygonButton;
    drawPolygonButton->setIcon(QIcon(":/button/drawPolygonButton.svg"));
    drawPolygonButton->setIconSize(QSize(30, 30));
    drawPolygonButton->setStyleSheet(buttonStyle);
    drawPolygonButton->setCheckable(true);
    drawPolygonButton->setAutoExclusive(false);
    drawPolygonButton->setToolTip(drawPolygonButtonToolTip);
    UiManager::getIns().registerDrawButton(drawPolygonButton);
    connect(drawPolygonButton, &QToolButton::clicked, this, &MainWindow::onDrawPolygonButtonClicked);
    //
    QToolButton *drawSpiralButton = UiManager::getIns().UI()->drawSpiralButton;
    drawSpiralButton->setIcon(QIcon(":/button/drawSpiralButton.svg"));
    drawSpiralButton->setIconSize(QSize(30, 30));
    drawSpiralButton->setStyleSheet(buttonStyle);
    drawSpiralButton->setCheckable(true);
    drawSpiralButton->setAutoExclusive(false);
    drawSpiralButton->setToolTip(drawSpiralButtonToolTip);
    UiManager::getIns().registerDrawButton(drawSpiralButton);
    connect(drawSpiralButton, &QToolButton::clicked, this, &MainWindow::onDrawSpiralButtonClicked);
}

///
/// \brief MainWindow::initEditToolButton
///
void MainWindow::initEditToolButton() {
    QString buttonStyle = buttonStyle1;
    //
    QToolButton *editButton = UiManager::getIns().UI()->editButton;
    editButton->setIcon(QIcon(":/button/editButton.svg"));
    editButton->setIconSize(QSize(30, 30));
    editButton->setStyleSheet(buttonStyle);
    editButton->setCheckable(true);
    editButton->setAutoExclusive(false);
    editButton->setToolTip("编辑模式");
    UiManager::getIns().registerToolButton(editButton);
    connect(editButton, &QToolButton::clicked, this, &MainWindow::onEditButtonClicked);
    //
    QToolButton *dragSceneButton = UiManager::getIns().UI()->dragSceneButton;
    dragSceneButton->setIcon(QIcon(":/button/dragSceneButton.svg"));
    dragSceneButton->setIconSize(QSize(30, 30));
    dragSceneButton->setStyleSheet(buttonStyle);
    dragSceneButton->setCheckable(true);
    dragSceneButton->setAutoExclusive(false);
    dragSceneButton->setToolTip("拖动画布；左键拖拽");
    UiManager::getIns().registerToolButton(dragSceneButton);
    connect(dragSceneButton, &QToolButton::clicked, this, &MainWindow::onDragSceneButtonClicked);
    //
    QToolButton *rotateButton = UiManager::getIns().UI()->rotateButton;
    rotateButton->setIcon(QIcon(":/button/rotateButton.svg"));
    rotateButton->setIconSize(QSize(30, 30));
    rotateButton->setStyleSheet(buttonStyle);
    rotateButton->setCheckable(true);
    rotateButton->setAutoExclusive(false);
    rotateButton->setToolTip("旋转对象");
    UiManager::getIns().registerToolButton(rotateButton);
    connect(rotateButton, &QToolButton::clicked, this, &MainWindow::onRotateButtonClicked);
    //
    QToolButton *deleteButton = UiManager::getIns().UI()->deleteButton;
    deleteButton->setIcon(QIcon(":/button/deleteButton.svg"));
    deleteButton->setIconSize(QSize(30, 30));
    deleteButton->setStyleSheet(buttonStyle);
    deleteButton->setCheckable(true);
    deleteButton->setAutoExclusive(false);
    deleteButton->setToolTip("删除对象");
    UiManager::getIns().registerToolButton(deleteButton);
    connect(deleteButton, &QToolButton::clicked, this, &MainWindow::onDeleteButtonClicked);
    //
    QToolButton *drawTestLineButton = UiManager::getIns().UI()->drawTestLineButton;
    drawTestLineButton->setIcon(QIcon(":/button/drawTestLineButton.svg"));
    drawTestLineButton->setIconSize(QSize(30, 30));
    drawTestLineButton->setStyleSheet(buttonStyle);
    drawTestLineButton->setCheckable(true);
    drawTestLineButton->setAutoExclusive(false);
    drawTestLineButton->setToolTip("测试按钮");
    UiManager::getIns().registerToolButton(drawTestLineButton);
    connect(drawTestLineButton, &QToolButton::clicked, this, &MainWindow::onDrawTestLineButtonClicked);
    //
    QToolButton *centerButton = UiManager::getIns().UI()->centerButton;
    centerButton->setIcon(QIcon(":/button/centerButton.svg"));
    centerButton->setIconSize(QSize(30, 30));
    centerButton->setStyleSheet(buttonStyle);
    centerButton->setCheckable(true);
    centerButton->setAutoExclusive(false);
    centerButton->setToolTip("移动对象到中心点");
    UiManager::getIns().registerToolButton(centerButton);
    connect(centerButton, &QToolButton::clicked, this, &MainWindow::onCenterButtonClicked);
    //
    QToolButton *redoButton = UiManager::getIns().UI()->redoButton;
    redoButton->setIcon(QIcon(":/button/redoButton.svg"));
    redoButton->setIconSize(QSize(30, 30));
    redoButton->setStyleSheet(buttonStyle);
    redoButton->setCheckable(true);
    redoButton->setAutoExclusive(false);
    redoButton->setToolTip("移动对象到中心点");
    UiManager::getIns().registerToolButton(redoButton);
    connect(redoButton, &QToolButton::clicked, this, &MainWindow::onRedoButtonClicked);
    //
    QToolButton *undoButton = UiManager::getIns().UI()->undoButton;
    undoButton->setIcon(QIcon(":/button/undoButton.svg"));
    undoButton->setIconSize(QSize(30, 30));
    undoButton->setStyleSheet(buttonStyle);
    undoButton->setCheckable(true);
    undoButton->setAutoExclusive(false);
    undoButton->setToolTip("移动对象到中心点");
    UiManager::getIns().registerToolButton(undoButton);
    connect(undoButton, &QToolButton::clicked, this, &MainWindow::onUndoButtonClicked);
    //
    QToolButton *breakCopiedItemButton = UiManager::getIns().UI()->breakCopiedItemButton;
    breakCopiedItemButton->setIcon(QIcon(":/button/breakCopiedItemButton.png"));
    breakCopiedItemButton->setIconSize(QSize(30, 30));
    breakCopiedItemButton->setStyleSheet(buttonStyle);
    breakCopiedItemButton->setCheckable(true);
    breakCopiedItemButton->setAutoExclusive(false);
    breakCopiedItemButton->setToolTip("打散复制对象组");
    UiManager::getIns().registerToolButton(breakCopiedItemButton);
    connect(breakCopiedItemButton, &QToolButton::clicked,
            this, &MainWindow::onBreakCopiedItemButtonClicked);
    //
    QToolButton *breakOffsetItemButton = UiManager::getIns().UI()->breakOffsetItemButton;
    breakOffsetItemButton->setIcon(QIcon(":/button/breakOffsetItemButton.png"));
    breakOffsetItemButton->setIconSize(QSize(30, 30));
    breakOffsetItemButton->setStyleSheet(buttonStyle);
    breakOffsetItemButton->setCheckable(true);
    breakOffsetItemButton->setAutoExclusive(false);
    breakOffsetItemButton->setToolTip("打散offset");
    UiManager::getIns().registerToolButton(breakOffsetItemButton);
    connect(breakOffsetItemButton, &QToolButton::clicked,
            this, &MainWindow::onBreakOffsetItemButtonClicked);
}

void MainWindow::initLayerButton() {
    auto buttonStyle = buttonStyle1;
    auto comboBoxStyle = comboBoxStyle1;
    //
    QToolButton *addLayerButton = UiManager::getIns().UI()->addLayerButton;
    addLayerButton->setIcon(QIcon(":/button/addLayerButton.png"));
    addLayerButton->setIconSize(QSize(30, 30));
    addLayerButton->setStyleSheet(buttonStyle);
    addLayerButton->setCheckable(false);
    addLayerButton->setToolTip("");
    UiManager::getIns().registerToolButton(addLayerButton);
    // connect(breakOffsetItemButton, &QToolButton::clicked,
    //         this, &MainWindow::onBreakOffsetItemButtonClicked);
    //
    QToolButton *deleteLayerButton = UiManager::getIns().UI()->deleteLayerButton;
    deleteLayerButton->setIcon(QIcon(":/button/deleteLayerButton.png"));
    deleteLayerButton->setIconSize(QSize(30, 30));
    deleteLayerButton->setStyleSheet(buttonStyle);
    deleteLayerButton->setCheckable(false);
    deleteLayerButton->setToolTip("");
    UiManager::getIns().registerToolButton(deleteLayerButton);
    // connect(breakOffsetItemButton, &QToolButton::clicked,
    //         this, &MainWindow::onBreakOffsetItemButtonClicked);
    //
    QToolButton *setLayerColorButton = UiManager::getIns().UI()->setLayerColorButton;
    setLayerColorButton->setIcon(QIcon(":/button/setLayerColorButton.png"));
    setLayerColorButton->setIconSize(QSize(30, 30));
    setLayerColorButton->setStyleSheet(buttonStyle);
    setLayerColorButton->setCheckable(false);
    setLayerColorButton->setToolTip("");
    UiManager::getIns().registerToolButton(setLayerColorButton);
    // connect(breakOffsetItemButton, &QToolButton::clicked,
    //         this, &MainWindow::onBreakOffsetItemButtonClicked);
    //
    QToolButton *showOnlyCurrentLayerButton = UiManager::getIns().UI()->showOnlyCurrentLayerButton;
    showOnlyCurrentLayerButton->setIcon(QIcon(":/button/showOnlyCurrentLayerButton.png"));
    showOnlyCurrentLayerButton->setIconSize(QSize(30, 30));
    showOnlyCurrentLayerButton->setStyleSheet(buttonStyle);
    showOnlyCurrentLayerButton->setCheckable(false);
    showOnlyCurrentLayerButton->setToolTip("");
    UiManager::getIns().registerToolButton(showOnlyCurrentLayerButton);
    // connect(breakOffsetItemButton, &QToolButton::clicked,
    //         this, &MainWindow::onBreakOffsetItemButtonClicked);
    //
    auto *selectLayerComboBox = UiManager::getIns().UI()->selectLayerComboBox;
    selectLayerComboBox->setStyleSheet(comboBoxStyle);
    selectLayerComboBox->setToolTip("");
    selectLayerComboBox->clear();
}

void MainWindow::initHardwareButton() {
    QString buttonStyle = buttonStyle1;
    QToolButton *digitalInButton = UiManager::getIns().UI()->digitalInButton;
    digitalInButton->setIcon(QIcon(":/button/digitalInButton.png"));
    digitalInButton->setIconSize(QSize(30, 30));
    digitalInButton->setStyleSheet(buttonStyle);
    digitalInButton->setCheckable(true);
    digitalInButton->setAutoExclusive(false);
    digitalInButton->setToolTip("");
    UiManager::getIns().registerToolButton(digitalInButton);
    // connect(signalInButton,
    //         &QToolButton::clicked,
    //         this,
    //         &MainWindow::onBreakOffsetItemButtonClicked);
    //
    QToolButton *digitalOutButton = UiManager::getIns().UI()->digitalOutButton;
    digitalOutButton->setIcon(QIcon(":/button/digitalOutButton.png"));
    digitalOutButton->setIconSize(QSize(30, 30));
    digitalOutButton->setStyleSheet(buttonStyle);
    digitalOutButton->setCheckable(true);
    digitalOutButton->setAutoExclusive(false);
    digitalOutButton->setToolTip("");
    UiManager::getIns().registerToolButton(digitalOutButton);
    // connect(breakOffsetItemButton,
    //         &QToolButton::clicked,
    //         this,
    //         &MainWindow::onBreakOffsetItemButtonClicked);
    //
    QToolButton *doPauseButton = UiManager::getIns().UI()->doPauseButton;
    doPauseButton->setIcon(QIcon(":/button/doPauseButton.png"));
    doPauseButton->setIconSize(QSize(30, 30));
    doPauseButton->setStyleSheet(buttonStyle);
    doPauseButton->setCheckable(true);
    doPauseButton->setAutoExclusive(false);
    doPauseButton->setToolTip("");
    UiManager::getIns().registerToolButton(doPauseButton);
    // connect(breakOffsetItemButton,
    //         &QToolButton::clicked,
    //         this,
    //         &MainWindow::onBreakOffsetItemButtonClicked);
    //
    QToolButton *delayTimeButton = UiManager::getIns().UI()->delayTimeButton;
    delayTimeButton->setIcon(QIcon(":/button/delayTimeButton.png"));
    delayTimeButton->setIconSize(QSize(30, 30));
    delayTimeButton->setStyleSheet(buttonStyle);
    delayTimeButton->setCheckable(true);
    delayTimeButton->setAutoExclusive(false);
    delayTimeButton->setToolTip("");
    UiManager::getIns().registerToolButton(delayTimeButton);
    // connect(breakOffsetItemButton,
    //         &QToolButton::clicked,
    //         this,
    //         &MainWindow::onBreakOffsetItemButtonClicked);
    QToolButton *motionButton = UiManager::getIns().UI()->motionButton;
    motionButton->setIcon(QIcon(":/button/motionButton.png"));
    motionButton->setIconSize(QSize(30, 30));
    motionButton->setStyleSheet(buttonStyle);
    motionButton->setCheckable(true);
    motionButton->setAutoExclusive(false);
    motionButton->setToolTip("");
    UiManager::getIns().registerToolButton(motionButton);
    // connect(breakOffsetItemButton,
    //         &QToolButton::clicked,
    //         this,
    //         &MainWindow::onBreakOffsetItemButtonClicked);
}

void MainWindow::initStatusBar() {
    this->labelMouseCoordinate = new QLabel("coordinate: ");
    this->labelMouseCoordinate->setMinimumWidth(150);
    UiManager::getIns().UI()->statusBar->addWidget(this->labelMouseCoordinate);
}

void MainWindow::initTreeViewModel() {
    ///
    /// \brief model
    ///
    auto* model = new TreeModel("Items Browser", this);
    auto* view = UiManager::getIns().UI()->treeView;
    view->setStyleSheet(treeViewModelStyle1);
    view->setModel(model);
    view->bindModel();
    view->expandAll();
    view->setSelectionMode(QAbstractItemView::ExtendedSelection);
    view->setDragEnabled(true);
    view->setAcceptDrops(true);
    view->setDropIndicatorShown(true);
    view->setDragDropMode(QAbstractItemView::InternalMove);
    ///
    ///  contextmenu
    ///
    view->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(view,
            &QWidget::customContextMenuRequested,
            this,
            &MainWindow::onTreeViewModelShowContextMenu);
    connect(view, &QTreeView::clicked, this, [ = ](const QModelIndex & index) {
        EditController::getIns().onTreeViewModelClicked (index);
    });
    connect(view->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
    [ = ](const QItemSelection & selected, const QItemSelection & deselected) {
        EditController::getIns().onTreeViewModelSelectionChanged(selected, deselected);
    });
}

void MainWindow::initTableViewModel() {
    // auto *model = new TableModel(this);
    // UiManager::getIns().UI()->tableView->setModel(model);
    // UiManager::getIns().UI()->tableView->verticalHeader()->setVisible(false);
    // UiManager::getIns().UI()->tableView->setAlternatingRowColors(true);
    // UiManager::getIns().UI()->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    // UiManager::getIns().UI()->tableView->setColumnWidth(0, 190);
    // UiManager::getIns().UI()->tableView->setColumnWidth(1, 190);
}

void MainWindow::initTabWidget() {
    UiManager::getIns().UI()->tabWidget->clearAllTabs();
}

void MainWindow::test() {
}

///
/// \brief MainWindow::keyPressEvent
/// \param event
///
void MainWindow::keyPressEvent(QKeyEvent * event) {
    KeyboardManager::getIns().onMainWindowKeyPressEvent(event);
    QMainWindow::keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent * event) {
    KeyboardManager::getIns().onMainWindowKeyReleaseEvent(event);
    QMainWindow::keyReleaseEvent(event);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);  // 调用基类实现（可选）
    SceneController::getIns().setSceneScale(0.1, 0.1);
    QTimer::singleShot(10, this, []() {
        SceneController::getIns().setSceneScale(10, 10);
    });
}

///
/// \brief MainWindow::on_graphicsview_mouse_move_triggered
///
void MainWindow::onGraphicsviewMouseMoved(QPoint pointCoordView) {
    QPointF pointCoordscene = UiManager::getIns().UI()->graphicsView->mapToScene(pointCoordView);
    auto event = MouseEvent::MouseMove;
    // 显示坐标在statusbar里
    this->labelMouseCoordinate->setText(
        QString::asprintf(
            "coordinate: x:%.0f,y:%.0f",
            pointCoordscene.x(),
            pointCoordscene.y()
        )
    );
    // 禁止鼠标左右键同时拖拽
    // if (KeyboardManager::getIns().IsMouseLeftButtonHold == true && KeyboardManager::getIns().IsMouseRightButtonHold == true) {
    //     DrawController::getIns().resetTmpItemStatus();
    //     auto allItems = Manager::getIns().getItemsByLayer(0);
    //     SceneController::getIns().scene->clearSelection();
    //     // 打断一下拖拽过程
    //     for (const auto& item : allItems) {
    //         Manager::getIns().setItemMovable(item, false);
    //         QTimer::singleShot(10, this, [item]() {
    //             Manager::getIns().setItemMovable(item, false);
    //         });
    //     }
    // }
    // 非拖拽行为
    if (KeyboardManager::getIns().IsMouseLeftButtonHold == false && KeyboardManager::getIns().IsMouseRightButtonHold == false) {
        switch (SceneController::getIns().currentOperationEvent) {
            case OperationEvent::EditProperty: {
                    EditController::getIns().editItemInScene(pointCoordscene, event);
                    break;
                }
            case OperationEvent::DrawCircle: {
                    DrawController::getIns().drawCircle(pointCoordscene, event);
                    break;
                }
            case OperationEvent::DrawPolyline: {
                    DrawController::getIns().drawPolyline(pointCoordscene, event);
                    break;
                }
            case OperationEvent::DrawArc: {
                    DrawController::getIns().drawArc(pointCoordscene, event);
                    break;
                }
            case OperationEvent::DrawLine: {
                    DrawController::getIns().drawLine(pointCoordscene, event);
                    break;
                }
            case OperationEvent::DrawSpiral: {
                    DrawController::getIns().drawSpiral(pointCoordscene, event);
                    break;
                }
            case OperationEvent::DrawRect: {
                    DrawController::getIns().drawRect(pointCoordscene, event);
                    break;
                }
            case OperationEvent::DrawPolygon: {
                    DrawController::getIns().drawPolygon(pointCoordscene, event);
                    break;
                }
            case OperationEvent::DrawEllipse: {
                    DrawController::getIns().drawEllipse(pointCoordscene, event);
                    break;
                }
            default:
                {}
        }
    }
    // 左键拖拽(尽量不要用 因为item的拖动也是左键拖拽 容易撞车造成bug)
    else if (KeyboardManager::getIns().IsMouseLeftButtonHold == true && KeyboardManager::getIns().IsMouseRightButtonHold == false) {
        switch (SceneController::getIns().currentOperationEvent) {
            case OperationEvent::DragScene: {
                    SceneController::getIns().dragScene(pointCoordView, event);
                    break;
                }
            default:
                {}
        }
    }
    // 右键拖拽
    else if (KeyboardManager::getIns().IsMouseLeftButtonHold == false && KeyboardManager::getIns().IsMouseRightButtonHold == true) {
        switch (SceneController::getIns().currentOperationEvent) {
            default:
                {}
        }
    }
}

void MainWindow::onGraphicsviewMouseLeftPressed(QPoint pointCoordView) {
    // INFO_MSG("LeftPress");
    KeyboardManager::getIns().IsMouseLeftButtonHold = true;
    auto event = MouseEvent::LeftPress;
    QPointF pointCoordscene = UiManager::getIns().UI()->graphicsView->mapToScene(pointCoordView);
    switch (SceneController::getIns().currentOperationEvent) {
        case OperationEvent::DragScene: {
                SceneController::getIns().dragScene(pointCoordView, event);
                break;
            }
        case OperationEvent:: EditProperty: {
                EditController::getIns().editItemInScene(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawCircle: {
                DrawController::getIns().drawCircle(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawPolyline: {
                DrawController::getIns().drawPolyline(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawArc: {
                DrawController::getIns().drawArc(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawLine: {
                DrawController::getIns().drawLine(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawPoint: {
                DrawController::getIns().drawPoint(pointCoordscene, event );
                break;
            }
        //
        case OperationEvent::DrawSpiral: {
                DrawController::getIns().drawSpiral(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawRect: {
                DrawController::getIns().drawRect(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawPolygon: {
                DrawController::getIns().drawPolygon(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawEllipse: {
                DrawController::getIns().drawEllipse(pointCoordscene, event );
                break;
            }
        default:
            {}
    }
}

void MainWindow::onGraphicsviewMouseRightPressed(QPoint pointCoordView) {
    KeyboardManager::getIns().IsMouseRightButtonHold = true;
    auto event = MouseEvent::RightPress;
    QPointF pointCoordscene = UiManager::getIns().UI()->graphicsView->mapToScene(pointCoordView);
    switch (SceneController::getIns().currentOperationEvent) {
        case OperationEvent::DragScene: {
                SceneController::getIns().dragScene(pointCoordView, event);
                break;
            }
        case OperationEvent:: EditProperty: {
                EditController::getIns().editItemInScene(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawCircle: {
                DrawController::getIns().drawCircle(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawPolyline: {
                DrawController::getIns().drawPolyline(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawArc: {
                DrawController::getIns().drawArc(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawLine: {
                DrawController::getIns().drawLine(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawSpiral: {
                DrawController::getIns().drawSpiral(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawRect: {
                DrawController::getIns().drawRect(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawPolygon: {
                DrawController::getIns().drawPolygon(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawEllipse: {
                DrawController::getIns().drawEllipse(pointCoordscene, event );
                break;
            }
        default:
            {}
    }
}

void MainWindow::onGraphicsviewMouseLeftReleased(QPoint pointCoordView) {
    KeyboardManager::getIns().IsMouseLeftButtonHold = false;
    QPointF pointCoordscene = UiManager::getIns().UI()->graphicsView->mapToScene(pointCoordView);
    auto event = MouseEvent::LeftRelease;
    switch (SceneController::getIns().currentOperationEvent) {
        case OperationEvent::DragScene: {
                SceneController::getIns().dragScene(pointCoordView, event);
                break;
            }
        case OperationEvent:: EditProperty: {
                EditController::getIns().editItemInScene(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawCircle: {
                DrawController::getIns().drawCircle(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawPolyline: {
                DrawController::getIns().drawPolyline(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawArc: {
                DrawController::getIns().drawArc(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawLine: {
                DrawController::getIns().drawLine(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawSpiral: {
                DrawController::getIns().drawSpiral(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawRect: {
                DrawController::getIns().drawRect(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawPolygon: {
                DrawController::getIns().drawPolygon(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawEllipse: {
                DrawController::getIns().drawEllipse(pointCoordscene, event );
                break;
            }
        default:
            {}
    }
}

void MainWindow::onGraphicsviewMouseRightReleased(QPoint pointCoordView) {
    KeyboardManager::getIns().IsMouseRightButtonHold = false;
    auto event = MouseEvent::RightRelease;
    QPointF pointCoordscene = UiManager::getIns().UI()->graphicsView->mapToScene(pointCoordView);
    switch (SceneController::getIns().currentOperationEvent) {
        case OperationEvent::DragScene: {
                SceneController::getIns().dragScene(pointCoordView, event);
                break;
            }
        case OperationEvent:: EditProperty: {
                EditController::getIns().editItemInScene(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawCircle: {
                DrawController::getIns().drawCircle(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawPolyline: {
                DrawController::getIns().drawPolyline(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawArc: {
                DrawController::getIns().drawArc(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawLine: {
                DrawController::getIns().drawLine(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawSpiral: {
                DrawController::getIns().drawSpiral(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawRect: {
                DrawController::getIns().drawRect(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawPolygon: {
                DrawController::getIns().drawPolygon(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawEllipse: {
                DrawController::getIns().drawEllipse(pointCoordscene, event );
                break;
            }
        default:
            {}
    }
}

void MainWindow::onGraphicsviewMouseRightDoubleClicked(QPoint pointCoordView) {
    UiManager::getIns().UI()->editButton->setChecked(true);
    this->onEditButtonClicked();
}

void MainWindow::onGraphicsviewMouseWheelTriggered(QWheelEvent * event) {
    if (event->angleDelta().y() > 0) {
        SceneController::getIns().setSceneScale(1.2, 1.2);
    } else {
        SceneController::getIns().setSceneScale(0.8, 0.8);
    }
}

///
/// \brief MainWindow::setDrawMode
///
void MainWindow::setDrawMode() {
    UiManager::getIns().UI()->graphicsView->viewport()->setCursor(Qt::CrossCursor);
    DrawController::getIns().resetTmpItemStatus();
    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::NoDrag);
    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
}

void MainWindow::onDrawLineButtonClicked() {
    setDrawMode();
    UiManager::getIns().UI()->drawLineButton->setChecked(true);
    SceneController::getIns().currentOperationEvent = OperationEvent::DrawLine;
}

void MainWindow::onDrawCircleButtonClicked() {
    setDrawMode();
    UiManager::getIns().UI()->drawCircleButton->setChecked(true);
    SceneController::getIns().currentOperationEvent = OperationEvent::DrawCircle;
}

void MainWindow::onDrawPolylineButtonClicked() {
    setDrawMode();
    UiManager::getIns().UI()->drawPolylineButton->setChecked(true);
    SceneController::getIns().currentOperationEvent = OperationEvent::DrawPolyline;
}

void MainWindow::onDrawArcButtonClicked() {
    setDrawMode();
    UiManager::getIns().UI()->drawArcButton->setChecked(true);
    SceneController::getIns().currentOperationEvent = OperationEvent::DrawArc;
}

void MainWindow::onDrawPointButtonClicked() {
    setDrawMode();
    UiManager::getIns().UI()->drawPointButton->setChecked(true);
    SceneController::getIns().currentOperationEvent = OperationEvent::DrawPoint;
}

void MainWindow::onDrawSpiralButtonClicked() {
    setDrawMode();
    UiManager::getIns().UI()->drawSpiralButton->setChecked(true);
    SceneController::getIns().currentOperationEvent = OperationEvent::DrawSpiral;
}

void MainWindow::onDrawRectButtonClicked() {
    setDrawMode();
    UiManager::getIns().UI()->drawRectButton->setChecked(true);
    SceneController::getIns().currentOperationEvent = OperationEvent::DrawRect;
}

void MainWindow::onDrawPolygonButtonClicked() {
    setDrawMode();
    UiManager::getIns().UI()->drawPolygonButton->setChecked(true);
    SceneController::getIns().currentOperationEvent = OperationEvent::DrawPolygon;
}

void MainWindow::onDrawEllipseButtonClicked() {
    setDrawMode();
    UiManager::getIns().UI()->drawEllipseButton->setChecked(true);
    SceneController::getIns().currentOperationEvent = OperationEvent::DrawEllipse;
}

///
/// \brief MainWindow::onDragSceneButtonClicked
///
void MainWindow::onDragSceneButtonClicked() {
    // 设置鼠标光标
    UiManager::getIns().UI()->graphicsView->viewport()->setCursor(Qt::OpenHandCursor);
    // tool status
    SceneController::getIns().currentOperationEvent = OperationEvent::DragScene;
    DrawController::getIns().resetTmpItemStatus();
    // drag mode/所有物体设置不可动
    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::NoDrag);
    auto allItems = Manager::getIns().getItemsByLayer(0);
    for (auto item : allItems) {
        Manager::getIns().setItemSelectable(item, false);
    }
    //button check
    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->dragSceneButton->setChecked(true);
}

///
/// \brief MainWindow::onEditButtonClicked
///
void MainWindow::onEditButtonClicked() {
    // 设置鼠标光标
    UiManager::getIns().UI()->graphicsView->viewport()->setCursor(Qt::ArrowCursor);
    // tool status
    SceneController::getIns().currentOperationEvent = OperationEvent::EditProperty;
    DrawController::getIns().resetTmpItemStatus();
    // drag mode
    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    // button check
    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->editButton->setChecked(true);
    // 设置当前图层内物体可动;所有物体颜色为黑;等等默认行为(都在setCurrentLayer里)
    // SceneController::getIns().setCurrentLayer(SceneController::getIns().getCurrentLayer());
}

void MainWindow::setEditMode() {
    // 设置鼠标光标
    UiManager::getIns().UI()->graphicsView->viewport()->setCursor(Qt::ArrowCursor);
    // tool status
    SceneController::getIns().currentOperationEvent = OperationEvent::EditProperty;
    DrawController::getIns().resetTmpItemStatus();
    // drag mode
    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    // button check
    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->editButton->setChecked(true);
}

void MainWindow::onCenterButtonClicked() {
    setEditMode();
    EditController::getIns().onCenterToOriginTriggered();
}

void MainWindow::onDeleteButtonClicked() {
    setEditMode();
    EditController::getIns().onDeleteTriggered ();
}

void MainWindow::onBreakCopiedItemButtonClicked() {
    setEditMode();
    EditController::getIns().onBreakCopiedItemTriggered();
}

void MainWindow::onBreakOffsetItemButtonClicked() {
    setEditMode();
    EditController::getIns().onBreakOffsetItemTriggered();
}

void MainWindow::onRotateButtonClicked() {
    setEditMode();
    EditController::getIns().onRotateTriggered();
}

///
/// \brief MainWindow::onTreeViewModelShowContextMenu 每次重新生成一个menu到右键点击处
/// \param pos
///
void MainWindow::onTreeViewModelShowContextMenu(const QPoint &pos) {
    // 获取鼠标点击的位置
    QModelIndex index = UiManager::getIns().UI()->treeView->indexAt(pos);
    if (!index.isValid()) {
        return;
    }
    QMenu contextMenu(this);
    this->addLayerAction = new QAction("Add Layer", &contextMenu);
    this->addGroupAction = new QAction("Add Group", &contextMenu);
    this->deleteNodeAction = new QAction("Delete Node", &contextMenu);// 这里的node包括item和group
    this->copyNodeAction = new QAction("Copy Node", &contextMenu);
    this->setLayerVisibleAction = new QAction("Set Layer Visible", &contextMenu);
    this->setLayerUnvisibleAction = new QAction("Set Layer Unvisible", &contextMenu);
    this->selectAllItemsInGroupAction = new QAction("Select all Items In this Group", &contextMenu);
    contextMenu.addAction(this->addLayerAction);
    contextMenu.addAction(this->addGroupAction);
    contextMenu.addAction(this->deleteNodeAction);
    contextMenu.addAction(this->copyNodeAction);
    contextMenu.addAction(this->setLayerVisibleAction);
    contextMenu.addAction(this->setLayerUnvisibleAction);
    contextMenu.addAction(this->selectAllItemsInGroupAction);
    connect(this->addLayerAction, &QAction::triggered, this, &MainWindow::onTreeViewModelAddLayer);
    connect(this->addGroupAction, &QAction::triggered, this, &MainWindow::onTreeViewModelAddGroup);
    connect(this->deleteNodeAction, &QAction::triggered, this, &MainWindow::onTreeViewModelDeleteNode);
    connect(this->copyNodeAction, &QAction::triggered, this, &MainWindow::onTreeViewModelCopyNode);
    connect(this->setLayerVisibleAction, &QAction::triggered, this, &MainWindow::onTreeViewModelSetLayerVisible);
    connect(this->setLayerUnvisibleAction, &QAction::triggered, this, &MainWindow::onTreeViewModelSetLayerUnvisible);
    connect(this->selectAllItemsInGroupAction, &QAction::triggered, this, &MainWindow::onTreeViewModelSelectAllItemsInGroup);
    onTreeViewModelUpdateActions();
    contextMenu.exec(UiManager::getIns().UI()->treeView->viewport()->mapToGlobal(pos));
}

void MainWindow::onTreeViewModelDeleteNode() {
    TreeModel *model = qobject_cast < TreeModel * > (UiManager::getIns().UI()->treeView->model());
    const auto nodeIndexList =  UiManager::getIns().UI()->treeView->selectionModel()->selectedIndexes();
    for (const QModelIndex &nodeIndex : nodeIndexList) {
        auto node = model->getNode(nodeIndex);
        auto name = node->property(TreeNodePropertyIndex::Name).toString();
        DEBUG_VAR(name);
        auto uuid = node->property(TreeNodePropertyIndex::UUID).toString();
        Manager::getIns().deleteItem(uuid);
    }
    onTreeViewModelUpdateActions();
}

void MainWindow::onTreeViewModelCopyNode() {
    TreeModel *model = qobject_cast < TreeModel * > (UiManager::getIns().UI()->treeView->model());
    const auto nodeIndexList =  UiManager::getIns().UI()->treeView->selectionModel()->selectedIndexes();
    for (const QModelIndex &nodeIndex : nodeIndexList) {
        auto uuid = model->getNode(nodeIndex)->property(TreeNodePropertyIndex::UUID).toString();
        Manager::getIns().copyItem(uuid);
    }
    onTreeViewModelUpdateActions();
}

void MainWindow::onTreeViewModelSetLayerVisible() {
    auto inLayerItems = Manager::getIns().getItemsByLayer(SceneController::getIns().getCurrentLayer ());
    for (const auto& item : inLayerItems) {
        Manager::getIns().setItemVisible(item, true);
    }
}

void MainWindow::onTreeViewModelSetLayerUnvisible() {
    auto inLayerItems = Manager::getIns().getItemsByLayer(SceneController::getIns().getCurrentLayer ());
    for (const auto& item : inLayerItems) {
        Manager::getIns().setItemVisible(item, false);
    }
}

void MainWindow::onTreeViewModelSelectAllItemsInGroup() {
    auto *treeView = UiManager::getIns().UI()->treeView;
    TreeModel *model = qobject_cast < TreeModel * > (treeView->model());
    const auto nodeIndexList
        = UiManager::getIns().UI()->treeView->selectionModel()->selectedIndexes();
    if (nodeIndexList.size() > 1) {
        return;
    }
    auto indexList = model->getAllChildIndexs(nodeIndexList[0]);
    indexList.push_back(nodeIndexList[0]);
    for (const auto &index : indexList) {
        treeView->selectionModel()->select(index,
                                           QItemSelectionModel::Select | QItemSelectionModel::Rows);
    }
}

void MainWindow::onTreeViewModelAddLayer() {
    TreeModel *model = qobject_cast < TreeModel * > (UiManager::getIns().UI()->treeView->model());
    auto layerCount = model->rowCount(QModelIndex());
    if (!model->insertRow(layerCount, QModelIndex())) {
        FATAL_MSG("fail insert layer");
    }
    const QModelIndex layerNodeIndex = model->index(layerCount, 0, QModelIndex());
    QString name = "Layer" + QString::number(layerCount + 1);
    QString type = "Layer";
    Manager::getIns().addItem(layerNodeIndex, name, type);
    onTreeViewModelUpdateActions();
}

void MainWindow::onTreeViewModelAddGroup() {
    TreeModel *model = qobject_cast < TreeModel * > (UiManager::getIns().UI()->treeView->model());
    // 提取选中的节点列表
    const auto nodeIndexList =  UiManager::getIns().UI()->treeView->selectionModel()->selectedIndexes();
    auto mimeList = model->mimeData(nodeIndexList);
    // //在目标处创建group节点
    QModelIndex targetIndex  = UiManager::getIns().UI()->treeView->selectionModel()->currentIndex();
    // DEBUG_VAR(model->getNode(targetIndex)->property(TreeNodePropertyIndex::Type));
    if (!model->insertRows(targetIndex.row() + 1, 1, targetIndex.parent())) {
        return;
    }
    const QModelIndex groupIndex = model->index(targetIndex.row() + 1, 0, targetIndex.parent());
    QString name = "Group";
    QString type = "Group";
    Manager::getIns().addItem(groupIndex, name, type);
    // 把节点列表移动到group节点下
    model->dropMimeData(mimeList, Qt::MoveAction, 0, 0, groupIndex);
    // 最后再把之前的节点删除; 一定不能先删除, 不然会影响到插入;
    for (const QModelIndex &nodeIndex : nodeIndexList) {
        auto node = model->getNode(nodeIndex);
        auto parentNode = node->parent();
        auto parentNodeIndex = model->getIndex(parentNode);
        model->removeRows(node->indexInParent(), 1, parentNodeIndex);
    }
    onTreeViewModelUpdateActions();
}

void MainWindow::onTreeViewModelUpdateActions() {
    TreeModel *model = qobject_cast < TreeModel * > (UiManager::getIns().UI()->treeView->model());
    const auto nodeIndexList =  UiManager::getIns().UI()->treeView->selectionModel()->selectedIndexes();
    for (const QModelIndex &nodeIndex : nodeIndexList) {
        QString type = model->nodeProperty(nodeIndex, TreeNodePropertyIndex::Type).toString();
        if (type == "Layer") { // layer已经被限制不能参与多选,只能被单选; 所以这里直接返回layer的menu就行
            this->addLayerAction->setEnabled(true);
            this->setLayerVisibleAction->setEnabled(true);
            this->setLayerUnvisibleAction->setEnabled(true);
            this->addGroupAction->setEnabled(false);
            this->deleteNodeAction->setEnabled(false);
            this->copyNodeAction->setEnabled(false);
            this->selectAllItemsInGroupAction->setEnabled(false);
            // SceneController::getIns().setCurrentLayer (model->getNode(nodeIndex)->indexInParent() + 1);
            return;
        } else if (type == "Group") {
            this->addLayerAction->setEnabled(false);
            this->setLayerVisibleAction->setEnabled(false);
            this->setLayerUnvisibleAction->setEnabled(false);
            this->addGroupAction->setEnabled(true);
            this->deleteNodeAction->setEnabled(true);
            this->copyNodeAction->setEnabled(false);
            this->selectAllItemsInGroupAction->setEnabled(true);
            return;
        } else if (type == "Item") {
            this->addLayerAction->setEnabled(false);
            this->setLayerVisibleAction->setEnabled(false);
            this->setLayerUnvisibleAction->setEnabled(false);
            this->addGroupAction->setEnabled(true);
            this->deleteNodeAction->setEnabled(true);
            this->copyNodeAction->setEnabled(true);
            this->selectAllItemsInGroupAction->setEnabled(false);
            return;
        }
    }
}


///
/// test function
///
void printResults(const std::vector < cavc::Polyline < double>>& results) {
    for (size_t i = 0; i < results.size(); ++i) {
        const cavc::Polyline < double > & polyline = results[i];
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










