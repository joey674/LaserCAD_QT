#ifndef POLYLINEITEM_H
#define POLYLINEITEM_H

#include "laseritem.h"
#include "manager.h"
#include "logger.h"

class PolylineItem: public LaserItem
{
public:
    PolylineItem();
    /// \brief control
    /// 直接修改 控制对象
    /// 这里面所有函数结束都要调用animate
    void addVertex(const QPointF& point, const double& angle);
    void editVertex(const int &index, const QPointF& point, const double& angle);
    void deleteVetex(const int &index);
    void setParallelOffset(const double& offset, const double& offsetNum) override;
    // void setCenterPos(const QPointF& point) override {
    //     QPointF currentCenter = this->getCenterPos(); // 当前中心点（scene 坐标）
    //     QPointF offset = point - currentCenter;       // 位移向量
    //     this->setPos(this->pos() + offset);
    // };
    void rotate(const double& angle) override;
    /// \brief update
    /// 更新函数 不能主动调用update；都在animate中调用
    void updateParallelOffset() override;
    void updatePaintItem() override;
    void animate() override;
    /// \brief get info
    /// 只获取信息
    double getParallelOffset() override;
    double getParallelOffsetNum() override;
    Vertex getVertex(const int& index) override;
    QPointF getVertexPos(const int& index)override;
    QPointF getCenterPos() override;
    QString getName() override;
    double getVertexCount();
    /// \brief reload
    /// 重载QGraphicsItem类的成员函数
    enum { Type = 6270 };
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
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
