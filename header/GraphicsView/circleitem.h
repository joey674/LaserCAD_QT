#ifndef CIRCLEITEM_H
#define CIRCLEITEM_H

// #include "protocol.h"
// #include "graphicsitem.h"
// #include "logger.h"

// class CircleItem: public GraphicsItem {
// public:
//     CircleItem();
//     /// \brief control
//     /// 直接修改 控制对象
//     /// 这里面所有函数结束都要调用animate
//     void editVertex(const int index, const QPointF point, const double angle = 0) override {
//         if (index >= 1) {
//             WARN_MSG("index can only be 0 for point");
//             return;
//         }
//         QPointF pos = point - this->scenePos();
//         this->m_vertex.point = pos;
//         animate();
//     }
//     void setParallelOffset(const double offset, const double offsetNum) override // TODO
//     {}
//     void setCenterPos(const QPointF point) override {
//         DEBUG_MSG("use point setCenterPos");
//         QPointF currentCenter = this->getCenterPos();
//         QPointF offset = point - currentCenter;
//         this->setPos(this->pos() + offset);
//         this->animate();
//     }
//     void rotate(const double angle) override // TODO
//     {}
//     /// \brief update
//     /// 更新函数 不能主动调用update；都在animate中调用
//     void updateParallelOffset() override// TODO
//     {}
//     void updatePaintItem() override {
//         // 这里实时把vertexlist里的点信息更新到itemlist里；然后paint函数会绘制itemlist里的东西
//         this->m_paintItem = nullptr;
//     }
//     /// \brief get info
//     /// 只获取信息
//     double getParallelOffset()override {
//         return this->m_offset;
//     }
//     double getParallelOffsetNum()override {
//         return this->m_offsetNum;
//     }
//     Vertex getVertex(const int index)override {
//         if (index > 0) {
//             WARN_MSG("false index:only 0 for point");
//         }
//         return m_vertex;
//     }
//     QPointF getVertexPos(const int index)override {
//         if (index > 1) {
//             WARN_MSG("false index:only 0");
//         }
//         QPointF point = m_vertex.point;
//         QPointF pos = point + this->scenePos();
//         return pos;
//     }
//     QPointF getCenterPos() override {
//         auto center = QPointF{};
//         center = m_vertex.point;
//         auto posOffset = this->pos();
//         return center + posOffset;
//     }
//     QString getName() override {
//         return "PointItem";
//     }
//     /// \brief reload
//     enum { Type = ItemTypeId::Point };
//     int type() const override {
//         return Type;
//     }
//     QRectF boundingRect() const override {
//         if (!this->m_paintItem) {
//             return QRectF();
//         }
//         QRectF newRect = m_paintItem->boundingRect();
//         // newRect = newRect.adjusted(
//         //     -abs(this->m_offset)*this->m_offsetNum - 1,
//         //     -abs(this->m_offset)*this->m_offsetNum - 1,
//         //     abs(this->m_offset)*this->m_offsetNum + 1,
//         //     abs(this->m_offset)*this->m_offsetNum + 1);
//         return newRect;
//     }
//     void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override {
//         Q_UNUSED(widget);
//         // 设置option删去offset线段的选框
//         QStyleOptionGraphicsItem optionx(* option);
//         optionx.state &= ~QStyle::State_Selected;
//         // 绘制线段
//         this->m_paintItem->paint(painter, &optionx, widget);
//         // 绘制offset
//         for (auto& item : this->m_offsetItemList) {
//             item->paint(painter, &optionx, widget);
//         }
//     }
// private:
//     ///
//     std::array < Vertex, 2 > m_vertexPair = {Vertex{QPointF{0, 0}, 0}, Vertex{QPointF{0, 0}, 0}};
//     std::shared_ptr < QGraphicsEllipseItem > m_paintItem;
//     ///
//     double m_offset  = 0;
//     int m_offsetNum = 1;
//     std::vector < std::shared_ptr < CircleItem>> m_offsetItemList;
// };

#endif // CIRCLEITEM_H
