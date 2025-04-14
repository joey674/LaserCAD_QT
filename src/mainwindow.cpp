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
#include "scenemanager.h"
#include "editmanager.h"
#include "drawmanager.h"
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
    initTreeViewModel();
    initTableViewModel();
    initStatusBar();
    initTabWidget();
    //
    connect(SceneManager::getIns().scene, &QGraphicsScene::selectionChanged, [ = ]() {
        EditManager::getIns().onSceneSelectionChanged();
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
    SceneManager::getIns().scene = new QGraphicsScene();
    UiManager::getIns().UI()->graphicsView->setScene(SceneManager::getIns().scene);
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
    SceneManager::getIns().setSceneScale(0.1, 0.1);
    QTimer::singleShot(100, []() {
        SceneManager::getIns().setSceneScale(10, 10);
    });
    QGraphicsLineItem *xAxis = new QGraphicsLineItem(-100, 0, 100, 0);
    QGraphicsLineItem *yAxis = new QGraphicsLineItem(0, -100, 0, 100);
    xAxis->setPen(AXIS_PEN);
    xAxis->setPos(0, 0);
    yAxis->setPen(AXIS_PEN);
    yAxis->setPos(0, 0);
    SceneManager::getIns().scene->addItem(xAxis);
    SceneManager::getIns().scene->addItem(yAxis);
    QGraphicsLineItem *xArrowL = new QGraphicsLineItem(90, 10, 100, 0);
    QGraphicsLineItem *xArrowR = new QGraphicsLineItem(90, -10, 100, 0);
    xArrowL->setPen(AXIS_PEN);
    xArrowR->setPen(AXIS_PEN);
    SceneManager::getIns().scene->addItem(xArrowL);
    SceneManager::getIns().scene->addItem(xArrowR);
    QGraphicsLineItem *yArrowL = new QGraphicsLineItem(10, 90, 0, 100);
    QGraphicsLineItem *yArrowR = new QGraphicsLineItem(-10, 90, 0, 100);
    yArrowL->setPen(AXIS_PEN);
    yArrowR->setPen(AXIS_PEN);
    SceneManager::getIns().scene->addItem(yArrowL);
    SceneManager::getIns().scene->addItem(yArrowR);
    QGraphicsLineItem *bound1 = new QGraphicsLineItem(900, 900, 1000, 1000);
    QGraphicsLineItem *bound2 = new QGraphicsLineItem(-1000, -1000, -900, -900);
    QGraphicsLineItem *bound3 = new QGraphicsLineItem(-900, 900, -1000, 1000);
    QGraphicsLineItem *bound4 = new QGraphicsLineItem(1000, -1000, 900, -900);
    bound1->setPen(AXIS_PEN);
    bound2->setPen(AXIS_PEN);
    bound3->setPen(AXIS_PEN);
    bound4->setPen(AXIS_PEN);
    SceneManager::getIns().scene->addItem(bound1);
    SceneManager::getIns().scene->addItem(bound2);
    SceneManager::getIns().scene->addItem(bound3);
    SceneManager::getIns().scene->addItem(bound4);
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
    QToolButton *drawLineButton = UiManager::getIns().UI()->drawLineButton;
    drawLineButton->setIcon(QIcon(":/button/drawLineButton.svg"));
    drawLineButton->setIconSize(QSize(30, 30));
    drawLineButton->setStyleSheet(buttonStyle);
    drawLineButton->setCheckable(true);
    drawLineButton->setAutoExclusive(false);
    drawLineButton->setToolTip(drawLineButtonToolTip);
    QToolButton *drawArcButton = UiManager::getIns().UI()->drawArcButton;
    drawArcButton->setIcon(QIcon(":/button/drawArcButton.svg"));
    drawArcButton->setIconSize(QSize(30, 30));
    drawArcButton->setStyleSheet(buttonStyle);
    drawArcButton->setCheckable(true);
    drawArcButton->setAutoExclusive(false);
    drawArcButton->setToolTip(drawArcButtonToolTip);
    QToolButton *drawPointButton = UiManager::getIns().UI()->drawPointButton;
    drawPointButton->setIcon(QIcon(":/button/drawPointButton.svg"));
    drawPointButton->setIconSize(QSize(30, 30));
    drawPointButton->setStyleSheet(buttonStyle);
    drawPointButton->setCheckable(true);
    drawPointButton->setAutoExclusive(false);
    // drawArcButton->setToolTip(drawArcButtonToolTip);
    QToolButton *drawCircleButton = UiManager::getIns().UI()->drawCircleButton;
    drawCircleButton->setIcon(QIcon(":/button/drawCircleButton.svg"));
    drawCircleButton->setIconSize(QSize(30, 30));
    drawCircleButton->setStyleSheet(buttonStyle);
    drawCircleButton->setCheckable(true);
    drawCircleButton->setAutoExclusive(false);
    drawCircleButton->setToolTip(drawCircleButtonToolTip);
    QToolButton *drawEllipseButton = UiManager::getIns().UI()->drawEllipseButton;
    drawEllipseButton->setIcon(QIcon(":/button/drawEllipseButton.svg"));
    drawEllipseButton->setIconSize(QSize(30, 30));
    drawEllipseButton->setStyleSheet(buttonStyle);
    drawEllipseButton->setCheckable(true);
    drawEllipseButton->setAutoExclusive(false);
    drawEllipseButton->setToolTip(drawEllipseButtonToolTip);
    QToolButton *drawRectButton = UiManager::getIns().UI()->drawRectButton;
    drawRectButton->setIcon(QIcon(":/button/drawRectButton.svg"));
    drawRectButton->setIconSize(QSize(30, 30));
    drawRectButton->setStyleSheet(buttonStyle);
    drawRectButton->setCheckable(true);
    drawRectButton->setAutoExclusive(false);
    drawRectButton->setToolTip(drawRectButtonToolTip);
    QToolButton *drawPolygonButton = UiManager::getIns().UI()->drawPolygonButton;
    drawPolygonButton->setIcon(QIcon(":/button/drawPolygonButton.svg"));
    drawPolygonButton->setIconSize(QSize(30, 30));
    drawPolygonButton->setStyleSheet(buttonStyle);
    drawPolygonButton->setCheckable(true);
    drawPolygonButton->setAutoExclusive(false);
    drawPolygonButton->setToolTip(drawPolygonButtonToolTip);
    QToolButton *drawSpiralButton = UiManager::getIns().UI()->drawSpiralButton;
    drawSpiralButton->setIcon(QIcon(":/button/drawSpiralButton.svg"));
    drawSpiralButton->setIconSize(QSize(30, 30));
    drawSpiralButton->setStyleSheet(buttonStyle);
    drawSpiralButton->setCheckable(true);
    drawSpiralButton->setAutoExclusive(false);
    drawSpiralButton->setToolTip(drawSpiralButtonToolTip);
    connect(drawPolylineButton, &QToolButton::clicked, this, &MainWindow::onDrawPolylineButtonClicked);
    connect(drawLineButton, &QToolButton::clicked, this, &MainWindow::onDrawLineButtonClicked);
    connect(drawArcButton, &QToolButton::clicked, this, &MainWindow::onDrawArcButtonClicked);
    connect(drawPointButton, &QToolButton::clicked, this, &MainWindow::onDrawPointButtonClicked);
    connect(drawCircleButton, &QToolButton::clicked, this, &MainWindow::onDrawCircleButtonClicked);
    connect(drawEllipseButton, &QToolButton::clicked, this, &MainWindow::onDrawEllipseButtonClicked);
    connect(drawRectButton, &QToolButton::clicked, this, &MainWindow::onDrawRectButtonClicked);
    connect(drawPolygonButton, &QToolButton::clicked, this, &MainWindow::onDrawPolygonButtonClicked);
    connect(drawSpiralButton, &QToolButton::clicked, this, &MainWindow::onDrawSpiralButtonClicked);
}

void MainWindow::initEditToolButton() {
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
}



void MainWindow::initLayerButton() {
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

void MainWindow::initStatusBar() {
    this->labelMouseCoordinate = new QLabel("coordinate: ");
    this->labelMouseCoordinate->setMinimumWidth(150);
    UiManager::getIns().UI()->statusBar->addWidget(this->labelMouseCoordinate);
}



void MainWindow::initTreeViewModel() {
    ///
    /// \brief model
    ///
    auto *model = new TreeModel("TreeViewModel", this);
    UiManager::getIns().UI()->treeView->setStyleSheet(treeViewModelStyle1);
    UiManager::getIns().UI()->treeView->setModel(model);
    UiManager::getIns().UI()->treeView->bindModel();
    UiManager::getIns().UI()->treeView->expandAll();
    UiManager::getIns().UI()->treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    UiManager::getIns().UI()->treeView->setDragEnabled(true);
    UiManager::getIns().UI()->treeView->setAcceptDrops(true);
    UiManager::getIns().UI()->treeView->setDropIndicatorShown(true);
    UiManager::getIns().UI()->treeView->setDragDropMode(QAbstractItemView::InternalMove);
    ///
    ///  contextmenu
    ///
    UiManager::getIns().UI()->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(UiManager::getIns().UI()->treeView, &QWidget::customContextMenuRequested, this, &MainWindow::onTreeViewModelShowContextMenu);
    // click
    connect(UiManager::getIns().UI()->treeView, &QTreeView::clicked, this, &MainWindow::onTreeViewModelNodeClicked);
}

void MainWindow::initTableViewModel() {
    auto *model = new TableModel(this);
    UiManager::getIns().UI()->tableView->setModel(model);
    UiManager::getIns().UI()->tableView->verticalHeader()->setVisible(false);
    UiManager::getIns().UI()->tableView->setAlternatingRowColors(true);
    UiManager::getIns().UI()->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    UiManager::getIns().UI()->tableView->setColumnWidth(0, 149);
    UiManager::getIns().UI()->tableView->setColumnWidth(1, 149);
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
    SceneManager::getIns().setSceneScale(0.1, 0.1);
    QTimer::singleShot(10, []() {
        SceneManager::getIns().setSceneScale(10, 10);
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
    if (KeyboardManager::getIns().IsMouseLeftButtonHold == true && KeyboardManager::getIns().IsMouseRightButtonHold == true) {
        DrawManager::getIns().resetTmpItemStatus();
        EditManager::getIns().currentEditItem = NULL;
        auto allItems = Manager::getIns().getItemsByLayer(0);
        SceneManager::getIns().scene->clearSelection();
        // 打断一下拖拽过程
        for (const auto& item : allItems) {
            Manager::getIns().setItemMovable(item, false);
            QTimer::singleShot(10, [item]() {
                Manager::getIns().setItemMovable(item, true);
            });
        }
    }
    // 非拖拽行为
    if (KeyboardManager::getIns().IsMouseLeftButtonHold == false && KeyboardManager::getIns().IsMouseRightButtonHold == false) {
        switch (SceneManager::getIns().currentOperationEvent) {
            case OperationEvent::EditProperty: {
                    EditManager::getIns().editItem(pointCoordscene, event);
                    break;
                }
            case OperationEvent::DrawCircle: {
                    DrawManager::getIns().drawCircle(pointCoordscene, event);
                    break;
                }
            case OperationEvent::DrawPolyline: {
                    DrawManager::getIns().drawPolyline(pointCoordscene, event);
                    break;
                }
            case OperationEvent::DrawArc: {
                    DrawManager::getIns().drawArc(pointCoordscene, event);
                    break;
                }
            case OperationEvent::DrawLine: {
                    DrawManager::getIns().drawLine(pointCoordscene, event);
                    break;
                }
            case OperationEvent::DrawSpiral: {
                    DrawManager::getIns().drawSpiral(pointCoordscene, event);
                    break;
                }
            case OperationEvent::DrawRect: {
                    DrawManager::getIns().drawRect(pointCoordscene, event);
                    break;
                }
            case OperationEvent::DrawPolygon: {
                    DrawManager::getIns().drawPolygon(pointCoordscene, event);
                    break;
                }
            case OperationEvent::DrawEllipse: {
                    DrawManager::getIns().drawEllipse(pointCoordscene, event);
                    break;
                }
            default:
                {}
        }
    }
    // 左键拖拽(尽量不要用 因为item的拖动也是左键拖拽 容易撞车造成bug)
    else if (KeyboardManager::getIns().IsMouseLeftButtonHold == true && KeyboardManager::getIns().IsMouseRightButtonHold == false) {
        switch (SceneManager::getIns().currentOperationEvent) {
            case OperationEvent::DragScene: {
                    SceneManager::getIns().dragScene(pointCoordView, event);
                    break;
                }
            default:
                {}
        }
    }
    // 右键拖拽
    else if (KeyboardManager::getIns().IsMouseLeftButtonHold == false && KeyboardManager::getIns().IsMouseRightButtonHold == true) {
        switch (SceneManager::getIns().currentOperationEvent) {
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
    switch (SceneManager::getIns().currentOperationEvent) {
        case OperationEvent::DragScene: {
                SceneManager::getIns().dragScene(pointCoordView, event);
                break;
            }
        case OperationEvent:: EditProperty: {
                EditManager::getIns().editItem(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawCircle: {
                DrawManager::getIns().drawCircle(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawPolyline: {
                DrawManager::getIns().drawPolyline(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawArc: {
                DrawManager::getIns().drawArc(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawLine: {
                DrawManager::getIns().drawLine(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawPoint: {
                DrawManager::getIns().drawPoint(pointCoordscene, event );
                break;
            }
        //
        case OperationEvent::DrawSpiral: {
                DrawManager::getIns().drawSpiral(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawRect: {
                DrawManager::getIns().drawRect(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawPolygon: {
                DrawManager::getIns().drawPolygon(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawEllipse: {
                DrawManager::getIns().drawEllipse(pointCoordscene, event );
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
    switch (SceneManager::getIns().currentOperationEvent) {
        case OperationEvent::DragScene: {
                SceneManager::getIns().dragScene(pointCoordView, event);
                break;
            }
        case OperationEvent:: EditProperty: {
                EditManager::getIns().editItem(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawCircle: {
                DrawManager::getIns().drawCircle(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawPolyline: {
                DrawManager::getIns().drawPolyline(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawArc: {
                DrawManager::getIns().drawArc(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawLine: {
                DrawManager::getIns().drawLine(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawSpiral: {
                DrawManager::getIns().drawSpiral(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawRect: {
                DrawManager::getIns().drawRect(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawPolygon: {
                DrawManager::getIns().drawPolygon(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawEllipse: {
                DrawManager::getIns().drawEllipse(pointCoordscene, event );
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
    switch (SceneManager::getIns().currentOperationEvent) {
        case OperationEvent::DragScene: {
                SceneManager::getIns().dragScene(pointCoordView, event);
                break;
            }
        case OperationEvent:: EditProperty: {
                EditManager::getIns().editItem(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawCircle: {
                DrawManager::getIns().drawCircle(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawPolyline: {
                DrawManager::getIns().drawPolyline(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawArc: {
                DrawManager::getIns().drawArc(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawLine: {
                DrawManager::getIns().drawLine(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawSpiral: {
                DrawManager::getIns().drawSpiral(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawRect: {
                DrawManager::getIns().drawRect(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawPolygon: {
                DrawManager::getIns().drawPolygon(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawEllipse: {
                DrawManager::getIns().drawEllipse(pointCoordscene, event );
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
    switch (SceneManager::getIns().currentOperationEvent) {
        case OperationEvent::DragScene: {
                SceneManager::getIns().dragScene(pointCoordView, event);
                break;
            }
        case OperationEvent:: EditProperty: {
                EditManager::getIns().editItem(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawCircle: {
                DrawManager::getIns().drawCircle(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawPolyline: {
                DrawManager::getIns().drawPolyline(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawArc: {
                DrawManager::getIns().drawArc(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawLine: {
                DrawManager::getIns().drawLine(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawSpiral: {
                DrawManager::getIns().drawSpiral(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawRect: {
                DrawManager::getIns().drawRect(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawPolygon: {
                DrawManager::getIns().drawPolygon(pointCoordscene, event );
                break;
            }
        case OperationEvent::DrawEllipse: {
                DrawManager::getIns().drawEllipse(pointCoordscene, event );
                break;
            }
        default:
            {}
    }
}

void MainWindow::onGraphicsviewMouseRightDoubleClicked(QPoint pointCoordView) {
    UiManager::getIns().UI()->editButton->setChecked(true);
    this->on_editButton_clicked();
}

void MainWindow::onGraphicsviewMouseWheelTriggered(QWheelEvent * event) {
    if (event->angleDelta().y() > 0) {
        SceneManager::getIns().setSceneScale(1.2, 1.2);
    } else {
        SceneManager::getIns().setSceneScale(0.8, 0.8);
    }
}

///
/// \brief MainWindow::onDrawLineButtonClicked
///
void MainWindow::onDrawLineButtonClicked() {
    // 设置鼠标光标
    UiManager::getIns().UI()->graphicsView->viewport()->setCursor(Qt::CrossCursor);
    DrawManager::getIns().resetTmpItemStatus();
    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::NoDrag);
    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->drawLineButton->setChecked(true);
    SceneManager::getIns().currentOperationEvent = OperationEvent::DrawLine;
}

void MainWindow::onDrawCircleButtonClicked() {
    // 设置鼠标光标
    UiManager::getIns().UI()->graphicsView->viewport()->setCursor(Qt::CrossCursor);
    DrawManager::getIns().resetTmpItemStatus();
    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::NoDrag);
    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->drawCircleButton->setChecked(true);
    SceneManager::getIns().currentOperationEvent = OperationEvent::DrawCircle;
}

void MainWindow::onDrawPolylineButtonClicked() {
    // 设置鼠标光标
    UiManager::getIns().UI()->graphicsView->viewport()->setCursor(Qt::CrossCursor);
    DrawManager::getIns().resetTmpItemStatus();
    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::NoDrag);
    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->drawPolylineButton->setChecked(true);
    SceneManager::getIns().currentOperationEvent = OperationEvent::DrawPolyline;
}

void MainWindow::onDrawArcButtonClicked() {
    // 设置鼠标光标
    UiManager::getIns().UI()->graphicsView->viewport()->setCursor(Qt::CrossCursor);
    DrawManager::getIns().resetTmpItemStatus();
    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::NoDrag);
    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->drawArcButton->setChecked(true);
    SceneManager::getIns().currentOperationEvent = OperationEvent::DrawArc;
}

void MainWindow::onDrawPointButtonClicked() {
    // 设置鼠标光标
    UiManager::getIns().UI()->graphicsView->viewport()->setCursor(Qt::CrossCursor);
    DrawManager::getIns().resetTmpItemStatus();
    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::NoDrag);
    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->drawPointButton->setChecked(true);
    SceneManager::getIns().currentOperationEvent = OperationEvent::DrawPoint;
}

void MainWindow::onDrawSpiralButtonClicked() {
    // 设置鼠标光标
    UiManager::getIns().UI()->graphicsView->viewport()->setCursor(Qt::CrossCursor);
    DrawManager::getIns().resetTmpItemStatus();
    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::NoDrag);
    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->drawSpiralButton->setChecked(true);
    SceneManager::getIns().currentOperationEvent = OperationEvent::DrawSpiral;
}

void MainWindow::onDrawRectButtonClicked() {
    // 设置鼠标光标
    UiManager::getIns().UI()->graphicsView->viewport()->setCursor(Qt::CrossCursor);
    DrawManager::getIns().resetTmpItemStatus();
    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::NoDrag);
    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->drawRectButton->setChecked(true);
    SceneManager::getIns().currentOperationEvent = OperationEvent::DrawRect;
}

void MainWindow::onDrawPolygonButtonClicked() {
    // 设置鼠标光标
    UiManager::getIns().UI()->graphicsView->viewport()->setCursor(Qt::CrossCursor);
    DrawManager::getIns().resetTmpItemStatus();
    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::NoDrag);
    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->drawPolygonButton->setChecked(true);
    SceneManager::getIns().currentOperationEvent = OperationEvent::DrawPolygon;
}

void MainWindow::onDrawEllipseButtonClicked() {
    // 设置鼠标光标
    UiManager::getIns().UI()->graphicsView->viewport()->setCursor(Qt::CrossCursor);
    DrawManager::getIns().resetTmpItemStatus();
    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::NoDrag);
    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->drawEllipseButton->setChecked(true);
    SceneManager::getIns().currentOperationEvent = OperationEvent::DrawEllipse;
}


///
///  编辑工具
///
void MainWindow::on_editButton_clicked() {
    // 设置鼠标光标
    UiManager::getIns().UI()->graphicsView->viewport()->setCursor(Qt::ArrowCursor);
    // tool status
    SceneManager::getIns().currentOperationEvent = OperationEvent::EditProperty;
    DrawManager::getIns().resetTmpItemStatus();
    EditManager::getIns().currentEditItem = NULL;
    // drag mode
    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    // button check
    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->editButton->setChecked(true);
    // 设置当前图层内物体可动;所有物体颜色为黑;等等默认行为(都在setCurrentLayer里)
    SceneManager::getIns().setCurrentLayer(SceneManager::getIns().getCurrentLayer());
}

void MainWindow::on_dragSceneButton_clicked() {
    // 设置鼠标光标
    UiManager::getIns().UI()->graphicsView->viewport()->setCursor(Qt::OpenHandCursor);
    // tool status
    SceneManager::getIns().currentOperationEvent = OperationEvent::DragScene;
    DrawManager::getIns().resetTmpItemStatus();
    // drag mode/所有物体设置不可动
    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::NoDrag);
    auto allItems = Manager::getIns().getItemsByLayer(0);
    for (auto item : allItems) {
        Manager::getIns().setItemMovable(item, false);
        Manager::getIns().setItemSelectable(item, false);
    }
    //button check
    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->dragSceneButton->setChecked(true);
}

void MainWindow::on_rotateButton_clicked() {
    // 设置鼠标光标
    UiManager::getIns().UI()->graphicsView->viewport()->setCursor(Qt::ArrowCursor);
    SceneManager::getIns().currentOperationEvent = OperationEvent::None;
    DrawManager::getIns().resetTmpItemStatus();
    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->rotateButton->setChecked(true);
    QList < QGraphicsItem * > selectedItems = SceneManager::getIns().scene->selectedItems();
    if (selectedItems.empty()) {
        return;
    }
    for (auto item = selectedItems.cbegin(); item != selectedItems.cend(); ++item) {
        auto angle = (*item)->rotation();
        (*item)->setRotation(angle + 90);
    }
}

void MainWindow::on_centerButton_clicked() {
    // 设置鼠标光标
    UiManager::getIns().UI()->graphicsView->viewport()->setCursor(Qt::ArrowCursor);
    SceneManager::getIns().currentOperationEvent = OperationEvent::None;
    DrawManager::getIns().resetTmpItemStatus();
    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->centerButton->setChecked(true);
    if (!EditManager::getIns().currentEditItem) {
        return;
    }
    //
    GraphicsItem *item = static_cast < GraphicsItem * > (EditManager::getIns().currentEditItem);
    item->setCenterPos(QPointF{0, 0});
}

void MainWindow::on_createOffsetButton_clicked() {
    // 设置鼠标光标
    UiManager::getIns().UI()->graphicsView->viewport()->setCursor(Qt::ArrowCursor);
    SceneManager::getIns().currentOperationEvent = OperationEvent::None;
    DrawManager::getIns().resetTmpItemStatus();
    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::NoDrag);
    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->createOffsetButton->setChecked(true);
    if (!EditManager::getIns().currentEditItem) {
        return;
    }
    switch (EditManager::getIns().currentEditItem->type()) {
        case PolylineItem::Type: {
                PolylineItem *polylineItem = static_cast < PolylineItem * > (EditManager::getIns().currentEditItem);
                polylineItem->setParallelOffset(20, 6);
                break;
            }
        case ArcItem::Type: {
                ArcItem *arcItem = static_cast < ArcItem * > (EditManager::getIns().currentEditItem);
                arcItem->setParallelOffset(20, 6);
                break;
            }
        default:
            {}
    }
}

void MainWindow::on_deleteButton_clicked() {
    // 设置鼠标光标
    UiManager::getIns().UI()->graphicsView->viewport()->setCursor(Qt::ArrowCursor);
    SceneManager::getIns().currentOperationEvent = OperationEvent::None;
    DrawManager::getIns().resetTmpItemStatus();
    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns().UI()->deleteButton->setChecked(true);
    QList < QGraphicsItem * > selectedItems = SceneManager::getIns().scene->selectedItems();
    if (selectedItems.empty()) {
        return;
    }
    for (auto it = selectedItems.cbegin(); it != selectedItems.cend(); ++it) {
        QGraphicsItem* graphicsItem = *it;
        GraphicsItem* laserItem = dynamic_cast < GraphicsItem * > (graphicsItem);
        // TODO 注意 这里不用删除scene; 会自动处理掉
        // SceneManager::getIns().scene ->removeItem(graphicsItem);
        if(!laserItem) {
            FATAL_MSG("fail pointer convertion");
        }
        Manager::getIns().deleteItem(laserItem->getUUID());
    }
}

void MainWindow::on_undoButton_clicked() {
}

void MainWindow::on_redoButton_clicked() {
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
    contextMenu.addAction(this->addLayerAction);
    contextMenu.addAction(this->addGroupAction);
    contextMenu.addAction(this->deleteNodeAction);
    contextMenu.addAction(this->copyNodeAction);
    contextMenu.addAction(this->setLayerVisibleAction);
    contextMenu.addAction(this->setLayerUnvisibleAction);
    connect(this->addLayerAction, &QAction::triggered, this, &MainWindow::onTreeViewModelAddLayer);
    connect(this->addGroupAction, &QAction::triggered, this, &MainWindow::onTreeViewModelAddGroup);
    connect(this->deleteNodeAction, &QAction::triggered, this, &MainWindow::onTreeViewModelDeleteNode);
    connect(this->copyNodeAction, &QAction::triggered, this, &MainWindow::onTreeViewModelCopyNode);
    connect(this->setLayerVisibleAction, &QAction::triggered, this, &MainWindow::onTreeViewModelSetLayerVisible);
    connect(this->setLayerUnvisibleAction, &QAction::triggered, this, &MainWindow::onTreeViewModelSetLayerUnvisible);
    onTreeViewModelUpdateActions();
    contextMenu.exec(UiManager::getIns().UI()->treeView->viewport()->mapToGlobal(pos));
}

void MainWindow::onTreeViewModelDeleteNode() {
    TreeModel *model = qobject_cast < TreeModel * > (UiManager::getIns().UI()->treeView->model());
    const auto nodeIndexList =  UiManager::getIns().UI()->treeView->selectionModel()->selectedIndexes();
    for (const QModelIndex &nodeIndex : nodeIndexList) {
        auto uuid = model->getNode(nodeIndex)->property(TreeNodePropertyIndex::UUID).toString();
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
    auto inLayerItems = Manager::getIns().getItemsByLayer(this->selectedLayerIndex);
    for (const auto& item : inLayerItems) {
        Manager::getIns().setItemVisible(item, true);
    }
}

void MainWindow::onTreeViewModelSetLayerUnvisible() {
    auto inLayerItems = Manager::getIns().getItemsByLayer(this->selectedLayerIndex);
    for (const auto& item : inLayerItems) {
        Manager::getIns().setItemVisible(item, false);
    }
}

void MainWindow::onTreeViewModelNodeClicked() {
    if (!KeyboardManager::getIns ().IsControlHold) {
        SceneManager::getIns().scene->clearSelection();
    }
    TreeModel *model = qobject_cast < TreeModel * > (UiManager::getIns().UI()->treeView->model());
    const auto node =  UiManager::getIns().UI()->treeView->selectionModel()->currentIndex();
    QString type = model->nodeProperty(node, TreeNodePropertyIndex::Type).toString();
    if (type == "Layer") {
        this->selectedLayerIndex = model->getNode(node)->indexInParent() + 1; // 左键点击和右键点击都要设置; 这两个不会同时触发
        SceneManager::getIns().setCurrentLayer(this->selectedLayerIndex);
    } else if (type == "Group") {
        auto nodeGroup = model->getAllChildNodes(node);
        for (auto node : nodeGroup) {
            auto nodeUuid = node->property(TreeNodePropertyIndex::UUID).toString();
            Manager::getIns().itemMapFind(nodeUuid)->setSelected(true);
        }
    } else if(type == "Item") {
        UUID uuid = model->nodeProperty(node, TreeNodePropertyIndex::UUID).toString();
        Manager::getIns().itemMapFind(uuid)->setSelected(true);
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
            this->selectedLayerIndex = model->getNode(nodeIndex)->indexInParent() + 1;
            SceneManager::getIns().setCurrentLayer(this->selectedLayerIndex);
            return;
        } else if (type == "Group") {
            this->addLayerAction->setEnabled(false);
            this->setLayerVisibleAction->setEnabled(false);
            this->setLayerUnvisibleAction->setEnabled(false);
            this->addGroupAction->setEnabled(true);
            this->deleteNodeAction->setEnabled(true);
            this->copyNodeAction->setEnabled(false);
            return;
        } else if (type == "Item") {
            this->addLayerAction->setEnabled(false);
            this->setLayerVisibleAction->setEnabled(false);
            this->setLayerUnvisibleAction->setEnabled(false);
            this->addGroupAction->setEnabled(true);
            this->deleteNodeAction->setEnabled(true);
            this->copyNodeAction->setEnabled(true);
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
void MainWindow::on_drawTestLineButton_clicked() {
    qDebug() << "";
    qDebug() << "------test------";
    ///
    /// test template
    ///
    // /*
    QList < QGraphicsItem * > selectedItems = SceneManager::getIns().scene->selectedItems();
    if (selectedItems.empty()) {
        return;
    }
    for (auto it = selectedItems.cbegin(); it != selectedItems.cend(); ++it) {
        QGraphicsItem* graphicsItem = *it;
        ArcItem* arcPtr = dynamic_cast < ArcItem * > (graphicsItem);
        auto arc = arcPtr->copy();
        SceneManager::getIns().scene->addItem(arc.get());
        Manager::getIns().addItem(arc);
    }
    // */
    ///
    /// test template
    ///
    // /*
    // std::shared_ptr<ArcItem> item = std::make_shared<ArcItem>();
    // Manager::getIns().addItem(item);
    // auto item1 = item->copy();
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









