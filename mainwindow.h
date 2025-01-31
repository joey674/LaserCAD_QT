#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLabel>
#include <qgraphicsitem.h>
#include <variant>
#include <vector>
#include "graphicsview.h"

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
        Circle
    };
    enum DrawEventType {
        LeftClick,
        RightClick,
        MouseMove
    };
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *Scene;

    // 绘制对象管理
    std::vector<std::variant<
        std::unique_ptr<QGraphicsEllipseItem>,
        std::unique_ptr<QGraphicsLineItem>>>
        Container;
    int ItemId = 1;

    // 绘制工具状态
    DrawToolType CurrentDrawTool = None;
    std::unique_ptr<QGraphicsLineItem> TmpLine;
    std::unique_ptr<QGraphicsEllipseItem> TmpCircle;

    // 状态栏
    QLabel *LabelMouseCoordinate;
    QLabel *LabelOperation;

    void initGraphicsView();
    void initStatusBar();
    void initTreeWidget();
    void displayOperation(QString);

    void resetDrawToolStatus();
    void drawLine(QPointF,DrawEventType);
    void drawCircle(QPointF,DrawEventType);
private slots:
    // 接收graphicsview信号的槽
    void on_graphicsview_mousemove_occurred(QPoint);
    void on_graphicsview_mouseleftclick_occurred(QPoint);
    void on_graphicsview_mouserightclick_occurred(QPoint);

    // mainwindow与前端按钮绑定的槽
    void on_drawLineButton_clicked();
    void on_drawCircleButton_clicked();
};
#endif // MAINWINDOW_H

