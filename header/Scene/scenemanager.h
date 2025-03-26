#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <utility>
#include "sceneprotocol.h"

class SceneManager
{
public:
    /// scene
    QGraphicsScene *scene;
    OperationEvent currentOperationEvent = None;
    /// scene scale
    std::pair<double,double> sceneScale = {1,1};
    void setSceneScale(double x, double y);
    std::pair<double, double> getSceneScale();
    /// layer
    void setCurrentLayer(int layer);
    int getCurrentLayer(){
        return currentLayer;
    };
    int layerCount();
    /// drag scene
    QPointF dragScenePoint = QPointF(0,0);
    void dragScene(QPointF pointCoordView,  MouseEvent event);
private:
    int currentLayer = 1;

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
