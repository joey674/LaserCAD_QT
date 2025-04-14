#ifndef POLYLINEITEM_H
#define POLYLINEITEM_H

#include "graphicsitem.h"
#include "utils.hpp"
#include "logger.h"
#include <polylineoffset.hpp>

class PolylineItem: public GraphicsItem {
public:
    PolylineItem();
    PolylineItem(const PolylineItem& other):
        m_vertexList(other.m_vertexList),
        m_offset(other.m_offset),
        m_offsetNum(other.m_offsetNum) {
        for (int i = 0; i < this->getVertexCount(); ++i) {
            m_vertexList[i].point = other.getVertexPos(i);
        }
        // 更新出来paintitem和offsetitem
        this->animate();
    }

    std::shared_ptr < GraphicsItem > copy() const  override {
        return std::make_shared < PolylineItem > (PolylineItem(*this));
    }
/// ********************
/// \brief control
/// 直接修改 控制对象
/// 这里面所有函数结束都要调用animate
/// ********************
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
        this->m_offsetNum = offsetNum;
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
/// ********************
/// \brief update
/// 更新函数 不能主动调用update；都在animate中调用
/// ********************
public:
    bool updateParallelOffset() override {
        if (m_vertexList.size() < 2) {
            return false;
        }
        if (this->m_offset == 0) {
            return true;
        }
        this->m_offsetItemList.clear();
        DEBUG_MSG("");
        DEBUG_MSG("update parallel offset");
        double inputOuputSign = -1;
        for (int offsetIndex = 1; offsetIndex <= this->m_offsetNum; offsetIndex++) {
            // 输入cavc库
            cavc::Polyline < double > input;
            for (int i = 0; i < this->getVertexCount(); ++i) {
                auto p1 = m_vertexList[i].point;
                auto p2 = m_vertexList[i + 1].point;
                auto angle = (i + 1 <= this->getVertexCount()) ?
                             m_vertexList[i + 1].angle : 0;
                if (angle > 180.01 || angle < -180.01) {
                    auto sign = angle > 0 ? 1 : -1;
                    input.addVertex(p1.x(), p1.y(), sign * inputOuputSign); /*先走180度*/
                    QPointF intersectPoint = QPointF{};
                    double newAngle = 0;
                    double newBulge = 0;
                    getIntersectPoint(p1, p2, angle, 180, intersectPoint);
                    newAngle = angle - sign * 180;
                    getBulgeFromAngle(newAngle, newBulge);
                    input.addVertex(intersectPoint.x(), intersectPoint.y(), newBulge * inputOuputSign);
                    DEBUG_VAR(intersectPoint.x());
                    DEBUG_VAR(intersectPoint.y());
                    DEBUG_VAR(newAngle);
                } else {
                    double bulge = 0;
                    getBulgeFromAngle(angle, bulge);
                    input.addVertex(p1.x(), p1.y(), bulge * inputOuputSign);
                    // DEBUG_VAR(p1.x());
                    // DEBUG_VAR(p1.y());
                    // DEBUG_VAR(bulge);
                }
            }
            // input.isClosed() = false;
            input.isClosed() = false;
            std::vector < cavc::Polyline < double>> results = cavc::parallelOffset(input, this->m_offset * offsetIndex);
            // 获取结果
            for (const auto& polyline : results) {
                auto item = std::make_shared < PolylineItem > ();
                // item->LineType = LineType::offsetItem;
                for (size_t i = 0; i < polyline.size(); ++i) {
                    auto newPoint = QPointF(polyline.vertexes()[i].x(), polyline.vertexes()[i].y());
                    auto newBulge = (i > 0) ?  polyline.vertexes()[i - 1].bulge()
                                    :   polyline.vertexes()[polyline.size() - 1].bulge();
                    double newAngle = 0;
                    getAngleFromBulge(newBulge * inputOuputSign, newAngle);
                    item->addVertex(newPoint, newAngle);
                    // DEBUG_VAR(newPoint.x());
                    // DEBUG_VAR(newPoint.y());
                    // DEBUG_VAR(newBulge);
                }
                this->m_offsetItemList.push_back(std::move(item));
            }
        }
        return true;
    }
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
/// ********************
/// \brief get info
/// 只获取信息
/// ********************
public:
    double getParallelOffset() const override;
    double getParallelOffsetNum() const override;
    Vertex getVertex(const int index) const override;
    QPointF getVertexPos(const int index)const override;
    QPointF getCenterPos() const override;
    QString getName() const override;
    double getVertexCount();
/// ********************
/// \brief overload
/// 重载基于QGraphicsitem的一些性质
/// ********************
public:
    enum { Type = ItemTypeId::Polyline };
    int type() const override;
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
/// ********************
/// private variable
/// ********************
private:
    ///
    std::vector < Vertex > m_vertexList;
    std::vector < std::shared_ptr < QGraphicsItem>> m_paintItemList;
    ///
    /// \brief m_offset
    double m_offset  = 0;
    uint m_offsetNum = 0;
    std::vector < std::shared_ptr < PolylineItem>> m_offsetItemList;
};


#endif // POLYLINEITEM_H
