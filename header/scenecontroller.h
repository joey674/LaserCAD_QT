#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <utility>
#include "protocol.h"

class SceneController {
    friend class ProjectManager;

public:
    /// scene
    ///
    QGraphicsScene *scene;
    OperationEvent m_currentOperationEvent = None;
public:
    /// scene scale
    ///
    std::pair < double, double > m_sceneScale = {1, 1};
    /// \brief SceneController::setSceneScale  放大缩小画布
    /// \param x,y  缩放倍率(基于当前状态再缩放)
    void setSceneScale(double x, double y);
    /// \brief SceneController::getSceneScale  获取当前画布缩放倍率
    /// \return
    std::pair < double, double > getSceneScale();

public:
    UUID m_currentLayer;
    int m_layerCreatedCount = 1;
    int m_newLayerExamplarColor = 1;

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
    /// \brief addLayer
    ///
    void addLayer();
    void deleteCurrentLayer();
    /// \brief m_dragScenePoint
    ///
    QColor getCurrentLayerColor() const;

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

const QList < QColor > kLayerColors = {
    QColor("#000000"),   // 黑
    QColor("#FF0000"),  // 红
    QColor("#00FF00"),  // 绿
    QColor("#0000FF"),  // 蓝
    QColor("#FFFF00"),  // 黄
    QColor("#FF00FF"),  // 紫
    QColor("#00FFFF"),  // 青
    QColor("#FFA500"),  // 橙
    QColor("#A52A2A"),  // 棕
    QColor("#808080"),  // 灰
};

#endif // SCENEMANAGER_H
