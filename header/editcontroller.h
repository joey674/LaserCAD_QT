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
    std::vector<std::shared_ptr<GraphicsItem> > m_currentEditItemGroup
        = std::vector<std::shared_ptr<GraphicsItem> >();
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
        //
        if (this->m_currentEditItemGroup.size() != 1) {
            return;
        }
        auto curEditItem = this->m_currentEditItemGroup[0];
        //
        QPointF unitOffset = dir * spacing;
        for (int i = 1; i <= count; ++i) {
            auto uuid = Manager::getIns().copyItem(curEditItem->getUUID());
            auto copiedItem = Manager::getIns().itemMapFind(uuid);
            if (!copiedItem) {
                continue;
            }
            QPointF offset = unitOffset * i;
            copiedItem->setCenterPos(curEditItem->getCenterPos() + offset);
        }
    }
    void onTabWidgetCopyTabMatrixCopy(
        QPointF hVec, QPointF vVec, double hSpacing, double vSpacing, int hCount, int vCount)
    {
        //
        if (this->m_currentEditItemGroup.size() != 1) {
            return;
        }
        auto curEditItem = this->m_currentEditItemGroup[0];
        //
        QPointF hOffset = hVec * hSpacing;
        QPointF vOffset = vVec * vSpacing;
        QPointF origin = curEditItem->getCenterPos();
        for (int row = 0; row < vCount; ++row) {
            for (int col = 0; col < hCount; ++col) {
                if (row == 0 && col == 0) {
                    continue;
                }
                auto uuid = Manager::getIns().copyItem(curEditItem->getUUID());
                auto copiedItem = Manager::getIns().itemMapFind(uuid);
                if (!copiedItem) {
                    continue;
                }
                QPointF offset = hOffset * col + vOffset * row;
                copiedItem->setCenterPos(origin + offset);
            }
        }
    }
    void onTabWidgetOffsetTabParallelOffset(double offset, double offsetNum) {
        //
        if (this->m_currentEditItemGroup.size() != 1) {
            return;
        }
        auto curEditItem = this->m_currentEditItemGroup[0];
        //
        Manager::getIns().setItemParallelOffset(curEditItem->getUUID(), offset, offsetNum);
        this->updateTableViewModel();
    }
    void onTabWidgetMarkParamsTab(MarkParams params) {
        //
        if (this->m_currentEditItemGroup.size() != 1) {
            return;
        }
        auto curEditItem = this->m_currentEditItemGroup[0];
        //
        curEditItem->setMarkParams(params);
        this->updateTableViewModel();
    }
    void onTabWidgetDelayParamsTab(DelayParams params) {
        //
        if (this->m_currentEditItemGroup.size() != 1) {
            return;
        }
        auto curEditItem = this->m_currentEditItemGroup[0];
        //
        curEditItem->setDelayParams(params);
        this->updateTableViewModel();
    }
    void onTabWidgetArcGeometryTab(QPointF start, QPointF end, double angle) {
        //
        if (this->m_currentEditItemGroup.size() != 1) {
            return;
        }
        auto curEditItem = this->m_currentEditItemGroup[0];
        //
        curEditItem->editVertex(0, start, 0);
        curEditItem->editVertex(1, end, angle);
        this->updateTableViewModel();
    }
    void onTabWidgetLineGeometryTab(QPointF start, QPointF end) {
        //
        if (this->m_currentEditItemGroup.size() != 1) {
            return;
        }
        auto curEditItem = this->m_currentEditItemGroup[0];
        //
        curEditItem->editVertex(0, start, 0);
        curEditItem->editVertex(1, end, 0);
        this->updateTableViewModel();
    }
    void onTabWidgetPointGeometryTab(QPointF pos) {
        //
        if (this->m_currentEditItemGroup.size() != 1) {
            return;
        }
        auto curEditItem = this->m_currentEditItemGroup[0];
        //
        curEditItem->editVertex(0, pos, 0);
        this->updateTableViewModel();
    }
    void onTabWidgetCircleGeometryTab(QPointF pos, double radius) {
        //
        if (this->m_currentEditItemGroup.size() != 1) {
            return;
        }
        auto curEditItem = this->m_currentEditItemGroup[0];
        //
        CircleItem *item = static_cast<CircleItem *>(curEditItem.get());
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
            auto item = m_currentEditItemGroup[i];
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

    /// \brief onTreeViewModelClicked
    /// \param index
    void onTreeViewModelClicked(const QModelIndex &index) {}
    /// \brief onTreeViewModelSelectionChanged
    ///
    /// TODO 重构 选中不是按照顺序
    void onTreeViewModelSelectionChanged(const QItemSelection &selected,
                                         const QItemSelection &deselected);

    /// \brief onSceneSelectionChanged
    /// Scene的整体变动回调; 全局的管控
    /// TODO 重构 选中不是按照顺序
    void onSceneSelectionChanged() {}
    /// \brief onGraphicsItemPositionHasChanged
    /// 单个物体位置变换后的回调
    void onGraphicsItemPositionHasChanged(UUID uuid) { this->updateTableViewModel(); }
    /// \brief onGraphicsItemSelectedHasChanged
    /// 单个物体选中状态变化的回调; selected状态可以重叠, 当tree中选中令scene中选中时, scene中的选中回调也会让tree选中; 但是不会触发selectedChanged;
    void onGraphicsItemSelectedHasChanged(UUID uuid, bool selected);
    /// \brief onGraphicsItemMouseRelease
    /// 物体上鼠标release事件; 更新一次tabWidget(尽量不实时更新 减少开销)
    void onGraphicsItemMouseRelease(UUID uuid)
    {
        // this->updateTableViewModel();
        this->updateTabWidget();
    }
    /// \brief onGraphicsItemMousePress
    /// 物体上鼠标press事件
    void onGraphicsItemMousePress(UUID uuid) {}

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
