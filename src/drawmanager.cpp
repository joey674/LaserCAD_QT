#include "drawmanager.h"
#include "manager.h"
#include "scenemanager.h"
#include "keyboardmanager.h"
#include "protocol.h"
#include "utils.hpp"


DrawManager DrawManager::ins;

void DrawManager::resetTmpItemStatus() {
    this->polygonEdgeNum = 3;
    this->tmpCircle = NULL;
    this->tmpPolyline = NULL;
    this->tmpArc = NULL;
    this->tmpPoint = NULL;
    this->tmpRect = NULL;
    this->tmpSpiral = NULL;
    this->tmpPolygon = NULL;
    this->tmpEllipse = NULL;
    this->tmpLine = NULL;
}

void DrawManager::drawPolyline(QPointF pointCoordscene, MouseEvent event) {
    if (!this->tmpPolyline && event == MouseEvent::LeftPress) {
        // 设置其他元素不可动不可选中 颜色为display
        auto allItems = Manager::getIns().getItemsByLayer(0);
        for (const auto& item : allItems) {
            Manager::getIns().setItemSelectable(item, false);
            Manager::getIns().setItemMovable(item, false);
            Manager::getIns().itemMapFind(item)->setPen(DISPLAY_PEN);
        }
        this->tmpPolyline = std::make_shared < PolylineItem > ();
        this->tmpPolyline->setPen(EDIT_PEN);
        SceneManager::getIns().scene->addItem(this->tmpPolyline.get());
        this->tmpPolyline->addVertex(pointCoordscene, 0);
        this->tmpPolyline->addVertex(pointCoordscene, 0);
    } else if  (this->tmpPolyline && event == MouseEvent::MouseMove) {
        int index = this->tmpPolyline->getVertexCount() - 1;
        if (!KeyboardManager::getIns().IsControlHold) { // 绘制line
            QPointF lastPoint = this->tmpPolyline->getVertexInScene(index - 1).point;
            if (KeyboardManager::getIns().IsXHold) {
                this->tmpPolyline->setVertexInScene(index,
                                                    Vertex{QPointF(pointCoordscene.x(), lastPoint.y()), 0});
            } else if (KeyboardManager::getIns().IsYHold) {
                this->tmpPolyline->setVertexInScene(index,
                                                    Vertex{QPointF(lastPoint.x(), pointCoordscene.y()), 0});
            } else {
                this->tmpPolyline->setVertexInScene(index, Vertex{pointCoordscene, 0});
            }
        } else { //绘制arc
            if (!KeyboardManager::getIns().IsCapsLocked) {
                this->tmpPolyline->setVertexInScene(index, Vertex{pointCoordscene, 180});
            } else {
                this->tmpPolyline->setVertexInScene(index, Vertex{pointCoordscene, -180});
            }
        }
    } else if (this->tmpPolyline && event == MouseEvent::LeftPress) {
        this->tmpPolyline->addVertex(pointCoordscene, 0);
    } else if (this->tmpPolyline && event == MouseEvent::RightPress) {
        Manager::getIns().addItem(std::move(this->tmpPolyline));
    }
}

void DrawManager::drawArc(QPointF pointCoordscene, MouseEvent event) {
    if (!this->tmpArc && event == MouseEvent::LeftPress) {
        // 设置其他元素不可动不可选中 颜色为display
        auto allItems = Manager::getIns().getItemsByLayer(0);
        for (const auto& item : allItems) {
            Manager::getIns().setItemSelectable(item, false);
            Manager::getIns().setItemMovable(item, false);
            Manager::getIns().itemMapFind(item)->setPen(DISPLAY_PEN);
        }
        this->tmpArc = std::make_shared < ArcItem > ();
        this->tmpArc->setPen(EDIT_PEN);
        SceneManager::getIns().scene->addItem(this->tmpArc.get());
        this->tmpArc->drawStep += 1;
        this->tmpArc->setVertexInScene(0, Vertex{pointCoordscene, 0});
        this->tmpArc->setVertexInScene(1, Vertex{pointCoordscene, 0});
    } else if (this->tmpArc && this->tmpArc->drawStep == 1 && event == MouseEvent::MouseMove) {
        this->tmpArc->setVertexInScene(1, Vertex{pointCoordscene, 180});
    } else if (this->tmpArc && this->tmpArc->drawStep == 1 && event == MouseEvent::LeftPress) {
        this->tmpArc->drawStep += 1;
        this->tmpArc->assistPoint = pointCoordscene;
    } else if (this->tmpArc && this->tmpArc->drawStep == 2 && event == MouseEvent::MouseMove) {
        auto center = QPointF{};
        double  radius = 0;
        double  angle = 0;
        auto p1 = this->tmpArc->getVertexInScene(0).point;
        auto p2 = this->tmpArc->assistPoint;
        auto p3 = this->tmpArc->getVertexInScene(1).point;
        getAngleFromThreePoints(p1, p2, p3, angle);
        this->tmpArc->setVertexInScene(1, Vertex{pointCoordscene, angle});
    } else if (this->tmpArc && this->tmpArc->drawStep == 2 && event == MouseEvent::LeftPress) {
        Manager::getIns().addItem(std::move(this->tmpArc));
    }
}

void DrawManager::drawLine(QPointF pointCoordscene, MouseEvent event) {
    if (!this->tmpLine && event == MouseEvent::LeftPress) {
        // 设置其他元素不可动不可选中 颜色为display
        auto allItems = Manager::getIns().getItemsByLayer(0);
        for (const auto& item : allItems) {
            Manager::getIns().setItemSelectable(item, false);
            Manager::getIns().setItemMovable(item, false);
            Manager::getIns().itemMapFind(item)->setPen(DISPLAY_PEN);
        }
        this->tmpLine = std::make_shared < LineItem > ();
        this->tmpLine->setPen(EDIT_PEN);
        SceneManager::getIns().scene->addItem(this->tmpLine.get());
        this->tmpLine->setVertexInScene(0, Vertex{pointCoordscene, 0});
        this->tmpLine->setVertexInScene(1, Vertex{pointCoordscene, 0});
    } else if  (this->tmpLine && event == MouseEvent::MouseMove) {
        QPointF vertex0 = this->tmpLine->getVertexInScene(0).point;
        if (!KeyboardManager::getIns().IsControlHold) {
            if (KeyboardManager::getIns().IsXHold) {
                this->tmpLine->setVertexInScene(1, Vertex{QPointF(pointCoordscene.x(), vertex0.y())});
            } else if (KeyboardManager::getIns().IsYHold) {
                this->tmpLine->setVertexInScene(1, Vertex{QPointF(vertex0.x(), pointCoordscene.y())});
            } else {
                this->tmpLine->setVertexInScene(1, Vertex{pointCoordscene, 0});
            }
        }
    } else if (this->tmpLine && event == MouseEvent::LeftPress) {
        Manager::getIns().addItem(std::move(this->tmpLine));
    }
}

void DrawManager::drawPoint(QPointF pointCoordscene, MouseEvent event) {
    if (!this->tmpPoint && event == MouseEvent::LeftPress) {
        // 设置其他元素不可动不可选中 颜色为display
        auto allItems = Manager::getIns().getItemsByLayer(0);
        for (const auto& item : allItems) {
            Manager::getIns().setItemSelectable(item, false);
            Manager::getIns().setItemMovable(item, false);
            Manager::getIns().itemMapFind(item)->setPen(DISPLAY_PEN);
        }
        this->tmpPoint = std::make_shared < PointItem > ();
        this->tmpPoint->setPen(EDIT_PEN);
        SceneManager::getIns().scene->addItem(this->tmpPoint.get());
        this->tmpPoint->setVertexInScene(0, Vertex{pointCoordscene, 0});
        Manager::getIns().addItem(std::move(this->tmpPoint));
    }
}

void DrawManager::drawCircle(QPointF pointCoordscene, MouseEvent event) {
    if (!this->tmpCircle && event == MouseEvent::LeftPress) {
        // 设置其他元素不可动不可选中 颜色为display
        auto allItems = Manager::getIns().getItemsByLayer(0);
        for (const auto &item : allItems) {
            Manager::getIns().setItemSelectable(item, false);
            Manager::getIns().setItemMovable(item, false);
            Manager::getIns().itemMapFind(item)->setPen(DISPLAY_PEN);
        }
        this->tmpCircle = std::make_shared < CircleItem > ();
        this->tmpCircle->setVertexInScene(0, Vertex{pointCoordscene, 0});
        this->tmpCircle->setPen(EDIT_PEN);
        SceneManager::getIns().scene->addItem(this->tmpCircle.get());
    } else if (this->tmpCircle && event == MouseEvent::MouseMove) {
        QPointF center = this->tmpCircle->getCenterInScene();
        double radius = QLineF(center, pointCoordscene).length();
        this->tmpCircle->setRadius(radius);
        // this->tmpCircle->setTransformOriginPoint(center);
    } else if (this->tmpCircle && event == MouseEvent::LeftPress) {
        Manager::getIns().addItem(std::move(this->tmpCircle));
    }
}
void DrawManager::drawRect(QPointF pointCoordscene, MouseEvent event) {
    if (!this->tmpRect && event == MouseEvent::LeftPress) {
        auto allItems = Manager::getIns().getItemsByLayer(0);
        for (const auto &item : allItems) {
            Manager::getIns().setItemSelectable(item, false);
            Manager::getIns().setItemMovable(item, false);
            Manager::getIns().itemMapFind(item)->setPen(DISPLAY_PEN);
        }
        this->tmpRect = std::make_shared < RectItem > ();
        this->tmpRect->setPen(EDIT_PEN);
        SceneManager::getIns().scene->addItem(this->tmpRect.get());
        this->tmpRect->setVertexInScene(0, Vertex{pointCoordscene, 0});
        this->tmpRect->setVertexInScene(1, Vertex{pointCoordscene, 0});
        this->tmpRect->setVertexInScene(2, Vertex{pointCoordscene, 0});
        this->tmpRect->setVertexInScene(3, Vertex{pointCoordscene, 0});
        this->tmpRect->setVertexInScene(4, Vertex{pointCoordscene, 0});
    } else if  (this->tmpRect && event == MouseEvent::MouseMove) {
        QPointF start = this->tmpRect->getVertexInScene(0).point;
        QPointF current = pointCoordscene;
        this->tmpRect->setVertexInScene(1, Vertex{QPointF(current.x(), start.y()), 0}); // 右上
        this->tmpRect->setVertexInScene(2, Vertex{QPointF(current.x(), current.y()), 0}); // 右下
        this->tmpRect->setVertexInScene(3, Vertex{QPointF(start.x(), current.y()), 0});
    } else if (this->tmpRect && event == MouseEvent::LeftPress) {
        Manager::getIns().addItem(std::move(this->tmpRect));
    }
}
void DrawManager::drawEllipse(QPointF pointCoordscene, MouseEvent event) {
    if (!this->tmpEllipse && event == MouseEvent::LeftPress) {
        // 第一次点击：创建临时椭圆，记录中心点
        auto allItems = Manager::getIns().getItemsByLayer(0);
        for (const auto &item : allItems) {
            Manager::getIns().setItemSelectable(item, false);
            Manager::getIns().setItemMovable(item, false);
            Manager::getIns().itemMapFind(item)->setPen(DISPLAY_PEN);
        }
        this->tmpEllipse = std::make_shared < EllipseItem > ();
        this->tmpEllipse->setPen(EDIT_PEN);
        this->tmpEllipse->setVertexInScene(0, Vertex{pointCoordscene, 0}); // 圆心
        SceneManager::getIns().scene->addItem(this->tmpEllipse.get());
    } else if (this->tmpEllipse && this->tmpEllipse->drawStep == 0
               && event == MouseEvent::MouseMove) {
        QPointF center = this->tmpEllipse->getVertexInScene(0).point;
        QPointF delta = pointCoordscene - center;
        double radiusX = std::hypot(delta.x(), delta.y());
        double angle = std::fmod((std::atan2(delta.y(), delta.x()) * 180.0 / M_PI + 360.0), 360.0);
        this->tmpEllipse->setRadiusX(radiusX);
        this->tmpEllipse->setRadiusY(radiusX); // 暂时等于X
        this->tmpEllipse->setRotateAngle(angle);
    } else if (this->tmpEllipse && this->tmpEllipse->drawStep == 0
               && event == MouseEvent::LeftPress) {
        // 第一次拖完点击确认，进入第三步
        this->tmpEllipse->drawStep = 1;
    } else if (this->tmpEllipse && this->tmpEllipse->drawStep == 1
               && event == MouseEvent::MouseMove) {
        // 第三步：拖出RY（保持RX、角度不变）
        QPointF center = this->tmpEllipse->getVertexInScene(0).point;
        double angleRad = this->tmpEllipse->getRotateAngle() * M_PI / 180.0;
        QPointF local = pointCoordscene - center;
        // 把鼠标坐标反向旋转回到 local 坐标系
        double cosA = std::cos(-angleRad);
        double sinA = std::sin(-angleRad);
        QPointF rotated(local.x() * cosA - local.y() * sinA, local.x() * sinA + local.y() * cosA);
        double radiusY = std::abs(rotated.y());
        this->tmpEllipse->setRadiusY(radiusY);
    } else if (this->tmpEllipse && this->tmpEllipse->drawStep == 1
               && event == MouseEvent::LeftPress) {
        Manager::getIns().addItem(std::move(this->tmpEllipse));
    }
}

void DrawManager::drawSpiral(QPointF pointCoordscene, MouseEvent event) {
    //     auto allItems = Manager::getIns().getItemsByLayer(0);
    //     EditController::getIns().setItemsStatus(false,true,true,allItems);
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
void DrawManager::drawPolygon(QPointF pointCoordscene, MouseEvent event) {
    //     auto allItems = Manager::getIns().getItemsByLayer(0);
    //     EditController::getIns().setItemsStatus(false,true,true,allItems);
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

DrawManager &DrawManager::getIns() {
    return ins;
}
