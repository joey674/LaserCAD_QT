#ifndef ARCITEM_H
#define ARCITEM_H

#include "protocol.h"
#include "laseritem.h"

class ArcItem: public LaserItem
{
public: // 只用于暂存一些计算变量，不属于状态，不参与实际更新
    int operateIndex = 0;// 绘制时记录当前第几次点击
    QPointF assistPoint =QPointF{};//绘制时记录中间的暂存点
public:
    ArcItem();
    /// \brief control
    /// 直接修改 控制对象
    /// 这里面所有函数结束都要调用animate
    void editVertex(const int &index, const QPointF& point, const double& angle);
    void createParallelOffset(const double& offset, const double& offsetNum) override;
    void rotate(const double& angle) override;
    /// \brief update
    /// 更新函数 不能主动调用update；都在animate中调用
    void updateParallelOffset() override;
    void updatePaintItem() override;
    void animate() override;
    /// \brief get info
    /// 只获取信息
    double getParallelOffset()override;
    double getParallelOffsetNum()override;
    Vertex getVertex(const int& index)override;
    QPointF getVertexPos(const int& index)override;
    QPointF getCenterPos() override;
    QString getName() override;
    /// \brief reload
    enum { Type = 6271 };
    int type() const override;
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
private:
    ///
    std::array<Vertex,2> VertexPair = {Vertex{QPointF{0,0}, 0},Vertex{QPointF{0,0}, 0}};
    std::shared_ptr<QGraphicsPathItem> PaintItem;
    ///
    double offset  = 0;
    int offsetNum = 1;
    std::vector<std::shared_ptr<ArcItem>> offsetItemList;
};

#endif // ARCITEM_H
