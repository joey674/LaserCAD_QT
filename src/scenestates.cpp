#include "scenestates.h"
#include "logger.h"
#include "uimanager.h"

SceneStates SceneStates::ins;

SceneStates &SceneStates::getIns()
{
    return ins;
}

///
/// \brief SceneStates::getSceneScale  获取当前画布缩放倍率
/// \return
///
std::pair<double, double> SceneStates::getSceneScale()
{
    return this->sceneScale;
}

void SceneStates::dragScene(QPointF pointCoordView, DrawEventType event)
{

    if (event == DrawEventType::LeftPress)
    {
        DEBUG_MSG("dragScene: LeftPress");
        // DEBUG_VAR(pointCoordView);

        this->dragScenePoint = pointCoordView;
    }
    else if (event == DrawEventType::MouseMove)
    {
        // DEBUG_MSG("dragScene: MouseMove");
        // DEBUG_VAR(pointCoordView);

        double dx = static_cast<double>(this->dragScenePoint.x()) - static_cast<double>(pointCoordView.x());
        double dy = static_cast<double>(this->dragScenePoint.y()) - static_cast<double>(pointCoordView.y());
        QPointF delta(dx, dy);

        double newX = std::fma(delta.x(), 1.0 / SceneStates::getIns().getSceneScale().first, 0.0);
        double newY = std::fma(delta.y(), 1.0 / SceneStates::getIns().getSceneScale().second, 0.0);
        delta = QPointF(newX, newY);
        // DEBUG_VAR(delta);

        auto newRect = SceneStates::getIns().scene->sceneRect().adjusted(delta.x(),delta.y(),delta.x(),delta.y());
        SceneStates::getIns().scene->setSceneRect(newRect);

        this->dragScenePoint = pointCoordView;
    }
    else if (event == DrawEventType::LeftRelease)
    {
        DEBUG_MSG("dragScene: LeftRelease");
        this->dragScenePoint = QPointF(0,0);
    }
}

///
/// \brief SceneStates::setItemStatus  设置物体状态
/// \param visible
/// \param selectable
/// \param movable
/// \param item
///




///
/// \brief SceneStates::setSceneScale  放大缩小画布
/// \param x 缩放倍率(基于当前状态再缩放)
/// \param y
///
void SceneStates::setSceneScale(double x, double y)
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
