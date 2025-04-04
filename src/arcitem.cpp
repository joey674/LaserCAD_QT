#include "arcitem.h"
#include "logger.h"
#include "graphicsmath.h"

ArcItem::ArcItem()
{
    // INFO_MSG("create ArcItem, uuid: "+this->getUUID());
}

void ArcItem::editVertex(const int index, const QPointF point, const double angle)
{
    if (index >1) return;

    QPointF pos = point - this->scenePos();
    this->m_vertexPair[index] = Vertex{pos,angle};

    animate();
}

void ArcItem::setParallelOffset(const double offset, const double offsetNum)
{
    this->m_offset = offset;
    this->m_offsetNum = offsetNum;
    this->animate();
}

void ArcItem::setCenterPos(const QPointF point)
{
    DEBUG_MSG("use arc setCenterPos");
    QPointF currentCenter = this->getCenterPos();
    QPointF offset = point - currentCenter;
    this->setPos(this->pos() + offset);
    this->animate();
}

void ArcItem::rotate(const double angle)
{

}

void ArcItem::updateParallelOffset()
{
    // if (this->m_offset == 0) return;
    // this->m_offsetItemList.clear();
    // qDebug() << "update offset";

    // for (int offsetIndex = 1;offsetIndex <= this->m_offsetNum; offsetIndex++)
    // {
    //     cavc::Polyline<double> input;

    //     input.addVertex(
    //         this->m_vertexPair[0].point.x(),
    //         this->m_vertexPair[0].point.y(),
    //             this->m_vertexPair[1].angle
    //         );
    //     input.addVertex(
    //         this->m_vertexPair[1].point.x(),
    //         this->m_vertexPair[1].point.y(),
    //         this->m_vertexPair[0].angle
    //         );

    //     input.isClosed() = false;
    //     std::vector<cavc::Polyline<double>> results = cavc::parallelOffset(input, this->m_offset * offsetIndex);

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
    //         this->m_offsetItemList.push_back(std::move(item));
    //     }
    // }
}

void ArcItem::updatePaintItem()
{
    // 这里实时把vertexlist里的点信息更新到itemlist里；然后paint函数会绘制itemlist里的东西
    this->m_paintItem = nullptr;

    auto v1 = m_vertexPair[0].point;
    auto v2 = m_vertexPair[1].point;
    double angle = m_vertexPair[1].angle;

    QPainterPath arcPath = createArcPath(v1,v2,angle);
    this->m_paintItem = std::make_shared<QGraphicsPathItem>(arcPath);
    this->m_paintItem->setPen(this->getPen());
}


double ArcItem::getParallelOffset()
{
    return this->m_offset;
}

double ArcItem::getParallelOffsetNum()
{
    return this->m_offsetNum;
}

Vertex ArcItem::getVertex(const int index)
{
    if (index > 1) assert("false index:only 0,1");
    return m_vertexPair[index];
}

QPointF ArcItem::getCenterPos()
{
    auto center = QPointF{};
    double radius =0;
    getCircleFromTwoPointsAndAngle(this->m_vertexPair[0].point,this->m_vertexPair[1].point,this->m_vertexPair[1].angle,center,radius);

    auto posOffset = this->pos();
    return center+posOffset;
}

QString ArcItem::getName()
{
    return "ArcItem";
}

void ArcItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(widget);

    // 设置option删去offset线段的选框
    QStyleOptionGraphicsItem optionx(* option);
    optionx.state &= ~QStyle::State_Selected;

    // 绘制线段
    this->m_paintItem->paint(painter, &optionx, widget);

    // 绘制编辑原点
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    for (const auto &vertex : m_vertexPair)
    {
        if (this->m_offsetNum>0)
        {
            painter->setBrush(Qt::red);
            painter->drawEllipse(vertex.point, GeneralPointSize.first, GeneralPointSize.second);
        }
        else
        {
            painter->setBrush(Qt::blue);
            painter->drawEllipse(vertex.point, GeneralPointSize.first, GeneralPointSize.second);
        }
    }

    // 绘制offset
    for (auto& item: this->m_offsetItemList)
        item->paint(painter, &optionx, widget);
}

int ArcItem::type() const
{
    return Type;
}

QRectF ArcItem::boundingRect() const
{
    if (!this->m_paintItem)
        return QRectF();

    QRectF newRect = m_paintItem->boundingRect();

    newRect = newRect.adjusted(
        -abs(this->m_offset)*this->m_offsetNum - 1,
        -abs(this->m_offset)*this->m_offsetNum - 1,
        abs(this->m_offset)*this->m_offsetNum + 1,
        abs(this->m_offset)*this->m_offsetNum + 1);
    return newRect;
}

QPointF ArcItem::getVertexPos(const int index)
{
    if (index > 1) assert("false index:only 0,1");
    QPointF point = m_vertexPair[index].point;
    QPointF pos = point + this->scenePos();

    return pos;
}
