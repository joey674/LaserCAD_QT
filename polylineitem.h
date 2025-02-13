#ifndef POLYLINEITEM_H
#define POLYLINEITEM_H

#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <QPainter>
#include <QDebug.h>
#include "utils.h"

class PolylineItem: public QGraphicsItem
{
public:
    struct Vertex
    {
        QPointF point;
        double bulge;
    };

    PolylineItem()
    {

    }

    void addVertex(QPointF point, double bulge)
    {
        Vertex newVertex = {point,bulge};
        VertexList.push_back(newVertex);

        animate();
    }

    void editVertex(int index, QPointF point, double bulge)
    {
        VertexList[index] = Vertex{point,bulge};

        animate();
    }

    void deleteVetex(int index)
    {
        VertexList.erase(VertexList.begin() +index);

        animate();
    }

    void animate()
    {
        prepareGeometryChange();

        // qDebug() << "animate";
        if (VertexList.size()<2) return;

        ItemList.clear();
        for (size_t i = 0; i < VertexList.size()-1; ++i)
        {
            Vertex& v1 = VertexList[i];
            Vertex& v2 = VertexList[i+1];

            // qDebug() <<  v1.point << v1.bulge <<  v2.point << v2.bulge ;

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

        update();
    }

    int getSize()
    {
        return VertexList.size();
    }

    QPointF getPoint(int index)
    {
        if (index >= VertexList.size()) return QPointF(0,0);
        return VertexList[index].point;
    }

    QPointF getCenter()
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
        return centerPoint;
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
        return newRect;
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override
    {
        Q_UNUSED(option);
        Q_UNUSED(widget);

        for (auto& item: this->ItemList)
        {
            item->paint(painter, option, widget);
        }
    }

private:
    QPen Pen = QPen(Qt::black, 1);

    std::vector<Vertex> VertexList;
    std::vector<std::unique_ptr<QGraphicsItem>> ItemList;
};


#endif // POLYLINEITEM_H
