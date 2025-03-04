#ifndef ARCITEM_H
#define ARCITEM_H

#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <QPainter>
#include <QDebug.h>
#include <QStyleOptionGraphicsItem>
#include "protocol.h"
#include "laseritem.h"

class ArcItem: public LaserItem
{
public: // 只用于暂存一些计算变量，不属于状态，不参与实际更新
    int operateIndex = 0;
    QPointF assistPoint =QPointF{};
public:
    ArcItem();
    /// \brief control
    /// 直接修改 控制对象
    /// 这里面所有函数结束都要调用animate
    void editVertex(const int &index, const QPointF& point, const double& angle) override;
    void createParallelOffset(const double& offset, const double& offsetNum) override;
    void rotate(double angle);
    /// \brief update
    /// 更新函数 不能主动调用update；都在animate中调用
    void updateParallelOffset() override;
    void updatePaintItem();
    void animate() override;
    /// \brief get info
    /// 只获取信息
    double getParallelOffset()override;
    double getParallelOffsetNum()override;
    Vertex getVertex(const int& index)override;
    QPointF getVertexPos(const int& index)override;
    QPointF getCenterPos() override;
    /// \brief reload
    enum { Type = 6271 };
    int type() const override;
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
private:
    std::array<Vertex,2> VertexPair = {Vertex{QPointF{0,0}, 0},Vertex{QPointF{0,0}, 0}};
    std::shared_ptr<QGraphicsPathItem> PaintItem;

    double offset  = 0;
    int offsetNum = 1;
    std::vector<std::shared_ptr<ArcItem>> offsetItemList;
};

#endif // ARCITEM_H
