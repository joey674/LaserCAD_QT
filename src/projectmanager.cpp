#include "projectmanager.h"
#include <QGraphicsScene>
#include <QTimer>
#include "colordelegate.h"
#include "css.h"
#include "drawcontroller.h"
#include "treemodel.h"
#include "uimanager.h"
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

const double AxisScale = 5;

ProjectManager ProjectManager::ins;

///
/// \brief ProjectManager::createProject
///
void ProjectManager::createProject() {
    // 先重置controller/manager
    resetDrawController();
    resetEditController();
    resetSceneController();
    resetManager();
    // 再重置view和model; 按照程序自身的启动生成顺序;
    // 因为在tree初始化的时候有调用manager
    newGraphicsView();
    newTreeViewModel();
}

///
/// \brief ProjectManager::openProject
///
std::shared_ptr < GraphicsItem > ProjectManager::createGraphicsItemFromJson(
    const QJsonObject &propertyObj) {
    QString type = propertyObj["type"].toString();
    std::shared_ptr < GraphicsItem > item;
    if (type == "ArcItem") {
        item = ArcItem().createFromJson(propertyObj);
    } else if (type == "CircleItem") {
        item = CircleItem().createFromJson(propertyObj);
    } else if (type == "EllipseItem") {
        item = EllipseItem().createFromJson(propertyObj);
    } else if (type == "LineItem") {
        item = LineItem().createFromJson(propertyObj);
    } else if (type == "PointItem") {
        item = PointItem().createFromJson(propertyObj);
    } else if (type == "PolygonItem") {
        item = PolygonItem().createFromJson(propertyObj);
    } else if (type == "PolylineItem") {
        item = PolylineItem().createFromJson(propertyObj);
    } else if (type == "RectItem") {
        item = RectItem().createFromJson(propertyObj);
    } else if (type == "SpiralItem") {
        item = SpiralItem().createFromJson(propertyObj);
    } else {
        WARN_MSG("new type need to define");
    }
    return item;
}
void ProjectManager::fillTreeNodeFromJson(TreeNode *node, const QJsonObject &obj) {
    // 设置当前节点属性
    node->setProperty(TreeNodePropertyIndex::Name, obj["name"].toString());
    node->setProperty(TreeNodePropertyIndex::Type, obj["type"].toString());
    // 设置item并创建item
    auto propertyObj = obj["property"].toObject();
    std::shared_ptr < GraphicsItem > item;
    if (obj["type"] == "Item") {
        item = createGraphicsItemFromJson(propertyObj);
    } else if (obj["type"] == "Layer") {
        SceneController::getIns().addLayer();
        UUID uuid = SceneController::getIns().getCurrentLayer();
        item = Manager::getIns().itemMapFind(uuid);
        item->setColor(QColor(propertyObj["color"].toString ()));// 设置图层颜色
    } else {
        item = std::make_shared < ArcItem > ();
    }
    node->setProperty(TreeNodePropertyIndex::UUID, item->getUUID()); // 设置节点uuid
    // 添加到 scene
    //
    if (obj["type"].toString() == "Item") {
        SceneController::getIns().scene->addItem(item.get());
    }
    // 注册到 Manager
    //
    Manager::getIns().addItem(item);
    // 添加到 tree
    //
    QJsonArray childrenArray = obj["children"].toArray(); // 获取子节点数组
    int childCount = childrenArray.size();
    if (childCount > 0) { // 插入默认子节点
        node->insertChilds(0, childCount); // 插入 childCount 个空子节点
        for (int i = 0; i < childCount; ++i) { // 递归设置子节点属性
            TreeNode *child = node->child(i);
            QJsonObject childObj = childrenArray.at(i).toObject();
            fillTreeNodeFromJson(child, childObj); // 递归设置
        }
    }
}

TreeNode *ProjectManager::deserializeTreeNode(const QJsonObject &obj) {
    TreeNode *node = new TreeNode();
    fillTreeNodeFromJson(node, obj);
    return node;
}

bool ProjectManager::openProject(const QString &filePath) {
    // 打开文件要重置一下内容
    this->resetSceneController();
    //
    auto treeView = UiManager::getIns(). treeView;
    TreeModel *model = qobject_cast < TreeModel * > (treeView->model());
    //
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        WARN_MSG("Failed to open file:" + filePath);
        return false;
    }
    QByteArray jsonData = file.readAll();
    file.close();
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        WARN_MSG("JSON parse error: " + parseError.errorString());
        return false;
    }
    QJsonObject rootObj = doc.object();
    if (!rootObj.contains("tree")) {
        WARN_MSG("Missing 'tree' field in JSON.");
        return false;
    }
    model->beginResetModel();
    TreeNode *newRoot = deserializeTreeNode(rootObj["tree"].toObject());
    newRoot->setProperty(TreeNodePropertyIndex::Name, rootObj["modelName"].toString());
    model->m_rootItem.reset(newRoot);
    model->endResetModel();
    INFO_MSG("Tree loaded from: " + filePath);
    // 打开项目后设置一下
    SceneController::getIns().setCurrentLayer(SceneController::getIns().getCurrentLayer());
    return true;
}

///
/// \brief ProjectManager::saveProject
///
QJsonObject ProjectManager::serializeTreeNode(TreeNode *node) {
    QJsonObject obj;
    obj["name"] = node->property(TreeNodePropertyIndex::Name).toString();
    obj["type"] = node->property(TreeNodePropertyIndex::Type).toString();
    auto uuid = node->property(TreeNodePropertyIndex::UUID).toString();
    DEBUG_MSG("uuid find use here");
    if (Manager::getIns().itemMapExist(uuid)) {
        auto item = Manager::getIns().itemMapFind(uuid);
        obj["property"] = item->saveToJson();
    }
    QJsonArray childrenArray;
    for (int i = 0; i < node->childCount(); ++i) {
        TreeNode *child = node->child(i);
        childrenArray.append(serializeTreeNode(child));
    }
    obj["children"] = childrenArray;
    return obj;
}

bool ProjectManager::saveProject(const QString &filePath) {
    auto treeView = UiManager::getIns(). treeView;
    TreeModel *model = qobject_cast < TreeModel * > (treeView->model());
    if (!model || !model->m_rootItem) {
        WARN_MSG("rootItem is null");
        return false;
    }
    QJsonObject rootObj;
    rootObj["modelName"] = model->m_rootItem->property(TreeNodePropertyIndex::Name).toString();
    rootObj["tree"] = serializeTreeNode(model->m_rootItem.get());
    QJsonDocument doc(rootObj);
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        WARN_MSG("Failed to open file:" + filePath);
        return false;
    }
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
    INFO_MSG("Project saved to: " + filePath);
    return true;
}

///
/// \brief ProjectManager::resetSceneController
///
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
    UiManager::getIns(). graphicsView->scale(1 / sceneController.m_sceneScale.first,
            1 / sceneController.m_sceneScale.second);
    sceneController.m_sceneScale = {1, 1};
}

void ProjectManager::resetDrawController() {
    auto &drawController = DrawController::getIns();
    drawController.resetTmpItemStatus();
}

void ProjectManager::resetEditController()
{
    EditController::getIns().m_currentEditItemGroup.clear();
    EditController::getIns().m_editRect = nullptr;
    EditController::getIns().m_currentCutCopyItemGroup.clear();
}

void ProjectManager::resetManager() {
    auto &manager = Manager::getIns();
    manager.m_itemMap.clear();
    manager.m_deletedItemList.clear();
}

void ProjectManager::newGraphicsView() {
    SceneController::getIns().scene = new QGraphicsScene();
    UiManager::getIns(). graphicsView->setScene(SceneController::getIns().scene);
    UiManager::getIns(). graphicsView->setRenderHint(QPainter::Antialiasing, true); //设置抗锯齿
    UiManager::getIns(). graphicsView->setRenderHint(QPainter::SmoothPixmapTransform, true);
    UiManager::getIns(). graphicsView->setViewportUpdateMode(
        QGraphicsView::SmartViewportUpdate);
    UiManager::getIns().graphicsView->setTransformationAnchor(
        /* QGraphicsView::NoAnchor*/ //但是当要用transform的时候好像得设置NoAnchor
        QGraphicsView::AnchorUnderMouse
        /*QGraphicsView::AnchorViewCenter*/); // 设置当缩放scene的时候,以什么为中心(无/鼠标位置/view中心);
    UiManager::getIns().graphicsView->setResizeAnchor(
        /*QGraphicsView::NoAnchor*/
        QGraphicsView::AnchorViewCenter); // 设置当窗口变化时(view也同时变化),view对应的scene中心
    // UiManager::getIns(). graphicsView->setSizeAdjustPolicy(
    //     QAbstractScrollArea::AdjustIgnored); // 设置画面缩放时不调整view大小
    UiManager::getIns(). graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    UiManager::getIns(). graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    UiManager::getIns(). graphicsView->setDragMode(QGraphicsView::NoDrag); // 设置初始为没有选框
    UiManager::getIns(). graphicsView->viewport()->setCursor(Qt::ArrowCursor);
    //
    UiManager::getIns().graphicsView->setMouseTracking(true);
    // 在窗口缩放时对准坐标中心
    SceneController::getIns().setSceneToCenter();
    // 绘制坐标轴
    QPen pen = []() {
        QPen pen(Qt::red, 1);
        pen.setCosmetic(true);
        return pen;
    }();
    QGraphicsLineItem *xAxis = new QGraphicsLineItem(-10*AxisScale, 0, 10*AxisScale, 0);
    QGraphicsLineItem *yAxis = new QGraphicsLineItem(0, -10*AxisScale, 0, 10*AxisScale);
    xAxis->setPen(pen);
    xAxis->setPos(0, 0);
    yAxis->setPen(pen);
    yAxis->setPos(0, 0);
    SceneController::getIns().scene->addItem(xAxis);
    SceneController::getIns().scene->addItem(yAxis);
    QGraphicsLineItem *xArrowL = new QGraphicsLineItem(9*AxisScale, 1*AxisScale, 10*AxisScale, 0);
    QGraphicsLineItem *xArrowR = new QGraphicsLineItem(9*AxisScale, -1*AxisScale, 10*AxisScale, 0);
    xArrowL->setPen(pen);
    xArrowR->setPen(pen);
    SceneController::getIns().scene->addItem(xArrowL);
    SceneController::getIns().scene->addItem(xArrowR);
    QGraphicsLineItem *yArrowL = new QGraphicsLineItem(1*AxisScale, 9*AxisScale, 0, 10*AxisScale);
    QGraphicsLineItem *yArrowR = new QGraphicsLineItem(-1*AxisScale, 9*AxisScale, 0, 10*AxisScale);
    yArrowL->setPen(pen);
    yArrowR->setPen(pen);
    SceneController::getIns().scene->addItem(yArrowL);
    SceneController::getIns().scene->addItem(yArrowR);
    QGraphicsLineItem *bound1 = new QGraphicsLineItem(90 * AxisScale,
        90 * AxisScale,
        100 * AxisScale,
        100 * AxisScale);
    QGraphicsLineItem *bound2 = new QGraphicsLineItem(-100 * AxisScale,
        -100 * AxisScale,
        -90 * AxisScale,
        -90 * AxisScale);
    QGraphicsLineItem *bound3 = new QGraphicsLineItem(-90 * AxisScale,
        90 * AxisScale,
        -100 * AxisScale,
        100 * AxisScale);
    QGraphicsLineItem *bound4 = new QGraphicsLineItem(100 * AxisScale,
        -100 * AxisScale,
        90 * AxisScale,
        -90 * AxisScale);
    bound1->setPen(pen);
    bound2->setPen(pen);
    bound3->setPen(pen);
    bound4->setPen(pen);
    SceneController::getIns().scene->addItem(bound1);
    SceneController::getIns().scene->addItem(bound2);
    SceneController::getIns().scene->addItem(bound3);
    SceneController::getIns().scene->addItem(bound4);

    // 缩放到合适的位置
    SceneController::getIns().setSceneScale(6, 6);
}

void ProjectManager::newTreeViewModel() {
    /// \brief model 初始化
    auto *model = new TreeModel("Items Browser");
    auto *view = UiManager::getIns(). treeView;
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

///
/// \brief ProjectManager::getIns
///
ProjectManager &ProjectManager::getIns() {
    return ins;
}
