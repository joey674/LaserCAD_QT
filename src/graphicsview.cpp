#include "header/graphicsview.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QGraphicsScene>

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QPoint point = event->pos();
        emit mouseleftclick_event(point);
    } else if (event->button() == Qt::RightButton) {
        QPoint point = event->pos();
        emit mouserightclick_event(point);
    }
    QGraphicsView::mousePressEvent(event);
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QPoint point = event->pos();
    emit mousemove_event(point);

    QGraphicsView::mouseMoveEvent(event);
}

void GraphicsView::mouseReleaseEvent(QMouseEvent * event)
{
    QPoint point = event->pos();
    emit mouserelease_event(point);

    if (event->button() == Qt::LeftButton)
    {
    } else if (event->button() == Qt::RightButton)
    {
    }

    QGraphicsView::mouseReleaseEvent(event);
}

void GraphicsView::wheelEvent(QWheelEvent * event)
{
    if (event->angleDelta().y() > 0) {
        this->scale(1.2, 1.2);
    } else {
        this->scale(0.8, 0.8);
    }
    event->accept();
}

void GraphicsView::mouseDoubleClickEvent(QMouseEvent* event)
{
    QPoint point = event->pos();
    if (event->button() == Qt::RightButton) {
        emit mousedoubleclick_event(point);
    }
}
