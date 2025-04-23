#ifndef EDITRECT_H
#define EDITRECT_H

#include <QGraphicsItem>
#include <QPointer>

class GraphicsItem;

class EditRect : public QGraphicsItem {
public:
    EditRect(GraphicsItem *target);

    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    GraphicsItem *m_target; // 被控制的目标对象
    QRectF m_targetRect;             // 目标的boundingRect
    int m_handleSize = 6;
    int m_activeHandleIndex = -1;
    QPointF m_lastMousePos;

    QRectF handleRect(int index) const;
    int hitTestHandles(const QPointF &pos) const;
    void applyResize(int handleIndex, const QPointF &delta);
};

#endif // EDITRECT_H

