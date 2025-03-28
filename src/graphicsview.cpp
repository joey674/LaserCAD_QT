#include "graphicsview.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "keyboardmanager.h"

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    QPoint point = event->pos();
    if (event->button() == Qt::LeftButton)
    {
        emit mouseLeftPressed(point);
    } else if (event->button() == Qt::RightButton)
    {
        emit mouseRightPressed(point);
    }

    QGraphicsView::mousePressEvent(event);
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QPoint point = event->pos();
    emit mouseMoved(point);

    QGraphicsView::mouseMoveEvent(event);
}

void GraphicsView::mouseReleaseEvent(QMouseEvent * event)
{
    QPoint point = event->pos();
    if (event->button() == Qt::LeftButton)
        emit mouseLeftReleased(point);
    else if (event->button() == Qt::RightButton)
        emit mouseRightReleased(point);

    QGraphicsView::mouseReleaseEvent(event);
}

void GraphicsView::wheelEvent(QWheelEvent * event)
{
    emit mouseWheelTriggered(event);

    event->accept();
}

void GraphicsView::mouseDoubleClickEvent(QMouseEvent* event)
{
    QPoint point = event->pos();
    if (event->button() == Qt::RightButton)
        emit mouseDoubleClicked(point);

    QGraphicsView::mouseDoubleClickEvent(event);
}

void GraphicsView::keyPressEvent(QKeyEvent *event)
{
    KeyboardManager::getIns().onGraphicsViewKeyPressEvent(event);
}

void GraphicsView::keyReleaseEvent(QKeyEvent *event)
{
KeyboardManager::getIns().onGraphicsViewKeyReleaseEvent(event);
}
