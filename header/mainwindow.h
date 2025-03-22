#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLabel>
#include <qgraphicsitem.h>
#include "polylineitem.h"
#include "arcitem.h"
#include "titlebar.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum DrawToolType {
        // 编辑工具
        DragScene,
        EditProperty,
        // 绘制工具
        None,
        Line,
        Circle,
        Polyline,
        Spiral,
        Arc,
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
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
private:// 编辑对象、ui
    void setItemStatus(bool visible, bool selectable, bool movable, QGraphicsItem* );
    void setItemsStatus(bool visible,bool selectable, bool movable,const std::vector<std::shared_ptr<LaserItem>>& items)
    {
        for (const auto& item : items)
        {
            if (item)
            {
                item->setVisible(visible);
                item->setFlag(QGraphicsItem::ItemIsMovable, movable);
                item->setFlag(QGraphicsItem::ItemIsSelectable, selectable);
            }
        }
    }
    void setAllDrawButtonChecked(bool);
    void setAllToolButtonChecked(bool);
    void setAllLayerButtonChecked(bool);
private: //全局状态
    // 记录画布放大倍率
    std::pair<double,double> sceneScale = {1,1};
    void setSceneScale(double, double);
    std::pair<double, double> getSceneScale();
    //记录图层情况
    int layerCount = 1;
    int currentLayer = 1;
private: // 初始化组件
    //titlebar
    TitleBar* titleBar;
    //statusbar
    QLabel* labelMouseCoordinate;
    QLabel* labelCurrentLayer;
    QLabel* labelCurrentGroup;
    QLabel* labelOperation;
    // Layer
    QVector<QPushButton*> layerButtons;
    //
    QAction* addNodeAction;
    QAction* removeNodeAction;
    QAction* insertChildNodeAction;
    void initTitleBar();
    void initGraphicsView();
    void initToolButton();
    void initLayerButton();
    void initStatusBar();
    void initPropertyTableWidget();
    void initTreeViewModel();
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
    void editPolyline(QPointF, PolylineItem *, DrawEventType);/*TODO*/
    void editArc(QPointF, ArcItem *, DrawEventType);/*TODO*/
    void editCircle(QGraphicsEllipseItem *, DrawEventType);/*TODO*/
    void editSpiral();/*TODO*/
    // 辅助线输入绘制
    QGraphicsLineItem* assisstLine1;
    QGraphicsLineItem* assisstLine2;
    QGraphicsPathItem* assisstArc1;
private:  // 绘制item工具
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
    void drawPolyline(QPointF,DrawEventType);
    void drawArc(QPointF,DrawEventType);
    void drawCircle(QPointF,DrawEventType);
    void drawRect(QPointF,DrawEventType);
    void drawSpiral(QPointF,DrawEventType);
    void drawPolygon(QPointF,DrawEventType);
    void drawEllipse(QPointF,DrawEventType);
private: // treeWidget事件

protected: // 键盘输入重载
    void keyPressEvent(QKeyEvent* ) override;
    void keyReleaseEvent(QKeyEvent* ) override;
private slots: // 接收graphicsview信号的槽
    void onGraphicsviewMouseMoved(QPoint);
    void onGraphicsviewMouseLeftPressed(QPoint);
    void onGraphicsviewMouseRightPressed(QPoint);
    void onGraphicsviewMouseLeftReleased(QPoint);
    void onGraphicsviewMouseRightReleased(QPoint);
    void onGraphicsviewMouseDoubleClicked(QPoint);
    void onGraphicsviewMouseWheelTriggered(QWheelEvent *);
private slots: // 绘制工具按钮
    void on_drawCircleButton_clicked();
    void on_propertyTableWidget_cellChanged(int row, int column);
    void on_drawPolylineButton_clicked();
    void on_drawArcButton_clicked();
    void on_drawSpiralButton_clicked();
    void on_drawRectButton_clicked();
    void on_drawPolygonButton_clicked();
    void on_drawEllipseButton_clicked();
private slots: // 编辑工具按钮
    void on_editButton_clicked();
    void on_drawTestLineButton_clicked();
    void on_rotateButton_clicked();
    void on_centerButton_clicked();
    void on_createOffsetButton_clicked();
    void on_deleteButton_clicked();
    void on_dragSceneButton_clicked();
    void on_undoButton_clicked();
    void on_redoButton_clicked();
private slots: // 图层按钮
    void onLayerButtonClicked(int);
    void onAddLayerButtonClicked();
private slots: // TreeViewModel的右键菜单栏
    void onTreeViewModelShowContextMenu(const QPoint &pos);
    void onTreeViewModelInsertChild();
    void onTreeViewModelAddNode();
    void onTreeViewModelRemoveNode();
public slots:
    void onTreeViewModelUpdateActions();
};
#endif // MAINWINDOW_H

