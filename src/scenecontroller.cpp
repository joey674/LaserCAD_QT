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
    return this->sceneScale;
}

void SceneController::setCurrentLayerUuid(UUID layerUuid) {
    TreeModel *model = qobject_cast < TreeModel * > (UiManager::getIns().UI()->treeView->model());
    auto uuids = Manager::getIns().getChildItems("0-0-0-0");
    for (const auto &uuid : uuids) {
        Manager::getIns().setItemSelectable(uuid, false);
        Manager::getIns().itemMapFind(uuid)->setPen(DISPLAY_PEN);
    }
    // 设置当前图层
    this->currentLayerUuid = layerUuid;
    // 当前图层可选中
    auto layerNodeIndex = model->getIndex(layerUuid);
    auto inLayerItems = model->getAllChildNodes(layerNodeIndex);
    for (const auto &item : inLayerItems) {
        auto uuid = item->property(TreeNodePropertyIndex::UUID).toString();
        Manager::getIns().setItemSelectable(uuid, true);
    }
}

UUID SceneController::getCurrentLayerUuid() {
    return currentLayerUuid;
}

int SceneController::layerCount() {
    TreeModel *model = qobject_cast < TreeModel * > (UiManager::getIns().UI()->treeView->model());
    auto layerCount = model->rowCount(QModelIndex());
    return layerCount;
}

void SceneController::dragScene(QPointF pointCoordView, MouseEvent event) {
    if (event == MouseEvent::LeftPress) {
        // 设置鼠标光标
        UiManager::getIns().UI()->graphicsView->viewport()->setCursor(Qt::ClosedHandCursor);
        this->dragScenePoint = pointCoordView;
    } else if (event == MouseEvent::MouseMove) {
        QPointF oldP  = this->dragScenePoint;
        QPointF newP = pointCoordView;
        QPointF translation = newP - oldP;
        // DEBUG_VAR(translation);
        translation.setX(translation.x() / SceneController::getIns().getSceneScale().first);
        translation.setY(translation.y() / SceneController::getIns().getSceneScale().second);
        UiManager::getIns().UI()->graphicsView->translate(translation.x(), translation.y());
        this->dragScenePoint = pointCoordView;
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
    this->sceneScale.first *= x;
    this->sceneScale.second *= y;
}
