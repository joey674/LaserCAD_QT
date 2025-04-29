#ifndef GRAPHICSITEMMANAGER_H
#define GRAPHICSITEMMANAGER_H

#include <QGraphicsScene>
#include <QMainWindow>
#include "arcitem.h"
#include "circleitem.h"
#include "ellipseitem.h"
#include "lineitem.h"
#include "pointitem.h"
#include "polylineitem.h"
#include "protocol.h"
#include "rectitem.h"
#include <qgraphicsitem.h>

class DrawController {
public:
    void resetTmpItemStatus();
    // 绘制对象暂存

    std::shared_ptr < PolylineItem > tmpPolyline;
    std::shared_ptr < ArcItem > tmpArc;
    std::shared_ptr < LineItem > tmpLine;
    std::shared_ptr < PointItem > tmpPoint;
    std::shared_ptr < CircleItem > tmpCircle;
    std::shared_ptr < RectItem > tmpRect;
    std::shared_ptr<EllipseItem> tmpEllipse;
    std::shared_ptr < QGraphicsPathItem > tmpSpiral;
    std::shared_ptr < QGraphicsPolygonItem > tmpPolygon;
    // 绘制辅助变量
    int polygonEdgeNum = 3; //绘制polygon使用
    // 绘制逻辑
    void drawPolyline(QPointF pointCoordscene, MouseEvent event);
    void drawArc(QPointF pointCoordscene, MouseEvent event);
    void drawLine(QPointF pointCoordscene, MouseEvent event);
    void drawPoint(QPointF pointCoordscene, MouseEvent event);
    void drawCircle(QPointF pointCoordscene, MouseEvent event);
    void drawRect(QPointF pointCoordscene, MouseEvent event);
    void drawSpiral(QPointF pointCoordscene, MouseEvent event);
    void drawPolygon(QPointF pointCoordscene, MouseEvent event);
    void drawEllipse(QPointF pointCoordscene, MouseEvent event);

private:
    static DrawController ins;
    DrawController() {};
    DrawController(const DrawController &);
    ~DrawController() {};
    DrawController &operator = (const DrawController &);
public:
    static DrawController &getIns();
};

#endif // GRAPHICSITEMMANAGER_H
