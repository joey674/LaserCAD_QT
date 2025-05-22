#ifndef EDITRECT_H
#define EDITRECT_H

#include <QCursor>
#include <QDialog>
#include <QDialogButtonBox>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QPixmap>
#include "circleitem.h"
#include "ellipseitem.h"
#include "graphicsitem.h"
#include "polygonitem.h"
#include "spiralitem.h"
#include <cmath>
#include <memory>
#include <vector>
#include "scenecontroller.h"


const double EdgeRectPadding = 1;
const double MinEdgeRectSize = 1;
const double BoundingRectPadding = 2;
const double VertexInputDialogSize = 2;
const double HandleSize = 8;// handle会根据scene自动调整; 不需要修改
const double MoveHandleOffset = 0.5;
const double RotateHandleOffset = 0.5;

enum class EditMode { None, Scale, Move, Rotate };

class EditRect : public QGraphicsItem {
public:
    EditRect() {
        setFlag(ItemIsSelectable, false);
        setFlag(ItemIsMovable, false);
        setFlag(ItemSendsGeometryChanges, true);
        setAcceptHoverEvents(true);
        setAcceptedMouseButtons(Qt::LeftButton);
        setZValue(999);
        QPixmap rawPixmap(":/cursor/rotateCursor.png");
        QPixmap scaled = rawPixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        m_rotateCursor = QCursor(scaled, 16, 16);
    }

    void setEditItems(std::vector < std::shared_ptr < GraphicsItem>> items) {
        prepareGeometryChange();
        m_editItems = std::move(items);
        if (m_editItems.empty()) {
            m_editRect = QRectF();
            setRotation(0);
            return;
        }
        QRectF combinedRect = m_editItems[0]->mapRectToScene(m_editItems[0]->getBoundingRectBasis());
        for (size_t i = 1; i < m_editItems.size(); ++i) {
            QRectF basisRect = m_editItems[i]->mapRectToScene(m_editItems[i]->getBoundingRectBasis());
            combinedRect = combinedRect.united(basisRect);
        }
        m_editRect = combinedRect;
        prepareGeometryChange();
        setRotation(0);
        setPos(m_editRect.center());
        m_editRect.moveCenter(QPointF(0, 0));
    }

    QRectF boundingRect() const override {
        return m_editRect.adjusted(-BoundingRectPadding, -BoundingRectPadding, BoundingRectPadding, BoundingRectPadding);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * = nullptr) override {
        painter->setRenderHint(QPainter::Antialiasing);
        QPen pen(Qt::gray, 1, Qt::DashLine);
        pen.setCosmetic(true);
        painter->setPen(pen);
        painter->setBrush(Qt::NoBrush);
        QRectF displayRect = m_editRect.adjusted(-EdgeRectPadding,
                             -EdgeRectPadding,
                             EdgeRectPadding,
                             EdgeRectPadding);
        painter->drawRect(displayRect);
        // editrect的编辑边框和handle在缩放时不发生变化
        // qreal scale = SceneController::getIns().getSceneScale().first;
        // DEBUG_VAR(scale);
        // qreal handleSize = 8.0 / scale;
        painter->setPen(Qt::NoPen);
        for (int i = 0; i < 6; ++i) {
            painter->setBrush(getHandleColor(i));
            QRectF rect = handleRect(i);
            painter->drawRect(rect);
            // QPointF center = rect.center();
            // QRectF fixedRect(center.x() - handleSize / 2,
            //                  center.y() - handleSize / 2,
            //                  handleSize, handleSize);
            // painter->drawRect(fixedRect);
        }
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            m_currentHandleIndex = hitTestHandles(event->pos());
            m_lastPressedScenePos = event->scenePos();
            m_lastPressedLocalPos = event->pos();
            m_startEditRect = m_editRect;
            m_startRotation = this->rotation();
            m_startPos = pos();
            if (m_currentHandleIndex == -1) {
                m_editMode = EditMode::None;
            } else if (m_currentHandleIndex <= 3) {
                m_editMode = EditMode::Scale;
            } else if (m_currentHandleIndex == 4) {
                m_editMode = EditMode::Rotate;
            } else if (m_currentHandleIndex == 5) {
                m_editMode = EditMode::Move;
            }
            if (m_editItems.size() == 1) {
                if (auto gItem = std::dynamic_pointer_cast < GraphicsItem > (m_editItems[0])) {
                    for (int i = 0; i < gItem->getVertexCount(); ++i) {
                        Vertex v = gItem->getVertexInScene(i);
                        QPointF scenePoint = v.point;
                        QPointF localPoint = mapFromScene(scenePoint);
                        if (QRectF(localPoint - QPointF(VertexInputDialogSize, VertexInputDialogSize), QSizeF(VertexInputDialogSize*2, VertexInputDialogSize*2))
                                .contains(event->pos())) {
                            openVertexInputDialog(*gItem, i, v); // 触发输入框
                            event->accept();
                            return;
                        }
                    }
                }
            }
        }
        event->accept();
    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override {
        QPointF deltaScene = event->scenePos() - m_lastPressedScenePos;
        QPointF deltaLocal = event->pos() - m_lastPressedLocalPos;
        switch (m_editMode) {
            case EditMode::Scale:
                applyScale(deltaLocal);
                break;
            case EditMode::Move:
                applyMove(deltaScene);
                break;
            case EditMode::Rotate:
                applyRotate(event->scenePos());
                break;
            default:
                break;
        }
        update();
        event->accept();
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override {
        int handleIndex = hitTestHandles(event->pos());
        switch (handleIndex) {
            case 0: // 左上角
                setCursor(Qt::SizeBDiagCursor);
                break;
            case 1: // 右上角
                setCursor(Qt::SizeFDiagCursor);
                break;
            case 2: // 左下角
                setCursor(Qt::SizeFDiagCursor);
                break;
            case 3: // 右下角
                setCursor(Qt::SizeBDiagCursor);
                break;
            case 4: // 旋转
                setCursor(m_rotateCursor);
                break;
            case 5: // 移动
                setCursor(Qt::SizeAllCursor);
                break;
            default:
                setCursor(Qt::ArrowCursor);
                break;
        }
        event->accept();
    }

private:
    std::vector < std::shared_ptr < GraphicsItem>> m_editItems;
    QRectF m_editRect;
    EditMode m_editMode = EditMode::None;
    int m_currentHandleIndex = -1;

    QPointF m_lastPressedScenePos;
    QPointF m_lastPressedLocalPos;
    QRectF m_startEditRect;
    qreal m_startRotation = 0.0;
    QPointF m_startPos;

    QCursor m_rotateCursor;

    QRectF handleRect(int index) const {
        QRectF displayRect = m_editRect.adjusted(-EdgeRectPadding, -EdgeRectPadding, EdgeRectPadding, EdgeRectPadding);
        QPointF pos;
        switch (index) {
            case 0:
                pos = displayRect.topLeft();
                break;
            case 1:
                pos = displayRect.topRight();
                break;
            case 2:
                pos = displayRect.bottomLeft();
                break;
            case 3:
                pos = displayRect.bottomRight();
                break;
            case 4:// rotate
                pos = (displayRect.topLeft() + displayRect.topRight()) / 2.0;
                pos.setY(pos.y() - RotateHandleOffset);
                break;
            case 5: // move
                pos = (displayRect.bottomLeft() + displayRect.bottomRight()) / 2.0;
                pos.setY(pos.y() + MoveHandleOffset);
                break;
        }
        auto handleRect = QRectF(pos.x() - HandleSize / 2,
                                 pos.y() - HandleSize / 2,
                                 HandleSize,
                                 HandleSize);
        //把handle的小矩形scale一下 可以根据scene缩放自动缩放
        qreal scale = SceneController::getIns().getSceneScale().first;
        qreal handleSize = HandleSize / scale;
        QPointF center = handleRect.center();
        QRectF scaledRect(center.x() - handleSize / 2,
                          center.y() - handleSize / 2,
                          handleSize,
                          handleSize);
        return scaledRect;
    }
    QColor getHandleColor(int index) const {
        if (index <= 3) {
            return Qt::green;
        }
        if (index == 4) {
            return Qt::red;
        }
        if (index == 5) {
            return Qt::blue;
        }
        return Qt::black;
    }
    int hitTestHandles(const QPointF & pos) const {
        for (int i = 0; i < 6; ++i) {
            if (handleRect(i).contains(pos)) {
                return i;
            }
        }
        return -1;
    }
    /// \brief applyScale
    /// \param delta
    void applyScale(const QPointF & delta) {
        prepareGeometryChange();
        QRectF rect = m_startEditRect;
        QPointF fixedPoint;
        QPointF movingPointRaw;
        switch (m_currentHandleIndex) {
            case 0: // 左上角
                fixedPoint = rect.bottomRight();
                movingPointRaw = rect.topLeft() + delta;
                break;
            case 1: // 右上角
                fixedPoint = rect.bottomLeft();
                movingPointRaw = rect.topRight() + delta;
                break;
            case 2: // 左下角
                fixedPoint = rect.topRight();
                movingPointRaw = rect.bottomLeft() + delta;
                break;
            case 3: // 右下角
                fixedPoint = rect.topLeft();
                movingPointRaw = rect.bottomRight() + delta;
                break;
            default:
                return;
        }
        // 原矩形宽高比
        qreal aspectRatio = m_startEditRect.width() / m_startEditRect.height();
        // 计算从fixedPoint到movingPointRaw的向量
        QPointF rawVec = movingPointRaw - fixedPoint;
        qreal dx = rawVec.x();
        qreal dy = rawVec.y();
        // 确保缩放时保持宽高比
        if (std::abs(dx) > std::abs(dy) * aspectRatio) {
            dy = dx / aspectRatio;
        } else {
            dx = dy * aspectRatio;
        }
        // 防止拉动到负宽高（翻转）
        qreal newWidth = std::abs(dx);
        qreal newHeight = std::abs(dy);
        if (newWidth < MinEdgeRectSize) {
            newWidth = MinEdgeRectSize;
            newHeight = MinEdgeRectSize / aspectRatio;
        }
        if (newHeight < MinEdgeRectSize) {
            newHeight = MinEdgeRectSize;
            newWidth = MinEdgeRectSize * aspectRatio;
        }
        // 根据handle方向，修正移动点
        QPointF correctedVec;
        switch (m_currentHandleIndex) {
            case 0: // 左上角
                correctedVec = QPointF(-newWidth, -newHeight);
                break;
            case 1: // 右上角
                correctedVec = QPointF(newWidth, -newHeight);
                break;
            case 2: // 左下角
                correctedVec = QPointF(-newWidth, newHeight);
                break;
            case 3: // 右下角
                correctedVec = QPointF(newWidth, newHeight);
                break;
        }
        QPointF movingPoint = fixedPoint + correctedVec;
        QRectF newRect(fixedPoint, movingPoint);
        m_editRect = newRect.normalized();
    }
    /// \brief applyMove
    /// \param deltaScene
    void applyMove(const QPointF & deltaScene) {
        prepareGeometryChange();
        setPos(m_startPos + deltaScene);
    }
    /// \brief applyRotate
    /// \param currentScenePos
    void applyRotate(const QPointF & currentScenePos) {
        prepareGeometryChange();
        // --- 动态实时计算当前m_editRect在scene中的中心 ---
        QPointF topLeft = mapToScene(m_editRect.topLeft());
        QPointF topRight = mapToScene(m_editRect.topRight());
        QPointF bottomLeft = mapToScene(m_editRect.bottomLeft());
        QPointF bottomRight = mapToScene(m_editRect.bottomRight());
        QPointF centerInScene = (topLeft + topRight + bottomLeft + bottomRight) / 4.0;
        // --- 计算鼠标变化角度 ---
        QPointF startVec = m_lastPressedScenePos - centerInScene;
        QPointF currentVec = currentScenePos - centerInScene;
        qreal startAngle = std::atan2(startVec.y(), startVec.x());
        qreal currentAngle = std::atan2(currentVec.y(), currentVec.x());
        qreal deltaAngleDeg = (currentAngle - startAngle) * 180.0 / M_PI;
        // --- 先旋转 ---
        setRotation(m_startRotation + deltaAngleDeg);
        // --- 再补偿pos，保证旋转中心不偏移 ---
        QPointF afterRotationCenter = mapToScene((m_editRect.topLeft() + m_editRect.topRight()
                                      + m_editRect.bottomLeft()
                                      + m_editRect.bottomRight())
                                      / 4.0);
        QPointF offset = centerInScene - afterRotationCenter;
        setPos(pos() + offset);
    }
    /// \brief applyMoveToGraphicsItem
    /// \param item
    void applyMoveToGraphicsItem(GraphicsItem & item, const QPointF & deltaMove) {
        for (int i = 0; i < item.getVertexCount(); ++i) {
            Vertex vertex = item.getVertexInScene(i);
            QPointF movedPos = vertex.point + deltaMove;
            item.setVertexInScene(i, Vertex{movedPos, vertex.angle});
        }
    }
    /// \brief applyRotateToGraphicsItem
    /// \param item
    void applyRotateToGraphicsItem(GraphicsItem & item, qreal deltaRotationDeg, const QPointF & center) {
        qreal radians = qDegreesToRadians(deltaRotationDeg);
        // 旋转所有顶点
        for (int i = 0; i < item.getVertexCount(); ++i) {
            Vertex vertex = item.getVertexInScene(i);
            QPointF vec = vertex.point - center;
            qreal xNew = vec.x() * std::cos(radians) - vec.y() * std::sin(radians);
            qreal yNew = vec.x() * std::sin(radians) + vec.y() * std::cos(radians);
            QPointF rotatedPos = center + QPointF(xNew, yNew);
            item.setVertexInScene(i, Vertex{rotatedPos, vertex.angle});
        }
        // 通用角度归一化函数
        auto normalizeAngle = [](double angle) {
            while (angle < 0.0) {
                angle += 360.0;
            }
            while (angle >= 360.0) {
                angle -= 360.0;
            }
            return angle;
        };
        // 特殊类型：更新其 angle 属性
        if (item.type() == GraphicsItemType::Ellipse) {
            if (auto ellipse = dynamic_cast < EllipseItem * > (&item)) {
                double oldAngle = ellipse->getRotateAngle();
                ellipse->setRotateAngle(normalizeAngle(oldAngle + deltaRotationDeg));
            }
        } else if (item.type() == GraphicsItemType::Polygon) {
            if (auto polygon = dynamic_cast < PolygonItem * > (&item)) {
                double oldAngle = polygon->getRotateAngle();
                polygon->setRotateAngle(normalizeAngle(oldAngle + deltaRotationDeg));
            }
        } else if (item.type() == GraphicsItemType::Spiral) {
            if (auto spiral = dynamic_cast < SpiralItem * > (&item)) {
                double oldAngle = spiral->getRotateAngle();
                spiral->setRotateAngle(normalizeAngle(oldAngle + deltaRotationDeg));
            }
        }
    }
    /// \brief applyScaleToGraphicsItem
    /// \param item
    void applyScaleToGraphicsItem(GraphicsItem & item,
                                  qreal scaleX,
                                  qreal scaleY,
                                  const QPointF & center) {
        // 顶点缩放（中心点）
        for (int i = 0; i < item.getVertexCount(); ++i) {
            Vertex vertex = item.getVertexInScene(i);
            QPointF vec = vertex.point - center;
            QPointF scaledVec(vec.x() * scaleX, vec.y() * scaleY);
            QPointF finalPos = center + scaledVec;
            item.setVertexInScene(i, Vertex{finalPos, vertex.angle});
        }
        // 针对各类图元做半径/尺寸缩放
        qreal uniformScale = scaleX; // 默认统一缩放比例，X/Y 一致才合理
        if (item.type() == GraphicsItemType::Circle) {
            auto circle = dynamic_cast < CircleItem * > (&item);
            if (circle) {
                double oldRadius = circle->getRadius();
                circle->setRadius(oldRadius * uniformScale);
            }
        } else if (item.type() == GraphicsItemType::Ellipse) {
            auto ellipse = dynamic_cast < EllipseItem * > (&item);
            if (ellipse) {
                double oldRadiusX = ellipse->getRadiusX();
                double oldRadiusY = ellipse->getRadiusY();
                ellipse->setRadiusX(oldRadiusX * uniformScale);
                ellipse->setRadiusY(oldRadiusY * uniformScale);
            }
        } else if (item.type() == GraphicsItemType::Polygon) {
            auto polygon = dynamic_cast < PolygonItem * > (&item);
            if (polygon) {
                double oldRadius = polygon->getRadius();
                polygon->setRadius(oldRadius * uniformScale);
            }
        } else if (item.type() == GraphicsItemType::Spiral) {
            auto spiral = dynamic_cast < SpiralItem * > (&item);
            if (spiral) {
                double oldR0 = spiral->getStartRadius();
                double oldR1 = spiral->getEndRadius();
                spiral->setStartRadius(oldR0 * uniformScale);
                spiral->setEndRadius(oldR1 * uniformScale);
            }
        }
    }
    /// \brief openVertexInputDialog
    /// \param item
    void openVertexInputDialog(GraphicsItem & item, int index, const Vertex & currentVertex) {
        QDialog dialog;
        dialog.setWindowTitle("Edit Vertex");
        QFormLayout *form = new QFormLayout(&dialog);
        QDoubleSpinBox *xSpin = new QDoubleSpinBox;
        QDoubleSpinBox *ySpin = new QDoubleSpinBox;
        QDoubleSpinBox *angleSpin = new QDoubleSpinBox;
        xSpin->setRange(-1e6, 1e6);
        ySpin->setRange(-1e6, 1e6);
        angleSpin->setRange(-360, 360);
        xSpin->setValue(currentVertex.point.x());
        ySpin->setValue(currentVertex.point.y());
        angleSpin->setValue(currentVertex.angle);
        form->addRow("X ", xSpin);
        form->addRow("Y ", ySpin);
        form->addRow("Angle", angleSpin);
        QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        form->addWidget(buttons);
        QObject::connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
        QObject::connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
        if (dialog.exec() == QDialog::Accepted) {
            QPointF newPos(xSpin->value(), ySpin->value());
            double newAngle = angleSpin->value();
            // 对于弧来说, 不允许其设置为直线
            // if (newAngle == 0) {
            //     return;
            // }
            item.setVertexInScene(index, Vertex{newPos, newAngle});
        }
        setEditItems(m_editItems);
    }
};

#endif // EDITRECT_H
