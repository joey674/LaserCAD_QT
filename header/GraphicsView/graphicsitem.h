#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H

#include <QDebug.h>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include "protocol.h"
#include "utils.hpp"
#include <polylineoffset.hpp>
#include <qgraphicsitem.h>
#include <qgraphicsscene.h>

class GraphicsItem: public QGraphicsItem {
public:
    GraphicsItem() {
        this->m_uuid = GenerateUUID();
        this->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    }
    GraphicsItem(const GraphicsItem &other) {
        this->m_uuid = GenerateUUID();
        this->setFlags(other.flags());
        this->markParams = other.markParams;
        this->delayParams = other.delayParams;
    }
    virtual std::shared_ptr < GraphicsItem > copy() const = 0;
/// ********************
/// \brief control
/// 直接修改 控制对象
/// 这里面所有函数结束都要调用animate
/// 这里存的vertex以及获得的pos都是真实scene位置; 都已经经过变换, 不用再考虑锚点
/// ********************
public:
    /// \brief setVertex
    /// \param point 这里输入的是scene真实位置；不考虑锚点位置;禁止直接修改vertex
    virtual bool setVertex(const int index, const Vertex vertex) = 0;
    /// \brief setCenter
    /// \param point 这里输入的是scene真实位置；不考虑锚点位置;禁止直接修改vertex
    virtual bool setCenter(const QPointF point) = 0;
    /// \brief setParallelOffset
    /// \param offset
    virtual bool setParallelOffset(const double offset, const double offsetNum) = 0;
    /// \brief rotate
    /// \param angle
    virtual bool rotate(const double angle) = 0;
    /// \brief setPen
    /// \param
    bool setPen(QPen setPen) {
        this->m_pen = setPen;
        this->animate();
        return true;
    };
    bool setMarkParams(const MarkParams params) {
        this->markParams = params;
        return true;
    }
    bool setDelayParams(const DelayParams params) {
        this->delayParams = params;
        return true;
    }
    /// ********************
/// \brief update
/// 更新函数 不能主动调用update；都在animate中调用
/// ********************
protected:
    virtual bool updateParallelOffset() = 0;
    virtual bool updatePaintItem() = 0;
    virtual bool animate() {
        prepareGeometryChange();
        // 这里实时把vertexlist里的点信息更新到itemlist里；然后paint函数会绘制itemlist里的东西
        this->updatePaintItem();
        // 更新offsetitem
        this->updateParallelOffset();
        update();
        return true;
    }
/// ********************
/// \brief get info
/// 只获取信息
/// ********************
public:
    /// \brief getParallelOffset
    /// \return
    virtual cavc::Polyline<double> getCavcForm() const = 0;
    virtual double getParallelOffset() const = 0;
    virtual double getParallelOffsetCount() const = 0;
    /// \brief getVertex
    /// \return 这里返回的是在scene中vertex的真实位置;不考虑锚点位置;禁止直接修改vertex
    virtual Vertex getVertex(const int index) const = 0;
    /// \brief getCenter
    /// \return 这里返回的是scene真实位置;不考虑锚点位置;禁止直接修改vertex
    virtual QPointF getCenter() const = 0;
    virtual QString getName() const;
    const QString getUUID() const;
    const QPen getPen() const;
    const MarkParams getMarkParams() const {
        return this->markParams;
    }
    const DelayParams getDelayParams() const {
        return this->delayParams;
    }
/// ********************
/// \brief overload
/// 重载基于QGraphicsitem的一些性质
/// ********************
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
/// ********************
/// private variable
/// ********************
private:
    QString m_uuid;
    QPen m_pen = DISPLAY_PEN;
    MarkParams markParams;
    DelayParams delayParams;
};

#endif // GRAPHICSITEM_H
