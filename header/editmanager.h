#ifndef EDITMANAGER_H
#define EDITMANAGER_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <qgraphicsitem.h>
#include "protocol.h"
#include "arcitem.h"
#include "polylineitem.h"


class EditManager {
public:
    QGraphicsItem *currentEditItem = NULL;
    /// \brief editItem     所有编辑事件都会传入该函数
    /// \param pointCoordscene event 接收的是鼠标坐标事件
    void editItem(QPointF pointCoordscene, MouseEvent event);
    int currentEditPolylineVertexIndex = -1;
/// 编辑单个特定对象时调用
public:
    void editPolyline(QPointF pointCoordscene, PolylineItem *, MouseEvent event);
    void editArc(QPointF pointCoordscene, ArcItem *, MouseEvent event);
    void updateTabWidget();
    void updateTableViewModel();
/// 类似slot
public:
    void onSceneSelectionChanged();
    void onTabWidgetCopyTabVectorCopy(QPointF dir, double spacing, int count);;
    void onTabWidgetCopyTabMatrixCopy(
        QPointF hVec, QPointF vVec, double hSpacing, double vSpacing, int hCount, int vCount);
    void onTabWidgetOffsetTabParallelOffset(double offset, double offsetNum) {
        GraphicsItem *item = static_cast < GraphicsItem * > (this->currentEditItem);
        item->setParallelOffset(offset, offsetNum);
    }

private:
    static EditManager ins;
    EditManager() {};
    EditManager(const EditManager &);
    ~EditManager() {};
    EditManager &operator = (const EditManager &);
public:
    static EditManager &getIns();
};

#endif // EDITMANAGER_H
