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
#include "colordelegate.h"
#include "drawcontroller.h"
#include "editcontroller.h"
#include "keyboardmanager.h"
#include "manager.h"
#include "scenecontroller.h"
#include "tablemodel.h"
#include "treemodel.h"
#include "uimanager.h"
#include "laserworker.h"
#include <polyline.hpp>
#include <QThread>

///
/// \brief MainWindow::MainWindow
/// \param parent
///
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    auto ui = std::make_shared < Ui::MainWindow > ();
    ui->setupUi(this);
    UiManager::getIns().setUI(std::move(ui));
    showMaximized();
    //
    initTitleBar();
    initGraphicsView();
    initDrawToolButton();
    initEditToolButton();
    initLayerButton();
    initSignalButton();
    initHardWareButton();
    initTreeViewModel();
    // initTableViewModel();
    initStatusBar();
    initTabWidget();
    initLaserWorker();
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
    QPen pen = []() {
        QPen pen(Qt::red, 1);
        pen.setCosmetic(true);
        return pen;
    }
    ();
    QGraphicsLineItem *xAxis = new QGraphicsLineItem(-100, 0, 100, 0);
    QGraphicsLineItem *yAxis = new QGraphicsLineItem(0, -100, 0, 100);
    xAxis->setPen(pen);
    xAxis->setPos(0, 0);
    yAxis->setPen(pen);
    yAxis->setPos(0, 0);
    SceneController::getIns().scene->addItem(xAxis);
    SceneController::getIns().scene->addItem(yAxis);
    QGraphicsLineItem *xArrowL = new QGraphicsLineItem(90, 10, 100, 0);
    QGraphicsLineItem *xArrowR = new QGraphicsLineItem(90, -10, 100, 0);
    xArrowL->setPen(pen);
    xArrowR->setPen(pen);
    SceneController::getIns().scene->addItem(xArrowL);
    SceneController::getIns().scene->addItem(xArrowR);
    QGraphicsLineItem *yArrowL = new QGraphicsLineItem(10, 90, 0, 100);
    QGraphicsLineItem *yArrowR = new QGraphicsLineItem(-10, 90, 0, 100);
    yArrowL->setPen(pen);
    yArrowR->setPen(pen);
    SceneController::getIns().scene->addItem(yArrowL);
    SceneController::getIns().scene->addItem(yArrowR);
    double scale = 4;
    QGraphicsLineItem *bound1 = new QGraphicsLineItem(900 * scale,
        900 * scale,
        1000 * scale,
        1000 * scale);
    QGraphicsLineItem *bound2 = new QGraphicsLineItem(-1000 * scale,
        -1000 * scale,
        -900 * scale,
        -900 * scale);
    QGraphicsLineItem *bound3 = new QGraphicsLineItem(-900 * scale,
        900 * scale,
        -1000 * scale,
        1000 * scale);
    QGraphicsLineItem *bound4 = new QGraphicsLineItem(1000 * scale,
        -1000 * scale,
        900 * scale,
        -900 * scale);
    bound1->setPen(pen);
    bound2->setPen(pen);
    bound3->setPen(pen);
    bound4->setPen(pen);
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
    /// 粘贴 复制 剪切
    ///
    ///
    QToolButton *cutButton = UiManager::getIns().UI()->cutButton;
    cutButton->setIcon(QIcon(":/button/cutButton.png"));
    cutButton->setIconSize(QSize(30, 30));
    cutButton->setStyleSheet(buttonStyle);
    cutButton->setCheckable(true);
    cutButton->setAutoExclusive(false);
    cutButton->setToolTip("");
    UiManager::getIns().registerToolButton(cutButton);
    connect(cutButton, &QToolButton::clicked,
            this, &MainWindow::onCutButtonClicked);
    //
    QToolButton *copyButton = UiManager::getIns().UI()->copyButton;
    copyButton->setIcon(QIcon(":/button/copyButton.png"));
    copyButton->setIconSize(QSize(30, 30));
    copyButton->setStyleSheet(buttonStyle);
    copyButton->setCheckable(true);
    copyButton->setAutoExclusive(false);
    copyButton->setToolTip("");
    UiManager::getIns().registerToolButton(copyButton);
    connect(copyButton, &QToolButton::clicked,
            this, &MainWindow::onCopyButtonClicked);
    //
    QToolButton *pasteButton = UiManager::getIns().UI()->pasteButton;
    pasteButton->setIcon(QIcon(":/button/pasteButton.png"));
    pasteButton->setIconSize(QSize(30, 30));
    pasteButton->setStyleSheet(buttonStyle);
    pasteButton->setCheckable(true);
    pasteButton->setAutoExclusive(false);
    pasteButton->setToolTip("");
    UiManager::getIns().registerToolButton(pasteButton);
    connect(pasteButton, &QToolButton::clicked,
            this, &MainWindow::onPasteButtonClicked);
    //
    //
    QToolButton *mirrorHorizontalButton = UiManager::getIns().UI()->mirrorHorizontalButton;
    mirrorHorizontalButton->setIcon(QIcon(":/button/mirrorHorizontalButton.png"));
    mirrorHorizontalButton->setIconSize(QSize(30, 30));
    mirrorHorizontalButton->setStyleSheet(buttonStyle);
    mirrorHorizontalButton->setCheckable(true);
    mirrorHorizontalButton->setAutoExclusive(false);
    mirrorHorizontalButton->setToolTip("");
    UiManager::getIns().registerToolButton(mirrorHorizontalButton);
    connect(mirrorHorizontalButton, &QToolButton::clicked,
            this, &MainWindow::onMirrorHorizontalButtonClicked);
    //
    QToolButton *mirrorVerticalButton = UiManager::getIns().UI()->mirrorVerticalButton;
    mirrorVerticalButton->setIcon(QIcon(":/button/mirrorVerticalButton.png"));
    mirrorVerticalButton->setIconSize(QSize(30, 30));
    mirrorVerticalButton->setStyleSheet(buttonStyle);
    mirrorVerticalButton->setCheckable(true);
    mirrorVerticalButton->setAutoExclusive(false);
    mirrorVerticalButton->setToolTip("");
    UiManager::getIns().registerToolButton(mirrorVerticalButton);
    connect(mirrorVerticalButton, &QToolButton::clicked,
            this, &MainWindow::onMirrorVerticalButtonClicked);
}

void MainWindow::initLayerButton() {
    auto buttonStyle = buttonStyle1;
    //
    QToolButton *addLayerButton = UiManager::getIns().UI()->addLayerButton;
    addLayerButton->setIcon(QIcon(":/button/addLayerButton.png"));
    addLayerButton->setIconSize(QSize(30, 30));
    addLayerButton->setStyleSheet(buttonStyle);
    addLayerButton->setCheckable(false);
    addLayerButton->setToolTip("");
    UiManager::getIns().registerToolButton(addLayerButton);
    connect(addLayerButton, &QToolButton::clicked,
            this, &MainWindow::onAddLayerButtonClicked);
    //
    QToolButton *deleteLayerButton = UiManager::getIns().UI()->deleteLayerButton;
    deleteLayerButton->setIcon(QIcon(":/button/deleteLayerButton.png"));
    deleteLayerButton->setIconSize(QSize(30, 30));
    deleteLayerButton->setStyleSheet(buttonStyle);
    deleteLayerButton->setCheckable(false);
    deleteLayerButton->setToolTip("");
    UiManager::getIns().registerToolButton(deleteLayerButton);
    connect(deleteLayerButton, &QToolButton::clicked,
            this, &MainWindow::onDeleteLayerButtonClicked);
    //
    // QToolButton *setLayerColorButton = UiManager::getIns().UI()->setLayerColorButton;
    // setLayerColorButton->setIcon(QIcon(":/button/setLayerColorButton.png"));
    // setLayerColorButton->setIconSize(QSize(30, 30));
    // setLayerColorButton->setStyleSheet(buttonStyle);
    // setLayerColorButton->setCheckable(false);
    // setLayerColorButton->setToolTip("");
    // UiManager::getIns().registerToolButton(setLayerColorButton);
    // connect(breakOffsetItemButton, &QToolButton::clicked,
    //         this, &MainWindow::onBreakOffsetItemButtonClicked);
    //
}

void MainWindow::initSignalButton() {
    QString buttonStyle = buttonStyle1;
    QToolButton *digitalInButton = UiManager::getIns().UI()->digitalInButton;
    digitalInButton->setIcon(QIcon(":/button/digitalInButton.png"));
    digitalInButton->setIconSize(QSize(30, 30));
    digitalInButton->setStyleSheet(buttonStyle);
    digitalInButton->setCheckable(true);
    digitalInButton->setAutoExclusive(false);
    digitalInButton->setToolTip("");
    UiManager::getIns().registerToolButton(digitalInButton);
    connect(digitalInButton,
            &QToolButton::clicked,
            this,
            &MainWindow::onDigitalInButtonClicked);
    //
    QToolButton *digitalOutButton = UiManager::getIns().UI()->digitalOutButton;
    digitalOutButton->setIcon(QIcon(":/button/digitalOutButton.png"));
    digitalOutButton->setIconSize(QSize(30, 30));
    digitalOutButton->setStyleSheet(buttonStyle);
    digitalOutButton->setCheckable(true);
    digitalOutButton->setAutoExclusive(false);
    digitalOutButton->setToolTip("");
    UiManager::getIns().registerToolButton(digitalOutButton);
    connect(digitalOutButton,
            &QToolButton::clicked,
            this,
            &MainWindow::onDigitalOutButtonClicked);
    //
    QToolButton *doPauseButton = UiManager::getIns().UI()->doPauseButton;
    doPauseButton->setIcon(QIcon(":/button/doPauseButton.png"));
    doPauseButton->setIconSize(QSize(30, 30));
    doPauseButton->setStyleSheet(buttonStyle);
    doPauseButton->setCheckable(true);
    doPauseButton->setAutoExclusive(false);
    doPauseButton->setToolTip("");
    UiManager::getIns().registerToolButton(doPauseButton);
    connect(doPauseButton,
            &QToolButton::clicked,
            this,
            &MainWindow::onDoPauseButtonClicked);
    //
    QToolButton *delayTimeButton = UiManager::getIns().UI()->delayTimeButton;
    delayTimeButton->setIcon(QIcon(":/button/delayTimeButton.png"));
    delayTimeButton->setIconSize(QSize(30, 30));
    delayTimeButton->setStyleSheet(buttonStyle);
    delayTimeButton->setCheckable(true);
    delayTimeButton->setAutoExclusive(false);
    delayTimeButton->setToolTip("");
    UiManager::getIns().registerToolButton(delayTimeButton);
    connect(delayTimeButton,
            &QToolButton::clicked,
            this,
            &MainWindow::onDelayTimeButtonClicked);
    //
    QToolButton *motionButton = UiManager::getIns().UI()->motionButton;
    motionButton->setIcon(QIcon(":/button/motionButton.png"));
    motionButton->setIconSize(QSize(30, 30));
    motionButton->setStyleSheet(buttonStyle);
    motionButton->setCheckable(true);
    motionButton->setAutoExclusive(false);
    motionButton->setToolTip("");
    UiManager::getIns().registerToolButton(motionButton);
    connect(motionButton,
            &QToolButton::clicked,
            this,
            &MainWindow::onMotionButtonClicked);
    //
    QToolButton *loopButton = UiManager::getIns().UI()->loopButton;
    loopButton->setIcon(QIcon(":/button/loopButton.png"));
    loopButton->setIconSize(QSize(30, 30));
    loopButton->setStyleSheet(buttonStyle);
    loopButton->setCheckable(true);
    loopButton->setAutoExclusive(false);
    loopButton->setToolTip("");
    UiManager::getIns().registerToolButton(loopButton);
    connect(loopButton,
            &QToolButton::clicked,
            this,
            &MainWindow::onLoopButtonClicked);
}

void MainWindow::initHardWareButton() {
    QString buttonStyle = buttonStyle1;
    //
    QToolButton *markButton = UiManager::getIns().UI()->markButton;
    markButton->setIcon(QIcon(":/button/markButton.png"));
    markButton->setIconSize(QSize(30, 30));
    markButton->setStyleSheet(buttonStyle1);
    markButton->setCheckable(false);
    markButton->setAutoExclusive(false);
    markButton->setToolTip("");
    connect(markButton,
            &QToolButton::clicked,
            this,
            &MainWindow::onMarkButtonClicked);
}

void MainWindow::initStatusBar() {
    this->labelMouseCoordinate = new QLabel("coordinate: ");
    this->labelMouseCoordinate->setMinimumWidth(150);
    UiManager::getIns().UI()->statusBar->addWidget(this->labelMouseCoordinate);
}

void MainWindow::initTreeViewModel() {
    /// \brief model
    auto* model = new TreeModel("Items Browser", this);
    auto* view = UiManager::getIns().UI()->treeView;
    model->setupDefaultModelData();
    view->setStyleSheet(treeViewModelStyle1);
    view->setModel(model);
    view->bindModel();
    view->expandAll();
    view->setSelectionMode(QAbstractItemView::ExtendedSelection);
    view->setDragEnabled(true);
    view->setAcceptDrops(true);
    view->setDropIndicatorShown(true);
    view->setDragDropMode(QAbstractItemView::InternalMove);
    view->setColumnWidth(0, 200);
    view->setColumnWidth(1, 60);
    view->setColumnWidth(2, 60);
    view->setColumnWidth(3, 60);
    ///  contextmenu
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
    /// 设置自定义颜色编辑器
    view->setItemDelegateForColumn(3, new ColorDelegate(view));
    view->setEditTriggers(QAbstractItemView::AllEditTriggers); // 单机弹出颜色框
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

void MainWindow::initLaserWorker() {
    LaserWorker* worker = new LaserWorker();
    QThread* thread = new QThread();
    worker->moveToThread(thread);
    connect(thread, &QThread::started, worker, &LaserWorker::run);
    thread->start();
}

void MainWindow::test() {}

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
    QMainWindow::resizeEvent(event);
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
    //         Manager::getIns().etItemMovable(item, false);
    //         QTimer::singleShot(10, this, [item]() {
    //             Manager::getIns().etItemMovable(item, false);
    //         });
    //     }
    // }
    // 非拖拽行为
    if (KeyboardManager::getIns().IsMouseLeftButtonHold == false && KeyboardManager::getIns().IsMouseRightButtonHold == false) {
        switch (SceneController::getIns().m_currentOperationEvent) {
            case OperationEvent::EditProperty: {
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
        switch (SceneController::getIns().m_currentOperationEvent) {
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
        switch (SceneController::getIns().m_currentOperationEvent) {
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
    switch (SceneController::getIns().m_currentOperationEvent) {
        case OperationEvent::DragScene: {
                SceneController::getIns().dragScene(pointCoordView, event);
                break;
            }
        case OperationEvent:: EditProperty: {
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
    switch (SceneController::getIns().m_currentOperationEvent) {
        case OperationEvent::DragScene: {
                SceneController::getIns().dragScene(pointCoordView, event);
                break;
            }
        case OperationEvent:: EditProperty: {
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
    switch (SceneController::getIns().m_currentOperationEvent) {
        case OperationEvent::DragScene: {
                SceneController::getIns().dragScene(pointCoordView, event);
                break;
            }
        case OperationEvent:: EditProperty: {
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
    switch (SceneController::getIns().m_currentOperationEvent) {
        case OperationEvent::DragScene: {
                SceneController::getIns().dragScene(pointCoordView, event);
                break;
            }
        case OperationEvent:: EditProperty: {
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
    SceneController::getIns().m_currentOperationEvent = OperationEvent::DrawLine;
}

void MainWindow::onDrawCircleButtonClicked() {
    setDrawMode();
    UiManager::getIns().UI()->drawCircleButton->setChecked(true);
    SceneController::getIns().m_currentOperationEvent = OperationEvent::DrawCircle;
}

void MainWindow::onDrawPolylineButtonClicked() {
    setDrawMode();
    UiManager::getIns().UI()->drawPolylineButton->setChecked(true);
    SceneController::getIns().m_currentOperationEvent = OperationEvent::DrawPolyline;
}

void MainWindow::onDrawArcButtonClicked() {
    setDrawMode();
    UiManager::getIns().UI()->drawArcButton->setChecked(true);
    SceneController::getIns().m_currentOperationEvent = OperationEvent::DrawArc;
}

void MainWindow::onDrawPointButtonClicked() {
    setDrawMode();
    UiManager::getIns().UI()->drawPointButton->setChecked(true);
    SceneController::getIns().m_currentOperationEvent = OperationEvent::DrawPoint;
}

void MainWindow::onDrawSpiralButtonClicked() {
    setDrawMode();
    UiManager::getIns().UI()->drawSpiralButton->setChecked(true);
    SceneController::getIns().m_currentOperationEvent = OperationEvent::DrawSpiral;
}

void MainWindow::onDrawRectButtonClicked() {
    setDrawMode();
    UiManager::getIns().UI()->drawRectButton->setChecked(true);
    SceneController::getIns().m_currentOperationEvent = OperationEvent::DrawRect;
}

void MainWindow::onDrawPolygonButtonClicked() {
    setDrawMode();
    UiManager::getIns().UI()->drawPolygonButton->setChecked(true);
    SceneController::getIns().m_currentOperationEvent = OperationEvent::DrawPolygon;
}

void MainWindow::onDrawEllipseButtonClicked() {
    setDrawMode();
    UiManager::getIns().UI()->drawEllipseButton->setChecked(true);
    SceneController::getIns().m_currentOperationEvent = OperationEvent::DrawEllipse;
}

///
/// \brief MainWindow::onDragSceneButtonClicked
///
void MainWindow::onDragSceneButtonClicked() {
    // 设置鼠标光标
    UiManager::getIns().UI()->graphicsView->viewport()->setCursor(Qt::OpenHandCursor);
    // tool status
    SceneController::getIns().m_currentOperationEvent = OperationEvent::DragScene;
    DrawController::getIns().resetTmpItemStatus();
    // drag mode/所有物体设置不可动
    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::NoDrag);
    auto allItems = Manager::getIns().getChildItems("0-0-0-0");
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
    SceneController::getIns().m_currentOperationEvent = OperationEvent::EditProperty;
    DrawController::getIns().resetTmpItemStatus();
    // drag mode
    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    // button check
    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->editButton->setChecked(true);
    // 设置当前图层内物体可动;所有物体颜色为黑;等等默认行为(都在setCurrentLayer里)
    SceneController::getIns().setCurrentLayer(SceneController::getIns().getCurrentLayer());
}

void MainWindow::setEditMode() {
    // 设置鼠标光标
    UiManager::getIns().UI()->graphicsView->viewport()->setCursor(Qt::ArrowCursor);
    // tool status
    SceneController::getIns().m_currentOperationEvent = OperationEvent::EditProperty;
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

void MainWindow::onMirrorHorizontalButtonClicked() {
    setEditMode();
    EditController::getIns().onMirrorHorizontalTriggered();
}

void MainWindow::onMirrorVerticalButtonClicked() {
    setEditMode();
    EditController::getIns().onMirrorVerticalTriggered();
}

void MainWindow::onDeleteButtonClicked() {
    setEditMode();
    EditController::getIns().onDeleteItemsTriggered ();
}

void MainWindow::onBreakCopiedItemButtonClicked() {
    setEditMode();
    EditController::getIns().onBreakCopiedItemTriggered();
}

void MainWindow::onBreakOffsetItemButtonClicked() {
    setEditMode();
    EditController::getIns().onBreakOffsetItemTriggered();
}

void MainWindow::onCutButtonClicked() {
    setEditMode();
    EditController::getIns().onCutItemsTriggered();
}

void MainWindow::onCopyButtonClicked() {
    setEditMode();
    EditController::getIns().onCopyItemsTriggered();
}

void MainWindow::onPasteButtonClicked() {
    setEditMode();
    EditController::getIns().onPasteItemsTriggered();
}

void MainWindow::onDigitalInButtonClicked() {
    setEditMode();
    Manager::getIns().addItem("DigitalIn", "Signal");
}

void MainWindow::onDigitalOutButtonClicked() {
    setEditMode();
    Manager::getIns().addItem("DigitalOut", "Signal");
}

void MainWindow::onDoPauseButtonClicked() {
    setEditMode();
    Manager::getIns().addItem("DoPause", "Signal");
}

void MainWindow::onDelayTimeButtonClicked() {
    setEditMode();
    Manager::getIns().addItem("DelayTime", "Signal");
}

void MainWindow::onMotionButtonClicked() {
    setEditMode();
    Manager::getIns().addItem("Motion", "Signal");
}

void MainWindow::onLoopButtonClicked() {
    setEditMode();
    Manager::getIns().addItem("Loop", "Signal");
}

void MainWindow::onMarkButtonClicked() {
    DEBUG_MSG(1);
}

void MainWindow::onAddLayerButtonClicked() {
    SceneController::getIns().addLayer();
}

void MainWindow::onDeleteLayerButtonClicked() {
    SceneController::getIns().deleteCurrentLayer ();
}


void MainWindow::onTreeViewModelShowContextMenu(const QPoint &pos) {
    // 获取鼠标点击的位置
    QModelIndex index = UiManager::getIns().UI()->treeView->indexAt(pos);
    if (!index.isValid()) {
        return;
    }
    QMenu contextMenu(this);
    this->addGroupAction = new QAction("Add group", &contextMenu);
    this->deleteGroupAction = new QAction("Delete group", &contextMenu);
    this->selectAllItemsInGroupAction = new QAction("Select all items in this group", &contextMenu);
    contextMenu.addAction(this->addGroupAction);
    contextMenu.addAction(this->deleteGroupAction);
    contextMenu.addAction(this->selectAllItemsInGroupAction);// 暂时只给group做这个功能 不给layer做
    connect(this->addGroupAction, &QAction::triggered, this, [ = ]() {
        EditController::getIns().onTreeViewModelAddGroup();
    });
    connect(this->deleteGroupAction, &QAction::triggered, this, [ = ]() {
        EditController::getIns().onTreeViewModelDeleteGroup();
    });
    connect(this->selectAllItemsInGroupAction, &QAction::triggered, this, [ = ]() {
        EditController::getIns().onTreeViewModelSelectAllItemsInGroup ();
    });
    onTreeViewModelUpdateActions();
    contextMenu.exec(UiManager::getIns().UI()->treeView->viewport()->mapToGlobal(pos));
}

void MainWindow::onTreeViewModelUpdateActions() {
    TreeModel *model = qobject_cast < TreeModel * > (UiManager::getIns().UI()->treeView->model());
    const auto nodeIndexList
        = UiManager::getIns().UI()->treeView->selectionModel()->selectedIndexes();
    if (nodeIndexList.empty()) {
        this->addGroupAction->setEnabled(false);
        this->selectAllItemsInGroupAction->setEnabled(true);
        return;
    }
    const auto nodeIndex = nodeIndexList[0];
    QString type = model->nodeProperty(nodeIndex, TreeNodePropertyIndex::Type).toString();
    if (type == "Layer") { // layer已经被限制无法选中
        this->addGroupAction->setEnabled(false);
        this->deleteGroupAction->setEnabled(false);
        this->selectAllItemsInGroupAction->setEnabled(false);
        return;
    } else if (type == "Group" && nodeIndexList.size () == 1 ) {
        this->addGroupAction->setEnabled(false);
        this->deleteGroupAction->setEnabled(true);
        this->selectAllItemsInGroupAction->setEnabled(true);
        return;
    } else if (type == "Item" && nodeIndexList.size () > 1) {
        this->addGroupAction->setEnabled(true);
        this->deleteGroupAction->setEnabled(false);
        this->selectAllItemsInGroupAction->setEnabled(false);
        return;
    } else {
        this->addGroupAction->setEnabled(false);
        this->deleteGroupAction->setEnabled(false);
        this->selectAllItemsInGroupAction->setEnabled(false);
        return;
    }
}
