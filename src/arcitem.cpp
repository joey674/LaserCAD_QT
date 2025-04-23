#include "arcitem.h"
#include "logger.h"




QRectF ArcItem::boundingRect() const {
    if (!this->m_paintItem) {
        return QRectF();
    }
    QRectF newRect = m_paintItem->boundingRect();
    // 包含offsetItem
    newRect = newRect.adjusted(
                  -abs(this->m_offsetParams.offset) * this->m_offsetParams.offsetCount - 1,
                  -abs(this->m_offsetParams.offset) * this->m_offsetParams.offsetCount - 1,
                  abs(this->m_offsetParams.offset) * this->m_offsetParams.offsetCount + 1,
                  abs(this->m_offsetParams.offset) * this->m_offsetParams.offsetCount + 1);
    // 包含所有 copiedItem
    for (const auto &item : m_copiedItemList) {
        if (item) {
            newRect = newRect.united(item->boundingRect());
        }
    }
    return newRect;
}


