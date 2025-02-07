#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLabel>
#include <qgraphicsitem.h>
#include <vector>
#include "polylineitem.h"
#include "variantlineitem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum DrawToolType {
        None,
        Line,
        Circle,
        Polyline,
        Spiral,
        Arc,
        VariantLine
    };
    enum DrawEventType {
        LeftClick,
        RightClick,
        MouseMove,
    };
    enum LaserProperty {
        GroupId = 0,
        Power = 1,
        Frequency = 2,
    };
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *Scene;

    std::vector<std::unique_ptr<QGraphicsItem>>
        Container;
    void setAllItemsMovable(bool);

    // 初始化组件
    QLabel *LabelMouseCoordinate;
    QLabel *LabelOperation;
    void initGraphicsView();
    void initStatusBar();
    void initOperationTreeWidget();
    void initPropertyTableWidget();
    void displayOperation(QString);

    // 编辑对象
    QGraphicsItem *CurrentEditItem;
    void editItem(QPointF);
    void editLine(QGraphicsLineItem *);
    void editCircle(QGraphicsEllipseItem *);
    void editArc(); /*TODO*/
    void editSpiral(); /*TODO*/
    void editVariantLine(); /*TODO*/

    // 绘制工具
    DrawToolType CurrentDrawTool = None;
    std::unique_ptr<QGraphicsLineItem> TmpLine;
    std::unique_ptr<QGraphicsEllipseItem> TmpCircle;
    std::unique_ptr<PolylineItem> TmpPolyline;
    std::unique_ptr<QGraphicsPathItem> TmpArc;
    std::unique_ptr<VariantLineItem> TmpVariantLine;
    void resetDrawToolStatus();
    void drawLine(QPointF,DrawEventType);
    void drawCircle(QPointF,DrawEventType);
    void drawPolyline(QPointF,DrawEventType);
    void drawArc(QPointF,DrawEventType); /*TODO*/
    void drawSpiral(QPointF,DrawEventType); /*TODO*/
    void drawVariantLine(QPointF,DrawEventType); /*TODO*/

private slots:
    // 接收graphicsview信号的槽
    void on_graphicsview_mousemove_occurred(QPoint);
    void on_graphicsview_mouseleftclick_occurred(QPoint);
    void on_graphicsview_mouserightclick_occurred(QPoint);
    void on_graphicsview_mouserelease_occurred(QPoint);

    // mainwindow与前端按钮绑定的槽
    void on_drawLineButton_clicked();
    void on_drawCircleButton_clicked();
    void on_propertyTableWidget_cellChanged(int row, int column);
    void on_resetButton_clicked();
    void on_drawPolylineButton_clicked();
    void on_drawTestLineButton_clicked();
    void on_drawArcButton_clicked();
    void on_drawSpiralButton_clicked();
    void on_drawVariantLineButton_clicked();
};
#endif // MAINWINDOW_H

