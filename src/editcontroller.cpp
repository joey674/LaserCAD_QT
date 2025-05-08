#include "editcontroller.h"
#include "polylineitem.h"
#include "arcitem.h"
#include "protocol.h"
#include "logger.h"
#include "scenecontroller.h"
#include "treemodel.h"
#include "uimanager.h"
#include "tablemodel.h"
#include "uimanager.h"
#include <QModelIndexList>

EditController EditController::ins;

///
/// \brief EditController::updateTabWidget
///
void EditController::updateTabWidget() {
    // clear
    TabWidget *tabWidget = UiManager::getIns().UI()->tabWidget;
    tabWidget->clearAllTabs();
    //
    if (this->m_currentEditItemGroup.empty()) {
        // WARN_MSG("no edit item");
        return;
    } else if (this->m_currentEditItemGroup.size() == 1) { // 只有一个编辑对象
        auto curEditItem = this->m_currentEditItemGroup[0];
        switch (curEditItem->type()) {
            case GraphicsItemType::Arc:
                UiManager::getIns().UI()->tabWidget->addArcGeometryTab(curEditItem->getUUID());
                break;
            case GraphicsItemType::Circle:
                UiManager::getIns().UI()->tabWidget->addCircleGeometryTab(curEditItem->getUUID());
                break;
            case GraphicsItemType::Line:
                UiManager::getIns().UI()->tabWidget->addLineGeometryTab(curEditItem->getUUID());
                break;
            case GraphicsItemType::Point:
                UiManager::getIns().UI()->tabWidget->addPointGeometryTab(curEditItem->getUUID());
                break;
            case GraphicsItemType::Polyline:
                // UiManager::getIns().UI()->tabWidget->addPolylineGeometryTab(curEditItem->getUUID());
                break;
            case GraphicsItemType::Rect:
                UiManager::getIns().UI()->tabWidget->addRectGeometryTab(curEditItem->getUUID());
                break;
            case GraphicsItemType::Ellipse:
                UiManager::getIns().UI()->tabWidget->addEllipseGeometryTab(curEditItem->getUUID());
                break;
            case GraphicsItemType::Spiral:
                UiManager::getIns().UI()->tabWidget->addSpiralGeometryTab(curEditItem->getUUID());
                break;
            case GraphicsItemType::Polygon:
                UiManager::getIns().UI()->tabWidget->addPolygonGeometryTab(curEditItem->getUUID());
                break;
            default:
                break;
        }
        UiManager::getIns().UI()->tabWidget->addCopyTab(curEditItem->getUUID());
        UiManager::getIns().UI()->tabWidget->addOffsetTab(curEditItem->getUUID());
        UiManager::getIns().UI()->tabWidget->addMarkParamsTab(curEditItem->getUUID());
        UiManager::getIns().UI()->tabWidget->addDelayParamsTab(curEditItem->getUUID());
        return;
    } else { // 多个编辑对象
        auto uuids = std::vector < UUID > ();
        for (auto item : this->m_currentEditItemGroup) {
            uuids.push_back(item->getUUID());
        }
        UiManager::getIns().UI()->tabWidget->addMultiItemsEditTab(uuids);
        UiManager::getIns().UI()->tabWidget->addMultiItemsAlignTab(uuids);
        UiManager::getIns().UI()->tabWidget->addDuoItemsBoolOpTab(uuids);
    }
}

void EditController::updateTableViewModel() {
    // // clear
    // TableModel* model = qobject_cast < TableModel * > (UiManager::getIns().UI()->tableView->model());
    // model->clear();
    // //
    // if (this->m_currentEditItemGroup.empty()) {
    //     return;
    // } else if (this->m_currentEditItemGroup.size() == 1) { // 只有一个编辑对象
    //     auto curEditItem = this->m_currentEditItemGroup[0];
    //     model->setCurrentDisplayItem(curEditItem->getUUID());
    // } else {
    // }
}

void EditController::onTreeViewModelSelectionChanged(
    const QItemSelection &selected,
    const QItemSelection &deselected) {
    auto treeView = UiManager::getIns().UI()->treeView;
    TreeModel *model = qobject_cast < TreeModel * > (treeView->model());
    // 分类出来(注意这里用的是所有选中, selected只是新选中的信号量 不是所有选中目标)
    QSet < QModelIndex > groupIndexes;
    QSet < QString > itemUUIDs;
    auto selectedIndexes = treeView->selectionModel()->selectedIndexes();
    for (const QModelIndex &idx : selectedIndexes) {
        if (idx.column() != 0) {
            continue;
        }
        QString type = model->nodeProperty(idx, TreeNodePropertyIndex::Type).toString();
        if (type == "Group") {
            groupIndexes.insert(idx);
        } else if (type == "Item" || type == "Signal") {
            itemUUIDs.insert(model->nodeProperty(idx, TreeNodePropertyIndex::UUID).toString());
        }
    }
    // DEBUG_VAR(groupIndexes);
    // DEBUG_VAR(itemUUIDs);
    // 检查 group 的子节点中是否有选中项
    bool conflictFound = false;
    for (const QModelIndex &groupIdx : groupIndexes) {
        auto children = model->getAllChildNodes(groupIdx);
        for (TreeNode *node : children) {
            QString uuid = node->property(TreeNodePropertyIndex::UUID).toString();
            // DEBUG_VAR(uuid);
            if (itemUUIDs.contains(uuid)) {
                conflictFound = true;
                break;
            }
        }
        if (conflictFound) {
            break;
        }
    }
    // 如果有就清空选中
    if (conflictFound) {
        treeView->selectionModel()->clearSelection();
        WARN_MSG("cant select group and its son node at the same time; will clear selection");
        return;
    }
    // 处理select对象
    for (const QModelIndex &idx : selected.indexes()) {
        QString type = model->nodeProperty(idx, TreeNodePropertyIndex::Type).toString();
        UUID uuid = model->nodeProperty(idx, TreeNodePropertyIndex::UUID).toString();
        auto item = Manager::getIns().itemMapFind(uuid);
        if (type == "Layer") {
        } else if (type == "Item" ) {
            item->setSelected(true);
        } else if (type == "Signal") {
            // 设置curEditItemGroup,添加item(因为对于signal来说,无法在场景中选中 从而触发添加进editgroup)
            this->m_currentEditItemGroup.push_back(item);
        }
    }
    // 处理deselect对象
    for (const QModelIndex &idx : deselected.indexes()) {
        if (idx.column() != 0) {
            continue;
        }
        QString type = model->nodeProperty(idx, TreeNodePropertyIndex::Type).toString();
        UUID uuid = model->nodeProperty(idx, TreeNodePropertyIndex::UUID).toString();
        auto item = Manager::getIns().itemMapFind(uuid);
        if (type == "Item" ) {
            item->setSelected(false);
        } else if (type == "Signal") {
            // 设置curEditItemGroup,移除item
            auto it = std::remove_if(this->m_currentEditItemGroup.begin(),
                                     this->m_currentEditItemGroup.end(),
            [&](const std::shared_ptr < GraphicsItem > &ptr) {
                return ptr == item;
            });
            this->m_currentEditItemGroup.erase(it, this->m_currentEditItemGroup.end());
        }
    }
}

void EditController::onGraphicsItemSelectedHasChanged(UUID uuid, bool selected) {
    // GraphicsItem
    auto item = Manager::getIns().itemMapFind(uuid);
    // TreeViewModel
    auto treeView = UiManager::getIns().UI()->treeView;
    TreeModel *model = qobject_cast < TreeModel * > (treeView->model());
    QModelIndex index = model->getIndex(uuid);
    Q_ASSERT(index.isValid());
    //
    if (selected) {
        // 设置treeview中选中
        treeView->selectionModel()->select(index,
                                           QItemSelectionModel::Select | QItemSelectionModel::Rows);
        treeView->expandToIndex(index);
        // 设置curEditItemGroup,添加item
        this->m_currentEditItemGroup.push_back(item);
    } else {
        // 设置treeview中取消选中
        treeView->selectionModel()->select(index,
                                           QItemSelectionModel::Deselect
                                           | QItemSelectionModel::Rows);
        treeView->expandToIndex(index);
        // 设置curEditItemGroup,移除item
        auto it = std::remove_if(this->m_currentEditItemGroup.begin(),
                                 this->m_currentEditItemGroup.end(),
        [&](const std::shared_ptr < GraphicsItem > &ptr) {
            return ptr == item;
        });
        this->m_currentEditItemGroup.erase(it, this->m_currentEditItemGroup.end());
    }
    //
    this->updateTabWidget();
    this->updateTableViewModel();
    this->updateEditRect();
}

EditController &EditController::getIns() {
    return ins;
}
