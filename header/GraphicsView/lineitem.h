#ifndef LINEITEM_H
#define LINEITEM_H

#include "protocol.h"
#include "graphicsitem.h"
#include "logger.h"

class LineItem: GraphicsItem
{
public:
    LineItem();
    /// \brief control
    /// 直接修改 控制对象
    /// 这里面所有函数结束都要调用animate
    void editVertex(const int index, const QPointF point, const double angle) override
    {
        if (index >1) return;

        QPointF pos = point - this->scenePos();
        this->m_vertexPair[index].point = pos;

        animate();
    }
    void setParallelOffset(const double offset, const double offsetNum) override;
    void setCenterPos(const QPointF point) override;
    void rotate(const double angle) override;// TODO
    /// \brief update
    /// 更新函数 不能主动调用update；都在animate中调用
    void updateParallelOffset() override;// TODO
    void updatePaintItem() override
    {
        // 这里实时把vertexlist里的点信息更新到itemlist里；然后paint函数会绘制itemlist里的东西
        this->m_paintItem = nullptr;

        auto v1 = m_vertexPair[0].point;
        auto v2 = m_vertexPair[1].point;

        this->m_paintItem = std::make_shared<QGraphicsLineItem>(
            QLineF(v1, v2)
            );
        this->m_paintItem->setPen(this->getPen());
    }
    /// \brief get info
    /// 只获取信息
    double getParallelOffset()override;
    double getParallelOffsetNum()override;
    Vertex getVertex(const int index)override;
    QPointF getVertexPos(const int index)override;
    QPointF getCenterPos() override
    {
        auto center = QPointF{};
        center = (m_vertexPair[0].point + m_vertexPair[1].point)/2;

        auto posOffset = this->pos();
        return center+posOffset;
    }
    QString getName() override;
    /// \brief reload
    enum { Type = ItemTypeId::Arc };
    int type() const override;
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override
    {
        Q_UNUSED(widget);

        // 设置option删去offset线段的选框
        QStyleOptionGraphicsItem optionx(* option);
        optionx.state &= ~QStyle::State_Selected;

        // 绘制线段
        this->m_paintItem->paint(painter, &optionx, widget);

        // 绘制编辑原点
        painter->setPen(Qt::NoPen);
        painter->setBrush(Qt::red);
        for (const auto &vertex : m_vertexPair)
        {
            if (this->m_offsetNum>0)
            {
                painter->setBrush(Qt::red);
                painter->drawEllipse(vertex.point, editPointSize.first, editPointSize.second);
            }
            else
            {
                painter->setBrush(Qt::blue);
                painter->drawEllipse(vertex.point, editPointSize.first, editPointSize.second);
            }
        }

        // 绘制offset
        for (auto& item: this->m_offsetItemList)
            item->paint(painter, &optionx, widget);
    }
private:
    ///
    std::array<Vertex,2> m_vertexPair = {Vertex{QPointF{0,0}, 0},Vertex{QPointF{0,0}, 0}};
    std::shared_ptr<QGraphicsLineItem> m_paintItem;
    ///
    double m_offset  = 0;
    int m_offsetNum = 1;
    std::vector<std::shared_ptr<LineItem>> m_offsetItemList;
};

#endif // LINEITEM_H
