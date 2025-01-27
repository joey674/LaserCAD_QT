#ifndef MYQGRAPHICSVIEW_H
#define MYQGRAPHICSVIEW_H

#include <QObject>
#include <QGraphicsView>

class MyQGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyQGraphicsView(QWidget *parent = nullptr);

private:
    void keyPressEvent(QKeyEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
signals:
    void KeyPress(QKeyEvent *event);
    void mouseDoubleClick(QPoint point);
    void mousePress(QPoint point) ;
    void mouseMove(QPoint point) ;
};

#endif // MYQGRAPHICSVIEW_H

