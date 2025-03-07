#include "header/CavalierContours/polyline.hpp"
#include "header/CavalierContours/polylineoffset.hpp"
#include "arcitem.h"
#include "logger.h"

ArcItem::ArcItem()
{
    INFO_MSG("create ArcItem");
    DEBUG_VAR(this->getUUID());
}

void ArcItem::editVertex(const int &index, const QPointF &point, const double &angle)
{
    if (index >1) return;

    QPointF pos = point - this->scenePos();
    this->VertexPair[index] = Vertex{pos,angle};

    animate();
}

void ArcItem::createParallelOffset(const double &offset, const double &offsetNum)
{
    this->offset = offset;
    this->offsetNum = offsetNum;
    this->animate();
}

void ArcItem::rotate(double angle)
{

}

void ArcItem::updateParallelOffset()
{
    // if (this->offset == 0) return;
    // this->offsetItemList.clear();
    // qDebug() << "update offset";

    // for (int offsetIndex = 1;offsetIndex <= this->offsetNum; offsetIndex++)
    // {
    //     cavc::Polyline<double> input;

    //     input.addVertex(
    //         this->VertexPair[0].point.x(),
    //         this->VertexPair[0].point.y(),
    //             this->VertexPair[1].angle
    //         );
    //     input.addVertex(
    //         this->VertexPair[1].point.x(),
    //         this->VertexPair[1].point.y(),
    //         this->VertexPair[0].angle
    //         );

    //     input.isClosed() = false;
    //     std::vector<cavc::Polyline<double>> results = cavc::parallelOffset(input, this->offset * offsetIndex);

    //     for (const auto& polyline : results) {
    //         auto item = std::make_shared<ArcItem>();
    //         item->LineType = LineType::offsetItem;

    //         for (size_t i = 0; i < 2; ++i) {
    //             auto newPoint = QPointF(polyline.vertexes()[i].x(), polyline.vertexes()[i].y());
    //             auto newangle = (i > 0) ?  polyline.vertexes()[i-1].angle()
    //                                     :   polyline.vertexes()[polyline.size()-1].angle();

    //             // qDebug() << " add vertex " << i << ":" << newPoint << newangle ;
    //             item->editVertex(i,newPoint,newangle);
    //         }
    //         this->offsetItemList.push_back(std::move(item));
    //     }
    // }
}

void ArcItem::updatePaintItem()
{
    // 这里实时把vertexlist里的点信息更新到itemlist里；然后paint函数会绘制itemlist里的东西
    this->PaintItem = nullptr;

    auto v1 = VertexPair[0].point;
    auto v2 = VertexPair[1].point;
    double angle = VertexPair[1].angle;

    QPainterPath arcPath = createArcPath(v1,v2,angle);
    this->PaintItem = std::make_unique<QGraphicsPathItem>(arcPath);
    this->PaintItem->setPen(defaultLinePen);
}

void ArcItem::animate()
{
    prepareGeometryChange();

    // 这里实时把vertexlist里的点信息更新到itemlist里；然后paint函数会绘制itemlist里的东西
    this->updatePaintItem();

    // 更新offsetitem
    this->updateParallelOffset();

    update();
}

double ArcItem::getParallelOffset()
{
    return this->offset;
}

double ArcItem::getParallelOffsetNum()
{
    return this->offsetNum;
}

Vertex ArcItem::getVertex(const int &index)
{
    if (index > 1) assert("false index:only 0,1");
    return VertexPair[index];
}

QPointF ArcItem::getCenterPos()
{
    // 返回弧的圆心 不是中心
}

void ArcItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(widget);

    // 设置option删去offset线段的选框
    QStyleOptionGraphicsItem optionx(* option);
    optionx.state &= ~QStyle::State_Selected;

    // 绘制线段
    this->PaintItem->paint(painter, &optionx, widget);

    // 绘制编辑原点
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    painter->drawEllipse(assistPoint, 1, 1);
    for (const auto &vertex : VertexPair)
    {
        if (this->offsetNum>0)
        {
            painter->setBrush(Qt::red);
            painter->drawEllipse(vertex.point, 1, 1);
        }
        else
        {
            painter->setBrush(Qt::blue);
            painter->drawEllipse(vertex.point, 1, 1);
        }
    }

    // 绘制offset
    for (auto& item: this->offsetItemList)
        item->paint(painter, &optionx, widget);
}

int ArcItem::type() const
{
    return Type;
}

QRectF ArcItem::boundingRect() const
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

QPointF ArcItem::getVertexPos(const int &index)
{
    if (index > 1) assert("false index:only 0,1");
    QPointF point = VertexPair[index].point;
    QPointF pos = point + this->scenePos();

    return pos;
}
