#include "scenecontroller.h"
#include "logger.h"
#include "uimanager.h"
#include "treemodel.h"
#include "manager.h"
#include <QScrollBar>

SceneController SceneController::ins;

SceneController &SceneController::getIns() {
    return ins;
}

std::pair < double, double > SceneController::getSceneScale() {
    return this->m_sceneScale;
}

void SceneController::setCurrentLayer(UUID layerUuid) {
    TreeModel *model = qobject_cast < TreeModel * > (UiManager::getIns().UI()->treeView->model());
    auto uuids = Manager::getIns().getChildItems("0-0-0-0");
    for (const auto &uuid : uuids) {
        Manager::getIns().setItemSelectable(uuid, false);
        Manager::getIns().itemMapFind(uuid)->setPen(DISPLAY_PEN);
    }
    // 设置当前图层
    this->m_currentLayer = layerUuid;
    // 当前图层可选中
    auto layerNodeIndex = model->getIndex(layerUuid);
    auto inLayerItems = model->getAllChildNodes(layerNodeIndex);
    for (const auto &item : inLayerItems) {
        auto uuid = item->property(TreeNodePropertyIndex::UUID).toString();
        Manager::getIns().setItemSelectable(uuid, true);
    }
}

UUID SceneController::getCurrentLayer() {
    return m_currentLayer;
}

void SceneController::initLayerUuid(UUID uuid) {
    this->m_currentLayer = uuid;
    this->m_layerList.push_back(uuid);
}

int SceneController::layerCount() {
    return this->m_layerList.size ();
}

void SceneController::addLayer() {
    // 添加到treemodel里/manager里
    TreeModel *model = qobject_cast < TreeModel * > (UiManager::getIns().UI()->treeView->model());
    if (!model->insertRow(this->layerCount(), QModelIndex())) {
        FATAL_MSG("fail insert layer");
    }
    const QModelIndex layerNodeIndex = model->index(this->layerCount(), 0, QModelIndex());
    QString name = "Layer" + QString::number(this->layerCount() + 1);
    QString type = "Layer";
    auto uuid = Manager::getIns().addItem(layerNodeIndex, name, type);
    // 添加到sceneController里
    this->m_layerList.push_back(uuid);
}

void SceneController::deleteCurrentLayer() {
    // if (this->layerCount() == 1) {
    //     WARN_MSG("can not delete last layer");
    // }
    // // 删除到treemodel里/manager里
    // TreeModel *model = qobject_cast < TreeModel * > (UiManager::getIns().UI()->treeView->model());
    // auto layerIndex = model->getIndex(this->m_currentLayer);
    // model->removeRow(layerIndex.row(), layerIndex.parent());
    // // 删除sceneController里
    // this->m_layerList.erase(this->m_currentLayer);
    // this->m_currentLayer = this->m_layerList[0];
}

void SceneController::dragScene(QPointF pointCoordView, MouseEvent event) {
    if (event == MouseEvent::LeftPress) {
        // 设置鼠标光标
        UiManager::getIns().UI()->graphicsView->viewport()->setCursor(Qt::ClosedHandCursor);
        this->m_dragScenePoint = pointCoordView;
    } else if (event == MouseEvent::MouseMove) {
        QPointF oldP  = this->m_dragScenePoint;
        QPointF newP = pointCoordView;
        QPointF translation = newP - oldP;
        // DEBUG_VAR(translation);
        translation.setX(translation.x() / SceneController::getIns().getSceneScale().first);
        translation.setY(translation.y() / SceneController::getIns().getSceneScale().second);
        UiManager::getIns().UI()->graphicsView->translate(translation.x(), translation.y());
        this->m_dragScenePoint = pointCoordView;
    } else if (event == MouseEvent::LeftRelease) {
        // 设置鼠标光标
        UiManager::getIns().UI()->graphicsView->viewport()->setCursor(Qt::OpenHandCursor);
    }
}

void SceneController::setSceneScale(double x, double y) {
    if (x <= 0 || y <= 0) {
        WARN_MSG("worng scene scale");
        return;
    }
    UiManager::getIns().UI()->graphicsView->scale(x, y);
    this->m_sceneScale.first *= x;
    this->m_sceneScale.second *= y;
}
