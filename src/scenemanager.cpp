#include "scenemanager.h"
#include "logger.h"
#include "uimanager.h"
#include "treemodel.h"
#include "manager.h"
#include <QScrollBar>

SceneManager SceneManager::ins;

SceneManager &SceneManager::getIns()
{
    return ins;
}

std::pair<double, double> SceneManager::getSceneScale()
{
    return this->sceneScale;
}

void SceneManager::setCurrentLayer(int layer){
    this->currentLayer = layer;

    TreeModel *model = qobject_cast<TreeModel *>(UiManager::getIns().UI()->treeView->model());
    model->update();

    auto inLayerItems = Manager::getIns().getItemsByLayer(this->currentLayer);
    auto allItems = Manager::getIns().getItemsByLayer(0);
    for (const auto& item : allItems) {
        Manager::getIns().setItemSelectable(item,false);
        Manager::getIns().setItemMovable(item,false);
        Manager::getIns().setItemRenderPen(item,DISPLAY_PEN);
    }
    for (const auto& item : inLayerItems) {
        Manager::getIns().setItemSelectable(item,true);
        Manager::getIns().setItemMovable(item,true);
    }
}

int SceneManager::getCurrentLayer(){
    return currentLayer;
}

int SceneManager::layerCount(){
    TreeModel *model = qobject_cast<TreeModel *>(UiManager::getIns().UI()->treeView->model());
    auto layerCount = model->rowCount(QModelIndex());

    return layerCount;
}

void SceneManager::dragScene(QPointF pointCoordView, MouseEvent event)
{
    if (event == MouseEvent::LeftPress) {
        this->dragScenePoint = pointCoordView;
    }
    else if (event == MouseEvent::MouseMove) {
        QPointF oldP  = this->dragScenePoint;
        QPointF newP = pointCoordView;
        QPointF translation = newP - oldP;
        // DEBUG_VAR(translation);
        translation.setX(translation.x() / SceneManager::getIns().getSceneScale().first);
        translation.setY(translation.y() / SceneManager::getIns().getSceneScale().second);

        UiManager::getIns().UI()->graphicsView->translate(translation.x(), translation.y());

        this->dragScenePoint = pointCoordView;
    }
    else if (event == MouseEvent::LeftRelease) {

    }
}

void SceneManager::setSceneScale(double x, double y)
{
    if (x <=0 || y<=0)
    {
        WARN_MSG("worng scene scale");
        return;
    }

    UiManager::getIns().UI()->graphicsView->scale(x,y);
    this->sceneScale.first *= x;
    this->sceneScale.second *= y;
}
