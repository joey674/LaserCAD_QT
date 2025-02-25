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
    ArcItem();

    ///
    /// \brief control 这里面所有函数结束都要调用animate
    ///
    void editVertex(int index, QPointF point, double bulge)
    {
        if (index >1) return;

        QPointF pos = point - this->scenePos();
        this->VertexPair[index] = Vertex{pos,bulge};

        this->center = calculateArcCenter(this->VertexPair[0].point,this->VertexPair[1].point,this->VertexPair[1].bulge, this->radius);
        qDebug() <<  "arc v1: "<< this->VertexPair[0].point;
        qDebug() <<  "arc v2: "<< this->VertexPair[1].point;
        qDebug() <<  "arc center: "<< this->center;
        qDebug() <<  "arc radius: "<< this->radius;

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

    ///
    /// \brief 更新函数 不能主动调用update；都在animate中调用
    ///
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

        Vertex& v1 = VertexPair[0];
        Vertex& v2 = VertexPair[1];

        QPainterPath arcPath = createArcPath();
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

    ///
    /// \brief get info
    ///
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
        QPointF point = VertexPair[0].point + VertexPair[1].point;
        QPointF pos = point + this->scenePos();

        return pos;
    }

    ///
    /// 计算
    ///
    QPainterPath createArcPath()
    {
        auto p1 = this->VertexPair[0].point;
        auto p2 = this->VertexPair[1].point;
        auto bulge = this->VertexPair[1].bulge;
        auto radius = this->radius;
        auto center = this->center;

        // 计算起始角度
        QLineF startVector(center, p1);
        double startAngle = startVector.angle();

        // 计算圆弧角度
        double sweepAngle = atan(std::abs(bulge)) * 4 * 180 / M_PI;
        if (bulge > 0) sweepAngle = -sweepAngle;

        qDebug() << "create arc path: startAngle:" << startAngle;
        qDebug() << "create arc path: sweepAngle:" << sweepAngle;

        // 创建圆弧路径
        QPainterPath path;
        path.moveTo(p1);
        path.arcTo(QRectF(center.x() - radius, center.y() - radius, 2 * radius, 2 * radius),
                   startAngle, sweepAngle);
        return path;
    }

    QPointF calculateArcCenter(QPointF p1, QPointF p2, double bulge, double &radius)
    {
        // 1. 计算 θ（弧度）
        double theta = atan(std::abs(bulge)) * 4;

        // 2. 计算弦长 AB
        double AB = sqrt(pow(p1.x() - p2.x(), 2) + pow(p1.y() - p2.y(), 2));

        // 3. 计算半径 R
        radius = (AB / 2) / sin(theta / 2);

        // 4. 计算 a 和 c
        double a = acos(std::min(1.0, (AB / 2) / radius));  // 防止浮点误差
        double c = atan2(p2.y() - p1.y(), p2.x() - p1.x()); // 计算 p1 到 p2 的角度

        // 5. 计算两个可能的圆心坐标
        double CX1 = p1.x() + cos(c + a) * radius;
        double CY1 = p1.y() + sin(c + a) * radius;
        double CX2 = p1.x() + cos(c - a) * radius;
        double CY2 = p1.y() + sin(c - a) * radius;

        // 6. 选择正确的圆心
        if (bulge < -1 || (bulge > 0 && bulge < 1)) {
            return QPointF(CX1, CY1);
        } else {
            return QPointF(CX2, CY2);
        }
    }

    ///
    /// \brief reload
    ///
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
        painter->setPen(Qt::NoPen);
        painter->setBrush(Qt::red);
        for (const auto &vertex : VertexPair)
        {
            if (this->LineType ==LineType::OriginItem)
                painter->drawEllipse(vertex.point, 1, 1);
        }

        // 绘制offset
        for (auto& item: this->offsetItemList)
            item->paint(painter, &optionx, widget);
    }


private:
    LineType LineType = LineType::OriginItem;

    double radius = 0;
    QPointF center = QPointF{};

    std::array<Vertex,2> VertexPair = {Vertex{QPointF{0,0}, 0},Vertex{QPointF{0,0}, 0}};
    std::shared_ptr<QGraphicsPathItem> PaintItem;

    double offset  = 0;
    int offsetNum = 1;
    std::vector<std::shared_ptr<ArcItem>> offsetItemList;
};



#endif // ARCITEM_H
