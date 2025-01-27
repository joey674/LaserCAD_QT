#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QDebug>
#include <QMainWindow>

class GraphicsView: public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsView(QWidget *parent = nullptr) {};
protected:
    // 重写系统事件导出到下面自定义的signals事件
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
signals:
    // 这里定义自己的逻辑
    void mouseLeftClick(QPoint);
    void mouseRightClick(QPoint);
    void mouseMove(QPoint);
};

#endif // GRAPHICSVIEW_H
