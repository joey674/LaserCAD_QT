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
    // 设置所有物体不可选中;
    TreeModel *model = qobject_cast < TreeModel * > (UiManager::getIns().UI()->treeView->model());
    auto uuids = Manager::getIns().getChildItems("0-0-0-0");
    for (const auto &uuid : uuids) {
        Manager::getIns().setItemSelectable(uuid, false);
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
    QString name = "Layer" + QString::number(this->m_layerCreatedCount + 1);
    QString type = "Layer";
    auto uuid = Manager::getIns().addItem( name, type, layerNodeIndex);
    // 添加到sceneController里
    this->m_layerList.push_back(uuid);
    // 统计总共创建过几个layer
    this->m_layerCreatedCount ++;
    // 设置工作图层为新加的图层
    this->setCurrentLayer(uuid);
    // 设置图层颜色
    QColor selectedColor = kLayerColors[this->m_newLayerExamplarColor];
    Manager::getIns().itemMapFind(uuid)->setColor(selectedColor);
    this->m_newLayerExamplarColor = (this->m_newLayerExamplarColor + 1) % kLayerColors.size();
}

void SceneController::deleteCurrentLayer() {
    if (this->layerCount() == 1) {
        WARN_MSG("can not delete last layer");
        return;
    }
    // 删除treemodel里/manager里
    TreeModel *model = qobject_cast < TreeModel * > (UiManager::getIns().UI()->treeView->model());
    auto layerIndex = model->getIndex(this->m_currentLayer);
    Manager::getIns().deleteItem(this->getCurrentLayer());
    // 删除sceneController里
    auto it = std::find(this->m_layerList.begin(), this->m_layerList.end(), this->m_currentLayer);
    if (it != this->m_layerList.end()) {
        this->m_layerList.erase(it);
    }
    this->m_currentLayer = this->m_layerList[0];
}

QColor SceneController::getCurrentLayerColor() const {
    auto uuid = this->m_currentLayer;
    auto color = Manager::getIns().itemMapFind(uuid)->getColor();
    return color;
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
