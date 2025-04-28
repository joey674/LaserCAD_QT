#ifndef EDITRECT_H
#define EDITRECT_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include "graphicsitem.h"
#include <cmath>
#include <memory>
#include <vector>

const int HandleSize = 8;
const qreal MinRectSize = 10.0;

enum class EditMode { None, Scale, Move, Rotate };

class EditRect : public QGraphicsItem
{
public:
    EditRect()
    {
        setFlag(ItemIsSelectable, false);
        setFlag(ItemIsMovable, false);
        setFlag(ItemSendsGeometryChanges, true);
        setAcceptHoverEvents(true);
        setAcceptedMouseButtons(Qt::LeftButton);
        setZValue(999);
    }

    void setEditItems(std::vector<std::shared_ptr<GraphicsItem>> items)
    {
        prepareGeometryChange();
        m_editItems = std::move(items);

        if (m_editItems.empty()) {
            m_editRect = QRectF();
            setRotation(0);
            return;
        }

        QRectF combinedRect = m_editItems[0]->sceneBoundingRect();
        for (size_t i = 1; i < m_editItems.size(); ++i) {
            combinedRect = combinedRect.united(m_editItems[i]->sceneBoundingRect());
        }
        m_editRect = combinedRect;

        prepareGeometryChange();
        setRotation(0);
        setPos(m_editRect.center());
        m_editRect.moveCenter(QPointF(0, 0));
    }

    QRectF boundingRect() const override { return m_editRect.adjusted(-50, -50, 50, 50); }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * = nullptr) override
    {
        painter->setRenderHint(QPainter::Antialiasing);

        QPen pen(Qt::gray, 1, Qt::DashLine);
        painter->setPen(pen);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(m_editRect);

        painter->setPen(Qt::NoPen);
        for (int i = 0; i < 6; ++i) {
            painter->setBrush(getHandleColor(i));
            painter->drawRect(handleRect(i));
        }
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override
    {
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
            m_editMode = EditMode::Move;
        } else if (m_currentHandleIndex == 5) {
            m_editMode = EditMode::Rotate;
        }
        event->accept();
    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override
    {
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

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override
    {
        if (m_editMode == EditMode::Move) {
            QPointF deltaMove = this->pos() - m_startPos;

            for (auto &item : m_editItems) {
                if (auto gItem = std::dynamic_pointer_cast<GraphicsItem>(item)) {
                    applyMoveToGraphicsItem(*gItem, deltaMove);
                }
            }
        } else if (m_editMode == EditMode::Rotate) {
            qreal deltaRotation = this->rotation() - m_startRotation;

            // 旋转中心
            QPointF center = mapToScene(QPointF(0, 0)); // 当前EditRect中心（已经是scene坐标了）

            for (auto &item : m_editItems) {
                if (auto gItem = std::dynamic_pointer_cast<GraphicsItem>(item)) {
                    applyRotateToGraphicsItem(*gItem, deltaRotation, center);
                }
            }
        } else if (m_editMode == EditMode::Scale) {
            // 计算缩放比例
            qreal scaleX = m_editRect.width() / m_startEditRect.width();
            qreal scaleY = m_editRect.height() / m_startEditRect.height();

            // 强制等比缩放
            qreal uniformScale = (std::abs(scaleX) < std::abs(scaleY)) ? scaleX : scaleY;
            scaleX = scaleY = uniformScale;

            // 确定固定点
            QPointF startFixedPoint;
            switch (m_currentHandleIndex) {
            case 0:
                startFixedPoint = m_startEditRect.bottomRight();
                break;
            case 1:
                startFixedPoint = m_startEditRect.bottomLeft();
                break;
            case 2:
                startFixedPoint = m_startEditRect.topRight();
                break;
            case 3:
                startFixedPoint = m_startEditRect.topLeft();
                break;
            default:
                startFixedPoint = m_startEditRect.center();
                break;
            }
            startFixedPoint = mapToScene(startFixedPoint);

            for (auto &item : m_editItems) {
                if (auto gItem = std::dynamic_pointer_cast<GraphicsItem>(item)) {
                    applyScaleToGraphicsItem(*gItem, scaleX, scaleY, startFixedPoint);
                }
            }

            //
            prepareGeometryChange();
            // 计算新的EditRect的中心 (注意是局部的)
            QPointF newCenterInScene = mapToScene(m_editRect.center());
            // 更新自己的位置
            setPos(newCenterInScene);
            // m_editRect中心移动到(0,0)
            m_editRect.moveCenter(QPointF(0, 0));
        }

        // 重置
        m_editMode = EditMode::None;
        m_currentHandleIndex = -1;
        event->accept();
    }

private:
    std::vector<std::shared_ptr<GraphicsItem>> m_editItems;
    QRectF m_editRect;
    EditMode m_editMode = EditMode::None;
    int m_currentHandleIndex = -1;

    QPointF m_lastPressedScenePos;
    QPointF m_lastPressedLocalPos;
    QRectF m_startEditRect;
    qreal m_startRotation = 0.0;
    QPointF m_startPos;

    QRectF handleRect(int index) const
    {
        QPointF pos;
        switch (index) {
        case 0:
            pos = m_editRect.topLeft();
            break;
        case 1:
            pos = m_editRect.topRight();
            break;
        case 2:
            pos = m_editRect.bottomLeft();
            break;
        case 3:
            pos = m_editRect.bottomRight();
            break;
        case 4:
            pos = (m_editRect.topLeft() + m_editRect.topRight()) / 2.0;
            pos.setY(pos.y() - 20);
            break;
        case 5:
            pos = (m_editRect.bottomLeft() + m_editRect.bottomRight()) / 2.0;
            pos.setY(pos.y() + 20);
            break;
        }
        return QRectF(pos.x() - HandleSize / 2, pos.y() - HandleSize / 2, HandleSize, HandleSize);
    }
    QColor getHandleColor(int index) const
    {
        if (index <= 3)
            return Qt::green;
        if (index == 4)
            return Qt::blue;
        if (index == 5)
            return Qt::red;
        return Qt::black;
    }
    int hitTestHandles(const QPointF &pos) const
    {
        for (int i = 0; i < 6; ++i) {
            if (handleRect(i).contains(pos))
                return i;
        }
        return -1;
    }

    /// \brief applyScale
    /// \param delta
    void applyScale(const QPointF &delta)
    {
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

        if (newWidth < MinRectSize) {
            newWidth = MinRectSize;
            newHeight = MinRectSize / aspectRatio;
        }
        if (newHeight < MinRectSize) {
            newHeight = MinRectSize;
            newWidth = MinRectSize * aspectRatio;
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
    void applyMove(const QPointF &deltaScene)
    {
        prepareGeometryChange();
        setPos(m_startPos + deltaScene);
    }
    /// \brief applyRotate
    /// \param currentScenePos
    void applyRotate(const QPointF &currentScenePos)
    {
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
    void applyMoveToGraphicsItem(GraphicsItem &item, const QPointF &deltaMove)
    {
        for (int i = 0; i < item.getVertexCount(); ++i) {
            Vertex vertex = item.getVertexInScene(i);
            QPointF movedPos = vertex.point + deltaMove;
            item.setVertexInScene(i, Vertex{movedPos, vertex.angle});
        }
    }
    /// \brief applyRotateToGraphicsItem
    /// \param item
    void applyRotateToGraphicsItem(GraphicsItem &item, qreal deltaRotationDeg, const QPointF &center)
    {
        qreal radians = qDegreesToRadians(deltaRotationDeg);

        for (int i = 0; i < item.getVertexCount(); ++i) {
            Vertex vertex = item.getVertexInScene(i);
            QPointF vec = vertex.point - center;

            qreal xNew = vec.x() * std::cos(radians) - vec.y() * std::sin(radians);
            qreal yNew = vec.x() * std::sin(radians) + vec.y() * std::cos(radians);

            QPointF rotatedPos = center + QPointF(xNew, yNew);

            item.setVertexInScene(i, Vertex{rotatedPos, vertex.angle});
        }
    }
    /// \brief applyScaleToGraphicsItem
    /// \param item
    void applyScaleToGraphicsItem(GraphicsItem &item,
                                  qreal scaleX,
                                  qreal scaleY,
                                  const QPointF &center)
    {
        for (int i = 0; i < item.getVertexCount(); ++i) {
            Vertex vertex = item.getVertexInScene(i);
            QPointF vec = vertex.point - center;

            QPointF scaledVec(vec.x() * scaleX, vec.y() * scaleY);
            QPointF finalPos = center + scaledVec;

            // 角度不变
            item.setVertexInScene(i, Vertex{finalPos, vertex.angle});
        }
    }
};

#endif // EDITRECT_H
