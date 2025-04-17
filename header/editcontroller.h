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
/// \brief m_currentEditItem
/// m_currentEditItemGroup
public:
    GraphicsItem *m_currentEditItem = NULL;
    std::vector < GraphicsItem * > m_currentEditItemGroup = std::vector < GraphicsItem * > ();
/// \brief editItemInScene     scene中的编辑事件会传入
/// \param pointCoordscene event 接收的是鼠标坐标事件
public:
    void editItemInScene(QPointF pointCoordscene, MouseEvent event);
    int currentEditPolylineVertexIndex = -1;
    void editPolyline(QPointF pointCoordscene, PolylineItem *, MouseEvent event);
    void editArc(QPointF pointCoordscene, ArcItem *, MouseEvent event);
/// 更新对应的编辑Widget
public:
    void updateTabWidget();
    void updateTableViewModel();
/// 类似slot的回调
public:
    /// \brief onTabWidgetCopyTabVectorCopy
    /// tabWidget的回调
    void onTabWidgetCopyTabVectorCopy(QPointF dir, double spacing, int count) {
        if (!this->m_currentEditItem) {
            return;
        }
        GraphicsItem *item = static_cast < GraphicsItem * > (this->m_currentEditItem);
        QPointF unitOffset = dir * spacing;
        for (int i = 1; i <= count; ++i) {
            auto uuid = Manager::getIns().copyItem(item->getUUID());
            auto copiedItem = Manager::getIns().itemMapFind(uuid);
            if (!copiedItem) {
                continue;
            }
            QPointF offset = unitOffset * i;
            // Manager::getIns().setItemPosition(copiedItem->getUUID(),  item->getCenterPos() + offset);
            copiedItem->setCenterPos(item->getCenterPos() + offset);
        }
    }
    void onTabWidgetCopyTabMatrixCopy(
        QPointF hVec, QPointF vVec, double hSpacing, double vSpacing, int hCount, int vCount);
    void onTabWidgetOffsetTabParallelOffset(double offset, double offsetNum) {
        GraphicsItem *item = static_cast < GraphicsItem * > (this->m_currentEditItem);
        Manager::getIns().setItemParallelOffset(item->getUUID(), offset, offsetNum);
        this->updateTableViewModel();
    }
    void onTabWidgetMarkParamsTab(MarkParams params) {
        if (!this->m_currentEditItem) {
            return;
        }
        this->m_currentEditItem->setMarkParams(params);
        this->updateTableViewModel();
    }
    void onTabWidgetDelayParamsTab(DelayParams params) {
        if (!this->m_currentEditItem) {
            return;
        }
        this->m_currentEditItem->setDelayParams(params);
        this->updateTableViewModel();
    }
    void onTabWidgetArcGeometryTab(QPointF start, QPointF end, double angle) {
        if (!this->m_currentEditItem) {
            return;
        }
        this->m_currentEditItem->editVertex(0, start, 0);
        this->m_currentEditItem->editVertex(1, end, angle);
        this->updateTableViewModel();
    }
    void onTabWidgetLineGeometryTab(QPointF start, QPointF end) {
        if (!this->m_currentEditItem) {
            return;
        }
        this->m_currentEditItem->editVertex(0, start, 0);
        this->m_currentEditItem->editVertex(1, end, 0);
        this->updateTableViewModel();
    }
    void onTabWidgetPointGeometryTab(QPointF pos) {
        if (!this->m_currentEditItem) {
            return;
        }
        this->m_currentEditItem->editVertex(0, pos, 0);
        this->updateTableViewModel();
    }
    void onTabWidgetCircleGeometryTab(QPointF pos, double radius) {
        if (!this->m_currentEditItem) {
            return;
        }
        CircleItem *item = static_cast < CircleItem * > (this->m_currentEditItem);
        item->editVertex(0, pos, 0);
        item->editRadius (radius);
        this->updateTableViewModel();
    }
    void onTabWidgetMutiEditTab(std::vector < MultiEditParam > params) {
        if (this->m_currentEditItemGroup.empty()) {
            return;
        }
        DEBUG_MSG(m_currentEditItemGroup.size());
        for (size_t i = 0; i < m_currentEditItemGroup.size(); ++i) {
            GraphicsItem* item = m_currentEditItemGroup[i];
            MarkParams mark = item->getMarkParams();
            DelayParams delay = item->getDelayParams();
            QPointF pos = item->getCenterPos ();
            for (const MultiEditParam& param : params) {
                QVariant val = param.baseValue;
                QVariant delta = param.deltaValue;
                QVariant finalVal;
                // 处理加法（支持 int 和 double）
                if (val.typeId() == QVariant::Double || delta.typeId() == QVariant::Double) {
                    finalVal = val.toDouble() + i * delta.toDouble();
                } else {
                    finalVal = val.toInt() + static_cast < int > (i) * delta.toInt();
                }
                const QString& key = param.fieldName;
                // --- MarkParams ---
                if (key == "MarkParams: markSpeed" || key == "MarkParams: jumpSpeed"
                        || key == "MarkParams: power" || key == "MarkParams: pulseWidth") {
                    mark.set(key, finalVal);
                } else if (key == "MarkParams: frequency" || key == "MarkParams: repetTime"
                           || key == "MarkParams: wobelAml" || key == "MarkParams: wobelFreq") {
                    mark.set(key, finalVal);
                }
                // --- DelayParams ---
                else if (key == "DelayParams: startDelay" || key == "DelayParams: endDelay"
                         || key == "DelayParams: markDelay" || key == "DelayParams: jumpDelay"
                         || key == "DelayParams: polygonDelay") {
                    delay.set(key, finalVal);
                }
                // --- Position ---
                else if (key == "Position.x") {
                    pos.setX(finalVal.toDouble());
                } else if (key == "Position.y") {
                    pos.setY(finalVal.toDouble());
                }
            }
            item->setMarkParams(mark);
            item->setDelayParams(delay);
            DEBUG_VAR(pos);
            item->setCenterPos(pos);
        }
    }

    /// \brief onSceneSelectionChanged
    /// Scene的整体变动回调; 会执行一些需要全局状态管理的操作
    void onSceneSelectionChanged() {
        // 先全部重置
        this->m_currentEditItem = nullptr;
        this->m_currentEditItemGroup.clear();
        auto selectedItems = SceneManager::getIns().scene->selectedItems();
        // selectedItems个数为1时设置为当前编辑对象
        if (selectedItems.size() == 1) {
            auto qtItem = selectedItems.at(0);
            this->m_currentEditItem = static_cast < GraphicsItem * > (qtItem);
        } else if(selectedItems.size() > 1) {
            for (int i = 0; i < selectedItems.size(); ++i) {
                auto *qtItem  = selectedItems.at(i);
                auto * item = static_cast < GraphicsItem * > (qtItem);
                this->m_currentEditItemGroup.push_back(item);
            }
        }
        // 更新tabwidget
        updateTabWidget();
        // 更新tablemodel
        updateTableViewModel();
    }
    /// \brief onTreeViewModelClicked
    /// \param index
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
