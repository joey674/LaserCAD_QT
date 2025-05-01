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
/// \brief EditController::editItem
/// \param pointCoordscene
/// \param event
///
void EditController::editItemInScene(QPointF pointCoordscene, MouseEvent event) {
    //
    // if (this->m_currentEditItemGroup.empty() || this->m_currentEditItemGroup.size() > 1) {
    //     return;
    // }
    // auto curEditItem = this->m_currentEditItemGroup[0];
    //
    // 处理scene中编辑
    // switch (curEditItem->type()) {
    //     case GraphicsItemType::Polyline: {
    //             PolylineItem *item = static_cast < PolylineItem * > (curEditItem.get());
    //             this->editPolyline(pointCoordscene, item, event);
    //             break;
    //         }
    //     case GraphicsItemType::Arc: {
    //             ArcItem *item = static_cast < ArcItem * > (curEditItem.get());
    //             this->editArc(pointCoordscene, item, event);
    //             break;
    //         }
    //     case GraphicsItemType::Line: {
    //             break;
    //         }
    //         // TODO
    // };
}

///
/// \brief EditController::editArc
/// \param pointCoordscene
/// \param item
/// \param event
///
void EditController::editArc(QPointF pointCoordscene, ArcItem* item, MouseEvent event) {
}

void EditController::editPolyline(QPointF pointCoordscene, PolylineItem* item, MouseEvent event) {
    if (!item) {
        return;
    }
    // 图形上直接编辑操作点
    if (this->currentEditPolylineVertexIndex == -1 && event == MouseEvent::LeftRelease) {
        double minDistance = 50;
        for (int i = 0; i < item->getVertexCount(); ++i) {
            double distance = QLineF(pointCoordscene, item->getVertexInScene(i).point).length();
            if (distance <= 10.0 && distance < minDistance) {
                minDistance = distance;
                this->currentEditPolylineVertexIndex = i;
                DEBUG_MSG("set vertex index" +  QString::number(this->currentEditPolylineVertexIndex));
            }
        }
    } else if (this->currentEditPolylineVertexIndex != -1 && event == MouseEvent::MouseMove) {
        double angle = item->getVertexInScene(this->currentEditPolylineVertexIndex).angle;
        item->setVertexInScene(this->currentEditPolylineVertexIndex, Vertex{pointCoordscene, angle});
        // 注意这里输入的是绝对坐标 所以要减去相对坐标！
    } else if (this->currentEditPolylineVertexIndex != -1 && event == MouseEvent::LeftRelease) {
        this->currentEditPolylineVertexIndex = -1;
    }
}

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
                UiManager::getIns().UI()->tabWidget->addPolylineGeometryTab(curEditItem->getUUID());
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
        } else if (type == "Item") {
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
        if (type == "Layer") {
        } else if (type == "Item") {
            UUID uuid = model->nodeProperty(idx, TreeNodePropertyIndex::UUID).toString();
            Manager::getIns().itemMapFind(uuid)->setSelected(true);
        }
    }
    // 处理deselect对象
    for (const QModelIndex &idx : deselected.indexes()) {
        if (idx.column() != 0) {
            continue;
        }
        QString type = model->nodeProperty(idx, TreeNodePropertyIndex::Type).toString();
        if (type == "Item") {
            UUID uuid = model->nodeProperty(idx, TreeNodePropertyIndex::UUID).toString();
            Manager::getIns().itemMapFind(uuid)->setSelected(false);
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
        //
        // item->m_editRect = new EditRect(item.get ());
        // SceneController::getIns().scene->addItem(item->m_editRect);
        // 设置treeview中选中
        treeView->selectionModel()->select(index,
                                           QItemSelectionModel::Select | QItemSelectionModel::Rows);
        treeView->expandToIndex(index);
        // 设置curEditItemGroup,添加item
        this->m_currentEditItemGroup.push_back(item);
    } else {
        // //
        // if (item->m_editRect) {
        //     SceneController::getIns().scene->removeItem(item->m_editRect);
        //     SceneController::getIns().scene->removeItem(item->m_editRect);
        //     item->m_editRect = nullptr;
        // }
        // 设置treeview中取消选中
        treeView->selectionModel()->select(index,
                                           QItemSelectionModel::Deselect
                                           | QItemSelectionModel::Rows);
        treeView->expandToIndex(index);
        // 设置curEditItemGroup,删除item
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

///
/// \brief EditController::onGraphicsItemSelectedHasChanged
/// \param uuid
/// \param selected
///

EditController &EditController::getIns() {
    return ins;
}
