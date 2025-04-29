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

void SceneController::setCurrentLayer(int layer) {
    //
    this->currentLayer = layer;
    //
    TreeModel *model = qobject_cast < TreeModel * > (UiManager::getIns().UI()->treeView->model());
    model->update();
    auto inLayerItems = Manager::getIns().getItemsByLayer(this->currentLayer);
    auto allItems = Manager::getIns().getItemsByLayer(0);
    for (const auto& item : allItems) {
        Manager::getIns().setItemSelectable(item, false);
        Manager::getIns().itemMapFind(item)->setPen(DISPLAY_PEN);
    }
    for (const auto& item : inLayerItems) {
        Manager::getIns().setItemSelectable(item, true);
    }
}

int SceneController::getCurrentLayer() {
    return currentLayer;
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
