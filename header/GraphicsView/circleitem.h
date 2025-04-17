#ifndef CIRCLEITEM_H
#define CIRCLEITEM_H

#include "protocol.h"
#include "graphicsitem.h"
#include "logger.h"
#include "polylineitem.h"

class CircleItem : public GraphicsItem {
public:
    CircleItem() {};
    CircleItem(const CircleItem& other):
        m_center(other.m_center),
        m_radius(other.m_radius),
        m_offset(other.m_offset),
        m_offsetNum(other.m_offsetNum) {
        // 更新出来paintitem和offsetitem
        this->animate();
    }
    std::shared_ptr < GraphicsItem > copy() const  override {
        return std::make_shared < CircleItem > (CircleItem(*this));
    }
public:
    /// 编辑圆心
    bool editVertex(const int index, const QPointF point, const double angle = 0) override {
        if (index > 1) {
            WARN_VAR(index);
            return false;
        }
        QPointF pos = point - this->scenePos();
        this->m_center = Vertex{pos, 0};
        animate();
        return true;
    }
    /// 编辑半径
    bool editRadius(const double radius) {
        if (radius < 0) {
            return false;
        }
        this->m_radius = radius;
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
        // DEBUG_MSG("use circle setCenterPos");
        // DEBUG_VAR(point);
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
        this->m_paintItem = std::make_shared < QGraphicsEllipseItem > ();
        QRectF rect(
            m_center.point.x() - m_radius,
            m_center.point.y() - m_radius,
            m_radius * 2,
            m_radius * 2
        );
        this->m_paintItem->setRect(rect);
        this->m_paintItem->setPen(this->getPen());
        return true;
    }
public:
    cavc::Polyline < double > getCavConForm() const override {
        cavc::Polyline < double > input;
        auto p1 = m_center.point - QPointF{this->m_radius, 0};
        auto p2 = m_center.point + QPointF{this->m_radius, 0};
        input.addVertex(p1.x(), p1.y(), -1);
        input.addVertex(p2.x(), p2.y(), -1);
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
            assert("false index:only 0");
        }
        return m_center;
    }
    QPointF getVertexPos(const int index) const override {
        if (index > 1) {
            assert("false index:only 0");
        }
        QPointF point = m_center.point;
        QPointF pos = point + this->scenePos();
        return pos;
    }
    QPointF getCenterPos() const override {
        auto posOffset = this->pos();
        auto centerPos = this->m_center.point + posOffset;
        // DEBUG_VAR(centerPos);
        return centerPos;
    }
    QString getName() const override {
        return "CircleItem";
    }
    double getRadius() {
        return this->m_radius;
    }
public:
    int type() const override {
        return GraphicsItemType::Circle;
    }
protected:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
private:
    ///
    Vertex m_center = Vertex{QPointF{0, 0}, 0};
    double m_radius = 0;
    std::shared_ptr < QGraphicsEllipseItem > m_paintItem;
    ///
    double m_offset  = 0;
    int m_offsetNum = 0;
    std::vector < std::shared_ptr < PolylineItem>> m_offsetItemList;
};

#endif // CIRCLEITEM_H
