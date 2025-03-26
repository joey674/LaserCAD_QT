#include "drawmanager.h"
#include "manager.h"
#include "scenemanager.h"
#include "keyboardmanager.h"
#include "protocol.h"
#include "graphicsmath.h"


DrawManager DrawManager::ins;

void DrawManager::resetTmpItemStatus()
{
    this->polygonEdgeNum = 3;
    this->tmpCircle = NULL;
    this->tmpPolyline = NULL;
    this->tmpArc = NULL;
    this->tmpRect = NULL;
    this->tmpSpiral = NULL;
    this->tmpPolygon = NULL;
    this->tmpEllipse = NULL;
}

void DrawManager::drawPolyline(QPointF pointCoordscene, MouseEvent event)
{
    if (!this->tmpPolyline && event == MouseEvent::LeftRelease)
    {
        // 设置其他元素不可动不可选中,且颜色为黑色;
        auto allItems = Manager::getIns().getItemsByLayer(0);
        for (const auto& item : allItems) {
            Manager::getIns().setItemSelectable(item,false);
            Manager::getIns().setItemMovable(item,false);
            Manager::getIns().setItemColor(item,DisplayColor);
        }

        this->tmpPolyline = std::make_shared<PolylineItem>();
        this->tmpPolyline->setColor(EditColor);
        SceneManager::getIns().scene->addItem(this->tmpPolyline.get());

        this->tmpPolyline->addVertex(pointCoordscene,0);
        this->tmpPolyline->addVertex(pointCoordscene,0);
    }
    else if  (this->tmpPolyline && event == MouseEvent::MouseMove)
    {
        int index = this->tmpPolyline->getSize()-1;
        if (!KeyboardManager::getIns().IsControlHold) // 绘制line
        {
            QPointF lastPoint = this->tmpPolyline->getVertex(index - 1).point;
            if (KeyboardManager::getIns().IsXHold)
                this->tmpPolyline->editVertex(index,QPointF(pointCoordscene.x(),lastPoint.y()),0);
            else if (KeyboardManager::getIns().IsYHold)
                this->tmpPolyline->editVertex(index,QPointF(lastPoint.x(),pointCoordscene.y()),0);
            else
                this->tmpPolyline->editVertex(index,pointCoordscene,0);
        }
        else //绘制arc
        {
            if (!KeyboardManager::getIns().IsCapsLocked)
                this->tmpPolyline->editVertex(index, pointCoordscene,180);
            else
                this->tmpPolyline->editVertex(index, pointCoordscene,-180);
        }
    }
    else if (this->tmpPolyline && event == MouseEvent::LeftRelease)
    {
        this->tmpPolyline->addVertex(pointCoordscene,0);
    }
    else if (this->tmpPolyline && event == MouseEvent::RightRelease)
    {
        Manager::getIns().addItem(std::move(this->tmpPolyline));
    }
}

void DrawManager::drawArc(QPointF pointCoordscene, MouseEvent event)
{
    if (!this->tmpArc && event == MouseEvent::LeftRelease)
    {
        // 设置其他元素不可动不可选中,且颜色为黑色;
        auto allItems = Manager::getIns().getItemsByLayer(0);
        for (const auto& item : allItems) {
            Manager::getIns().setItemSelectable(item,false);
            Manager::getIns().setItemMovable(item,false);
            Manager::getIns().setItemColor(item,DisplayColor);
        }

        this->tmpArc = std::make_shared<ArcItem>();
        this->tmpArc->setColor(EditColor);
        SceneManager::getIns().scene->addItem(this->tmpArc.get());

        this->tmpArc->operateIndex += 1;

        this->tmpArc->editVertex(0,pointCoordscene,0);
        this->tmpArc->editVertex(1,pointCoordscene,0);
    }
    else if  (this->tmpArc  &&  this->tmpArc->operateIndex == 1 && event == MouseEvent::MouseMove)
    {
        this->tmpArc->editVertex(1,pointCoordscene,180);
    }
    else if (this->tmpArc && this->tmpArc->operateIndex == 1 && event == MouseEvent::LeftRelease)
    {
        this->tmpArc->operateIndex += 1;
        this->tmpArc->assistPoint = pointCoordscene;
    }
    else if  (this->tmpArc && this->tmpArc->operateIndex == 2 && event == MouseEvent::MouseMove)
    {
        auto center = QPointF{};
        double  radius = 0;
        double  angle = 0;
        auto p1 =this->tmpArc->getVertex(0).point;
        auto p2 =this->tmpArc->assistPoint;
        auto p3 =this->tmpArc->getVertex(1).point;
        getAngleFromThreePoints(p1,p2,p3,angle);

        this->tmpArc->editVertex(1, pointCoordscene, angle);
    }
    else if (this->tmpArc && this->tmpArc->operateIndex == 2 && event == MouseEvent::LeftRelease)
    {
        this->tmpArc->setColor(DisplayColor);
        Manager::getIns().addItem(std::move(this->tmpArc));
    }
}

void DrawManager::drawCircle(QPointF pointCoordscene, MouseEvent event)
{
    // auto allItems = Manager::getIns().getItemsByLayer(0);
    // EditManager::getIns().setItemsStatus(false,true,true,allItems);

    // if (!this->tmpCircle && event == MouseEvent::LeftRelease)
    // {
    //     QRectF initialRect(pointCoordscene.x(), pointCoordscene.y(), 0, 0);
    //     this->tmpCircle = std::make_shared<QGraphicsEllipseItem>(initialRect);
    //     this->tmpCircle->setPen(QPen(Qt::black, 1));
    //     /// TODO
    //     /// setLayer
    //     SceneManager::getIns().scene->addItem(this->tmpCircle.get());
    // }
    // else if  (this->tmpCircle && event == MouseEvent::MouseMove)
    // {
    //     QRectF currentRect = this->tmpCircle->rect();
    //     QPointF center = currentRect.center();
    //     double radius = QLineF(center, pointCoordscene).length();
    //     QRectF newRect(center.x() - radius,
    //                    center.y() - radius,
    //                    2 * radius,
    //                    2 * radius);
    //     this->tmpCircle->setRect(newRect);
    //     this->tmpCircle->setTransformOriginPoint(center);
    // }
    // else if (this->tmpCircle && event == MouseEvent::LeftRelease)
    // {
    //     // Manager::getIns().addItem(std::move(this->tmpCircle));
    // }
}

void DrawManager::drawRect(QPointF pointCoordscene, MouseEvent event)
{
    //     auto allItems = Manager::getIns().getItemsByLayer(0);
    //     EditManager::getIns().setItemsStatus(false,false,false,allItems);

    //     /// TODO
    //     /// setLayer
    //     if (!this->tmpRect && event == MouseEvent::LeftRelease)
    //     {
    //         this->tmpRect = std::make_shared<QGraphicsRectItem>(pointCoordscene.x(), pointCoordscene.y(),0,0);
    //         this->tmpRect->setPen(QPen(Qt::black, 1));
    //         SceneManager::getIns().scene->addItem(this->tmpRect.get());
    //     }
    //     else if  (this->tmpRect && event == MouseEvent::MouseMove)
    //     {
    //         qreal width = pointCoordscene.x() - this->tmpRect->rect().topLeft().x();
    //         qreal height = pointCoordscene.y() - this->tmpRect->rect().topLeft().y();
    //         QRectF newRect(this->tmpRect->rect().topLeft().x(),this->tmpRect->rect().topLeft().y(),width,height);
    //         this->tmpRect->setRect(newRect);
    //     }
    //     else if (this->tmpRect && event == MouseEvent::LeftRelease) {
    //         this->tmpRect->setTransformOriginPoint(this->tmpRect->rect().center());
    //             // Manager::getIns().addItem(std::move(this->tmpRect));
    //     }
}

void DrawManager::drawSpiral(QPointF pointCoordscene, MouseEvent event)
{
    //     auto allItems = Manager::getIns().getItemsByLayer(0);
    //     EditManager::getIns().setItemsStatus(false,true,true,allItems);

    //     /* center：螺旋的中心点
    //     radius：螺旋的初始半径
    //     spacing：每圈的间距
    //     turns：螺旋的圈数*/
    //     /// TODO
    //     /// setLayer
    //     if (!this->tmpSpiral && event == MouseEvent::LeftRelease)
    //     {
    //         QPointF centerPoint  = pointCoordscene;
    //         this->tmpSpiral =  std::make_shared<QGraphicsPathItem>();
    //         this->tmpSpiral->setData(0,pointCoordscene);
    //         this->tmpSpiral->setPen(QPen(Qt::black, 1));
    //         SceneManager::getIns().scene->addItem(this->tmpSpiral.get());
    //     }
    //     else if  (this->tmpSpiral && event == MouseEvent::MouseMove)
    //     {
    //         // 这里都是设置了一个演示默认值；
    //         QPointF centerPoint = this->tmpSpiral->data(0).toPointF();
    //         QPointF endPoint = pointCoordscene;
    //         int turns = 3;
    //         double radius = QLineF(centerPoint,endPoint).length()/2;
    //         double spacing = QLineF(centerPoint,endPoint).length()/6;
    //         double dx = endPoint.x() - centerPoint.x();
    //         double dy = endPoint.y() - centerPoint.y();

    //         QPainterPath path;
    //         bool start = true;
    //         for (double theta = 0; theta < turns * 2 * M_PI; theta += 0.1)
    //         {
    //             double r = radius + spacing * theta / (2 * M_PI);
    //             double x = centerPoint.x() + r * cos(theta);
    //             double y = centerPoint.y() + r * sin(theta);

    //             if (start == true)
    //             {
    //                 path.moveTo(centerPoint.x() + r * cos(theta),centerPoint.y()+r* sin(theta));
    //                 start = false;
    //             } else
    //             {
    //                 path.lineTo(x, y);
    //             }
    //         }
    //         this->tmpSpiral->setTransformOriginPoint(centerPoint);
    //         this->tmpSpiral->setRotation(atan2(dy, dx)* 180 / M_PI);

    //         this->tmpSpiral->setPath(path);
    //     }
    //     else if (this->tmpSpiral && event == MouseEvent::LeftRelease)
    //     {
    //         // Manager::getIns().addItem(std::move(this->tmpSpiral));
    //     }
}

void DrawManager::drawPolygon(QPointF pointCoordscene, MouseEvent event)
{
    //     auto allItems = Manager::getIns().getItemsByLayer(0);
    //     EditManager::getIns().setItemsStatus(false,true,true,allItems);

    //     /// TODO
    //     /// setLayer
    //     if (!this->tmpPolygon && event == MouseEvent::LeftRelease)
    //     {
    //         this->tmpPolygon = std::make_shared<QGraphicsPolygonItem>();
    //         this->tmpPolygon->setData(0,pointCoordscene);
    //         this->tmpPolygon->setPen(QPen(Qt::black, 1));
    //         SceneManager::getIns().scene->addItem(this->tmpPolygon.get());
    //     }
    //     else if  (this->tmpPolygon && event == MouseEvent::MouseMove)
    //     {
    //         QPolygonF newPolygon;

    //         QPointF centerPoint = this->tmpPolygon->data(0).toPointF();
    //         double radius = QLineF(centerPoint,pointCoordscene).length();
    //         int edgeNum = polygonEdgeNum;

    //         double angleStep = 2 * M_PI / edgeNum;
    //         for (int i =0;i<edgeNum;i++) {
    //             double angle = i * angleStep - M_PI/2;
    //             QPointF Vertex(centerPoint.x()+radius*cos(angle),centerPoint.y()+radius*sin(angle));
    //             newPolygon << Vertex;
    //         }

    //         this->tmpPolygon->setPolygon(newPolygon);
    //         this->tmpPolygon->setTransformOriginPoint(centerPoint);
    //     }
    //     else if (this->tmpPolygon && event == MouseEvent::LeftRelease)
    //     {
    //         // Manager::getIns().addItem(std::move(this->tmpPolygon));
    //     }
}

void DrawManager::drawEllipse(QPointF pointCoordscene, MouseEvent event)
{
    // auto allItems = Manager::getIns().getItemsByLayer(0);
    // EditManager::getIns().setItemsStatus(false,true,true,allItems);

    // /// TODO
    // /// setLayer
    // if (!this->tmpEllipse && event == MouseEvent::LeftRelease)
    // {
    //     QRectF initialRect(pointCoordscene.x(), pointCoordscene.y(), 0, 0);
    //     this->tmpEllipse = std::make_shared<QGraphicsEllipseItem>(initialRect);
    //     this->tmpEllipse->setPen(QPen(Qt::black, 1));
    //     SceneManager::getIns().scene->addItem(this->tmpEllipse.get());
    // }
    // else if  (this->tmpEllipse && event == MouseEvent::MouseMove)
    // {
    //     if (!this->tmpEllipse->data(0).isValid()) {
    //         QRectF currentRect = this->tmpEllipse->rect();
    //         QPointF center = currentRect.center();
    //         double radius = QLineF(center, pointCoordscene).length();
    //         QRectF newRect(center.x() - radius,
    //                        center.y() - radius,
    //                        2 * radius,
    //                        2 * radius);
    //         this->tmpEllipse->setRect(newRect);
    //     } else {
    //         QPointF firstAxisPoint = this->tmpEllipse->data(0).toPointF();
    //         QRectF currentRect = this->tmpEllipse->rect();
    //         QPointF center = currentRect.center();

    //         double majorAxis = QLineF(center, firstAxisPoint).length();

    //         double dx = firstAxisPoint.x() - center.x();
    //         double dy = firstAxisPoint.y() - center.y();
    //         double theta = atan2(dy, dx);

    //         QLineF axisLine(center, firstAxisPoint);
    //         QLineF perpendicularLine = axisLine.normalVector();
    //         QPointF perpendicularPoint = perpendicularLine.p2();
    //         double minorAxis = QLineF(center, pointCoordscene).length();

    //         QRectF finalRect(center.x() - majorAxis, center.y() - minorAxis,
    //                          2 * majorAxis, 2 * minorAxis);

    //         this->tmpEllipse->setRect(finalRect);

    //         this->tmpEllipse->setTransformOriginPoint(center);
    //         this->tmpEllipse->setRotation(theta * 180 / M_PI);
    //     }

    // }
    // else if (this->tmpEllipse && event == MouseEvent::LeftRelease)
    // {
    //     if (!this->tmpEllipse->data(0).isValid())
    //     {
    //         this->tmpEllipse->setData(0,pointCoordscene);
    //     } else
    //     {
    //         // Manager::getIns().addItem(std::move(this->tmpEllipse));
    //     }
    // }
}

DrawManager &DrawManager::getIns()
{
    return ins;
}
