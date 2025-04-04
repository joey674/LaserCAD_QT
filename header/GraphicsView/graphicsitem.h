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
    GraphicsItem();
/// ********************
/// \brief control
/// 直接修改 控制对象
/// 这里面所有函数结束都要调用animate
/// ********************
public:
    /// \brief editVertex
    /// \param point 这里输入的是scene真实位置；不考虑锚点位置
    virtual void editVertex(const int index, const QPointF point, const double angle) = 0;
    /// \brief setParallelOffset
    /// \param offset
    virtual void setParallelOffset(const double offset, const double offsetNum) = 0;
    /// \brief setCenterPos
    /// \param point 这里输入的是scene真实位置；不考虑锚点位置
    virtual void setCenterPos(const QPointF point) = 0;
    /// \brief rotate
    /// \param angle
    virtual void rotate(const double angle) = 0;
    /// \brief setPen
    /// \param
    protected:
    friend class Manager;friend class DrawManager;
    void setPen(QPen setPen)
    {
        this->m_pen = setPen;
        this->animate();
    };
/// ********************
/// \brief update
/// 更新函数 不能主动调用update；都在animate中调用
/// ********************
public:
    virtual void updateParallelOffset() = 0;
    virtual void updatePaintItem() = 0;
    virtual void animate()
    {
        prepareGeometryChange();

        // 这里实时把vertexlist里的点信息更新到itemlist里；然后paint函数会绘制itemlist里的东西
        this->updatePaintItem();

        // 更新offsetitem
        this->updateParallelOffset();

        update();
    };
/// ********************
/// \brief get info
/// 只获取信息
/// ********************
public:
    virtual double getParallelOffset() = 0;
    virtual double getParallelOffsetNum() = 0;
    /// \brief getCenterPos
    /// \return 这里返回的point是vertex相对锚点的位置； 物体移动时，该点不变；
    virtual Vertex getVertex(const int index) = 0;
    /// \brief getCenterPos
    /// \return 这里返回的是在scene中vertex的真实位置；不考虑锚点位置
    virtual QPointF getVertexPos(const int index) = 0;
    /// \brief getCenterPos
    /// \return 这里返回的是scene真实位置；不考虑锚点位置
    virtual QPointF getCenterPos() = 0;
    virtual QString getName();
    const QString getUUID();
    const QPen getPen();
/// ********************
/// \brief overload
/// 重载基于QGraphicsitem的一些性质
/// ********************
public:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
/// ********************
/// private variable
/// /// ********************
private:
    QString m_uuid;
    QPen m_pen = DISPLAY_PEN;
};

#endif // GRAPHICSITEM_H
