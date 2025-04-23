#ifndef ELLIPSEITEM_H
#define ELLIPSEITEM_H

#include "graphicsitem.h"
#include "logger.h"
#include "polylineitem.h"
#include "protocol.h"

class EllipseItem : public GraphicsItem {
public:
    int drawStep = 0;

public:
    EllipseItem() {};
    EllipseItem(const EllipseItem &other)
        : m_radiusX(other.m_radiusX),
          m_radiusY(other.m_radiusY),
          m_rotateAngle(other.m_rotateAngle),
          m_offset(other.m_offset),
          m_offsetCount(other.m_offsetCount) {
    }
    std::shared_ptr < GraphicsItem > clone() const  {
        return std::make_shared < EllipseItem > (EllipseItem(*this));
    }

public:
    /// 编辑圆心
    bool setVertexInScene(const int index, const Vertex vertex) override {
        if (index > 1) {
            WARN_VAR(index);
            return false;
        }
        QPointF pos = vertex.point - this->scenePos();
        this->m_center = Vertex{pos, 0};
        animate();
        return true;
    }
    /// 编辑半径/旋转角度
    bool setRadiusX(const double radius) {
        if (radius < 0) {
            return false;
        }
        this->m_radiusX = radius;
        animate();
        return true;
    }
    bool setRadiusY(const double radius) {
        if (radius < 0) {
            return false;
        }
        this->m_radiusY = radius;
        animate();
        return true;
    }
    bool setRotateAngle(const double angle) {
        if (angle < 0) {
            return false;
        }
        this->m_rotateAngle = angle;
        animate();
        return true;
    }
    bool setCenterInScene(const QPointF point) override {
        // DEBUG_MSG("use circle setCenterInScene");
        // DEBUG_VAR(point);
        QPointF currentCenter = this->getCenterInScene();
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
            cavc::Polyline < double > input = this->getCavcForm(false);
            input.isClosed() = true;
            std::vector < cavc::Polyline < double>> results = cavc::parallelOffset(input,
                this->m_offset
                * offsetIndex);
            // 获取结果
            for (const auto &polyline : results) {
                auto item = FromCavcForm(polyline);
                this->m_offsetItemList.push_back(std::move(item));
            }
        }
        return true;
    }
    bool updatePaintItem() override {
        this->m_paintItem = nullptr;
        const int segments = 64; // 越多越圆滑
        QPainterPath path;
        double angleRad = m_rotateAngle * M_PI / 180.0;
        double cosA = std::cos(angleRad);
        double sinA = std::sin(angleRad);
        auto mapPoint = [&](double x, double y) -> QPointF {
            // 先椭圆坐标，再旋转，再平移
            double xr = x * cosA - y * sinA;
            double yr = x * sinA + y * cosA;
            return QPointF(xr, yr) + m_center.point;
        };
        for (int i = 0; i <= segments; ++i) {
            double theta = 2.0 * M_PI * i / segments;
            double x = m_radiusX * std::cos(theta);
            double y = m_radiusY * std::sin(theta);
            QPointF pt = mapPoint(x, y);
            if (i == 0) {
                path.moveTo(pt);
            } else {
                path.lineTo(pt);
            }
        }
        auto pathItem = new QGraphicsPathItem(path);
        pathItem->setPen(this->getPen());
        this->m_paintItem.reset(pathItem);
        return true;
    }

public:
    cavc::Polyline < double > getCavcForm(bool inSceneCoord) const override {
        cavc::Polyline < double > input;
        QPointF p1, p2;
        if (inSceneCoord) {
            // p1 = this->getVertexInScene(0).point - QPointF{this->m_radius, 0};
            // p2 = this->getVertexInScene(1).point + QPointF{this->m_radius, 0};
        } else {
            // p1 = m_center.point - QPointF{this->m_radius, 0};
            // p2 = m_center.point + QPointF{this->m_radius, 0};
        }
        return input;
    }
    Vertex getVertexInScene(const int index = 0) const override {
        if (index > 1) {
            assert("false index:only 0");
        }
        QPointF point = m_center.point;
        double angle = m_center.angle;
        QPointF pos = point + this->scenePos();
        return Vertex{pos, angle};
    }
    QPointF getCenterInScene() const override {
        auto posOffset = this->pos();
        auto centerPos = this->m_center.point + posOffset;
        // DEBUG_VAR(centerPos);
        return centerPos;
    }
    QString getName() const override {
        return "EllipseItem";
    }
    double getRadiusX() {
        return this->m_radiusX;
    }
    double getRadiusY() {
        return this->m_radiusY;
    }
    double getRotateAngle() {
        return this->m_rotateAngle;
    }

public:
    int type() const override {
        return GraphicsItemType::Circle;
    }

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    ///
    Vertex m_center = Vertex{QPointF{0, 0}, 0};
    double m_radiusX = 0;
    double m_radiusY = 0;
    double m_rotateAngle = 0;
    std::shared_ptr < QGraphicsPathItem > m_paintItem;
    ///
    double m_offset = 0;
    int m_offsetCount = 0;
    std::vector < std::shared_ptr < PolylineItem>> m_offsetItemList;
};

#endif // ELLIPSEITEM_H
