#include "lineitem.h"
#include "logger.h"

LineItem::LineItem() {}



void LineItem::setParallelOffset(const double offset, const double offsetNum)
{
    this->m_offset = offset;
    this->m_offsetNum = offsetNum;
    this->animate();
}

void LineItem::setCenterPos(const QPointF point)
{
    QPointF currentCenter = this->getCenterPos();
    QPointF offset = point - currentCenter;
    this->setPos(this->pos() + offset);
    this->animate();
}

void LineItem::rotate(const double angle)
{

}

void LineItem::updateParallelOffset()
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





double LineItem::getParallelOffset()
{
    return this->m_offset;
}

double LineItem::getParallelOffsetNum()
{
    return this->m_offsetNum;
}

Vertex LineItem::getVertex(const int index)
{
    if (index > 1) assert("false index:only 0,1");
    return m_vertexPair[index];
}



QString LineItem::getName()
{
    return "LineItem";
}



int LineItem::type() const
{
    return Type;
}

QRectF LineItem::boundingRect() const
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

QPointF LineItem::getVertexPos(const int index)
{
    if (index > 1) assert("false index:only 0,1");
    QPointF point = m_vertexPair[index].point;
    QPointF pos = point + this->scenePos();

    return pos;
}
