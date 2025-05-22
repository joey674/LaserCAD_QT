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
    TabWidget *editTabWidget = UiManager::getIns(). editTabWidget;
    editTabWidget->clearAllTabs();
    //
    if (this->m_currentEditItemGroup.empty()) {
        // WARN_MSG("no edit item");
    } else if (this->m_currentEditItemGroup.size() == 1) { // 只有一个编辑对象
        auto curEditItem = this->m_currentEditItemGroup[0];
        switch (curEditItem->type()) {
            case GraphicsItemType::Arc:
                UiManager::getIns(). editTabWidget->addArcGeometryTab(curEditItem->getUUID());
                break;
            case GraphicsItemType::Circle:
                UiManager::getIns(). editTabWidget->addCircleGeometryTab(curEditItem->getUUID());
                break;
            case GraphicsItemType::Line:
                UiManager::getIns(). editTabWidget->addLineGeometryTab(curEditItem->getUUID());
                break;
            case GraphicsItemType::Point:
                UiManager::getIns(). editTabWidget->addPointGeometryTab(curEditItem->getUUID());
                break;
            case GraphicsItemType::Polyline:
                // UiManager::getIns(). editTabWidget->addPolylineGeometryTab(curEditItem->getUUID());
                break;
            case GraphicsItemType::Rect:
                UiManager::getIns(). editTabWidget->addRectGeometryTab(curEditItem->getUUID());
                break;
            case GraphicsItemType::Ellipse:
                UiManager::getIns(). editTabWidget->addEllipseGeometryTab(curEditItem->getUUID());
                break;
            case GraphicsItemType::Spiral:
                UiManager::getIns(). editTabWidget->addSpiralGeometryTab(curEditItem->getUUID());
                break;
            case GraphicsItemType::Polygon:
                UiManager::getIns(). editTabWidget->addPolygonGeometryTab(curEditItem->getUUID());
                break;
            default:
                break;
        }
        UiManager::getIns(). editTabWidget->addCopyTab(curEditItem->getUUID());
        UiManager::getIns(). editTabWidget->addFillTab(curEditItem->getUUID());
        UiManager::getIns(). editTabWidget->addMarkParamsTab(curEditItem->getUUID());
        UiManager::getIns(). editTabWidget->addDelayParamsTab(curEditItem->getUUID());
    } else { // 多个编辑对象
        auto uuids = std::vector < UUID > ();
        for (auto item : this->m_currentEditItemGroup) {
            uuids.push_back(item->getUUID());
        }
        UiManager::getIns(). editTabWidget->addMultiItemsEditTab(uuids);
        UiManager::getIns(). editTabWidget->addMultiItemsAlignTab(uuids);
        UiManager::getIns(). editTabWidget->addDuoItemsBoolOpTab(uuids);
    }

    // 记录上次手动切换的tab序号; 然后在之后updateTab的时候主动打开
    auto indexCount = UiManager::getIns().editTabWidget->count();
    if (m_selectedTabIndex <= indexCount - 1) {
        UiManager::getIns().editTabWidget->setCurrentIndex(m_selectedTabIndex);
    }
}

void EditController::updateTableViewModel() {
    // // clear
    // TableModel* model = qobject_cast < TableModel * > (UiManager::getIns(). tableView->model());
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
    auto treeView = UiManager::getIns(). treeView;
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
        } else if (type == "Group" ) {
        } else if (type == "Item" ) {
            item->setSelected(true); // 设置graphicsItem被选中
        } else if (type == "Signal") {
            // 设置curEditItemGroup,添加item(因为对于signal来说,无法在场景中选中 从而触发添加进editgroup)
            item->setSelected(true);
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
    auto treeView = UiManager::getIns(). treeView;
    TreeModel *model = qobject_cast < TreeModel * > (treeView->model());
    QModelIndex index = model->getIndex(uuid);
    // Q_ASSERT(index.isValid());
    if (!index.isValid()) {
        WARN_MSG("index invalid");
        return;
    }
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

void EditController::onTreeViewModelSelectAllItemsInGroup() {
    auto *treeView = UiManager::getIns(). treeView;
    TreeModel *model = qobject_cast < TreeModel * > (treeView->model());
    const auto nodeIndexList
        = UiManager::getIns(). treeView->selectionModel()->selectedIndexes();
    if (nodeIndexList.size() > 1) {
        return;
    }
    auto indexList = model->getClosedChildIndexs(nodeIndexList[0]);
    // 先把group取消select,因为设置了group不能和子节点同时选中
    treeView->selectionModel()->select(nodeIndexList[0],
                                       QItemSelectionModel::Deselect | QItemSelectionModel::Rows);
    // 依次选中所有子节点
    for (const auto &index : indexList) {
        DEBUG_VAR(index);
        treeView->selectionModel()->select(index,
                                           QItemSelectionModel::Select | QItemSelectionModel::Rows);
    }
}

void EditController::onTreeViewModelAddGroup() {
    TreeModel *model = qobject_cast < TreeModel * > (UiManager::getIns(). treeView->model());
    // 提取选中的节点列表
    const auto nodeIndexList
        = UiManager::getIns(). treeView->selectionModel()->selectedIndexes();
    auto mimeList = model->mimeData(nodeIndexList);
    // //在目标处创建group节点
    QModelIndex targetIndex = UiManager::getIns(). treeView->selectionModel()->currentIndex();
    // DEBUG_VAR(model->getNode(targetIndex)->property(TreeNodePropertyIndex::Type));
    if (!model->insertRows(targetIndex.row() + 1, 1, targetIndex.parent())) {
        return;
    }
    const QModelIndex groupIndex = model->index(targetIndex.row() + 1, 0, targetIndex.parent());
    QString name = "Group";
    QString type = "Group";
    Manager::getIns().addItem(name, type, groupIndex);
    // 把节点列表移动到group节点下
    model->dropMimeData(mimeList, Qt::MoveAction, 0, 0, groupIndex);
    // 最后再把之前的节点删除; 一定不能先删除, 不然会影响到插入;
    for (const QModelIndex &nodeIndex : nodeIndexList) {
        auto node = model->getNode(nodeIndex);
        auto parentNode = node->parent();
        auto parentNodeIndex = model->getIndex(parentNode);
        model->removeRows(node->indexInParent(), 1, parentNodeIndex);
    }
}

void EditController::onTreeViewModelDeleteGroup() {
    TreeModel *model = qobject_cast < TreeModel * > (UiManager::getIns(). treeView->model());
    // 提取选中的节点
    const auto groupIndex
        = UiManager::getIns(). treeView->selectionModel()->selectedIndexes()[0];
    auto groupNode = model->getNode(groupIndex);
    auto groupUuid = groupNode->property(TreeNodePropertyIndex::UUID).toString();
    Manager::getIns().deleteItem(groupUuid);
}
EditController &EditController::getIns() {
    return ins;
}
