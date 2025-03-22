#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <utility>
#include "protocol1.h"

class SceneStates
{
public:
    /// scene
    QGraphicsScene *scene;
public:
    std::pair<double,double> sceneScale = {1,1};
    void setSceneScale(double x, double y);
    std::pair<double, double> getSceneScale();
public:
    /// 记录图层情况
    int layerCount = 1;
    int currentLayer = 1;
public:
    QPointF dragScenePoint = QPointF(0,0);
    void dragScene(QPointF pointCoordView,  MouseEvent event);

private:
    static SceneStates ins;
    SceneStates(){};
    SceneStates(const SceneStates&);
    ~SceneStates(){};
    SceneStates& operator = (const SceneStates&);
public:
    static SceneStates& getIns();
};
#endif // VIEWMANAGER_H
