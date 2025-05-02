#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLabel>
#include <qgraphicsitem.h>
#include <QTreeView>
#include "titlebar.h"


QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private: // 初始化组件
    TitleBar *titleBar;
    QLabel *labelMouseCoordinate;
    void initTitleBar();
    void initGraphicsView();
    void initDrawToolButton();
    void initEditToolButton();
    void initLayerButton();
    void initHardwareButton();
    void initStatusBar();
    void initTreeViewModel();
    void initTableViewModel();
    void initTabWidget();
    void test();
public: // 把编辑/绘制模式下几个按钮按下的逻辑的初始化抽象一下
    void setEditMode();
    void setDrawMode();
protected: // 键盘输入重载
    void keyPressEvent(QKeyEvent* ) override;
    void keyReleaseEvent(QKeyEvent* ) override;
    void resizeEvent(QResizeEvent *event) override;
private slots: // 接收graphicsview信号的槽
    void onGraphicsviewMouseMoved(QPoint);
    void onGraphicsviewMouseLeftPressed(QPoint);
    void onGraphicsviewMouseRightPressed(QPoint);
    void onGraphicsviewMouseLeftReleased(QPoint);
    void onGraphicsviewMouseRightReleased(QPoint);
    void onGraphicsviewMouseRightDoubleClicked(QPoint);
    void onGraphicsviewMouseWheelTriggered(QWheelEvent *);
private slots: // 绘制工具按钮
    void onDrawLineButtonClicked();
    void onDrawPolylineButtonClicked();
    void onDrawArcButtonClicked();
    void onDrawPointButtonClicked();
    void onDrawCircleButtonClicked();
    void onDrawSpiralButtonClicked();
    void onDrawRectButtonClicked();
    void onDrawPolygonButtonClicked();
    void onDrawEllipseButtonClicked();
private slots: // 编辑工具按钮
    void onEditButtonClicked();
    void onCenterButtonClicked();
    void onMirrorHorizontalButtonClicked();
    void onMirrorVerticalButtonClicked();
    void onAlignButtonClicked();
    //
    void onDragSceneButtonClicked();
    //
    void onBreakCopiedItemButtonClicked();
    void onBreakOffsetItemButtonClicked();
    //
    void onDeleteButtonClicked();
    void onCutButtonClicked();
    void onCopyButtonClicked();
    void onPasteButtonClicked();
    //
    void onDrawTestLineButtonClicked() {}
    void onUndoButtonClicked() {}
    void onRedoButtonClicked() {}
private slots: // 硬件操作按钮
    void onDigitalInButtonClicked();
    void onDigitalOutButtonClicked();
    void onDoPauseButtonClicked();
    void onDelayTimeButtonClicked();
    void onMotionButtonClicked();
    void onLoopButtonClicked();
private slots: //图层按钮
    void onAddLayerButtonClicked();
    void onDeleteLayerButtonClicked();
private slots: // TreeViewModel的右键菜单栏
    void onTreeViewModelShowContextMenu(const QPoint &pos);
    void onTreeViewModelAddLayer();
    void onTreeViewModelAddGroup();
    void onTreeViewModelDeleteNode();
    void onTreeViewModelCopyNode();
    void onTreeViewModelSetLayerVisible();
    void onTreeViewModelSetLayerUnvisible();
    void onTreeViewModelSelectAllItemsInGroup();
public slots:
    void onTreeViewModelUpdateActions();
};
#endif // MAINWINDOW_H

