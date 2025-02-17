#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QDebug>
#include <QMainWindow>
#include <QApplication>
#include <QPainter>

class GraphicsView: public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsView(QWidget *parent = nullptr) {
        // setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    };
    enum EventType {
        LeftPress,
        RightPress,
        LeftRelease,
        RightRelease,
        MouseMove,
    };

protected:
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void wheelEvent(QWheelEvent *) override;
    void mouseDoubleClickEvent(QMouseEvent*) override;
signals:
    void mouseleftpress_event(QPoint);
    void mouserightpress_event(QPoint);
    void mouseleftrelease_event(QPoint);
    void mouserightrelease_event(QPoint);
    void mousemove_event(QPoint);
    void mousedoubleclick_event(QPoint);
};

#endif // GRAPHICSVIEW_H
