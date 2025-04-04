#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLabel>
#include <qgraphicsitem.h>
#include <QTreeView>
#include "titlebar.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private: // 初始化组件
    // titlebar
    TitleBar* titleBar;
    // statusbar
    QLabel* labelMouseCoordinate;
    //
    QAction* addLayerAction;
    QAction* addGroupAction;
    QAction* deleteNodeAction;
    QAction* setLayerVisibleAction;
    QAction* setLayerUnvisibleAction;
    int selectedLayerIndex;

    ///
    void initTitleBar();
    void initGraphicsView();
    void initDrawToolButton();
    void initEditToolButton();
    void initLayerButton();
    void initStatusBar();
    void initTreeViewModel();
    void initTableViewModel();
    void test();

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
    void onDrawPointButtonClicked();;
    void onDrawCircleButtonClicked();
    void onDrawSpiralButtonClicked();
    void onDrawRectButtonClicked();
    void onDrawPolygonButtonClicked();
    void onDrawEllipseButtonClicked();
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
private slots: // TreeViewModel的右键菜单栏
    void onTreeViewModelShowContextMenu(const QPoint &pos);
    void onTreeViewModelAddLayer();
    void onTreeViewModelAddGroup();
    void onTreeViewModelDeleteNode();
    void onTreeViewModelSetLayerVisible();
    void onTreeViewModelSetLayerUnvisible();
    void onTreeViewModelNodeClicked();
public slots:
    void onTreeViewModelUpdateActions();
};
#endif // MAINWINDOW_H

