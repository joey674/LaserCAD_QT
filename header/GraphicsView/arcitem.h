#ifndef ARCITEM_H
#define ARCITEM_H

#include "graphicsitem.h"
#include "logger.h"
#include "polylineitem.h"
#include "protocol.h"
#include "utils.hpp"
#include <polylineoffset.hpp>

class ArcItem: public GraphicsItem {
    friend class ArcItem;
public:
    /// 绘制时记录当前第几次点击
    int drawStep = 0;
    /// 绘制时记录中间的暂存点
    QPointF assistPoint = QPointF{};
public:
    ArcItem();
    ArcItem(const ArcItem &other)
        : GraphicsItem(other)
        , m_vertexPair(other.m_vertexPair),
          m_offset(other.m_offset),
          m_offsetCount(other.m_offsetCount) {
        // m_vertexPair[0] = other.getVertex(0);
        // m_vertexPair[1] = other.getVertex(1);
        // 更新出来paintitem和offsetitem
        this->animate();
    }
    std::shared_ptr < GraphicsItem > copy() const  override {
        return std::make_shared < ArcItem > (ArcItem(*this));
    }
public:
    bool setVertex(const int index, const Vertex vertex) override {
        if (index > 1 || vertex.angle >= 360 || vertex.angle <= -360) {
            WARN_VAR(index);
            return false;
        }
        QPointF pos = vertex.point - this->scenePos();
        this->m_vertexPair[index] = Vertex{pos, vertex.angle};
        animate();
        return true;
    }
    bool setCenter(const QPointF point) override {
        //
        auto center = QPointF{};
        double radius = 0;
        getCircleFromTwoPointsAndAngle(this->m_vertexPair[0].point,
                                       this->m_vertexPair[1].point, this->m_vertexPair[1].angle, center, radius);
        auto posOffset = this->pos();
        QPointF currentCenter = center + posOffset;
        //
        QPointF offset = point - currentCenter;
        this->setPos(this->pos() + offset);
        this->animate();
        return true;
    }
    bool rotate(const double angle) override { //TODO
        return true;
    }
    bool setOffsetItem(const double offset, const double offsetNum) override {
        this->m_offset = offset;
        this->m_offsetCount = offsetNum;
        this->animate();
        return true;
    }
    bool setCopiedItem(QPointF dir, double spacing, int count) override {
        m_copiedItemList.clear();
        //
        QPointF unitOffset = dir * spacing;
        for (int i = 1; i <= count; ++i) {
            auto copiedItem = std::dynamic_pointer_cast < ArcItem > (this->copy());
            QPointF offset = unitOffset * i;
            copiedItem->m_vertexPair[0].point += offset;
            copiedItem->m_vertexPair[1].point += offset;
            copiedItem->animate();
            m_copiedItemList.push_back(copiedItem);
        }
        //
        this->animate();
        return true;
    }
    bool setCopiedItem(QPointF hVec, QPointF vVec,
                       double hSpacing, double vSpacing,
                       int hCount, int vCount,
                       int copiedOrder )  override {
        m_copiedItemList.clear();
        QPointF hOffset = hVec * hSpacing;
        QPointF vOffset = vVec * vSpacing;
        for (int row = 0; row < vCount; ++row) {
            for (int col = 0; col < hCount; ++col) {
                if (row == 0 && col == 0) {
                    continue;
                }
                auto copiedItem = std::dynamic_pointer_cast < ArcItem > (this->copy());
                if (!copiedItem) {
                    continue;
                }
                QPointF totalOffset = hOffset * col + vOffset * row;
                // 由于是再内部paint 所以是内部偏移 vertex, 而不是外部调用inScene的Vertex
                copiedItem->m_vertexPair[0].point += totalOffset;
                copiedItem->m_vertexPair[1].point += totalOffset;
                copiedItem->animate();
                m_copiedItemList.push_back(copiedItem);
            }
        }
        this->animate();
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
            input.isClosed() = false;
            std::vector < cavc::Polyline < double>> results = cavc::parallelOffset(input, this->m_offset * offsetIndex);
            // 获取结果
            for (const auto& polyline : results) {
                auto item = FromCavcForm(polyline);
                this->m_offsetItemList.push_back(std::move(item));
            }
        }
        return true;
    }
    bool updatePaintItem() override {
        // 这里实时把vertexlist里的点信息更新到itemlist里；然后paint函数会绘制itemlist里的东西
        this->m_paintItem = nullptr;
        auto v1 = m_vertexPair[0].point;
        auto v2 = m_vertexPair[1].point;
        double angle = m_vertexPair[1].angle;
        QPainterPath arcPath = createArcPath(v1, v2, angle);
        this->m_paintItem = std::make_shared < QGraphicsPathItem > (arcPath);
        this->m_paintItem->setPen(this->getPen());
        return true;
    }
    bool updateCopiedItem() override {
        //传进来的就是成品 就不用再转换了
        // for (auto &item : this->m_copiedItemList) {
        //     DEBUG_VAR(item->getVertex(0).point);
        //     DEBUG_VAR(item->getVertex(1).point);
        //     DEBUG_VAR(item->getVertex(1).angle);
        // }
        return true;
    };
public:
    cavc::Polyline < double > getCavcForm(bool inSceneCoord) const override {
        // 输入cavc库
        cavc::Polyline < double > input;
        QPointF p1, p2;
        if (inSceneCoord) {
            p1 = this->getVertex(0).point;
            p2 = this->getVertex(1).point;
        } else {
            p1 = m_vertexPair[0].point;
            p2 = m_vertexPair[1].point;
        }
        auto angle = m_vertexPair[1].angle;
        if (angle > 180.01 || angle < -180.01) {
            auto sign = angle > 0 ? 1 : -1;
            input.addVertex(p1.x(), p1.y(), sign * (-1)); /*先走180度*/
            QPointF intersectPoint = QPointF{};
            double newAngle = 0;
            double newBulge = 0;
            getIntersectPoint(p1, p2, angle, 180, intersectPoint);
            newAngle = angle - sign * 180;
            getBulgeFromAngle(newAngle, newBulge);
            input.addVertex(intersectPoint.x(),
                            intersectPoint.y(),
                            newBulge * (-1)); /*再走剩余的角度*/
            input.addVertex(p2.x(), p2.y(), 0); /*再添加尾部节点*/
            // DEBUG_VAR(intersectPoint.x());
            // DEBUG_VAR(intersectPoint.y());
            // DEBUG_VAR(newAngle);
        } else {
            double bulge = 0;
            getBulgeFromAngle(angle, bulge);
            input.addVertex(p1.x(), p1.y(), bulge * (-1));
            input.addVertex(p2.x(), p2.y(), 0);
            // DEBUG_VAR(p1.x());
            // DEBUG_VAR(p1.y());
            // DEBUG_VAR(bulge);
        }
        return input;
    }
    double getOffset() const override {
        return this->m_offset;
    }
    double getOffsetCount() const override {
        return this->m_offsetCount;
    }
    Vertex getVertex(const int index) const override {
        if (index > 1) {
            assert("false index:only 0,1");
        }
        QPointF point = m_vertexPair[index].point;
        double angle = m_vertexPair[index].angle;
        QPointF pos = point + this->scenePos();
        return Vertex{pos, angle};
    }
    QPointF getCenter() const override {
        auto center = QPointF{};
        double radius = 0;
        getCircleFromTwoPointsAndAngle(this->m_vertexPair[0].point,
                                       this->m_vertexPair[1].point, this->m_vertexPair[1].angle, center, radius);
        auto posOffset = this->pos();
        auto centerPos = center + posOffset;
        // DEBUG_VAR(centerPos);
        return centerPos;
    }
    QString getName() const override {
        return "ArcItem";
    }
    int type() const override {
        return GraphicsItemType::Arc;
    }
protected:
    QRectF boundingRect() const override;
    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem* option,
               QWidget* widget) override;
private:
    ///
    std::array < Vertex, 2 > m_vertexPair = {Vertex{QPointF{0, 0}, 0}, Vertex{QPointF{0, 0}, 0}};
    std::shared_ptr < QGraphicsPathItem > m_paintItem;
    ///
    double m_offset  = 0;
    int m_offsetCount = 0;
    std::vector < std::shared_ptr < PolylineItem>> m_offsetItemList;
    std::vector < std::shared_ptr < ArcItem>> m_copiedItemList;
};

#endif // ARCITEM_H
