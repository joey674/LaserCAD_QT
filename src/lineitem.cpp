#include "lineitem.h"

LineItem::LineItem() {}

bool LineItem::editVertex(const int index, const QPointF point, const double angle) {
    if (index > 1) {
        return false;
    }
    QPointF pos = point - this->scenePos();
    this->m_vertexPair[index].point = pos;
    animate();
    return true;
}



bool LineItem::setParallelOffset(const double offset, const double offsetNum) {
    this->m_offset = offset;
    this->m_offsetNum = offsetNum;
    this->animate();
    return true;
}

bool LineItem::setCenterPos(const QPointF point) {
    QPointF currentCenter = this->getCenterPos();
    QPointF offset = point - currentCenter;
    this->setPos(this->pos() + offset);
    this->animate();
    return true;
}

bool LineItem::rotate(const double angle) {
    return true;
}

bool LineItem::updateParallelOffset() {
    if (this->m_offset == 0 || this->m_offsetNum == 0) {
        return true;
    }
    this->m_offsetItemList.clear();
    for (int offsetIndex = 1; offsetIndex <= this->m_offsetNum; offsetIndex++) {
        // 输入cavc库
        cavc::Polyline < double > input = this->getCavConForm();
        input.isClosed() = false;
        std::vector < cavc::Polyline < double>> results = cavc::parallelOffset(input, this->m_offset * offsetIndex);
        // 获取结果
        for (const auto& polyline : results) {
            auto item = FromCavConForm(polyline);
            this->m_offsetItemList.push_back(std::move(item));
        }
    }
    return true;
}

bool LineItem::updatePaintItem() {
    // 这里实时把vertexlist里的点信息更新到itemlist里；然后paint函数会绘制itemlist里的东西
    this->m_paintItem = nullptr;
    auto v1 = m_vertexPair[0].point;
    auto v2 = m_vertexPair[1].point;
    this->m_paintItem = std::make_shared < QGraphicsLineItem > (
                            QLineF(v1, v2)
                        );
    this->m_paintItem->setPen(this->getPen());
    return true;
}

cavc::Polyline < double > LineItem::getCavConForm() const {
    // 输入cavc库
    cavc::Polyline < double > input;
    auto p1 = m_vertexPair[0].point;
    auto p2 = m_vertexPair[1].point;
    input.addVertex(p1.x(), p1.y(), 0);
    input.addVertex(p2.x(), p2.y(), 0);
    return input;
}

double LineItem::getParallelOffset()const {
    return this->m_offset;
}

double LineItem::getParallelOffsetNum()const {
    return this->m_offsetNum;
}

Vertex LineItem::getVertex(const int index)const {
    if (index > 1) {
        assert("false index:only 0,1");
    }
    return m_vertexPair[index];
}



QString LineItem::getName()const {
    return "LineItem";
}


QRectF LineItem::boundingRect() const {
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



QPointF LineItem::getVertexPos(const int index)const {
    if (index > 1) {
        assert("false index:only 0,1");
    }
    QPointF point = m_vertexPair[index].point;
    QPointF pos = point + this->scenePos();
    return pos;
}

QPointF LineItem::getCenterPos()const {
    auto center = QPointF{};
    center = (m_vertexPair[0].point + m_vertexPair[1].point) / 2;
    auto posOffset = this->pos();
    return center + posOffset;
}
