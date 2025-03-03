#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLabel>
#include <qgraphicsitem.h>
#include "polylineitem.h"
#include "arcitem.h"
#include "manager.h"
#include "titlebar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum DrawToolType {
        DragScene,

        None,
        Line,
        Circle,
        Polyline,
        Spiral,
        Arc,
        VariantLine,
        Rect,
        Ellipse,
        Polygon
    };
    enum DrawEventType {
        LeftPress,
        RightPress,
        LeftRelease,
        RightRelease,
        MouseMove,
    };
    enum LaserProperty {
        GroupId = 0,
        Power = 1,
        Frequency = 2,
    };
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    // 编辑对象、ui
    void setAllItemsMovable(bool);
    void setAllDrawButtonChecked(bool);
    void setAllToolButtonChecked(bool);
    // 记录画布放大倍率
    std::pair<double,double> sceneScale = {1,1};
    void setSceneScale(double, double);
    std::pair<double, double> getSceneScale();
    // 初始化组件
    TitleBar*titleBar;
    QLabel *labelMouseCoordinate;
    QLabel *labelOperation;
    void initTitleBar();
    void initGraphicsView();
    void initButton();
    void initStatusBar();
    void initOperationTreeWidget();
    void initPropertyTableWidget();
    void displayOperation(QString);
private:    // 编辑工具
    QPointF dragScenePoint = QPointF(0,0);
    void dragScene(QPointF,  DrawEventType);
    void copyItem();
    void deleteItem();
    // 编辑item对象
    QGraphicsItem *currentEditItem = NULL;
    int currentEditPolylineVertexIndex = -1;
    void editItem(QPointF,DrawEventType);
    void editLine(QGraphicsLineItem *, DrawEventType);
    void editCircle(QGraphicsEllipseItem *, DrawEventType);
    void editPolyline(QPointF, PolylineItem *, DrawEventType);
    void editArc();
    void editSpiral();
    // 辅助线输入绘制
    QGraphicsLineItem* assisstLine1;
    QGraphicsLineItem* assisstLine2;
    QGraphicsPathItem* assisstArc1;
private:    // 绘制item工具
    DrawToolType currentDrawTool = None;
    int polygonEdgeNum = 3; //绘制polygon使用
    void resetDrawToolStatus();
    //绘制对象暂存
    std::shared_ptr<QGraphicsEllipseItem> tmpCircle;
    std::shared_ptr<PolylineItem> tmpPolyline;
    std::shared_ptr<ArcItem> tmpArc;
    std::shared_ptr<QGraphicsRectItem> tmpRect;
    std::shared_ptr<QGraphicsPathItem> tmpSpiral;
    std::shared_ptr<QGraphicsPolygonItem> tmpPolygon;
    std::shared_ptr<QGraphicsEllipseItem> tmpEllipse;
    // 绘制逻辑
    void drawCircle(QPointF,DrawEventType);
    void drawPolyline(QPointF,DrawEventType);
    void drawArc(QPointF,DrawEventType);
    void drawRect(QPointF,DrawEventType);
    void drawSpiral(QPointF,DrawEventType);
    void drawPolygon(QPointF,DrawEventType);
    void drawEllipse(QPointF,DrawEventType);
protected:
    void keyPressEvent(QKeyEvent* ) override;
    void keyReleaseEvent(QKeyEvent* ) override;
private slots:
    // 接收graphicsview信号的槽
    void on_graphicsview_mousemove_occurred(QPoint);
    void on_graphicsview_mouseleftpress_occurred(QPoint);
    void on_graphicsview_mouserightpress_occurred(QPoint);
    void on_graphicsview_mouseleftrelease_occurred(QPoint);
    void on_graphicsview_mouserightrelease_occurred(QPoint);
    void on_graphicsview_mousedoubleclick_occurred(QPoint);
    void on_graphicsview_mousewheel_occurred(QWheelEvent *);
    // 绘制工具
    void on_drawCircleButton_clicked();
    void on_propertyTableWidget_cellChanged(int row, int column);
    void on_drawPolylineButton_clicked();
    void on_drawArcButton_clicked();
    void on_drawSpiralButton_clicked();
    void on_drawRectButton_clicked();
    void on_drawPolygonButton_clicked();
    void on_drawEllipseButton_clicked();
    // 编辑工具
    void on_resetButton_clicked();
    void on_drawTestLineButton_clicked();
    void on_rotateButton_clicked();
    void on_centerButton_clicked();
    void on_createOffsetButton_clicked();
    void on_deleteButton_clicked();
    void on_dragSceneButton_clicked();
    void on_undoButton_clicked();
    void on_redoButton_clicked();
};
#endif // MAINWINDOW_H

