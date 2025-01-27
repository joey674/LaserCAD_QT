#include "myqgraphicsview.h"
#include <QMouseEvent>

MyQGraphicsView::MyQGraphicsView(QWidget *parent) : QGraphicsView(parent)
{

}

void MyQGraphicsView::keyPressEvent(QKeyEvent *event)
{
    emit KeyPress(event);

    QGraphicsView::keyPressEvent(event);
}

void MyQGraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        QPoint point=event->pos();
        emit mouseDoubleClick(point);
    }

    QGraphicsView::mouseDoubleClickEvent(event);
}

void MyQGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        QPoint point=event->pos();
        emit mousePress(point);
    }

    QGraphicsView::mousePressEvent(event);
}

void MyQGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QPoint point=event->pos();

    emit mouseMove(point);
    QGraphicsView::mouseMoveEvent(event);
}

