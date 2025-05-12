#include "projectmanager.h"
#include <QGraphicsScene>
#include <QTimer>
#include "colordelegate.h"
#include "css.h"
#include "drawcontroller.h"
#include "treemodel.h"
#include "uimanager.h"

ProjectManager ProjectManager::ins;

void ProjectManager::createProject() {
    // 先重置controller/manager
    resetDrawController();
    resetSceneController();
    resetManager();
    // 再重置view和model; 按照程序自身的启动生成顺序;
    // 因为在tree初始化的时候有调用manager
    newGraphicsView();
    newTreeViewModel();
}

void ProjectManager::resetSceneController() {
    auto &sceneController = SceneController::getIns();
    //
    sceneController.m_currentOperationEvent = None;
    //
    sceneController.m_currentLayer = "UndefinedLayerUUID";
    sceneController.m_layerCreatedCount = 1;
    sceneController.m_newLayerExamplarColor = 1;
    sceneController.m_layerList.clear();
    //
    sceneController.m_dragScenePoint = QPointF(0, 0);
    // view是不删的 要重置一下
    UiManager::getIns().UI()->graphicsView->scale(1 / sceneController.m_sceneScale.first,
            1 / sceneController.m_sceneScale.second);
    sceneController.m_sceneScale = {1, 1};
}

void ProjectManager::resetDrawController() {
    auto &drawController = DrawController::getIns();
    drawController.resetTmpItemStatus();
}

void ProjectManager::resetManager() {
    auto &manager = Manager::getIns();
    manager.m_itemMap.clear();
    manager.m_deletedItemList.clear();
}

void ProjectManager::newGraphicsView() {
    SceneController::getIns().scene = new QGraphicsScene();
    UiManager::getIns().UI()->graphicsView->setScene(SceneController::getIns().scene);
    UiManager::getIns().UI()->graphicsView->setRenderHint(QPainter::Antialiasing, true); //设置抗锯齿
    UiManager::getIns().UI()->graphicsView->setRenderHint(QPainter::SmoothPixmapTransform, true);
    UiManager::getIns().UI()->graphicsView->setViewportUpdateMode(
        QGraphicsView::SmartViewportUpdate);
    UiManager::getIns().UI()->graphicsView->setTransformationAnchor(QGraphicsView::NoAnchor);
    UiManager::getIns().UI()->graphicsView->setResizeAnchor(QGraphicsView::NoAnchor);
    UiManager::getIns().UI()->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    UiManager::getIns().UI()->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    UiManager::getIns().UI()->graphicsView->setSizeAdjustPolicy(
        QAbstractScrollArea::AdjustIgnored); // 设置画面缩放时不调整view大小
    UiManager::getIns().UI()->graphicsView->setDragMode(QGraphicsView::NoDrag); // 设置初始为没有选框
    UiManager::getIns().UI()->graphicsView->viewport()->setCursor(Qt::ArrowCursor);
    SceneController::getIns().setSceneScale(0.1, 0.1);
    QTimer::singleShot(100, []() {
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
}

void ProjectManager::newTreeViewModel() {
    /// \brief model 初始化
    auto *model = new TreeModel("Items Browser");
    auto *view = UiManager::getIns().UI()->treeView;
    view->setModel(model);
    model->setupDefaultModelData();
    view->bindModel();
    //
    view->setStyleSheet(treeViewModelStyle1);
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
    /// 设置自定义颜色编辑器
    view->setItemDelegateForColumn(3, new ColorDelegate(view));
    view->setEditTriggers(QAbstractItemView::AllEditTriggers); // 单机弹出颜色框
}

ProjectManager &ProjectManager::getIns() {
    return ins;
}
