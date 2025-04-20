#include "lineitem.h"

LineItem::LineItem() {}















cavc::Polyline < double > LineItem::getCavcForm() const {
    // 输入cavc库
    cavc::Polyline < double > input;
    auto p1 = m_vertexPair[0].point;
    auto p2 = m_vertexPair[1].point;
    input.addVertex(p1.x(), p1.y(), 0);
    input.addVertex(p2.x(), p2.y(), 0);
    return input;
}












QRectF LineItem::boundingRect() const {
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

void LineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    // 设置option删去offset线段的选框
    QStyleOptionGraphicsItem optionx(* option);
    optionx.state &= ~QStyle::State_Selected;
    // 绘制线段
    // this->m_paintItem->paint(painter, &optionx, widget);
    this->m_paintItem->paint(painter, option, widget);
    // 绘制编辑原点
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    for (const auto &vertex : m_vertexPair) {
        if (this->m_offsetCount > 0) {
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






