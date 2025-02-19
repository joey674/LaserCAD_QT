#ifndef POLYLINEITEM_H
#define POLYLINEITEM_H

#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <QPainter>
#include <QDebug.h>
#include "utils.h"
#include "header/CavalierContours/polyline.hpp"
#include "header/CavalierContours/polylineoffset.hpp"

class PolylineItem: public QGraphicsItem
{
public:
    struct Vertex
    {
        QPointF point;
        double bulge;
    };

    enum LineType
    {
        OriginItem,
        offsetItem,
    };

    PolylineItem()
    {
    }

    ///
    /// \brief control 这里面所有函数结束都要调用animate
    ///
    void addVertex(QPointF point, double bulge)
    {
        Vertex newVertex = {point,bulge};
        VertexList.push_back(newVertex);

        animate();
    }

    void editVertex(int index, QPointF point, double bulge)
    {
        QPointF pos = point - this->scenePos();
        this->VertexList[index] = Vertex{pos,bulge};

        animate();
    }

    void deleteVetex(int index)
    {
        VertexList.erase(VertexList.begin() +index);

        animate();
    }

    void createParallelOffset(double offset, double offsetNum)
    {
        this->offset = offset;
        this->offsetNum = offsetNum;
        this->animate();
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
            for (int i = 0; i < this->getSize(); ++i)
            {
                // 这里好像addvertex的时候加的bulge是下一个点的; 并且我们之间的bulge是相反的;
                input.addVertex(
                    this->VertexList[i].point.x(),
                    this->VertexList[i].point.y(),
                    (i + 1 < this->getSize()) ?
                        this->VertexList[i+1].bulge
                                              : this->VertexList[0].bulge
                    );
            }
            input.isClosed() = false;
            std::vector<cavc::Polyline<double>> results = cavc::parallelOffset(input, this->offset * offsetIndex);

            for (const auto& polyline : results) {
                auto item = std::make_unique<PolylineItem>();
                item->LineType = LineType::offsetItem;

                for (size_t i = 0; i < polyline.size(); ++i) {
                    auto newPoint = QPointF(polyline.vertexes()[i].x(), polyline.vertexes()[i].y());
                    auto newBulge = (i > 0) ?  polyline.vertexes()[i-1].bulge()
                                            :   polyline.vertexes()[polyline.size()-1].bulge();

                    // qDebug() << " add vertex " << i << ":" << newPoint << newBulge ;
                    item->addVertex(newPoint,newBulge);
                }
                this->offsetItemList.push_back(std::move(item));
            }
        }
    }

    void updateItemList()
    {
        // 这里实时把vertexlist里的点信息更新到itemlist里；然后paint函数会绘制itemlist里的东西
        ItemList.clear();
        for (size_t i = 0; i < VertexList.size()-1; ++i)
        {
            Vertex& v1 = VertexList[i];
            Vertex& v2 = VertexList[i+1];

            if (std::abs(v2.bulge) < 1e-6)
            {
                auto lineItem = std::make_unique<QGraphicsLineItem>(
                    QLineF(v1.point, v2.point)
                    );
                lineItem->setPen(Pen);
                ItemList.push_back(std::move(lineItem));
            }
            else
            {
                QPainterPath arcPath = createArcPath(v1.point, v2.point, v2.bulge);
                auto pathItem = std::make_unique<QGraphicsPathItem>(arcPath);
                pathItem->setPen(Pen);
                ItemList.push_back(std::move(pathItem));
            }
        }
    }

    void animate()
    {
        prepareGeometryChange();

        if (VertexList.size()<2) return;

        // 这里实时把vertexlist里的点信息更新到itemlist里；然后paint函数会绘制itemlist里的东西
        this->updateItemList();

        // 更新offsetitem
        this->updateParallelOffset();

        update();
    }

    ///
    /// \brief get info
    ///
    int getSize()
    {
        return VertexList.size();
    }

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
        return VertexList[index];
    }

    QPointF getVertexPos(int index)
    {
        QPointF point = VertexList[index].point;
        QPointF pos = point + this->scenePos();

        return pos;
    }

    QPointF getCenterPos()
    {
        if (this->VertexList.empty())
            return QPointF(0,0);

        QPointF centerPoint = this->VertexList[0].point;
        for (auto& item: this->VertexList)
        {
            centerPoint = QPointF(
                (centerPoint.x()+item.point.x())/2,
                (centerPoint.y()+item.point.y())/2);
        }
        QPointF pos = centerPoint + this->scenePos();

        return pos;
    }

    ///
    /// \brief reload
    ///
    enum { Type = 6270 };

    int type() const override
    {
        return Type;
    }

    QRectF boundingRect() const override
    {
        if (this->ItemList.empty())
            return QRectF();

        QRectF newRect = ItemList[0]->boundingRect();
        for (auto& item: this->ItemList)
        {
            qreal minX = std::min(newRect.left(), item->boundingRect().left());
            qreal minY = std::min(newRect.top(), item->boundingRect().top());
            qreal maxX = std::max(newRect.right(), item->boundingRect().right());
            qreal maxY = std::max(newRect.bottom(), item->boundingRect().bottom());

            newRect = QRectF(QPointF(minX, minY), QPointF(maxX, maxY));
        }
        newRect = newRect.adjusted(-abs(offset)*offsetNum,-abs(offset)*offsetNum,abs(offset)*offsetNum,abs(offset)*offsetNum);
        return newRect;
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override
    {
        Q_UNUSED(option);
        Q_UNUSED(widget);

        // 绘制线段
        for (auto& item: this->ItemList)
            item->paint(painter, option, widget);

        // 绘制拖拽原点
        painter->setPen(Qt::NoPen);
        painter->setBrush(Qt::red);
        for (const auto &vertex : VertexList)
        {
            if (this->LineType ==LineType::OriginItem)
                painter->drawEllipse(vertex.point, 1.5, 1.5);
        }

        // 绘制offset
        for (auto& item: this->offsetItemList)
            item->paint(painter, option, widget);
    }

private:
    LineType LineType = LineType::OriginItem;
    QPen Pen = QPen(Qt::black, 1);

    std::vector<Vertex> VertexList;
    std::vector<std::unique_ptr<QGraphicsItem>> ItemList;

    double offset  = 0;
    int offsetNum = 1;
    std::vector<std::unique_ptr<PolylineItem>> offsetItemList;
};


#endif // POLYLINEITEM_H
