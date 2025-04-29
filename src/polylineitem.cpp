#include "polylineitem.h"
#include <polyline.hpp>
#include <polylineoffset.hpp>

bool PolylineItem::updateOffsetItem()
{
    if (m_vertexList.size() < 2) {
        return false;
    }
    if (this->m_offsetParams.offset == 0) {
        return true;
    }
    this->m_offsetItemList.clear();
    for (int offsetIndex = 1; offsetIndex <= this->m_offsetParams.offsetCount; offsetIndex++) {
        // 输入cavc库
        auto input = this->getCavcForm(false);
        input.isClosed() = false;
        // input.isClosed() = true;
        std::vector<cavc::Polyline<double>> results
            = cavc::parallelOffset(input, this->m_offsetParams.offset * offsetIndex);
        // 获取结果
        for (const auto &polyline : results) {
            auto item = FromCavcForm(polyline);
            this->m_offsetItemList.push_back(std::move(item));
        }
    }
    return true;
}

Vertex PolylineItem::getVertexInScene(const int index) const
{
    QPointF point = m_vertexList[index].point;
    QPointF pos = point + this->scenePos();
    return Vertex{pos, m_vertexList[index].angle};
}

QPointF PolylineItem::getCenterInScene() const {
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

uint PolylineItem::getVertexCount() const
{
    return m_vertexList.size();
}




