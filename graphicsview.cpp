#include "graphicsview.h"



void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QPoint point = event->pos();
        emit mouseLeftClick(point);
    } else if (event->button() == Qt::RightButton) {
        QPoint point = event->pos();
        emit mouseRightClick(point);
    }
    QGraphicsView::mousePressEvent(event);
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QPoint point = event->pos();
    emit mouseMove(point);
    QGraphicsView::mouseMoveEvent(event);
}
