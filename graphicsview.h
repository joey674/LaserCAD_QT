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
    explicit GraphicsView(QWidget *parent = nullptr) {};
protected:
    // 重写系统事件导出到下面自定义的signals事件
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void wheelEvent(QWheelEvent *) override;
signals:
    void mouseleftclick_event(QPoint);
    void mouserightclick_event(QPoint);
    void mouserelease_event(QPoint);
    void mousemove_event(QPoint);
};

#endif // GRAPHICSVIEW_H
