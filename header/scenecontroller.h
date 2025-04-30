#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <utility>
#include "protocol.h"

class SceneController {
public:
    /// scene
    QGraphicsScene *scene;
    OperationEvent m_currentOperationEvent = None;
public:
    /// scene scale
    std::pair < double, double > m_sceneScale = {1, 1};
    /// \brief SceneController::setSceneScale  放大缩小画布
    /// \param x,y  缩放倍率(基于当前状态再缩放)
    void setSceneScale(double x, double y);
    /// \brief SceneController::getSceneScale  获取当前画布缩放倍率
    /// \return
    std::pair < double, double > getSceneScale();

public:
    UUID m_currentLayer;
    UUID m_layerCount;
    std::vector < UUID > m_layerList;
    /// \brief setCurrentLayer 设置当前layer; 同时还会做一些操作: 设定只有当前图层物体可动,其他不可动; 以及其他图层颜色为display;
    /// \param layer
    void setCurrentLayer(UUID layerUuid);
    /// \brief getCurrentLayer
    /// \return
    UUID getCurrentLayer();
    /// \brief initLayerUuid  初始化函数 只在treemodel初始化的时候调用
    /// \param uuid
    void initLayerUuid(UUID uuid);
    /// \brief layerCount
    /// \return
    int layerCount();

    void addLayer();
    void deleteCurrentLayer();
public:
    /// drag scene
    QPointF m_dragScenePoint = QPointF(0, 0);
    /// \brief dragScene 拖动scene事件 供
    /// \param pointCoordView
    void dragScene(QPointF pointCoordView,  MouseEvent event);
private:
    static SceneController ins;
    SceneController() {};
    SceneController(const SceneController &);
    ~SceneController() {};
    SceneController &operator = (const SceneController &);
public:
    static SceneController &getIns();
};
#endif // SCENEMANAGER_H
