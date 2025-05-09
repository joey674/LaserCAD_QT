#include "drawcontroller.h"
#include "manager.h"
#include "scenecontroller.h"
#include "keyboardmanager.h"
#include "protocol.h"
#include "utils.hpp"


DrawController DrawController::ins;

void DrawController::resetTmpItemStatus() {
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

void DrawController::drawPolyline(QPointF pointCoordscene, MouseEvent event) {
    if (!this->tmpPolyline && event == MouseEvent::LeftPress) {
        // 设置其他元素不可选中
        auto allItems = Manager::getIns().getChildItems("0-0-0-0");
        for (const auto& item : allItems) {
            Manager::getIns().setItemSelectable(item, false);
        }
        this->tmpPolyline = std::make_shared < PolylineItem > ();
        this->tmpPolyline->setColor(SceneController::getIns().getCurrentLayerColor());
        SceneController::getIns().scene->addItem(this->tmpPolyline.get());
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

void DrawController::drawArc(QPointF pointCoordscene, MouseEvent event) {
    if (!this->tmpArc && event == MouseEvent::LeftPress) {
        // 设置其他元素不可选中
        auto allItems = Manager::getIns().getChildItems("0-0-0-0");
        for (const auto& item : allItems) {
            Manager::getIns().setItemSelectable(item, false);
        }
        this->tmpArc = std::make_shared < ArcItem > ();
        this->tmpArc->setColor(SceneController::getIns().getCurrentLayerColor());
        SceneController::getIns().scene->addItem(this->tmpArc.get());
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

void DrawController::drawLine(QPointF pointCoordscene, MouseEvent event) {
    if (!this->tmpLine && event == MouseEvent::LeftPress) {
        // 设置其他元素不可选中
        auto allItems = Manager::getIns().getChildItems("0-0-0-0");
        for (const auto& item : allItems) {
            Manager::getIns().setItemSelectable(item, false);
        }
        this->tmpLine = std::make_shared < LineItem > ();
        this->tmpLine->setColor(SceneController::getIns().getCurrentLayerColor());
        SceneController::getIns().scene->addItem(this->tmpLine.get());
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

void DrawController::drawPoint(QPointF pointCoordscene, MouseEvent event) {
    if (!this->tmpPoint && event == MouseEvent::LeftPress) {
        // 设置其他元素不可选中
        auto allItems = Manager::getIns().getChildItems("0-0-0-0");
        for (const auto& item : allItems) {
            Manager::getIns().setItemSelectable(item, false);
        }
        this->tmpPoint = std::make_shared < PointItem > ();
        this->tmpPoint->setColor(SceneController::getIns().getCurrentLayerColor());
        SceneController::getIns().scene->addItem(this->tmpPoint.get());
        this->tmpPoint->setVertexInScene(0, Vertex{pointCoordscene, 0});
        Manager::getIns().addItem(std::move(this->tmpPoint));
    }
}

void DrawController::drawCircle(QPointF pointCoordscene, MouseEvent event) {
    if (!this->tmpCircle && event == MouseEvent::LeftPress) {
        // 设置其他元素不可选中
        auto allItems = Manager::getIns().getChildItems("0-0-0-0");
        for (const auto &item : allItems) {
            Manager::getIns().setItemSelectable(item, false);
        }
        this->tmpCircle = std::make_shared < CircleItem > ();
        this->tmpCircle->setVertexInScene(0, Vertex{pointCoordscene, 0});
        this->tmpCircle->setColor(SceneController::getIns().getCurrentLayerColor());
        SceneController::getIns().scene->addItem(this->tmpCircle.get());
    } else if (this->tmpCircle && event == MouseEvent::MouseMove) {
        QPointF center = this->tmpCircle->getCenterInScene();
        double radius = QLineF(center, pointCoordscene).length();
        this->tmpCircle->setRadius(radius);
        // this->tmpCircle->setTransformOriginPoint(center);
    } else if (this->tmpCircle && event == MouseEvent::LeftPress) {
        Manager::getIns().addItem(std::move(this->tmpCircle));
    }
}

void DrawController::drawRect(QPointF pointCoordscene, MouseEvent event) {
    if (!this->tmpRect && event == MouseEvent::LeftPress) {
        auto allItems = Manager::getIns().getChildItems("0-0-0-0");
        for (const auto &item : allItems) {
            Manager::getIns().setItemSelectable(item, false);
        }
        this->tmpRect = std::make_shared < RectItem > ();
        this->tmpRect->setColor(SceneController::getIns().getCurrentLayerColor());
        SceneController::getIns().scene->addItem(this->tmpRect.get());
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
void DrawController::drawEllipse(QPointF pointCoordscene, MouseEvent event) {
    if (!this->tmpEllipse && event == MouseEvent::LeftPress) {
        // 第一次点击：创建临时椭圆，记录中心点
        auto allItems = Manager::getIns().getChildItems("0-0-0-0");
        for (const auto &item : allItems) {
            Manager::getIns().setItemSelectable(item, false);
        }
        this->tmpEllipse = std::make_shared < EllipseItem > ();
        this->tmpEllipse->setColor(SceneController::getIns().getCurrentLayerColor());
        this->tmpEllipse->setVertexInScene(0, Vertex{pointCoordscene, 0}); // 圆心
        SceneController::getIns().scene->addItem(this->tmpEllipse.get());
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

void DrawController::drawSpiral(QPointF pointCoordscene, MouseEvent event) {
    if (!this->tmpSpiral && event == MouseEvent::LeftPress) {
        auto allItems = Manager::getIns().getChildItems("0-0-0-0");
        for (const auto &item : allItems) {
            Manager::getIns().setItemSelectable(item, false);
        }
        this->tmpSpiral = std::make_shared < SpiralItem > ();
        this->tmpSpiral->setVertexInScene(0, Vertex{pointCoordscene, 0});
        this->tmpSpiral->setColor(SceneController::getIns().getCurrentLayerColor());
        this->tmpSpiral->setStartRadius(0); // 默认起始半径
        this->tmpSpiral->setEndRadius(0);
        this->tmpSpiral->setTurns(3);          // 默认圈数
        this->tmpSpiral->setAngleStepDeg(5.0); // 默认角度分辨率
        SceneController::getIns().scene->addItem(this->tmpSpiral.get());
    } else if (this->tmpSpiral && event == MouseEvent::MouseMove) {
        QPointF center = this->tmpSpiral->getCenterInScene();
        double radius = QLineF(center, pointCoordscene).length();
        this->tmpSpiral->setEndRadius(radius);
    } else if (this->tmpSpiral && event == MouseEvent::LeftPress) {
        Manager::getIns().addItem(std::move(this->tmpSpiral));
    }
}

void DrawController::drawPolygon(QPointF pointCoordscene, MouseEvent event) {
    if (!this->tmpPolygon && event == MouseEvent::LeftPress) {
        // 设置其他元素不可选中
        auto allItems = Manager::getIns().getChildItems("0-0-0-0");
        for (const auto &item : allItems) {
            Manager::getIns().setItemSelectable(item, false);
        }
        this->tmpPolygon = std::make_shared < PolygonItem > ();
        this->tmpPolygon->setVertexInScene(0, Vertex{pointCoordscene, 0});
        this->tmpPolygon->setColor(SceneController::getIns().getCurrentLayerColor());
        SceneController::getIns().scene->addItem(this->tmpPolygon.get());
    } else if (this->tmpPolygon && event == MouseEvent::MouseMove) {
        QPointF center = this->tmpPolygon->getCenterInScene();
        double radius = QLineF(center, pointCoordscene).length();
        this->tmpPolygon->setRadius(radius);
        // this->tmpPolygon->setTransformOriginPoint(center);
    } else if (this->tmpPolygon && event == MouseEvent::LeftPress) {
        Manager::getIns().addItem(std::move(this->tmpPolygon));
    }
}

DrawController &DrawController::getIns() {
    return ins;
}
