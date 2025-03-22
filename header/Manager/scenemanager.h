#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <utility>
#include "protocol1.h"

class SceneManager
{
public:
    /// scene
    QGraphicsScene *scene;
    OperationEvent currentOperationEvent = None;
public:
    /// scene scale
    std::pair<double,double> sceneScale = {1,1};
    void setSceneScale(double x, double y);
    std::pair<double, double> getSceneScale();
public:
    /// layer
    int layerCount = 1;
    int currentLayer = 1;
public:
    QPointF dragScenePoint = QPointF(0,0);
    void dragScene(QPointF pointCoordView,  MouseEvent event);


private:
    static SceneManager ins;
    SceneManager(){};
    SceneManager(const SceneManager&);
    ~SceneManager(){};
    SceneManager& operator = (const SceneManager&);
public:
    static SceneManager& getIns();
};
#endif // SCENEMANAGER_H
