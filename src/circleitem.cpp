#include "circleitem.h"

void CircleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    // 设置option删去offset线段的选框
    QStyleOptionGraphicsItem optionx(* option);
    optionx.state &= ~QStyle::State_Selected;
    // 绘制线段
    // this->m_paintItem->paint(painter, &optionx, widget);
    this->m_paintItem->paint(painter, option, widget);
    // 绘制offset
    for (auto& item : this->m_offsetItemList) {
        item->paint(painter, &optionx, widget);
    }
}

QRectF CircleItem::boundingRect() const {
    if (!this->m_paintItem) {
        return QRectF();
    }
    QRectF newRect = m_paintItem->boundingRect();
    newRect = newRect.adjusted(
                  -abs(this->m_offset) * this->m_offsetCount - 1,
                  -abs(this->m_offset) * this->m_offsetCount - 1,
                  abs(this->m_offset) * this->m_offsetCount + 1,
                  abs(this->m_offset) * this->m_offsetCount + 1);
    return newRect;
}
