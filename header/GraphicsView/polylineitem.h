#ifndef POLYLINEITEM_H
#define POLYLINEITEM_H

#include "graphicsitem.h"
#include "manager.h"
#include "logger.h"

class PolylineItem: public GraphicsItem
{
public:
    PolylineItem();
    /// \brief control
    /// 直接修改 控制对象
    /// 这里面所有函数结束都要调用animate
    void addVertex(const QPointF point, const double angle);
    void editVertex(const int &index, const QPointF point, const double angle);
    void deleteVetex(const int index);
    void setParallelOffset(const double offset, const double offsetNum) override;
    void setCenterPos(const QPointF point) override
    {
        DEBUG_MSG("use polyline setCenterPos" );
        QPointF currentCenter = this->getCenterPos();
        QPointF offset = point - currentCenter;

        DEBUG_VAR(point);
        QString msg = QString("curCenter: (%1, %2), offset: (%3, %4), this->pos: (%5, %6)")
                          .arg(currentCenter.x(), 0, 'f', 2)
                          .arg(currentCenter.y(), 0, 'f', 2)
                          .arg(offset.x(), 0, 'f', 2)
                          .arg(offset.y(), 0, 'f', 2)
                            .arg(this->pos().x(), 0, 'f', 2)
                            .arg(this->pos().y(), 0, 'f', 2);
        DEBUG_MSG(msg);

        this->setPos(this->pos() + offset);
        this->animate();
    };
    void rotate(const double angle) override;
    /// \brief update
    /// 更新函数 不能主动调用update；都在animate中调用
    void updateParallelOffset() override;
    void updatePaintItem() override;
    void animate() override;
    /// \brief get info
    /// 只获取信息
    double getParallelOffset() override;
    double getParallelOffsetNum() override;
    Vertex getVertex(const int index) override;
    QPointF getVertexPos(const int index)override;
    QPointF getCenterPos() override
    {
        if (this->VertexList.empty())
            return QPointF(0,0);

        qreal minX = std::numeric_limits<int>::max();
        qreal minY = std::numeric_limits<int>::max();
        qreal maxX =std::numeric_limits<int>::min();
        qreal maxY =std::numeric_limits<int>::min();

        for (auto& item: this->VertexList)
        {
            minX = std::min(minX, item.point.x() + this->scenePos().x());
            minY = std::min(minY, item.point.y() + this->scenePos().y());
            maxX = std::max(maxX,  item.point.x() + this->scenePos().x());
            maxY = std::max(maxY,  item.point.y() + this->scenePos().y());
        }

        QPointF pos = QPointF((maxX+minX)/2,(maxY+minY)/2);

        return pos;
    }
    QString getName() override;
    double getVertexCount();
    /// \brief reload
    /// 重载QGraphicsItem类的成员函数
    enum { Type = 6270 };
    int type() const override;
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
private:
    ///
    std::vector<Vertex> VertexList;
    std::vector<std::shared_ptr<QGraphicsItem>> PaintItemList;
    ///
    double offset  = 0;
    uint offsetNum = 0;
    std::vector<std::shared_ptr<PolylineItem>> offsetItemList;
};


#endif // POLYLINEITEM_H
