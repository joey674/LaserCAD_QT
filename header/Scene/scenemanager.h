#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <utility>
#include "protocol.h"

class SceneManager
{
public:
    /// scene
    QGraphicsScene *scene;
    OperationEvent currentOperationEvent = None;
    /// scene scale
    std::pair<double,double> sceneScale = {1,1};
    /// \brief SceneManager::setSceneScale  放大缩小画布
    /// \param x,y  缩放倍率(基于当前状态再缩放)
    void setSceneScale(double x, double y);
    /// \brief SceneManager::getSceneScale  获取当前画布缩放倍率
    /// \return
    std::pair<double, double> getSceneScale();
    /// \brief setCurrentLayer 设置当前layer; 同时还会做一些操作: 设定只有当前图层物体可动,其他不可动; 以及其他图层颜色为display;
    /// \param layer
    void setCurrentLayer(int layer);
    /// \brief getCurrentLayer
    /// \return
    int getCurrentLayer();
    /// \brief layerCount
    /// \return
    int layerCount();

    /// drag scene
    QPointF dragScenePoint = QPointF(0,0);
    /// \brief dragScene 拖动scene事件 供
    /// \param pointCoordView
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
