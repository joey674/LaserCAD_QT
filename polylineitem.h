#ifndef POLYLINEITEM_H
#define POLYLINEITEM_H

#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <QPainter>

class PolylineItem: public QGraphicsItem
{
public:
    PolylineItem(QLineF line)
    {
        this->TmpLine = std::make_unique<QGraphicsLineItem>(line);
        this->TmpLine->setPen(this->Pen);
        this->NodeList.push_back(line.p1());
    };

    void setLine(QLineF line, bool isNewLine)
    {
        prepareGeometryChange();

        if (isNewLine == false)
        {
            this->TmpLine->setLine(line);
        }
        else
        {
            this->NodeList.push_back(line.p1());
            this->ItemList.push_back(std::move(this->TmpLine));

            this->TmpLine = std::make_unique<QGraphicsLineItem>(line);
            this->TmpLine->setPen(this->Pen);
        }

        update();
    }

    void setPolylineFlags(GraphicsItemFlags flags)
    {
        if (this->ItemList.empty())
        {
             this->TmpLine->setFlags(flags);
            return;
        }

        for (auto& item: this->ItemList)
        {
            item->setFlags(flags);
        }
    }

    QLineF tmpline()
    {
        return this->TmpLine->line();
    }

    QRectF boundingRect() const override
    {
        QRectF newRect = this->TmpLine->boundingRect();
        if (this->ItemList.empty())
            return newRect;


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
        this->TmpLine->paint(painter, option, widget);
    }

private:
    QGraphicsScene *Scene;
    std::unique_ptr<QGraphicsLineItem> TmpLine;
    QPen Pen = QPen(Qt::black, 1);

    std::vector<QPointF> NodeList;
    std::vector<std::unique_ptr<QGraphicsItem>> ItemList;
    std::vector<std::unique_ptr<QGraphicsItem>> FilledItemList;
};


#endif // POLYLINEITEM_H
