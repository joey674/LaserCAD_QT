#include "polylineitem.h"
#include "logger.h"
#include <polyline.hpp>
#include <polylineoffset.hpp>
#include "utils.hpp"

PolylineItem::PolylineItem() {
    // INFO_MSG("create PolylineItem, uuid: "+this->getUUID());
}

bool PolylineItem::updateParallelOffset() {
    if (m_vertexList.size() < 2) {
        return false;
    }
    if (this->m_offset == 0) {
        return true;
    }
    this->m_offsetItemList.clear();
    for (int offsetIndex = 1; offsetIndex <= this->m_offsetNum; offsetIndex++) {
        // 输入cavc库
        auto input = this->getCavConForm();
        input.isClosed() = false;
        // input.isClosed() = true;
        std::vector < cavc::Polyline < double>> results = cavc::parallelOffset(input,
            this->m_offset
            * offsetIndex);
        // 获取结果
        for (const auto &polyline : results) {
            auto item = FromCavConForm(polyline);
            this->m_offsetItemList.push_back(std::move(item));
        }
    }
    return true;
}

double PolylineItem::getParallelOffset()const {
    return this->m_offset;
}

double PolylineItem::getParallelOffsetNum()const {
    return  this->m_offsetNum;
}

Vertex PolylineItem::getVertex(const int index) const {
    return  m_vertexList[index];
}

QPointF PolylineItem::getVertexPos(const int index)const {
    QPointF point = m_vertexList[index].point;
    QPointF pos = point + this->scenePos();
    return  pos;
}

QPointF PolylineItem::getCenterPos() const {
    if (m_vertexList.empty()) {
        return QPointF(0, 0);
    }
    qreal minX = std::numeric_limits < int >::max();
    qreal minY = std::numeric_limits < int >::max();
    qreal maxX = std::numeric_limits < int >::min();
    qreal maxY = std::numeric_limits < int >::min();
    for (auto& item : m_vertexList) {
        minX = std::min(minX, item.point.x() + this->scenePos().x());
        minY = std::min(minY, item.point.y() + this->scenePos().y());
        maxX = std::max(maxX,  item.point.x() + this->scenePos().x());
        maxY = std::max(maxY,  item.point.y() + this->scenePos().y());
    }
    QPointF pos = QPointF((maxX + minX) / 2, (maxY + minY) / 2);
    return pos;
}



QString PolylineItem::getName() const {
    return "PolylineItem";
}

uint PolylineItem::getVertexCount() const {
    return m_vertexList.size();
}


QRectF PolylineItem::boundingRect() const {
    if (this->m_paintItemList.empty()) {
        return QRectF();
    }
    QRectF newRect = m_paintItemList[0]->boundingRect();
    for (auto& item : this->m_paintItemList) {
        qreal minX = std::min(newRect.left(), item->boundingRect().left());
        qreal minY = std::min(newRect.top(), item->boundingRect().top());
        qreal maxX = std::max(newRect.right(), item->boundingRect().right());
        qreal maxY = std::max(newRect.bottom(), item->boundingRect().bottom());
        newRect = QRectF(QPointF(minX, minY), QPointF(maxX, maxY));
    }
    newRect = newRect.adjusted(
                  -abs(this->m_offset) * this->m_offsetNum - 1,
                  -abs(this->m_offset) * this->m_offsetNum - 1,
                  abs(this->m_offset) * this->m_offsetNum + 1,
                  abs(this->m_offset) * this->m_offsetNum + 1);
    return newRect;
}

void PolylineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    // 设置option删去offset线段的选框
    QStyleOptionGraphicsItem optionx(* option);
    optionx.state &= ~QStyle::State_Selected;
    // 绘制线段
    // for (auto& item : this->m_paintItemList) {
    //     item->paint(painter, &optionx, widget);
    // }
    for (auto& item : this->m_paintItemList) {
        item->paint(painter, option, widget);
    }
    // 绘制拖拽原点
    painter->setPen(Qt::NoPen);
    for (const auto &vertex : m_vertexList) {
        if (this->m_offsetNum > 0) {
            painter->setBrush(Qt::red);
            painter->drawEllipse(vertex.point, DisplayPointSize.first, DisplayPointSize.second);
        } else {
            painter->setBrush(Qt::blue);
            painter->drawEllipse(vertex.point, DisplayPointSize.first, DisplayPointSize.second);
        }
    }
    // 绘制offset
    for (auto& item : this->m_offsetItemList) {
        item->paint(painter, &optionx, widget);
    }
}

std::shared_ptr < PolylineItem > FromCavConForm(cavc::Polyline < double > polyline) {
    auto item = std::make_shared < PolylineItem > ();
    // item->LineType = LineType::offsetItem;
    for (size_t i = 0; i < polyline.size(); ++i) {
        auto newPoint = QPointF(polyline.vertexes()[i].x(), polyline.vertexes()[i].y());
        auto newBulge = (i > 0) ? polyline.vertexes()[i - 1].bulge()
                        : polyline.vertexes()[polyline.size() - 1].bulge();
        double newAngle = 0;
        getAngleFromBulge(newBulge * (-1), newAngle);
        item->addVertex(newPoint, newAngle);
        // DEBUG_VAR(newPoint.x());
        // DEBUG_VAR(newPoint.y());
        // DEBUG_VAR(newBulge);
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
