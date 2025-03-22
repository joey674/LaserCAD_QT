#include "scenemanager.h"
#include "logger.h"
#include "uimanager.h"

SceneManager SceneManager::ins;

SceneManager &SceneManager::getIns()
{
    return ins;
}

std::pair<double, double> SceneManager::getSceneScale()
{
    return this->sceneScale;
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
