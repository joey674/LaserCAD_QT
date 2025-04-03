#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H

#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <QPainter>
#include <QDebug.h>
#include <QStyleOptionGraphicsItem>
#include "protocol.h"

class GraphicsItem: public QGraphicsItem
{
public:
    std::pair<double,double> editPointSize = std::pair<double,double>{1,1};
public:
    GraphicsItem();
public:
    /// \brief control
    /// 直接修改 控制对象
    /// 这里面所有函数结束都要调用animate
    virtual void editVertex(const int index, const QPointF point, const double angle) = 0;
    virtual void setParallelOffset(const double offset, const double offsetNum) = 0;
    virtual void setCenterPos(const QPointF point) = 0;
    virtual void rotate(const double angle) = 0;
    protected: friend class Manager;friend class DrawManager; void setPen(QPen setPen)
    {
        this->m_pen = setPen;
        this->animate();
    };
public:
    /// \brief update
    /// 更新函数 不能主动调用update；都在animate中调用
    virtual void updateParallelOffset() = 0;
    virtual void updatePaintItem() = 0;
    virtual void animate() {
        prepareGeometryChange();

        // 这里实时把vertexlist里的点信息更新到itemlist里；然后paint函数会绘制itemlist里的东西
        this->updatePaintItem();

        // 更新offsetitem
        this->updateParallelOffset();

        update();
    };
public:
    /// \brief get info
    /// 只获取信息
    virtual double getParallelOffset() = 0;
    virtual double getParallelOffsetNum() = 0;
    virtual Vertex getVertex(const int index) = 0;
    virtual QPointF getVertexPos(const int index) = 0;
    virtual QPointF getCenterPos() = 0;
    virtual QString getName();
    const QString getUUID();
    const QPen getPen();
public:
    /// \brief reload
    /// 重载QGraphicsItem类的成员函数
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    QString m_uuid;
    QPen m_pen = DISPLAY_PEN;
};

#endif // GRAPHICSITEM_H
