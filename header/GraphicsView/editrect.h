#ifndef EDITRECT_H
#define EDITRECT_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include "graphicsitem.h"
#include <cmath>
#include <memory>
#include <vector>

const int HandleSize = 8;       // 手柄尺寸
const qreal MinRectSize = 10.0; // 最小宽高，避免被缩成负数或消失

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
        resetCenter();
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
        m_startTargetRect = m_editRect;
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
    QRectF m_startTargetRect;
    qreal m_startRotation = 0.0;
    QPointF m_startPos;

    void resetCenter()
    {
        prepareGeometryChange();
        setRotation(0);
        setPos(m_editRect.center());
        m_editRect.moveCenter(QPointF(0, 0));
    }

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

    void applyScale(const QPointF &delta)
    {
        prepareGeometryChange();
        QRectF rect = m_startTargetRect;

        switch (m_currentHandleIndex) {
        case 0:
            rect.setTopLeft(rect.topLeft() + delta);
            break;
        case 1:
            rect.setTopRight(rect.topRight() + delta);
            break;
        case 2:
            rect.setBottomLeft(rect.bottomLeft() + delta);
            break;
        case 3:
            rect.setBottomRight(rect.bottomRight() + delta);
            break;
        }

        // 防止负宽高
        if (rect.width() < MinRectSize)
            rect.setWidth(MinRectSize);
        if (rect.height() < MinRectSize)
            rect.setHeight(MinRectSize);

        m_editRect = rect;
    }

    void applyMove(const QPointF &deltaScene)
    {
        prepareGeometryChange();
        setPos(m_startPos + deltaScene);
    }

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
};

#endif // EDITRECT_H
