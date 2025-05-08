#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QDebug>
#include <QMainWindow>
#include <QApplication>
#include <QPainter>
#include "logger.h"

class GraphicsView: public QGraphicsView {
    Q_OBJECT
public:
    explicit GraphicsView(QWidget *parent = nullptr) {};
    ~GraphicsView() {
        INFO_MSG( "GraphicsView destructed");
    }

protected:
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void wheelEvent(QWheelEvent *) override;
    void mouseDoubleClickEvent(QMouseEvent*) override;
    void keyPressEvent(QKeyEvent * event) override;
    void keyReleaseEvent(QKeyEvent * event) override;
signals:
    void mouseLeftPressed(QPoint);
    void mouseRightPressed(QPoint);
    void mouseLeftReleased(QPoint);
    void mouseRightReleased(QPoint);
    void mouseMoved(QPoint);
    void mouseDoubleClicked(QPoint);
    void mouseWheelTriggered(QWheelEvent *);
};

#endif // GRAPHICSVIEW_H
