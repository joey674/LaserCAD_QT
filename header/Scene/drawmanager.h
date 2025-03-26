#ifndef GRAPHICSITEMMANAGER_H
#define GRAPHICSITEMMANAGER_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <qgraphicsitem.h>
#include "polylineitem.h"
#include "arcitem.h"
#include "sceneprotocol.h"


class DrawManager
{
public:
    void resetTmpItemStatus();
    // 绘制对象暂存
    std::shared_ptr<QGraphicsEllipseItem> tmpCircle;
    std::shared_ptr<PolylineItem> tmpPolyline;
    std::shared_ptr<ArcItem> tmpArc;
    std::shared_ptr<QGraphicsRectItem> tmpRect;
    std::shared_ptr<QGraphicsPathItem> tmpSpiral;
    std::shared_ptr<QGraphicsPolygonItem> tmpPolygon;
    std::shared_ptr<QGraphicsEllipseItem> tmpEllipse;
    // 绘制辅助变量
    int polygonEdgeNum = 3; //绘制polygon使用
    // 绘制逻辑
    void drawPolyline(QPointF pointCoordscene,MouseEvent event);
    void drawArc(QPointF pointCoordscene,MouseEvent event);
    void drawCircle(QPointF pointCoordscene,MouseEvent event);
    void drawRect(QPointF pointCoordscene,MouseEvent event);
    void drawSpiral(QPointF pointCoordscene,MouseEvent event);
    void drawPolygon(QPointF pointCoordscene,MouseEvent event);
    void drawEllipse(QPointF pointCoordscene,MouseEvent event);

private:
    static DrawManager ins;
    DrawManager(){};
    DrawManager(const DrawManager&);
    ~DrawManager(){};
    DrawManager& operator = (const DrawManager&);
public:
    static DrawManager& getIns();
};

#endif // GRAPHICSITEMMANAGER_H
