#ifndef ARCITEM_H
#define ARCITEM_H

#include "protocol.h"
#include "graphicsitem.h"
#include "logger.h"

class ArcItem: public GraphicsItem
{
public: // 只用于暂存一些计算变量，不属于状态，不参与实际更新
    int operateIndex = 0;// 绘制时记录当前第几次点击
    QPointF assistPoint =QPointF{};//绘制时记录中间的暂存点
public:
    ArcItem();
    /// \brief control
    /// 直接修改 控制对象
    /// 这里面所有函数结束都要调用animate
    void editVertex(const int index, const QPointF point, const double angle) override;
    void setParallelOffset(const double offset, const double offsetNum) override;
    void setCenterPos(const QPointF point) override;
    void rotate(const double angle) override;
    /// \brief update
    /// 更新函数 不能主动调用update；都在animate中调用
    void updateParallelOffset() override;
    void updatePaintItem() override;
    /// \brief get info
    /// 只获取信息
    double getParallelOffset()override;
    double getParallelOffsetNum()override;
    Vertex getVertex(const int index)override;
    QPointF getVertexPos(const int index)override;
    QPointF getCenterPos() override;
    QString getName() override;
    /// \brief reload
    enum { Type = ItemTypeId::Arc };
    int type() const override;
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
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
