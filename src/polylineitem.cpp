#include "polylineitem.h"
#include "logger.h"
#include "CavalierContours/polyline.hpp"
#include "CavalierContours/polylineoffset.hpp"
#include "graphicsmath.h"

PolylineItem::PolylineItem()
{
    // INFO_MSG("create PolylineItem, uuid: "+this->getUUID());
}

void PolylineItem::addVertex(const QPointF& point, const double& angle)
{
    Vertex newVertex = {point,angle};
    VertexList.push_back(newVertex);

    animate();
}

void PolylineItem::editVertex(const int &index, const QPointF& point, const double& angle)
{
    QPointF pos = point - this->scenePos();
    this->VertexList[index] = Vertex{pos,angle};

    animate();
}

void PolylineItem::deleteVetex(const int &index)
{
    VertexList.erase(VertexList.begin() +index);

    animate();
}

void PolylineItem::setParallelOffset(const double& offset, const double& offsetNum)
{
    this->offset = offset;
    this->offsetNum = offsetNum;
    if (offsetNum < 0)
        FATAL_MSG("offset num must be positive");
    this->animate();
}

void PolylineItem::rotate(const double& angle)
{

}

void PolylineItem::updateParallelOffset()
{
    if (this->offset == 0) return;
    this->offsetItemList.clear();
    DEBUG_MSG("");
    DEBUG_MSG("update parallel offset");

    double inputOuputSign = -1;

    for (int offsetIndex = 1;offsetIndex <= this->offsetNum; offsetIndex++)
    {
        // 输入cavc库
        cavc::Polyline<double> input;
        for (int i = 0; i < this->getVertexCount(); ++i)
        {
            auto p1 = this->VertexList[i].point;
            auto p2 = this->VertexList[i+1].point;
            auto angle = (i+1 <= this->getVertexCount())?
                             this->VertexList[i+1].angle:0;

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
        std::vector<cavc::Polyline<double>> results = cavc::parallelOffset(input, this->offset * offsetIndex);


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
            this->offsetItemList.push_back(std::move(item));
        }
    }
}

void PolylineItem::updatePaintItem()
{
    // 这里实时把vertexlist里的点信息更新到itemlist里；然后paint函数会绘制itemlist里的东西
    PaintItemList.clear();
    for (size_t i = 0; i < VertexList.size()-1; ++i)
    {
        QPointF v1 = VertexList[i].point;
        QPointF v2 = VertexList[i+1].point;
        double angle = VertexList[i+1].angle;

        if (std::abs(angle) < 1e-20)
        {
            auto lineItem = std::make_shared<QGraphicsLineItem>(
                QLineF(v1, v2)
                );
            lineItem->setPen(this->getPen());
            PaintItemList.push_back(std::move(lineItem));
        }
        else
        {
            QPainterPath arcPath = createArcPath(v1,v2,angle);
            auto pathItem = std::make_shared<QGraphicsPathItem>(arcPath);
            pathItem->setPen(this->getPen());
            PaintItemList.push_back(std::move(pathItem));
        }
    }
}

void PolylineItem::animate()
{
    prepareGeometryChange();

    if (VertexList.size()<2) return;

    // 这里实时把vertexlist里的点信息更新到itemlist里；然后paint函数会绘制itemlist里的东西
    this->updatePaintItem();

    // 更新offsetitem
    this->updateParallelOffset();

    update();
}



double PolylineItem::getParallelOffset()
{
     return this->offset;
}

double PolylineItem::getParallelOffsetNum()
{
    return  this->offsetNum;
}

Vertex PolylineItem::getVertex(const int& index)
{
    return  VertexList[index];
}

QPointF PolylineItem::getVertexPos(const int& index)
{
    QPointF point = VertexList[index].point;
    QPointF pos = point + this->scenePos();

    return  pos;
}

QPointF PolylineItem::getCenterPos()
{
    if (this->VertexList.empty())
        return QPointF(0,0);

    qreal minX = std::numeric_limits<int>::max();
    qreal minY = std::numeric_limits<int>::max();
    qreal maxX =std::numeric_limits<int>::min();
    qreal maxY =std::numeric_limits<int>::min();

    for (auto& item: this->VertexList)
    {
        minX = std::min(minX, item.point.x() + this->scenePos().x());
        minY = std::min(minY, item.point.y() + this->scenePos().y());
        maxX = std::max(maxX,  item.point.x() + this->scenePos().x());
        maxY = std::max(maxY,  item.point.y() + this->scenePos().y());
    }

    QPointF pos = QPointF((maxX+minX)/2,(maxY+minY)/2);

    return pos;
}

QString PolylineItem::getName()
{
    return "PolylineItem";
}

double PolylineItem::getVertexCount()
{
    return VertexList.size();
}

QVariant PolylineItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionHasChanged) {
        Manager::getIns().propertyMapFind(this->getUUID(),PropertyIndex::Position) = this->getCenterPos();
        // DEBUG_MSG(Manager::getIns().propertyMapFind(this->getUUID(),PropertyIndex::Position));
    }
    return QGraphicsItem::itemChange(change, value);
}

int PolylineItem::type() const
{
    return Type;
}

QRectF PolylineItem::boundingRect() const
{
    if (this->PaintItemList.empty())
        return QRectF();

    QRectF newRect = PaintItemList[0]->boundingRect();
    for (auto& item: this->PaintItemList)
    {
        qreal minX = std::min(newRect.left(), item->boundingRect().left());
        qreal minY = std::min(newRect.top(), item->boundingRect().top());
        qreal maxX = std::max(newRect.right(), item->boundingRect().right());
        qreal maxY = std::max(newRect.bottom(), item->boundingRect().bottom());

        newRect = QRectF(QPointF(minX, minY), QPointF(maxX, maxY));
    }
    newRect = newRect.adjusted(
        -abs(offset)*offsetNum - 1,
        -abs(offset)*offsetNum - 1,
        abs(offset)*offsetNum + 1,
        abs(offset)*offsetNum + 1);
    return newRect;
}

void PolylineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    // 设置option删去offset线段的选框
    QStyleOptionGraphicsItem optionx(* option);
    optionx.state &= ~QStyle::State_Selected;

    // 绘制线段
    for (auto& item: this->PaintItemList)
        item->paint(painter, &optionx, widget);

    // 绘制拖拽原点
    painter->setPen(Qt::NoPen);
    for (const auto &vertex : VertexList)
    {
        if (this->offsetNum>0)
        {
            painter->setBrush(Qt::red);
            painter->drawEllipse(vertex.point, editPointSize.first, editPointSize.second);
        }
        else
        {
            painter->setBrush(Qt::blue);
            painter->drawEllipse(vertex.point, editPointSize.first, editPointSize.second);
        }
    }

    // 绘制offset
    for (auto& item: this->offsetItemList)
        item->paint(painter, &optionx, widget);
}
