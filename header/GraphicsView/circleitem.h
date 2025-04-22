#ifndef CIRCLEITEM_H
#define CIRCLEITEM_H

#include "protocol.h"
#include "graphicsitem.h"
#include "logger.h"
#include "polylineitem.h"

class CircleItem : public GraphicsItem {
public:
    CircleItem() {};
    CircleItem(const CircleItem& other): GraphicsItem(other),
        m_radius(other.m_radius),
        m_offset(other.m_offset),
        m_offsetCount(other.m_offsetCount) {
        // 更新出来paintitem和offsetitem
        this->m_center = other.getVertex(0);
        this->animate();
    }
    std::shared_ptr < GraphicsItem > copy() const  override {
        return std::make_shared < CircleItem > (CircleItem(*this));
    }
public:
    /// 编辑圆心
    bool setVertex(const int index, const Vertex vertex) override
    {
        if (index > 1) {
            WARN_VAR(index);
            return false;
        }
        QPointF pos = vertex.point - this->scenePos();
        this->m_center = Vertex{pos, 0};
        animate();
        return true;
    }
    /// 编辑半径
    bool setRadius(const double radius)
    {
        if (radius < 0) {
            return false;
        }
        this->m_radius = radius;
        animate();
        return true;
    }
    bool setOffsetItem(const double offset, const double offsetNum) override {
        this->m_offset = offset;
        this->m_offsetCount = offsetNum;
        this->animate();
        return true;
    }
    bool setCenter(const QPointF point) override
    {
        // DEBUG_MSG("use circle setCenter");
        // DEBUG_VAR(point);
        QPointF currentCenter = this->getCenter();
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
    bool updateOffsetItem() override {
        if (this->m_offset == 0 || this->m_offsetCount == 0) {
            return true;
        }
        this->m_offsetItemList.clear();
        for (int offsetIndex = 1; offsetIndex <= this->m_offsetCount; offsetIndex++) {
            // 输入cavc库
            cavc::Polyline<double> input = this->getCavcForm(false);
            input.isClosed() = true;
            std::vector < cavc::Polyline < double>> results = cavc::parallelOffset(input, this->m_offset * offsetIndex);
            // 获取结果
            for (const auto &polyline : results) {
                auto item = FromCavcForm(polyline);
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
    cavc::Polyline<double> getCavcForm(bool inSceneCoord) const override
    {
        cavc::Polyline < double > input;
        QPointF p1, p2;
        if (inSceneCoord) {
            p1 = this->getVertex(0).point - QPointF{this->m_radius, 0};
            p2 = this->getVertex(1).point + QPointF{this->m_radius, 0};
        } else {
            p1 = m_center.point - QPointF{this->m_radius, 0};
            p2 = m_center.point + QPointF{this->m_radius, 0};
        }
        input.addVertex(p1.x(), p1.y(), -1);
        input.addVertex(p2.x(), p2.y(), -1);
        return input;
    }
    double getOffset() const override {
        return this->m_offset;
    }
    double getOffsetCount() const override {
        return this->m_offsetCount;
    }
    Vertex getVertex(const int index = 0) const override
    {
        if (index > 1) {
            assert("false index:only 0");
        }
        QPointF point = m_center.point;
        double angle = m_center.angle;
        QPointF pos = point + this->scenePos();
        return Vertex{pos, angle};
    }
    QPointF getCenter() const override
    {
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
    int m_offsetCount = 0;
    std::vector < std::shared_ptr < PolylineItem>> m_offsetItemList;
};

#endif // CIRCLEITEM_H
