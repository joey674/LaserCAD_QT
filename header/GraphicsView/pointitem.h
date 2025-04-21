#ifndef POINTITEM_H
#define POINTITEM_H

#include "protocol.h"
#include "graphicsitem.h"
#include "logger.h"

class PointItem: public GraphicsItem {
public:
    PointItem();
    PointItem(const PointItem &other)
        : GraphicsItem(other)
        , m_offset(other.m_offset)
        , m_offsetCount(other.m_offsetCount)
    {
        m_vertex = other.getVertex(0);
        // 更新出来paintitem和offsetitem
        this->animate();
    }
    std::shared_ptr < GraphicsItem > copy() const  override {
        return std::make_shared < PointItem > (PointItem(*this));
    }
public:
    bool setVertex(const int index, const Vertex vertex) override
    {
        if (index >= 1) {
            WARN_MSG("index can only be 0 for point");
            return false;
        }
        this->m_vertex.point = vertex.point - this->scenePos();
        this->m_vertex.angle = vertex.angle;
        animate();
        return true;
    }
    bool setParallelOffset(const double offset, const double offsetNum) override { // TODO
        return true;
    }
    bool setCenter(const QPointF point) override
    {
        DEBUG_MSG("use point setCenter");
        QPointF currentCenter = this->getCenter();
        QPointF offset = point - currentCenter;
        this->setPos(this->pos() + offset);
        this->animate();
        return true;
    }
    bool rotate(const double angle) override { // TODO
        return true;
    }
protected:
    bool updateParallelOffset() override { // TODO
        return true;
    }
    bool updatePaintItem() override {
        // 这里判断是不是为编辑模式 如果是的话就画一个大一点的圆
        auto pointSize = DisplayPointSize;
        if (m_isEditMode) {
            pointSize = EditPointSize;
        }
        // 这里实时把vertexlist里的点信息更新到itemlist里；然后paint函数会绘制itemlist里的东西
        this->m_paintItem = nullptr;
        this->m_paintItem = std::make_shared < QGraphicsEllipseItem > ();
        double rx = pointSize.first;
        double ry = pointSize.second;
        this->m_paintItem->setRect(QRectF(
                                       m_vertex.point.x() - rx,
                                       m_vertex.point.y() - ry,
                                       rx * 2,
                                       ry * 2));
        this->m_paintItem->setBrush(QBrush(Qt::red));
        this->m_paintItem->setPen(this->getPen());
        return true;
    }
public:
    cavc::Polyline<double> getCavcForm(bool inSceneCoord) const override
    {
        return cavc::Polyline < double > ();
    }
    double getParallelOffset() const override {
        return this->m_offset;
    }
    double getParallelOffsetCount() const override {
        return this->m_offsetCount;
    }
    Vertex getVertex(const int index) const override
    {
        if (index > 1) {
            WARN_MSG("false index:only 0");
        }
        QPointF point = m_vertex.point;
        double angle = m_vertex.angle;
        QPointF pos = point + this->scenePos();
        return Vertex{pos, angle};
    }
    QPointF getCenter() const override
    {
        auto center = QPointF{};
        center = m_vertex.point;
        auto posOffset = this->pos();
        return center + posOffset;
    }
    QString getName() const override {
        return "PointItem";
    }
public:
    int type() const override {
        return GraphicsItemType::Point;
    }
protected:
    QRectF boundingRect() const override {
        if (!this->m_paintItem) {
            return QRectF();
        }
        QRectF newRect = m_paintItem->boundingRect();
        // newRect = newRect.adjusted(
        //     -abs(this->m_offset)*this->m_offsetCount - 1,
        //     -abs(this->m_offset)*this->m_offsetCount - 1,
        //     abs(this->m_offset)*this->m_offsetCount + 1,
        //     abs(this->m_offset)*this->m_offsetCount + 1);
        return newRect;
    }
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override {
        Q_UNUSED(widget);
        // 设置option删去offset线段的选框
        QStyleOptionGraphicsItem optionx(* option);
        optionx.state &= ~QStyle::State_Selected;
        // 绘制线段
        this->m_paintItem->paint(painter, &optionx, widget);
        // 绘制offset
        for (auto& item : this->m_offsetItemList) {
            item->paint(painter, &optionx, widget);
        }
    }
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override {
        // 先执行父类
        QVariant result = GraphicsItem::itemChange(change, value);
        // 再执行自己的重载
        if (change == QGraphicsItem::ItemSelectedHasChanged) {
            bool selected = value.toBool();
            if (selected) {
                m_isEditMode = true;
            } else {
                m_isEditMode = false;
            }
            animate ();
        }
        return result;
    }
private:
    ///
    Vertex m_vertex = Vertex{QPointF{0, 0}, 0};
    bool m_isEditMode = false;
    std::shared_ptr < QGraphicsEllipseItem > m_paintItem;
    ///
    double m_offset  = 0;
    int m_offsetCount = 0;
    std::vector < std::shared_ptr < PointItem>> m_offsetItemList;
};

#endif // POINTITEM_H
