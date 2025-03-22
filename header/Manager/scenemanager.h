#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include <QGraphicsScene>
#include <utility>

class SceneManager
{
public:
    /// scene
    QGraphicsScene *scene;
    /// 记录画布放大倍率
    std::pair<double,double> sceneScale = {1,1};
    /// 记录图层情况
    int layerCount = 1;
    int currentLayer = 1;
public:
    void setSceneScale(double x, double y);
    std::pair<double, double> getSceneScale();

private:
    static SceneManager ins;
    SceneManager(){};
    SceneManager(const SceneManager&);
    ~SceneManager(){};
    SceneManager& operator = (const SceneManager&);
public:
    static SceneManager& getIns();
};
#endif // VIEWMANAGER_H
