#include "arcitem.h"
#include "logger.h"


ArcItem::ArcItem() {
    // INFO_MSG("create ArcItem, uuid: "+this->getUUID());
}












void ArcItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(widget);
    // 设置option删去offset线段的选框
    QStyleOptionGraphicsItem optionx(* option);
    optionx.state &= ~QStyle::State_Selected;
    // 绘制线段
    this->m_paintItem->paint(painter, &optionx, widget);
    // 绘制编辑原点
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    for (const auto &vertex : m_vertexPair) {
        if (this->m_offsetNum > 0) {
            painter->setBrush(Qt::red);
            painter->drawEllipse(vertex.point, GeneralPointSize.first, GeneralPointSize.second);
        } else {
            painter->setBrush(Qt::blue);
            painter->drawEllipse(vertex.point, GeneralPointSize.first, GeneralPointSize.second);
        }
    }
    // 绘制offset
    for (auto& item : this->m_offsetItemList) {
        item->paint(painter, &optionx, widget);
    }
}

int ArcItem::type() const {
    return Type;
}

QRectF ArcItem::boundingRect() const {
    if (!this->m_paintItem) {
        return QRectF();
    }
    QRectF newRect = m_paintItem->boundingRect();
    newRect = newRect.adjusted(
                  -abs(this->m_offset) * this->m_offsetNum - 1,
                  -abs(this->m_offset) * this->m_offsetNum - 1,
                  abs(this->m_offset) * this->m_offsetNum + 1,
                  abs(this->m_offset) * this->m_offsetNum + 1);
    return newRect;
}


