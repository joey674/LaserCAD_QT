#ifndef POLYLINEITEM_H
#define POLYLINEITEM_H

#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <QPainter>
#include <QDebug.h>
#include <QStyleOptionGraphicsItem>
#include "protocol.h"
#include "laseritem.h"

class PolylineItem: public LaserItem
{
public:
    PolylineItem();
    /// \brief control
    /// 直接修改 控制对象
    /// 这里面所有函数结束都要调用animate
    void addVertex(const QPointF& point, const double& angle) override;
    void editVertex(const int &index, const QPointF& point, const double& angle) override;
    void deleteVetex(const int &index) override;
    void createParallelOffset(const double& offset, const double& offsetNum) override;
    void rotate(const double& angle) override;
    /// \brief update
    /// 更新函数 不能主动调用update；都在animate中调用
    void updateParallelOffset() override;
    void updateItemList() override;
    void animate() override;
    /// \brief get info
    /// 只获取信息
    double getSize();
    double getParallelOffset() override;
    double getParallelOffsetNum() override;
    Vertex getVertex(const int& index) override;
    QPointF getVertexPos(const int& index)override ;
    QPointF getCenterPos() override;
    QString getName() override;
    /// \brief reload
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
