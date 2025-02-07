#ifndef VARIANTLINEITEM_H
#define VARIANTLINEITEM_H

#include <qgraphicsitem.h>
#include <qgraphicsscene.h>

class VariantLineItem: public QGraphicsItem
{
public:
    enum LineType {
        Line,
        Arc
    };

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
            path.arcTo(newRect, angle, 180);
            tmparc->setPath(path);
            break;
        }
        }

        update();
    }

    void setFlags(GraphicsItemFlags flags)
    {
        // if (this->ItemList.empty())
        // {
        //     this->TmpLine->setFlags(flags);
        //     this->TmpArc->setFlags(flags);
        //     return;
        // }

        // for (auto& item: this->ItemList)
        // {
        //     this->TmpLine->setFlags(flags);
        //     this->TmpArc->setFlags(flags);
        //     item->setFlags(flags);
        // }
    }

    QRectF boundingRect() const override
    {
        if (this->ItemList.empty())
            return QRectF(QPointF(0,0),QPointF(0,0));

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
    QGraphicsScene *Scene;
    std::unique_ptr<QGraphicsItem> TmpLine;
    QPen Pen = QPen(Qt::black, 1);

    std::vector<QPointF> NodeList;
    std::vector<std::unique_ptr<QGraphicsItem>> ItemList;
    std::vector<std::unique_ptr<QGraphicsItem>> FilledItemList;
};

#endif // VARIANTLINEITEM_H
