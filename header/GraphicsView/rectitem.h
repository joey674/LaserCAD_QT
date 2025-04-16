#ifndef RECTITEM_H
#define RECTITEM_H

#include "protocol.h"
#include "graphicsitem.h"
#include "logger.h"
#include "polylineitem.h"

class RectItem : public GraphicsItem {
public:
    RectItem() {};
    RectItem(const RectItem& other):
        m_offset(other.m_offset),
        m_offsetNum(other.m_offsetNum) {
        m_vertexPair[0].point = other.getVertexPos(0);
        m_vertexPair[1].point = other.getVertexPos(1);
        // 更新出来paintitem和offsetitem
        this->animate();
    }
    std::shared_ptr < GraphicsItem > copy() const  override {
        return std::make_shared < RectItem > (RectItem(*this));
    }
protected:
    friend class Manager;
    friend class DrawManager;
    /// 编辑vertex; 0是左上坐标,1是右下坐标
    bool editVertex(const int index, const QPointF point, const double angle = 0) override {
        if (index > 1) {
            return false;
        }
        QPointF pos = point - this->scenePos();
        this->m_vertexPair[index].point = pos;
        animate();
        return true;
    }
    bool setParallelOffset(const double offset, const double offsetNum) override {
        this->m_offset = offset;
        this->m_offsetNum = offsetNum;
        this->animate();
        return true;
    }
    bool setCenterPos(const QPointF point) override {
        QPointF currentCenter = this->getCenterPos();
        QPointF offset = point - currentCenter;
        this->setPos(this->pos() + offset);
        this->animate();
        return true;
    }
    bool rotate(const double angle) override {
        //TODO
        return true;
    }
protected:
    bool updateParallelOffset() override {
        if (this->m_offset == 0 || this->m_offsetNum == 0) {
            return true;
        }
        this->m_offsetItemList.clear();
        for (int offsetIndex = 1; offsetIndex <= this->m_offsetNum; offsetIndex++) {
            // 输入cavc库
            cavc::Polyline < double > input = this->getCavConForm ();
            input.isClosed() = true;
            std::vector < cavc::Polyline < double>> results = cavc::parallelOffset(input, this->m_offset * offsetIndex);
            // 获取结果
            for (const auto &polyline : results) {
                auto item = FromCavConForm(polyline);
                this->m_offsetItemList.push_back(std::move(item));
            }
        }
        return true;
    }
    bool updatePaintItem() override {
        // 这里实时把vertexlist里的点信息更新到itemlist里；然后paint函数会绘制itemlist里的东西
        this->m_paintItem = nullptr;
        this->m_paintItem = std::make_shared < QGraphicsRectItem > ();
        // 构造 QRectF
        QPointF topLeft = m_vertexPair[0].point;
        QPointF bottomRight = m_vertexPair[1].point;
        QRectF rect(topLeft, bottomRight);
        // 设置绘图矩形
        this->m_paintItem->setRect(rect);
        this->m_paintItem->setPen(this->getPen());
        return true;
    }
public:
    cavc::Polyline < double > getCavConForm() const override {
        cavc::Polyline < double > input;
        // 获取矩形
        QPointF topLeft = m_vertexPair[0].point;
        QPointF bottomRight = m_vertexPair[1].point;
        QRectF rect(topLeft, bottomRight);
        rect = rect.normalized();
        // 按顺时针方向添加四个点
        input.addVertex(rect.left(), rect.top(), -1);
        input.addVertex(rect.right(), rect.top(), -1);
        input.addVertex(rect.right(), rect.bottom(), -1);
        input.addVertex(rect.left(), rect.bottom(), -1);
        input.isClosed() = true;
        return input;
    }
    double getParallelOffset() const override {
        return this->m_offset;
    }
    double getParallelOffsetNum() const override {
        return this->m_offsetNum;
    }
    Vertex getVertex(const int index = 0) const override {
        if (index > 1) {
            assert("false index:only 0,1");
        }
        return m_vertexPair[index];
    }
    QPointF getVertexPos(const int index) const override {
        if (index > 1) {
            assert("false index:only 0,1");
        }
        QPointF point = m_vertexPair[index].point;
        QPointF pos = point + this->scenePos();
        return pos;
    }
    QPointF getCenterPos() const override {
        auto center = QPointF{};
        center = (m_vertexPair[0].point + m_vertexPair[1].point) / 2;
        auto posOffset = this->pos();
        return center + posOffset;
    }
    QString getName() const override {
        return "RectItem";
    }
public:
    int type() const override {
        return GraphicsItemType::Rect;
    }
protected:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
private:
    ///
    std::array < Vertex, 2 > m_vertexPair = {Vertex{QPointF{0, 0}, 0}, Vertex{QPointF{0, 0}, 0}};
    std::shared_ptr < QGraphicsRectItem > m_paintItem;
    ///
    double m_offset  = 0;
    int m_offsetNum = 0;
    std::vector < std::shared_ptr < PolylineItem>> m_offsetItemList;
};
#endif // RECTITEM_H
