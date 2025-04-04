#ifndef ARCITEM_H
#define ARCITEM_H

#include "protocol.h"
#include "graphicsitem.h"
#include "logger.h"

class ArcItem: public GraphicsItem
{
/// ********************
/// 暂存一些计算变量
/// 不属于状态，不参与实际更新
/// 只用于在绘制时提供一些绘制信息
/// ********************
public:
    /// 绘制时记录当前第几次点击
    int operateIndex = 0;
    /// 绘制时记录中间的暂存点
    QPointF assistPoint =QPointF{};
public:
    ArcItem();
/// ********************
/// \brief control
/// 直接修改 控制对象
/// 这里面所有函数结束都要调用animate
/// ********************
public:
    bool editVertex(const int index, const QPointF point, const double angle) override
    {
        if (index >1 || angle >= 360 || angle <=-360) {
            WARN_VAR(index);
            WARN_VAR(angle);
            return false;
        }


        QPointF pos = point - this->scenePos();
        this->m_vertexPair[index] = Vertex{pos,angle};

        animate();
        return true;
    }
    bool setParallelOffset(const double offset, const double offsetNum) override
    {
        this->m_offset = offset;
        this->m_offsetNum = offsetNum;
        this->animate();
        return true;
    }
    bool setCenterPos(const QPointF point) override
    {
        DEBUG_MSG("use arc setCenterPos");
        QPointF currentCenter = this->getCenterPos();
        QPointF offset = point - currentCenter;
        this->setPos(this->pos() + offset);
        this->animate();
        return true;
    }
    bool rotate(const double angle) override
    {
        return true;
    }
/// ********************
/// \brief update
/// 更新函数 不能主动调用update；都在animate中调用
/// ********************
public:
    bool updateParallelOffset() override;
    bool updatePaintItem() override;
/// ********************
/// \brief get info
/// 只获取信息
/// ********************
public:
    double getParallelOffset()override;
    double getParallelOffsetNum()override;
    Vertex getVertex(const int index)override;
    QPointF getVertexPos(const int index)override;
    QPointF getCenterPos() override;
    QString getName() override;
/// ********************
/// \brief overload
/// 重载基于QGraphicsitem的一些性质
/// ********************
public:
    enum { Type = ItemTypeId::Arc };
    int type() const override;
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
/// ********************
/// private variable
/// ********************
private:
    ///
    std::array<Vertex,2> m_vertexPair = {Vertex{QPointF{0,0}, 0},Vertex{QPointF{0,0}, 0}};
    std::shared_ptr<QGraphicsPathItem> m_paintItem;
    ///
    double m_offset  = 0;
    int m_offsetNum = 1;
    std::vector<std::shared_ptr<ArcItem>> m_offsetItemList;
};

#endif // ARCITEM_H
