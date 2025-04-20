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
        m_offset(other.m_offset),
        m_offsetCount(other.m_offsetCount) {
        for (int i = 0; i < this->getVertexCount(); ++i) {
            m_vertexList[i] = other.getVertex(i);
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
    bool setVertex(const int index, const Vertex vertex) override
    {
        QPointF pos = vertex.point - this->scenePos();
        m_vertexList[index] = Vertex{pos, vertex.angle};
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
    bool setCenter(const QPointF point) override
    {
        DEBUG_MSG("use polyline setCenter");
        QPointF currentCenter = this->getCenter();
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
    cavc::Polyline<double> getCavcForm(bool inSceneCoord) const override
    {
        cavc::Polyline < double > input;
        int count = this->getVertexCount();
        for (int i = 0; i < count; ++i) {
            QPointF p1, p2;
            if (inSceneCoord) {
                p1 = this->getVertex(i).point;
                p2 = this->getVertex((i + 1) % count).point;
            } else {
                p1 = this->m_vertexList[i].point;
                p2 = this->m_vertexList[(i + 1) % count].point;
            }
            auto angle = this->m_vertexList[(i + 1) % count].angle;
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
        // 输出的结果我们的格式是没有ClosedForm的, 不会和cavc一样,设置isClosed的时候使用闭合bulge连接第一个点,而是默认全是开放的;
        // 如果直接输入我们自己的格式时, 最后一个点和第一个点一致说明闭合, 但是cavc会自动闭合这连个点, 就会认为这里时零向量报错;
        // 所以这里需要转换一下, 如果最后一个点和第一个点是一致的, 就说明这个图形是封闭的, 就把最后一个点删了
        if (this->m_vertexList[0].point == this->m_vertexList[count - 1].point) {
            auto &verts = input.vertexes();
            if (!verts.empty()) {
                verts.pop_back(); // 删除最后一个点
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
    QPointF getCenter() const override;
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
