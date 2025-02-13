#ifndef VARIANTLINEITEM_H
#define VARIANTLINEITEM_H

#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include "manager.h"

class VariantLineItem: public QGraphicsItem
{
public:
    enum LineType
    {
        Line,
        Arc
    };
    static bool  arcDirectionIsClockwise;

    VariantLineItem(QPointF point)
    {
        this->NodeList.push_back(point);
        this->TmpLine = std::make_unique<QGraphicsLineItem>();
        auto tmpline = dynamic_cast<QGraphicsLineItem*>(this->TmpLine.get());
        tmpline->setPen(QPen(Qt::black, 1));
        QLineF line(point,point);
        tmpline->setLine(line);
    };

    void setLine(QPointF point, bool isCreate,LineType lineType)
    {
        prepareGeometryChange();

        if (isCreate == true)
        {
            this->NodeList.push_back(point);
            this->ItemList.push_back(std::move(this->TmpLine));
        }
        else
        {
            this->NodeList.back() = point;
        }

        auto startPoint = *(NodeList.rbegin()+1);
        auto endPoint = *(NodeList.rbegin());

        switch (lineType)
        {
        case LineType::Line:
        {
            this->TmpLine = std::make_unique<QGraphicsLineItem>();
            auto tmpline = dynamic_cast<QGraphicsLineItem*>(this->TmpLine.get());
            tmpline->setPen(QPen(Qt::black, 1));

            if (Manager::getIns().IsXHold)
                endPoint = QPointF(endPoint.x(), startPoint.y());
            else if (Manager::getIns().IsYHold)
                endPoint = QPointF(startPoint.x(), endPoint.y());

            NodeList.back() = endPoint;

            QLineF line(startPoint, endPoint);
            tmpline->setLine(line);
            break;
        };
        case LineType::Arc:
        {
            this->TmpLine = std::make_unique<QGraphicsPathItem>();
            auto tmparc = dynamic_cast<QGraphicsPathItem*>(this->TmpLine.get());
            tmparc->setPen(QPen(Qt::black, 1));

            double radius = QLineF(startPoint, endPoint).length()/2;
            QPointF centerPoint((startPoint.x()+endPoint.x())/2, (startPoint.y()+endPoint.y())/2);
            QRectF newRect(QPointF(centerPoint.x() - radius, centerPoint.y() - radius),
                           QPointF(centerPoint.x() + radius, centerPoint.y() + radius));
            QLineF diameterLine(startPoint, endPoint);
            double angle = diameterLine.angle();
            QPainterPath path;
            path.arcMoveTo(newRect, angle);
            path.arcTo(newRect, angle, arcDirectionIsClockwise ? 180 : -180);
            tmparc->setPath(path);
            break;
        }
        }

        update();
    }

    QPointF getCenter()
    {
         if (this->NodeList.empty())
            return QPointF(0,0);

         QPointF centerPoint = this->NodeList[0];
         for (auto& item: this->NodeList)
        {
             centerPoint = QPointF(
                 (centerPoint.x()+item.x())/2,
                 (centerPoint.y()+item.y())/2);
         }
         return centerPoint;
    }

    QRectF boundingRect() const override
    {
        if (this->ItemList.empty())
            return this->TmpLine->boundingRect();

        QRectF newRect = this->TmpLine->boundingRect();
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

        if (!this->TmpLine) return;

        for (auto& item: this->ItemList)
        {
            item->paint(painter, option, widget);
        }
        this->TmpLine->paint(painter, option, widget);
    }

private:
    std::unique_ptr<QGraphicsItem> TmpLine;
    QPen Pen = QPen(Qt::black, 1);

    std::vector<QPointF> NodeList;
    std::vector<std::unique_ptr<QGraphicsItem>> ItemList;
    std::vector<std::unique_ptr<QGraphicsItem>> FilledItemList;
};

#endif // VARIANTLINEITEM_H
