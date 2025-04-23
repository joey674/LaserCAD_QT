#include "EditRect.h"
#include "graphicsitem.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

EditRect::EditRect(GraphicsItem *target)
    : m_target(target) {
    setFlags(ItemIsSelectable | ItemIsMovable | ItemSendsGeometryChanges);
    setZValue(999); // 确保在最上层
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
    this->setParentItem(m_target);
    m_targetRect = m_target->boundingRect();
}

QRectF EditRect::boundingRect() const {
    return m_targetRect.adjusted(-4, -4, 4, 4);
}

void EditRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    QPen pen(Qt::gray, 1, Qt::DashLine);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(m_targetRect);
    painter->setBrush(Qt::green);
    for (int i = 0; i < 4; ++i) {
        painter->drawRect(handleRect(i));
    }
}

QRectF EditRect::handleRect(int index) const {
    QPointF pos;
    switch (index) {
        case 0:
            pos = m_targetRect.topLeft();
            break;
        case 1:
            pos = m_targetRect.topRight();
            break;
        case 2:
            pos = m_targetRect.bottomLeft();
            break;
        case 3:
            pos = m_targetRect.bottomRight();
            break;
    }
    return QRectF(pos.x() - m_handleSize / 2, pos.y() - m_handleSize / 2,
                  m_handleSize, m_handleSize);
}

int EditRect::hitTestHandles(const QPointF &pos) const {
    for (int i = 0; i < 4; ++i) {
        if (handleRect(i).contains(pos)) {
            return i;
        }
    }
    return -1;
}

void EditRect::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    m_activeHandleIndex = hitTestHandles(event->pos());
    m_lastMousePos = event->pos();
    event->accept();
}

void EditRect::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (m_activeHandleIndex != -1 && m_target) {
        QPointF delta = event->pos() - m_lastMousePos;
        applyResize(m_activeHandleIndex, delta);
        m_lastMousePos = event->pos();
        update();
    }
    event->accept();
}

void EditRect::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    m_activeHandleIndex = -1;
    event->accept();
}

void EditRect::applyResize(int handleIndex, const QPointF &delta) {
    // 示例：这里只更新显示用的 m_targetRect，并未实际操作目标图形
    switch (handleIndex) {
        case 0:
            m_targetRect.setTopLeft(m_targetRect.topLeft() + delta);
            break;
        case 1:
            m_targetRect.setTopRight(m_targetRect.topRight() + delta);
            break;
        case 2:
            m_targetRect.setBottomLeft(m_targetRect.bottomLeft() + delta);
            break;
        case 3:
            m_targetRect.setBottomRight(m_targetRect.bottomRight() + delta);
            break;
    }
    // TODO: 通知目标图形进行实际的几何更新，如 setVertex 等
    if (m_target) {
        m_target->prepareGeometryChange();
        m_target->update();
    }
}
