#ifndef POLYLINEITEM_H
#define POLYLINEITEM_H

#include "graphicsitem.h"
#include "logger.h"
#include "utils.hpp"
#include <polylineoffset.hpp>
#include <vector.hpp>

class PolylineItem: public GraphicsItem {
public:
    PolylineItem();
    PolylineItem(const PolylineItem& other): GraphicsItem(other),
        m_vertexList(other.m_vertexList),
        m_offset(other.m_offset),
        m_offsetCount(other.m_offsetCount) {
        for (int i = 0; i < this->getVertexCount(); ++i) {
            m_vertexList[i].point = other.getVertexPos(i);
        }
        // 更新出来paintitem和offsetitem
        this->animate();
    }
    std::shared_ptr < GraphicsItem > copy() const  override {
        return std::make_shared < PolylineItem > (PolylineItem(*this));
    }

public:
    bool addVertex(const QPointF point, const double angle) {
        Vertex newVertex = {point, angle};
        m_vertexList.push_back(newVertex);
        animate();
        return true;
    }
    bool editVertex(const int index, const QPointF point, const double angle) override {
        QPointF pos = point - this->scenePos();
        m_vertexList[index] = Vertex{pos, angle};
        animate();
        return true;
    }
    bool deleteVetex(const int index) {
        m_vertexList.erase(m_vertexList.begin() + index);
        animate();
        return true;
    }
    bool setParallelOffset(const double offset, const double offsetNum) override {
        this->m_offset = offset;
        this->m_offsetCount = offsetNum;
        if (offsetNum < 0) {
            FATAL_MSG("offset num must be positive");
        }
        this->animate();
        return true;
    }
    bool setCenterPos(const QPointF point) override {
        DEBUG_MSG("use polyline setCenterPos" );
        QPointF currentCenter = this->getCenterPos();
        QPointF offset = point - currentCenter;
        DEBUG_VAR(point);
        QString msg = QString("curCenter: (%1, %2), offset: (%3, %4), this->pos: (%5, %6)")
                      .arg(currentCenter.x(), 0, 'f', 2)
                      .arg(currentCenter.y(), 0, 'f', 2)
                      .arg(offset.x(), 0, 'f', 2)
                      .arg(offset.y(), 0, 'f', 2)
                      .arg(this->pos().x(), 0, 'f', 2)
                      .arg(this->pos().y(), 0, 'f', 2);
        DEBUG_MSG(msg);
        this->setPos(this->pos() + offset);
        this->animate();
        return true;
    };
    bool rotate(const double angle) override {
        return true;
    }
protected:
    bool updateParallelOffset() override;
    bool updatePaintItem() override {
        if (m_vertexList.size() < 2) {
            return false;
        }
        // 这里实时把vertexlist里的点信息更新到itemlist里；然后paint函数会绘制itemlist里的东西
        m_paintItemList.clear();
        for (size_t i = 0; i < m_vertexList.size() - 1; ++i) {
            QPointF v1 = m_vertexList[i].point;
            QPointF v2 = m_vertexList[i + 1].point;
            double angle = m_vertexList[i + 1].angle;
            if (std::abs(angle) < 1e-20) {
                auto lineItem = std::make_shared < QGraphicsLineItem > (
                                    QLineF(v1, v2)
                                );
                lineItem->setPen(this->getPen());
                m_paintItemList.push_back(std::move(lineItem));
            } else {
                QPainterPath arcPath = createArcPath(v1, v2, angle);
                auto pathItem = std::make_shared < QGraphicsPathItem > (arcPath);
                pathItem->setPen(this->getPen());
                m_paintItemList.push_back(std::move(pathItem));
            }
        }
        return true;
    }
public:
    cavc::Polyline<double> getCavcForm() const override
    {
        cavc::Polyline < double > input;
        for (int i = 0; i < this->getVertexCount(); ++i) {
            auto p1 = m_vertexList[i].point;
            auto p2 = m_vertexList[(i + 1) % this->getVertexCount()].point;
            auto angle = m_vertexList[(i + 1) % this->getVertexCount()].angle;
            // DEBUG_VAR(QString("V%1: (%2, %3), angle=%4")
            //           .arg(i).arg(p1.x ()).arg(p1.y ()).arg(angle));
            if (angle > 180.01 || angle < -180.01) {
                auto sign = angle > 0 ? 1 : -1;
                input.addVertex(p1.x(), p1.y(), sign * (-1)); /*先走180度*/
                QPointF intersectPoint = QPointF{};
                double newAngle = 0;
                double newBulge = 0;
                getIntersectPoint(p1, p2, angle, 180, intersectPoint);
                newAngle = angle - sign * 180;
                getBulgeFromAngle(newAngle, newBulge);
                input.addVertex(intersectPoint.x(), intersectPoint.y(), newBulge *  (-1));
                // DEBUG_VAR(intersectPoint.x());
                // DEBUG_VAR(intersectPoint.y());
                // DEBUG_VAR(newAngle);
            } else {
                double bulge = 0;
                getBulgeFromAngle(angle, bulge);
                input.addVertex(p1.x(), p1.y(), bulge *  (-1));
            }
        }
        ///********************************************
        /// DEBUG
        // for (std::size_t i = 0; i < input.size(); ++i) {
        //     const auto& v = input[i];
        //     double x = v.x ();
        //     double y = v.y ();
        //     double bulge = v.bulge();
        //     DEBUG_VAR(QString("V%1: (%2, %3), bulge=%4")
        //               .arg(i).arg(x).arg(y).arg(bulge));
        // }
        /// DEBUG
        ///********************************************
        return input;
    }
    double getParallelOffset() const override;
    double getParallelOffsetCount() const override;
    Vertex getVertex(const int index) const override;
    QPointF getVertexPos(const int index)const override;
    QPointF getCenterPos() const override;
    QString getName() const override;
    uint getVertexCount() const;
public:
    int type() const override {
        return GraphicsItemType::Polyline;
    }

public:
    QRectF boundingRect() const override;
    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem* option,
               QWidget* widget) override;
private:
    ///
    std::vector < Vertex > m_vertexList;
    std::vector < std::shared_ptr < QGraphicsItem>> m_paintItemList;
    ///
    /// \brief m_offset
    double m_offset  = 0;
    uint m_offsetCount = 0;
    std::vector < std::shared_ptr < PolylineItem>> m_offsetItemList;
};

inline std::shared_ptr<PolylineItem> FromCavcForm(cavc::Polyline<double> polyline)
{
    auto item = std::make_shared<PolylineItem>();
    // item->LineType = LineType::offsetItem;
    for (size_t i = 0; i < polyline.size(); ++i) {
        auto newPoint = QPointF(polyline.vertexes()[i].x(), polyline.vertexes()[i].y());
        auto newBulge = (i > 0) ? polyline.vertexes()[i - 1].bulge()
                                : polyline.vertexes()[polyline.size() - 1].bulge();
        double newAngle = 0;
        getAngleFromBulge(newBulge * (-1), newAngle);
        item->addVertex(newPoint, newAngle);
    }
    if (polyline.isClosed()) {
        auto newPoint = QPointF(polyline.vertexes()[0].x(), polyline.vertexes()[0].y());
        auto idx = polyline.size() - 1;
        auto newBulge = polyline.vertexes()[idx].bulge();
        double newAngle = 0;
        getAngleFromBulge(newBulge * (-1), newAngle);
        item->addVertex(newPoint, newAngle);
    }
    return item;
}

#endif // POLYLINEITEM_H
