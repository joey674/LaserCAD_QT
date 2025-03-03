#ifndef ARCITEM_H
#define ARCITEM_H

#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <QPainter>
#include <QDebug.h>
#include <QStyleOptionGraphicsItem>
#include "protocol.h"
#include "header/CavalierContours/polyline.hpp"
#include "header/CavalierContours/polylineoffset.hpp"

class ArcItem: public QGraphicsItem
{
public:
    int operateIndex = 0;
    QPointF assistPoint =QPointF{};
public:
    ArcItem();

    // \brief control 这里面所有函数结束都要调用animate
    void editVertex(int index, QPointF point, float bulge)
    {
        if (index >1) return;

        QPointF pos = point - this->scenePos();
        this->VertexPair[index] = Vertex{pos,bulge};

        animate();
    }
    void createParallelOffset(double offset, double offsetNum)
    {
        this->offset = offset;
        this->offsetNum = offsetNum;
        this->animate();
    }
    void rotate(double angle)
    {

    }
    //\brief 更新函数 不能主动调用update；都在animate中调用
    void updateParallelOffset()
    {
        if (this->offset == 0) return;
        this->offsetItemList.clear();
        qDebug() << "update offset";

        for (int offsetIndex = 1;offsetIndex <= this->offsetNum; offsetIndex++)
        {
            cavc::Polyline<double> input;

            input.addVertex(
                this->VertexPair[0].point.x(),
                this->VertexPair[0].point.y(),
                    this->VertexPair[1].bulge
                );
            input.addVertex(
                this->VertexPair[1].point.x(),
                this->VertexPair[1].point.y(),
                this->VertexPair[0].bulge
                );

            input.isClosed() = false;
            std::vector<cavc::Polyline<double>> results = cavc::parallelOffset(input, this->offset * offsetIndex);

            for (const auto& polyline : results) {
                auto item = std::make_shared<ArcItem>();
                item->LineType = LineType::offsetItem;

                for (size_t i = 0; i < 2; ++i) {
                    auto newPoint = QPointF(polyline.vertexes()[i].x(), polyline.vertexes()[i].y());
                    auto newBulge = (i > 0) ?  polyline.vertexes()[i-1].bulge()
                                            :   polyline.vertexes()[polyline.size()-1].bulge();

                    // qDebug() << " add vertex " << i << ":" << newPoint << newBulge ;
                    item->editVertex(i,newPoint,newBulge);
                }
                this->offsetItemList.push_back(std::move(item));
            }
        }
    }
    void updatePaintItem()
    {
        // 这里实时把vertexlist里的点信息更新到itemlist里；然后paint函数会绘制itemlist里的东西
        this->PaintItem = nullptr;

        auto v1 = VertexPair[0].point;
        auto v2 = VertexPair[1].point;
        float bulge = VertexPair[1].bulge;

        QPainterPath arcPath = createArcPath(v1,v2,bulge);
        this->PaintItem = std::make_unique<QGraphicsPathItem>(arcPath);
        this->PaintItem->setPen(defaultLinePen);
    }
    void animate()
    {
        prepareGeometryChange();

        // 这里实时把vertexlist里的点信息更新到itemlist里；然后paint函数会绘制itemlist里的东西
        this->updatePaintItem();

        // 更新offsetitem
        this->updateParallelOffset();

        update();
    }
    /// \brief get info
    double getOffset()
    {
        return this->offset;
    }
    double getOffsetNum()
    {
        return this->offsetNum;
    }
    Vertex getVertex(int index)
    {
        if (index > 1) assert("false index:only 0,1");
        return VertexPair[index];
    }
    QPointF getVertexPos(int index)
    {
        if (index > 1) assert("false index:only 0,1");
        QPointF point = VertexPair[index].point;
        QPointF pos = point + this->scenePos();

        return pos;
    }
    QPointF getCenterPos()
    {
        // 返回弧的圆心 不是中心
    }
    //  reload
    enum { Type = 6271 };
    int type() const override
    {
        return Type;
    }
    QRectF boundingRect() const override
    {
        if (!this->PaintItem)
            return QRectF();

        QRectF newRect = PaintItem->boundingRect();

        newRect = newRect.adjusted(
            -abs(offset)*offsetNum - 1,
            -abs(offset)*offsetNum - 1,
            abs(offset)*offsetNum + 1,
            abs(offset)*offsetNum + 1);
        return newRect;
    }
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override
    {
        Q_UNUSED(widget);

        // 设置option删去offset线段的选框
        QStyleOptionGraphicsItem optionx(* option);
        optionx.state &= ~QStyle::State_Selected;

        // 绘制线段
        this->PaintItem->paint(painter, &optionx, widget);

        // 绘制拖拽原点
        // painter->setPen(Qt::NoPen);
        // painter->setBrush(Qt::red);
        // for (const auto &vertex : VertexPair)
        // {
        //     if (this->LineType ==LineType::OriginItem)
        //         painter->drawEllipse(vertex.point, 1, 1);
        // }

        // 绘制offset
        for (auto& item: this->offsetItemList)
            item->paint(painter, &optionx, widget);
    }
private:
    LineType LineType = LineType::OriginItem;

    std::array<Vertex,2> VertexPair = {Vertex{QPointF{0,0}, 0},Vertex{QPointF{0,0}, 0}};
    std::shared_ptr<QGraphicsPathItem> PaintItem;

    double offset  = 0;
    int offsetNum = 1;
    std::vector<std::shared_ptr<ArcItem>> offsetItemList;
};



#endif // ARCITEM_H
