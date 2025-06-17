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
#include <QFileDialog>
#include <QMessageBox>
#include <QStatusBar>
#include <QThread>
#include <QToolButton>
#include "drawcontroller.h"
#include "editcontroller.h"
#include "keyboardmanager.h"
#include "laserworker.h"
#include "itemmanager.h"
#include "projectmanager.h"
#include "scenecontroller.h"
#include "treemodel.h"
#include "uimanager.h"
#include <polyline.hpp>
#include <QInputDialog>
#include "hardwarecontroller.h"

void MainWindow::onDrawTestLineButtonClicked() {

}

///
/// \brief MainWindow::MainWindow
///
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    QWidget *container = new QWidget(this);
    UiManager::getIns().initLayout(container);
    this->setCentralWidget(container);
    //
    initGraphicsView();
    initTreeViewModel();
    initTabWidget();
    //
    initProjectButton();
    initDrawToolButton();
    initEditToolButton();
    initLayerButton();
    initSignalButton();
    //
    initTitleBar();
    initStatusBar();
}

MainWindow::~MainWindow() {
    // 不用delete,由unique ptr管理内存
    // delete UiManager::getIns().UI();
}

void MainWindow::initGraphicsView() {
    //
    ProjectManager::getIns().newGraphicsView();
    auto *view = UiManager::getIns().graphicsView;
    // 设置整个view的正方向是右上
    QTransform transform;
    transform.scale(6, -6);
    view->setTransform(transform);
    // 连接组件信号
    connect(view,
            SIGNAL(mouseMoved(QPoint)),
            this,
            SLOT(onGraphicsviewMouseMoved(QPoint)));
    connect(view, SIGNAL(mouseLeftPressed(QPoint)),
            this, SLOT(onGraphicsviewMouseLeftPressed(QPoint)));
    connect(view, SIGNAL(mouseRightPressed(QPoint)),
            this, SLOT(onGraphicsviewMouseRightPressed(QPoint)));
    connect(view, SIGNAL(mouseLeftReleased(QPoint)),
            this, SLOT(onGraphicsviewMouseLeftReleased(QPoint)));
    connect(view, SIGNAL(mouseRightReleased(QPoint)),
            this, SLOT(onGraphicsviewMouseRightReleased(QPoint)));
    connect(view, SIGNAL(mouseDoubleClicked(QPoint)),
            this, SLOT(onGraphicsviewMouseRightDoubleClicked(QPoint)));
    connect(view, SIGNAL(mouseWheelTriggered(QWheelEvent*)),
            this, SLOT(onGraphicsviewMouseWheelTriggered(QWheelEvent*)));
}

void MainWindow::initTreeViewModel() {
    ProjectManager::getIns().newTreeViewModel();
    auto *view = UiManager::getIns(). treeView;
    //  contextmenu
    view->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(view,
            &QWidget::customContextMenuRequested,
            this,
            &MainWindow::onTreeViewModelShowContextMenu);
    //
    connect(view, &QTreeView::clicked, this, [ = ](const QModelIndex & index) {
        EditController::getIns().onTreeViewModelClicked(index);
    });
    //
    connect(view->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
    [ = ](const QItemSelection & selected, const QItemSelection & deselected) {
        EditController::getIns().onTreeViewModelSelectionChanged(selected, deselected);
    });
}

void MainWindow::initTabWidget() {
    //编辑tab
    auto *editTabWidget = UiManager::getIns().editTabWidget;
    connect(editTabWidget->tabBar(), &QTabBar::tabBarClicked, this, [=](int index) {
        EditController::getIns().setTabIndex(index);
    });
}

void MainWindow::initDrawToolButton() {
    QToolButton *drawPolylineButton = UiManager::getIns(). drawPolylineButton;
    connect(drawPolylineButton, &QToolButton::clicked, this, &MainWindow::onDrawPolylineButtonClicked);
    //
    QToolButton *drawLineButton = UiManager::getIns(). drawLineButton;
    connect(drawLineButton, &QToolButton::clicked, this, &MainWindow::onDrawLineButtonClicked);
    //
    QToolButton *drawArcButton = UiManager::getIns(). drawArcButton;
    connect(drawArcButton, &QToolButton::clicked, this, &MainWindow::onDrawArcButtonClicked);
    //
    QToolButton *drawPointButton = UiManager::getIns(). drawPointButton;
    connect(drawPointButton, &QToolButton::clicked, this, &MainWindow::onDrawPointButtonClicked);
    //
    QToolButton *drawCircleButton = UiManager::getIns(). drawCircleButton;
    connect(drawCircleButton, &QToolButton::clicked, this, &MainWindow::onDrawCircleButtonClicked);
    //
    QToolButton *drawEllipseButton = UiManager::getIns(). drawEllipseButton;
    connect(drawEllipseButton, &QToolButton::clicked, this, &MainWindow::onDrawEllipseButtonClicked);
    //
    QToolButton *drawRectButton = UiManager::getIns(). drawRectButton;
    connect(drawRectButton, &QToolButton::clicked, this, &MainWindow::onDrawRectButtonClicked);
    //
    QToolButton *drawPolygonButton = UiManager::getIns(). drawPolygonButton;
    connect(drawPolygonButton, &QToolButton::clicked, this, &MainWindow::onDrawPolygonButtonClicked);
    //
    QToolButton *drawSpiralButton = UiManager::getIns(). drawSpiralButton;
    connect(drawSpiralButton, &QToolButton::clicked, this, &MainWindow::onDrawSpiralButtonClicked);
}

void MainWindow::initEditToolButton() {
    QToolButton *editButton = UiManager::getIns(). editButton;
    connect(editButton, &QToolButton::clicked, this, &MainWindow::onEditButtonClicked);
    //
    QToolButton *dragSceneButton = UiManager::getIns(). dragSceneButton;
    connect(dragSceneButton, &QToolButton::clicked, this, &MainWindow::onDragSceneButtonClicked);
    //
    QToolButton *deleteButton = UiManager::getIns(). deleteButton;
    connect(deleteButton, &QToolButton::clicked, this, &MainWindow::onDeleteButtonClicked);
    //
    QToolButton *drawTestLineButton = UiManager::getIns(). drawTestLineButton;
    connect(drawTestLineButton, &QToolButton::clicked, this, &MainWindow::onDrawTestLineButtonClicked);
    //
    QToolButton *centerButton = UiManager::getIns(). centerButton;
    connect(centerButton, &QToolButton::clicked, this, &MainWindow::onCenterButtonClicked);
    //
    // QToolButton *redoButton = UiManager::getIns(). redoButton;
    // connect(redoButton, &QToolButton::clicked, this, &MainWindow::onRedoButtonClicked);
    //
    // QToolButton *undoButton = UiManager::getIns(). undoButton;
    // connect(undoButton, &QToolButton::clicked, this, &MainWindow::onUndoButtonClicked);
    //
    QToolButton *breakCopiedItemButton = UiManager::getIns(). breakCopiedItemButton;
    connect(breakCopiedItemButton, &QToolButton::clicked,
            this, &MainWindow::onBreakCopiedItemButtonClicked);
    //
    QToolButton *breakContourFillItemButton = UiManager::getIns(). breakContourFillItemButton;
    connect(breakContourFillItemButton, &QToolButton::clicked,
            this, &MainWindow::onBreakContourFillItemButtonClicked);
    //
    QToolButton *breakHatchFillItemButton = UiManager::getIns(). breakHatchFillItemButton;
    connect(breakHatchFillItemButton, &QToolButton::clicked,
            this, &MainWindow::onBreakHatchFillItemButtonClicked);
    /// 粘贴 复制 剪切
    ///
    ///
    QToolButton *cutButton = UiManager::getIns(). cutButton;
    connect(cutButton, &QToolButton::clicked,
            this, &MainWindow::onCutButtonClicked);
    //
    QToolButton *copyButton = UiManager::getIns(). copyButton;
    connect(copyButton, &QToolButton::clicked,
            this, &MainWindow::onCopyButtonClicked);
    //
    QToolButton *pasteButton = UiManager::getIns(). pasteButton;
    connect(pasteButton, &QToolButton::clicked,
            this, &MainWindow::onPasteButtonClicked);
    //
    QToolButton *combineButton = UiManager::getIns().combineButton;
    connect(combineButton, &QToolButton::clicked, this, &MainWindow::onCombineButtonClicked);
    //
    QToolButton *breakButton = UiManager::getIns().breakButton;
    connect(breakButton, &QToolButton::clicked, this, &MainWindow::onBreakButtonClicked);
    //
    //
    QToolButton *mirrorHorizontalButton = UiManager::getIns(). mirrorHorizontalButton;
    connect(mirrorHorizontalButton, &QToolButton::clicked,
            this, &MainWindow::onMirrorHorizontalButtonClicked);
    //
    QToolButton *mirrorVerticalButton = UiManager::getIns(). mirrorVerticalButton;
    connect(mirrorVerticalButton, &QToolButton::clicked,
            this, &MainWindow::onMirrorVerticalButtonClicked);
}

void MainWindow::initLayerButton() {
    QToolButton *addLayerButton = UiManager::getIns(). addLayerButton;
    connect(addLayerButton, &QToolButton::clicked,
            this, &MainWindow::onAddLayerButtonClicked);
    //
    QToolButton *deleteLayerButton = UiManager::getIns(). deleteLayerButton;
    connect(deleteLayerButton, &QToolButton::clicked,
            this, &MainWindow::onDeleteLayerButtonClicked);
    //
    // QToolButton *setLayerColorButton = UiManager::getIns(). setLayerColorButton;
    // connect(breakContourFillItemButton, &QToolButton::clicked,
    //         this, &MainWindow::onBreakContourFillItemButtonClicked);
    //
}

void MainWindow::initSignalButton() {
    QToolButton *digitalInButton = UiManager::getIns(). digitalInButton;
    connect(digitalInButton,
            &QToolButton::clicked,
            this,
            &MainWindow::onDigitalInButtonClicked);
    //
    QToolButton *digitalOutButton = UiManager::getIns(). digitalOutButton;
    connect(digitalOutButton,
            &QToolButton::clicked,
            this,
            &MainWindow::onDigitalOutButtonClicked);
    //
    QToolButton *doPauseButton = UiManager::getIns(). doPauseButton;
    connect(doPauseButton,
            &QToolButton::clicked,
            this,
            &MainWindow::onDoPauseButtonClicked);
    //
    QToolButton *delayTimeButton = UiManager::getIns(). delayTimeButton;
    connect(delayTimeButton,
            &QToolButton::clicked,
            this,
            &MainWindow::onDelayTimeButtonClicked);
    //
    QToolButton *motionButton = UiManager::getIns(). motionButton;
    connect(motionButton,
            &QToolButton::clicked,
            this,
            &MainWindow::onMotionButtonClicked);
    //
    QToolButton *loopButton = UiManager::getIns(). loopButton;
    connect(loopButton,
            &QToolButton::clicked,
            this,
            &MainWindow::onLoopButtonClicked);
}

void MainWindow::initProjectButton() {
    QToolButton *createProjectButton = UiManager::getIns(). createProjectButton;
    connect(createProjectButton,
            &QToolButton::clicked,
            this,
            &MainWindow::onCreateProjectButtonClicked);
    //
    //
    QToolButton *openProjectButton = UiManager::getIns(). openProjectButton;
    connect(openProjectButton, &QToolButton::clicked, this, &MainWindow::onOpenProjectButtonClicked);
    //
    //
    QToolButton *saveProjectButton = UiManager::getIns(). saveProjectButton;
    connect(saveProjectButton, &QToolButton::clicked, this, &MainWindow::onSaveProjectButtonClicked);
}

void MainWindow::initStatusBar() {
    this->labelMouseCoordinate = new QLabel("coordinate: ");
    this->labelMouseCoordinate->setMinimumWidth(150);
    // UiManager::getIns(). statusBar->addWidget(this->labelMouseCoordinate);
}

void MainWindow::initTableViewModel() {
    // auto *model = new TableModel(this);
    // UiManager::getIns(). tableView->setModel(model);
    // UiManager::getIns(). tableView->verticalHeader()->setVisible(false);
    // UiManager::getIns(). tableView->setAlternatingRowColors(true);
    // UiManager::getIns(). tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    // UiManager::getIns(). tableView->setColumnWidth(0, 190);
    // UiManager::getIns(). tableView->setColumnWidth(1, 190);
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
    SceneController::getIns().setSceneToCenter();
}

///
/// \brief MainWindow::on_graphicsview_mouse_move_triggered
///
void MainWindow::onGraphicsviewMouseMoved(QPoint pointCoordView) {
    QPointF pointCoordscene = UiManager::getIns(). graphicsView->mapToScene(pointCoordView);
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
    //     auto allItems = ItemManager::getIns().getItemsByLayer(0);
    //     SceneController::getIns().scene->clearSelection();
    //     // 打断一下拖拽过程
    //     for (const auto& item : allItems) {
    //         ItemManager::getIns().etItemMovable(item, false);
    //         QTimer::singleShot(10, this, [item]() {
    //             ItemManager::getIns().etItemMovable(item, false);
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
    QPointF pointCoordscene = UiManager::getIns(). graphicsView->mapToScene(pointCoordView);
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
    QPointF pointCoordscene = UiManager::getIns(). graphicsView->mapToScene(pointCoordView);
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
    QPointF pointCoordscene = UiManager::getIns(). graphicsView->mapToScene(pointCoordView);
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
    QPointF pointCoordscene = UiManager::getIns(). graphicsView->mapToScene(pointCoordView);
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
    UiManager::getIns(). editButton->setChecked(true);
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
    UiManager::getIns(). graphicsView->viewport()->setCursor(Qt::CrossCursor);
    DrawController::getIns().resetTmpItemStatus();
    UiManager::getIns(). graphicsView->setDragMode(QGraphicsView::NoDrag);
    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
}

void MainWindow::onDrawLineButtonClicked() {
    setDrawMode();
    UiManager::getIns(). drawLineButton->setChecked(true);
    SceneController::getIns().m_currentOperationEvent = OperationEvent::DrawLine;
}

void MainWindow::onDrawCircleButtonClicked() {
    setDrawMode();
    UiManager::getIns(). drawCircleButton->setChecked(true);
    SceneController::getIns().m_currentOperationEvent = OperationEvent::DrawCircle;
}

void MainWindow::onDrawPolylineButtonClicked() {
    setDrawMode();
    UiManager::getIns(). drawPolylineButton->setChecked(true);
    SceneController::getIns().m_currentOperationEvent = OperationEvent::DrawPolyline;
}

void MainWindow::onDrawArcButtonClicked() {
    setDrawMode();
    UiManager::getIns(). drawArcButton->setChecked(true);
    SceneController::getIns().m_currentOperationEvent = OperationEvent::DrawArc;
}

void MainWindow::onDrawPointButtonClicked() {
    setDrawMode();
    UiManager::getIns(). drawPointButton->setChecked(true);
    SceneController::getIns().m_currentOperationEvent = OperationEvent::DrawPoint;
}

void MainWindow::onDrawSpiralButtonClicked() {
    setDrawMode();
    UiManager::getIns(). drawSpiralButton->setChecked(true);
    SceneController::getIns().m_currentOperationEvent = OperationEvent::DrawSpiral;
}

void MainWindow::onDrawRectButtonClicked() {
    setDrawMode();
    UiManager::getIns(). drawRectButton->setChecked(true);
    SceneController::getIns().m_currentOperationEvent = OperationEvent::DrawRect;
}

void MainWindow::onDrawPolygonButtonClicked() {
    setDrawMode();
    UiManager::getIns(). drawPolygonButton->setChecked(true);
    SceneController::getIns().m_currentOperationEvent = OperationEvent::DrawPolygon;
}

void MainWindow::onDrawEllipseButtonClicked() {
    setDrawMode();
    UiManager::getIns(). drawEllipseButton->setChecked(true);
    SceneController::getIns().m_currentOperationEvent = OperationEvent::DrawEllipse;
}

///
/// \brief MainWindow::onDragSceneButtonClicked
///
void MainWindow::onDragSceneButtonClicked() {
    // 设置鼠标光标
    UiManager::getIns(). graphicsView->viewport()->setCursor(Qt::OpenHandCursor);
    // tool status
    SceneController::getIns().m_currentOperationEvent = OperationEvent::DragScene;
    DrawController::getIns().resetTmpItemStatus();
    // drag mode/所有物体设置不可动
    UiManager::getIns(). graphicsView->setDragMode(QGraphicsView::NoDrag);
    auto allItems = ItemManager::getIns().getChildItems("0-0-0-0");
    for (auto item : allItems) {
        ItemManager::getIns().setItemSelectable(item, false);
    }
    //button check
    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns(). dragSceneButton->setChecked(true);
}

///
/// \brief MainWindow::onEditButtonClicked
///
void MainWindow::onEditButtonClicked() {
    // 设置鼠标光标
    UiManager::getIns(). graphicsView->viewport()->setCursor(Qt::ArrowCursor);
    // tool status
    SceneController::getIns().m_currentOperationEvent = OperationEvent::EditProperty;
    DrawController::getIns().resetTmpItemStatus();
    // drag mode
    UiManager::getIns(). graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    // button check
    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns(). editButton->setChecked(true);
    // 设置当前图层内物体可动;所有物体颜色为黑;等等默认行为(都在setCurrentLayer里)
    SceneController::getIns().setCurrentLayer(SceneController::getIns().getCurrentLayer());
}

void MainWindow::setEditMode() {
    // 设置鼠标光标
    UiManager::getIns(). graphicsView->viewport()->setCursor(Qt::ArrowCursor);
    // tool status
    SceneController::getIns().m_currentOperationEvent = OperationEvent::EditProperty;
    DrawController::getIns().resetTmpItemStatus();
    // drag mode
    UiManager::getIns(). graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    // button check
    UiManager::getIns().setAllDrawButtonChecked(false);
    UiManager::getIns().setAllToolButtonChecked(false);
    UiManager::getIns(). editButton->setChecked(true);
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

void MainWindow::onBreakContourFillItemButtonClicked() {
    setEditMode();
    EditController::getIns().onBreakContourFillItemTriggered();
}
void MainWindow::onBreakHatchFillItemButtonClicked() {
    setEditMode();
    EditController::getIns().onBreakHatchFillItemTriggered();
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

void MainWindow::onCombineButtonClicked()
{
    setEditMode();
    EditController::getIns().onCombineItemsTriggered();
}

void MainWindow::onBreakButtonClicked()
{
    setEditMode();
    EditController::getIns().onBreakItemsTriggered();
}

void MainWindow::onDigitalInButtonClicked() {
    setEditMode();
    ItemManager::getIns().addItem("DigitalIn", "Signal");
}

void MainWindow::onDigitalOutButtonClicked() {
    setEditMode();
    ItemManager::getIns().addItem("DigitalOut", "Signal");
}

void MainWindow::onDoPauseButtonClicked() {
    setEditMode();
    ItemManager::getIns().addItem("DoPause", "Signal");
}

void MainWindow::onDelayTimeButtonClicked() {
    setEditMode();
    ItemManager::getIns().addItem("DelayTime", "Signal");
}

void MainWindow::onMotionButtonClicked() {
    setEditMode();
    ItemManager::getIns().addItem("Motion", "Signal");
}

void MainWindow::onLoopButtonClicked() {
    setEditMode();
    ItemManager::getIns().addItem("Loop", "Signal");
}


void MainWindow::onAddLayerButtonClicked() {
    SceneController::getIns().addLayer();
}

void MainWindow::onDeleteLayerButtonClicked() {
    SceneController::getIns().deleteCurrentLayer ();
}

void MainWindow::onCreateProjectButtonClicked() {
    ProjectManager::getIns().createProject();
}

void MainWindow::onOpenProjectButtonClicked() {
    QString path = QFileDialog::getOpenFileName(this,
                   tr("Open Project File"),
                   tr("../../tmp"),
                   tr("File Type (*.json);; (*)"));
    if (!path.isEmpty()) {
        DEBUG_MSG(path);
        ProjectManager::getIns().openProject(path);
    }
}

void MainWindow::onSaveProjectButtonClicked() {
    QString timeStr = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss");
    QString fileName = QString("laserCAD_%1.json").arg(timeStr);

    QString projectDirPath = "projectFile";
    QDir projectDir(projectDirPath);
    if (!projectDir.exists()) {
        if (!projectDir.mkpath(".")) {
            qWarning() << "Cannot create project directory:" << projectDirPath;
        }
    }

    QString defaultFullPath = projectDir.filePath(fileName);

    QString path = QFileDialog::getSaveFileName(
        this,
        tr("Save Project File"),
        defaultFullPath,
        tr("Project Files (*.json);;All Files (*)"));

    if (!path.isEmpty()) {
        if (!path.endsWith(".json", Qt::CaseInsensitive)) {
            path += ".json";
        }
        ProjectManager::getIns().saveProject(path);
    }
}


void MainWindow::onTreeViewModelShowContextMenu(const QPoint &pos) {
    // 获取鼠标点击的位置
    QModelIndex index = UiManager::getIns(). treeView->indexAt(pos);
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
    contextMenu.exec(UiManager::getIns(). treeView->viewport()->mapToGlobal(pos));
}

void MainWindow::onTreeViewModelUpdateActions() {
    TreeModel *model = qobject_cast < TreeModel * > (UiManager::getIns(). treeView->model());
    const auto nodeIndexList
        = UiManager::getIns(). treeView->selectionModel()->selectedIndexes();
    if (nodeIndexList.empty()) { // layer已经被限制无法选中, 所以右键直接是空选,也就是转到这里 不是下面
        this->addGroupAction->setEnabled(false);
        this->deleteGroupAction->setEnabled(false);
        this->selectAllItemsInGroupAction->setEnabled(false);
        return;
    }
    const auto nodeIndex = nodeIndexList[0];
    QString type = model->nodeProperty(nodeIndex, TreeNodePropertyIndex::Type).toString();
    if (type == "Layer") { // layer已经被限制无法选中
        // this->addGroupAction->setEnabled(false);
        // this->deleteGroupAction->setEnabled(false);
        // this->selectAllItemsInGroupAction->setEnabled(false);
        // return;
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
