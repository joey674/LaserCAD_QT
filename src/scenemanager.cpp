#include "scenemanager.h"
#include "logger.h"
#include "uimanager.h"
#include "treemodel.h"

SceneManager SceneManager::ins;

SceneManager &SceneManager::getIns()
{
    return ins;
}

///
/// \brief SceneManager::getSceneScale  获取当前画布缩放倍率
/// \return
///
std::pair<double, double> SceneManager::getSceneScale()
{
    return this->sceneScale;
}

int SceneManager::layerCount(){
    TreeModel *model = qobject_cast<TreeModel *>(UiManager::getIns().UI()->treeView->model());
    auto layerCount = model->rowCount(QModelIndex());

    return layerCount;
}

void SceneManager::dragScene(QPointF pointCoordView, MouseEvent event)
{

    if (event == MouseEvent::LeftPress)
    {
        DEBUG_MSG("dragScene: LeftPress");
        // DEBUG_VAR(pointCoordView);

        this->dragScenePoint = pointCoordView;
    }
    else if (event == MouseEvent::MouseMove)
    {
        // DEBUG_MSG("dragScene: MouseMove");
        // DEBUG_VAR(pointCoordView);

        double dx = static_cast<double>(this->dragScenePoint.x()) - static_cast<double>(pointCoordView.x());
        double dy = static_cast<double>(this->dragScenePoint.y()) - static_cast<double>(pointCoordView.y());
        QPointF delta(dx, dy);

        double newX = std::fma(delta.x(), 1.0 / SceneManager::getIns().getSceneScale().first, 0.0);
        double newY = std::fma(delta.y(), 1.0 / SceneManager::getIns().getSceneScale().second, 0.0);
        delta = QPointF(newX, newY);
        // DEBUG_VAR(delta);

        auto newRect = SceneManager::getIns().scene->sceneRect().adjusted(delta.x(),delta.y(),delta.x(),delta.y());
        SceneManager::getIns().scene->setSceneRect(newRect);

        this->dragScenePoint = pointCoordView;
    }
    else if (event == MouseEvent::LeftRelease)
    {
        DEBUG_MSG("dragScene: LeftRelease");
        this->dragScenePoint = QPointF(0,0);
    }
}

///
/// \brief SceneManager::setSceneScale  放大缩小画布
/// \param x 缩放倍率(基于当前状态再缩放)
/// \param y
///
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
