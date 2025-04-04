#include "polylineitem.h"
#include "logger.h"
#include "CavalierContours/polyline.hpp"
#include "CavalierContours/polylineoffset.hpp"
#include "graphicsmath.h"

PolylineItem::PolylineItem()
{
    // INFO_MSG("create PolylineItem, uuid: "+this->getUUID());
}

bool PolylineItem::addVertex(const QPointF point, const double angle)
{
    Vertex newVertex = {point,angle};
    m_vertexList.push_back(newVertex);

    animate();
    return true;
}

bool PolylineItem::editVertex(const int index, const QPointF point, const double angle)
{
    QPointF pos = point - this->scenePos();
    m_vertexList[index] = Vertex{pos,angle};

    animate();
    return true;
}

bool PolylineItem::deleteVetex(const int index)
{
    m_vertexList.erase(m_vertexList.begin() +index);

    animate();
    return true;
}

bool PolylineItem::setParallelOffset(const double offset, const double offsetNum)
{
    this->m_offset = offset;
    this->m_offsetNum = offsetNum;
    if (offsetNum < 0)
        FATAL_MSG("offset num must be positive");
    this->animate();
    return true;
}

bool PolylineItem::rotate(const double angle)
{

}

bool PolylineItem::updateParallelOffset()
{
    if (this->m_offset == 0) return true;
    this->m_offsetItemList.clear();
    DEBUG_MSG("");
    DEBUG_MSG("update parallel offset");

    double inputOuputSign = -1;

    for (int offsetIndex = 1;offsetIndex <= this->m_offsetNum; offsetIndex++)
    {
        // 输入cavc库
        cavc::Polyline<double> input;
        for (int i = 0; i < this->getVertexCount(); ++i)
        {
            auto p1 = m_vertexList[i].point;
            auto p2 = m_vertexList[i+1].point;
            auto angle = (i+1 <= this->getVertexCount())?
                             m_vertexList[i+1].angle:0;

            if (angle>180.01 || angle < -180.01)
            {
                auto sign = angle>0? 1:-1;
                input.addVertex(p1.x(),p1.y(), sign*inputOuputSign);/*先走180度*/

                QPointF intersectPoint = QPointF{};
                double newAngle = 0;
                double newBulge = 0;
                getIntersectPoint(p1,p2,angle,180,intersectPoint);
                newAngle = angle - sign*180;
                getBulgeFromAngle(newAngle,newBulge);
                input.addVertex(intersectPoint.x(),intersectPoint.y(), newBulge *inputOuputSign);

                DEBUG_VAR(intersectPoint.x());
                DEBUG_VAR(intersectPoint.y());
                DEBUG_VAR(newAngle);
            }else
            {
                double bulge = 0;
                getBulgeFromAngle(angle,bulge);
                input.addVertex(p1.x(),p1.y(), bulge *inputOuputSign);

                // DEBUG_VAR(p1.x());
                // DEBUG_VAR(p1.y());
                // DEBUG_VAR(bulge);
            }
        }
        input.isClosed() = false;
        std::vector<cavc::Polyline<double>> results = cavc::parallelOffset(input, this->m_offset * offsetIndex);


        // 获取结果
        for (const auto& polyline : results) {
            auto item = std::make_shared<PolylineItem>();
            // item->LineType = LineType::offsetItem;

            for (size_t i = 0; i < polyline.size(); ++i)
            {
                auto newPoint = QPointF(polyline.vertexes()[i].x(), polyline.vertexes()[i].y());
                auto newBulge = (i > 0) ?  polyline.vertexes()[i-1].bulge()
                                        :   polyline.vertexes()[polyline.size()-1].bulge();

                double newAngle = 0;
                getAngleFromBulge(newBulge *inputOuputSign,newAngle);
                item->addVertex(newPoint,newAngle);

                // DEBUG_VAR(newPoint.x());
                // DEBUG_VAR(newPoint.y());
                // DEBUG_VAR(newBulge);
            }
            this->m_offsetItemList.push_back(std::move(item));
        }
    }
    return true;
}

bool PolylineItem::updatePaintItem()
{
    // 这里实时把vertexlist里的点信息更新到itemlist里；然后paint函数会绘制itemlist里的东西
    m_paintItemList.clear();
    for (size_t i = 0; i < m_vertexList.size()-1; ++i)
    {
        QPointF v1 = m_vertexList[i].point;
        QPointF v2 = m_vertexList[i+1].point;
        double angle = m_vertexList[i+1].angle;

        if (std::abs(angle) < 1e-20)
        {
            auto lineItem = std::make_shared<QGraphicsLineItem>(
                QLineF(v1, v2)
                );
            lineItem->setPen(this->getPen());
            m_paintItemList.push_back(std::move(lineItem));
        }
        else
        {
            QPainterPath arcPath = createArcPath(v1,v2,angle);
            auto pathItem = std::make_shared<QGraphicsPathItem>(arcPath);
            pathItem->setPen(this->getPen());
            m_paintItemList.push_back(std::move(pathItem));
        }
    }
    return true;
}

bool PolylineItem::animate()
{
    prepareGeometryChange();

    if (m_vertexList.size()<2) return false;

    // 这里实时把vertexlist里的点信息更新到itemlist里；然后paint函数会绘制itemlist里的东西
    this->updatePaintItem();

    // 更新offsetitem
    this->updateParallelOffset();

    update();
    return true;
}



double PolylineItem::getParallelOffset()
{
     return this->m_offset;
}

double PolylineItem::getParallelOffsetNum()
{
    return  this->m_offsetNum;
}

Vertex PolylineItem::getVertex(const int index)
{
    return  m_vertexList[index];
}

QPointF PolylineItem::getVertexPos(const int index)
{
    QPointF point = m_vertexList[index].point;
    QPointF pos = point + this->scenePos();

    return  pos;
}



QString PolylineItem::getName()
{
    return "PolylineItem";
}

double PolylineItem::getVertexCount()
{
    return m_vertexList.size();
}



int PolylineItem::type() const
{
    return Type;
}

QRectF PolylineItem::boundingRect() const
{
    if (this->m_paintItemList.empty())
        return QRectF();

    QRectF newRect = m_paintItemList[0]->boundingRect();
    for (auto& item: this->m_paintItemList)
    {
        qreal minX = std::min(newRect.left(), item->boundingRect().left());
        qreal minY = std::min(newRect.top(), item->boundingRect().top());
        qreal maxX = std::max(newRect.right(), item->boundingRect().right());
        qreal maxY = std::max(newRect.bottom(), item->boundingRect().bottom());

        newRect = QRectF(QPointF(minX, minY), QPointF(maxX, maxY));
    }
    newRect = newRect.adjusted(
        -abs(this->m_offset)*this->m_offsetNum - 1,
        -abs(this->m_offset)*this->m_offsetNum - 1,
        abs(this->m_offset)*this->m_offsetNum + 1,
        abs(this->m_offset)*this->m_offsetNum + 1);
    return newRect;
}

void PolylineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    // 设置option删去offset线段的选框
    QStyleOptionGraphicsItem optionx(* option);
    optionx.state &= ~QStyle::State_Selected;

    // 绘制线段
    for (auto& item: this->m_paintItemList)
        item->paint(painter, &optionx, widget);

    // 绘制拖拽原点
    painter->setPen(Qt::NoPen);
    for (const auto &vertex : m_vertexList)
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
