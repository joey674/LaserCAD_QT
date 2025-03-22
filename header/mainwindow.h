#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLabel>
#include <qgraphicsitem.h>
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
    //titlebar
    TitleBar* titleBar;
    //statusbar
    QLabel* labelMouseCoordinate;
    QLabel* labelCurrentLayer;
    QLabel* labelCurrentGroup;
    QLabel* labelOperation;
    //
    QAction* addNodeAction;
    QAction* removeNodeAction;
    QAction* insertChildNodeAction;
    ///
    void initTitleBar();
    void initGraphicsView();
    void initToolButton();
    void initLayerButton();
    void initStatusBar();
    void initPropertyTableWidget();
    void initTreeViewModel();
    void displayOperation(QString);

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

