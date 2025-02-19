#include "header/graphicsview.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QGraphicsScene>

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    QPoint point = event->pos();
    if (event->button() == Qt::LeftButton)
    {
        this->setDragMode(QGraphicsView::RubberBandDrag);
        emit mouseleftpress_event(point);
    } else if (event->button() == Qt::RightButton)
    {
        this->setDragMode(QGraphicsView::NoDrag);
        emit mouserightpress_event(point);
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
    if (event->button() == Qt::LeftButton)
        emit mouseleftrelease_event(point);
    else if (event->button() == Qt::RightButton)
        emit mouserightrelease_event(point);

    QGraphicsView::mouseReleaseEvent(event);
}

void GraphicsView::wheelEvent(QWheelEvent * event)
{
    emit mousewheel_event(event);

    event->accept();
}

void GraphicsView::mouseDoubleClickEvent(QMouseEvent* event)
{
    QPoint point = event->pos();
    if (event->button() == Qt::RightButton)
        emit mousedoubleclick_event(point);

    QGraphicsView::mouseDoubleClickEvent(event);
}
