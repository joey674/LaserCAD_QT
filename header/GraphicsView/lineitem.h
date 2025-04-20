#ifndef LINEITEM_H
#define LINEITEM_H

#include "protocol.h"
#include "graphicsitem.h"
#include "polylineitem.h"

class LineItem: public GraphicsItem {
public:
    LineItem();
    LineItem(const LineItem &other): GraphicsItem(other),
        m_vertexPair(other.m_vertexPair)
        , m_offset(other.m_offset)
        , m_offsetCount(other.m_offsetCount) {
        m_vertexPair[0] = other.getVertex(0);
        m_vertexPair[1] = other.getVertex(1);
        // 更新出来paintitem和offsetitem
        this->animate();
    }
    std::shared_ptr < GraphicsItem > copy() const  override {
        return std::make_shared < LineItem > (LineItem(*this));
    }
public:
    bool setVertex(const int index, const Vertex vertex) override
    {
        if (index > 1) {
            return false;
        }
        this->m_vertexPair[index].point = vertex.point - this->scenePos();
        this->m_vertexPair[index].angle = vertex.angle;
        animate();
        return true;
    }
    bool setParallelOffset(const double offset, const double offsetNum) override
    {
        this->m_offset = offset;
        this->m_offsetCount = offsetNum;
        this->animate();
        return true;
    }
    bool setCenter(const QPointF point) override
    {
        QPointF currentCenter = this->getCenter();
        QPointF offset = point - currentCenter;
        this->setPos(this->pos() + offset);
        this->animate();
        return true;
    }
    bool rotate(const double angle) override { return true; } // TODO
protected:
    bool updateParallelOffset() override
    {
        if (this->m_offset == 0 || this->m_offsetCount == 0) {
            return true;
        }
        this->m_offsetItemList.clear();
        for (int offsetIndex = 1; offsetIndex <= this->m_offsetCount; offsetIndex++) {
            // 输入cavc库
            cavc::Polyline<double> input = this->getCavcForm(false);
            input.isClosed() = false;
            std::vector<cavc::Polyline<double>> results = cavc::parallelOffset(input,
                                                                               this->m_offset
                                                                                   * offsetIndex);
            // 获取结果
            for (const auto &polyline : results) {
                auto item = FromCavcForm(polyline);
                this->m_offsetItemList.push_back(std::move(item));
            }
        }
        return true;
    } // TODO
    bool updatePaintItem() override
    {
        // 这里实时把vertexlist里的点信息更新到itemlist里；然后paint函数会绘制itemlist里的东西
        this->m_paintItem = nullptr;
        auto v1 = m_vertexPair[0].point;
        auto v2 = m_vertexPair[1].point;
        this->m_paintItem = std::make_shared<QGraphicsLineItem>(QLineF(v1, v2));
        this->m_paintItem->setPen(this->getPen());
        return true;
    }

public:
    cavc::Polyline<double> getCavcForm(bool inSceneCoord) const override
    {
        // 输入cavc库
        cavc::Polyline<double> input;
        QPointF p1, p2;
        if (inSceneCoord) {
            p1 = this->getVertex(0).point;
            p2 = this->getVertex(1).point;
        } else {
            p1 = m_vertexPair[0].point;
            p2 = m_vertexPair[1].point;
        }

        input.addVertex(p1.x(), p1.y(), 0);
        input.addVertex(p2.x(), p2.y(), 0);
        return input;
    }
    double getParallelOffset() const override { return this->m_offset; }
    double getParallelOffsetCount() const override { return this->m_offsetCount; }
    Vertex getVertex(const int index) const override
    {
        if (index > 1) {
            assert("false index:only 0,1");
        }
        QPointF point = m_vertexPair[index].point;
        double angle = m_vertexPair[index].angle;
        QPointF pos = point + this->scenePos();
        return Vertex{pos, angle};
    }
    QPointF getCenter() const override
    {
        auto center = QPointF{};
        center = (m_vertexPair[0].point + m_vertexPair[1].point) / 2;
        auto posOffset = this->pos();
        return center + posOffset;
    }
    QString getName() const override { return "LineItem"; }

public:
    int type() const override {
        return GraphicsItemType::Line;
    }
protected:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
private:
    ///
    std::array < Vertex, 2 > m_vertexPair = {Vertex{QPointF{0, 0}, 0}, Vertex{QPointF{0, 0}, 0}};
    std::shared_ptr < QGraphicsLineItem > m_paintItem;
    ///
    double m_offset  = 0;
    int m_offsetCount = 0;
    std::vector < std::shared_ptr < PolylineItem>> m_offsetItemList;
};

#endif // LINEITEM_H
