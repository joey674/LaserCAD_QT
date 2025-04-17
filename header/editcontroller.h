#ifndef EDITCONTROLLER_H
#define EDITCONTROLLER_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <qgraphicsitem.h>
#include "protocol.h"
#include "arcitem.h"
#include "polylineitem.h"
#include "manager.h"


class EditController {
public:
    GraphicsItem *currentEditItem = NULL;
    /// \brief editItemInScene     所有编辑事件都会传入该函数
    /// \param pointCoordscene event 接收的是鼠标坐标事件
    void editItemInScene(QPointF pointCoordscene, MouseEvent event);
    int currentEditPolylineVertexIndex = -1;
/// 编辑单个特定对象时调用
public:
    void editPolyline(QPointF pointCoordscene, PolylineItem *, MouseEvent event);
    void editArc(QPointF pointCoordscene, ArcItem *, MouseEvent event);
/// 更新对应的编辑Widget
public:
    void updateTabWidget();
    void updateTableViewModel();
/// 类似slot的回调
public:
    /// \brief onSceneSelectionChanged
    /// Scene的整体变动回调; 会执行一些需要全局状态管理的操作
    void onSceneSelectionChanged();

    /// \brief onTabWidgetCopyTabVectorCopy
    /// tabWidget的回调
    void onTabWidgetCopyTabVectorCopy(QPointF dir, double spacing, int count);
    void onTabWidgetCopyTabMatrixCopy(
        QPointF hVec, QPointF vVec, double hSpacing, double vSpacing, int hCount, int vCount);
    void onTabWidgetOffsetTabParallelOffset(double offset, double offsetNum) {
        GraphicsItem *item = static_cast < GraphicsItem * > (this->currentEditItem);
        Manager::getIns().setItemParallelOffset(item->getUUID(), offset, offsetNum);
    }
    void onTabWidgetMarkParamsTab(MarkParams params) {
        if (!this->currentEditItem) {
            return;
        }
        this->currentEditItem->setMarkParams(params);
    }
    void onTabWidgetDelayParamsTab(DelayParams params) {
        if (!this->currentEditItem) {
            return;
        }
        this->currentEditItem->setDelayParams(params);
    }
    void onTabWidgetArcGeometryTab(QPointF start, QPointF end, double angle) {
        if (!this->currentEditItem) {
            return;
        }
        this->currentEditItem->editVertex(0, start, 0);
        this->currentEditItem->editVertex(1, end, angle);
    }
    void onTabWidgetLineGeometryTab(QPointF start, QPointF end) {
        if (!this->currentEditItem) {
            return;
        }
        this->currentEditItem->editVertex(0, start, 0);
        this->currentEditItem->editVertex(1, end, 0);
    }
    void onTabWidgetPointGeometryTab(QPointF pos) {
        if (!this->currentEditItem) {
            return;
        }
        this->currentEditItem->editVertex(0, pos, 0);
    }
    void onTabWidgetCircleGeometryTab(QPointF pos, double radius) {
        if (!this->currentEditItem) {
            return;
        }
        CircleItem *item = static_cast < CircleItem * > (this->currentEditItem);
        item->editVertex(0, pos, 0);
        item->editRadius (radius);
    }

    void onTreeViewModelClicked(const QModelIndex & index);
    void onTreeViewModelSelectionChanged(const QItemSelection &selected,
                                         const QItemSelection &deselected);

    /// \brief onGraphicsItemPositionHasChanged 物体位置变换后的操作
    /// \param uuid
    void onGraphicsItemPositionHasChanged(UUID uuid);
    /// \brief onGraphicsItemSelectedHasChanged 物体选中后的操作
    /// \param uuid
    void onGraphicsItemSelectedHasChanged(UUID uuid, bool selected);
    /// \brief onGraphicsItemMouseRelease
    /// 物体上鼠标release事件
    void onGraphicsItemMouseRelease(UUID uuid);
    /// \brief onGraphicsItemMousePress
    /// 物体上鼠标press事件
    void  onGraphicsItemMousePress(UUID uuid);

private:
    static EditController ins;
    EditController() {};
    EditController(const EditController &);
    ~EditController() {};
    EditController &operator = (const EditController &);
public:
    static EditController &getIns();
};

#endif // EDITCONTROLLER_H
