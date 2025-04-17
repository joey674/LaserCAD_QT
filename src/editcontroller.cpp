#include "editcontroller.h"
#include "polylineitem.h"
#include "arcitem.h"
#include "protocol.h"
#include "logger.h"
#include "scenemanager.h"
#include "treemodel.h"
#include "uimanager.h"
#include "tablemodel.h"
#include "uimanager.h"

EditController EditController::ins;

///
/// \brief EditController::editItem
/// \param pointCoordscene
/// \param event
///
void EditController::editItemInScene(QPointF pointCoordscene, MouseEvent event) {
    if (this->m_currentEditItem) {
        // 处理scene中编辑
        switch (this->m_currentEditItem->type()) {
            case GraphicsItemType::Polyline: {
                    PolylineItem *item = static_cast < PolylineItem * > (this->m_currentEditItem);
                    this->editPolyline(pointCoordscene, item, event);
                    break;
                }
            case GraphicsItemType::Arc: {
                    ArcItem *item = static_cast < ArcItem * > (this->m_currentEditItem);
                    this->editArc(pointCoordscene, item, event);
                    break;
                }
            case GraphicsItemType::Line: {
                    break;
                }
                // TODO
        };
    }
}

///
/// \brief EditController::editArc
/// \param pointCoordscene
/// \param item
/// \param event
///
void EditController::editArc(QPointF pointCoordscene, ArcItem* item, MouseEvent event) {
    // if (this->currentEditPolylineVertexIndex == -1 && event == MouseEvent::LeftRelease)
    // {
    //     INFO_MSG("edit arc");
    //     DEBUG_VAR(item->getCenterPos());
    //     DEBUG_VAR(item->pos());
    //     // 把对象的属性映射到属性修改面板
    //     // 清除table
    //     UiManager::getIns().UI()->propertyTableWidget->clearContents();
    //     UiManager::getIns().UI()->propertyTableWidget->setRowCount(0);
    //     // 先blocksignal,不然会频繁触发修改属性table的回调
    //     UiManager::getIns().UI()->propertyTableWidget->blockSignals(true);
    //     // 映射属性
    //     int row = UiManager::getIns().UI()->propertyTableWidget->rowCount();
    //     QTableWidgetItem *propertyName =nullptr;
    //     QTableWidgetItem *propertyValue = nullptr;
    //     auto posOffset = item->pos();
    //     row = UiManager::getIns().UI()->propertyTableWidget->rowCount();
    //     UiManager::getIns().UI()->propertyTableWidget->insertRow(row);
    //     propertyName = new QTableWidgetItem("startPoint.x");
    //     propertyValue = new QTableWidgetItem(QString::number(item->getVertex(0).point.x()+posOffset.x()));
    //     propertyName->setFlags(propertyName->flags() & ~Qt::ItemIsEditable);
    //     propertyValue->setFlags(propertyValue->flags() | Qt::ItemIsEditable);
    //     UiManager::getIns().UI()->propertyTableWidget->setItem(row, 0, propertyName);
    //     UiManager::getIns().UI()->propertyTableWidget->setItem(row, 1, propertyValue);
    //     row = UiManager::getIns().UI()->propertyTableWidget->rowCount();
    //     UiManager::getIns().UI()->propertyTableWidget->insertRow(row);
    //     propertyName = new QTableWidgetItem("startPoint.y");
    //     propertyValue = new QTableWidgetItem(QString::number(item->getVertex(0).point.y()+posOffset.y()));
    //     propertyName->setFlags(propertyName->flags() & ~Qt::ItemIsEditable);
    //     propertyValue->setFlags(propertyValue->flags() | Qt::ItemIsEditable);
    //     UiManager::getIns().UI()->propertyTableWidget->setItem(row, 0, propertyName);
    //     UiManager::getIns().UI()->propertyTableWidget->setItem(row, 1, propertyValue);
    //     row = UiManager::getIns().UI()->propertyTableWidget->rowCount();
    //     UiManager::getIns().UI()->propertyTableWidget->insertRow(row);
    //     propertyName = new QTableWidgetItem("endPoint.x");
    //     propertyValue = new QTableWidgetItem(QString::number(item->getVertex(1).point.x()+posOffset.x()));
    //     propertyName->setFlags(propertyName->flags() & ~Qt::ItemIsEditable);
    //     propertyValue->setFlags(propertyValue->flags() | Qt::ItemIsEditable);
    //     UiManager::getIns().UI()->propertyTableWidget->setItem(row, 0, propertyName);
    //     UiManager::getIns().UI()->propertyTableWidget->setItem(row, 1, propertyValue);
    //     row = UiManager::getIns().UI()->propertyTableWidget->rowCount();
    //     UiManager::getIns().UI()->propertyTableWidget->insertRow(row);
    //     propertyName = new QTableWidgetItem("endPoint.y");
    //     propertyValue = new QTableWidgetItem(QString::number(item->getVertex(1).point.y()+posOffset.y()));
    //     propertyName->setFlags(propertyName->flags() & ~Qt::ItemIsEditable);
    //     propertyValue->setFlags(propertyValue->flags() | Qt::ItemIsEditable);
    //     UiManager::getIns().UI()->propertyTableWidget->setItem(row, 0, propertyName);
    //     UiManager::getIns().UI()->propertyTableWidget->setItem(row, 1, propertyValue);
    //     row = UiManager::getIns().UI()->propertyTableWidget->rowCount();
    //     UiManager::getIns().UI()->propertyTableWidget->insertRow(row);
    //     propertyName = new QTableWidgetItem("angle");
    //     propertyValue = new QTableWidgetItem(QString::number(item->getVertex(1).angle));
    //     propertyName->setFlags(propertyName->flags() & ~Qt::ItemIsEditable);
    //     propertyValue->setFlags(propertyValue->flags() | Qt::ItemIsEditable);
    //     UiManager::getIns().UI()->propertyTableWidget->setItem(row, 0, propertyName);
    //     UiManager::getIns().UI()->propertyTableWidget->setItem(row, 1, propertyValue);
    //     UiManager::getIns().UI()->propertyTableWidget->blockSignals(false);
    // }
}

void EditController::editPolyline(QPointF pointCoordscene, PolylineItem* item, MouseEvent event) {
    if (!item) {
        return;
    }
    // 图形上直接编辑操作点
    if (this->currentEditPolylineVertexIndex == -1 && event == MouseEvent::LeftRelease) {
        double minDistance = 50;
        for (int i = 0; i < item->getVertexCount(); ++i) {
            double distance = QLineF(pointCoordscene, item->getVertexPos(i)).length();
            if (distance <= 10.0 && distance < minDistance) {
                minDistance = distance;
                this->currentEditPolylineVertexIndex = i;
                DEBUG_MSG("set vertex index" +  QString::number(this->currentEditPolylineVertexIndex));
            }
        }
    } else if (this->currentEditPolylineVertexIndex != -1 && event == MouseEvent::MouseMove) {
        double angle = item->getVertex(this->currentEditPolylineVertexIndex).angle;
        item->editVertex(this->currentEditPolylineVertexIndex, pointCoordscene, angle);
        // 注意这里输入的是绝对坐标 所以要减去相对坐标！
    } else if (this->currentEditPolylineVertexIndex != -1 && event == MouseEvent::LeftRelease) {
        this->currentEditPolylineVertexIndex = -1;
    }
}

///
/// \brief EditController::updateTabWidget
///
void EditController::updateTabWidget() {
    TabWidget* tabWidget = UiManager::getIns().UI()->tabWidget;
    tabWidget ->clearAllTabs();
    if (this->m_currentEditItem) {
        switch (this->m_currentEditItem->type()) {
            case GraphicsItemType::Arc:
                UiManager::getIns().UI()->tabWidget->addArcGeometryTab(this->m_currentEditItem->getUUID ());
                break;
            case GraphicsItemType::Circle:
                UiManager::getIns().UI()->tabWidget->addCircleGeometryTab(this->m_currentEditItem->getUUID ());
                break;
            case GraphicsItemType::Line:
                UiManager::getIns().UI()->tabWidget->addLineGeometryTab(this->m_currentEditItem->getUUID ());
                break;
            case GraphicsItemType::Point:
                UiManager::getIns().UI()->tabWidget->addPointGeometryTab(this->m_currentEditItem->getUUID ());
                break;
            case GraphicsItemType::Polyline:
                UiManager::getIns().UI()->tabWidget->addPolylineGeometryTab(this->m_currentEditItem->getUUID ());
                break;
            default:
                break;
        }
        UiManager::getIns().UI()->tabWidget->addCopyTab(this->m_currentEditItem->getUUID ());
        UiManager::getIns().UI()->tabWidget->addOffsetTab(this->m_currentEditItem->getUUID ());
        UiManager::getIns().UI()->tabWidget->addMarkParamsTab (this->m_currentEditItem->getUUID ());
        UiManager::getIns().UI()->tabWidget->addDelayParamsTab (this->m_currentEditItem->getUUID ());
        return;
    }
    //
    else if (!this->m_currentEditItemGroup.empty ()) {
        UiManager::getIns().UI()->tabWidget->addMutiItemsEditTab(std::vector < UUID > ());
    }
}

void EditController::updateTableViewModel() {
    TableModel* model = qobject_cast < TableModel * > (UiManager::getIns().UI()->tableView->model());
    model->clear();
    if (!this->m_currentEditItem) {
        // WARN_MSG("no current edititem");
        return;
    }
    model->setCurrentDisplayItem(this->m_currentEditItem->getUUID());
}





void EditController::onTabWidgetCopyTabMatrixCopy(
    QPointF hVec, QPointF vVec,
    double hSpacing, double vSpacing,
    int hCount, int vCount) {
    if (!this->m_currentEditItem) {
        return;
    }
    GraphicsItem* item = static_cast < GraphicsItem * > (this->m_currentEditItem);
    QPointF hOffset = hVec * hSpacing;
    QPointF vOffset = vVec * vSpacing;
    QPointF origin = item->getCenterPos();
    // 外层纵向（v），内层横向（h）
    for (int row = 0; row < vCount; ++row) {
        for (int col = 0; col < hCount; ++col) {
            // 不要复制原件自己（0,0）
            if (row == 0 && col == 0) {
                continue;
            }
            // 执行复制
            auto uuid = Manager::getIns().copyItem(item->getUUID());
            auto copiedItem = Manager::getIns().itemMapFind(uuid);
            if (!copiedItem) {
                continue;
            }
            // 设置新位置
            QPointF offset = hOffset * col + vOffset * row;
            // Manager::getIns().setItemPosition(copiedItem->getUUID(), origin + offset);
            copiedItem->setCenterPos(origin + offset);
        }
    }
}

void EditController::onTreeViewModelClicked(const QModelIndex &index) {}

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
            DEBUG_VAR(uuid);
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
        if (idx.column() != 0) {
            continue;
        }
        QString type = model->nodeProperty(idx, TreeNodePropertyIndex::Type).toString();
        if (type == "Layer") {
            SceneManager::getIns().setCurrentLayer(model->getNode(idx)->indexInParent() + 1);
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

void EditController::onGraphicsItemPositionHasChanged(UUID uuid) {
    this->updateTableViewModel();
}

///
/// \brief EditController::onGraphicsItemSelectedHasChanged
/// \param uuid
/// \param selected
///
void EditController::onGraphicsItemSelectedHasChanged(UUID uuid, bool selected) {
    auto treeView = UiManager::getIns().UI()->treeView;
    TreeModel *model = qobject_cast < TreeModel * > (treeView->model());
    QModelIndex index = model->getIndex(uuid);
    // 设置显示
    if (selected) {
        Manager::getIns().itemMapFind(uuid)->setPen(EDIT_PEN);
        // 设置treeview中选中
        treeView->selectionModel()->select(index,
                                           QItemSelectionModel::Select | QItemSelectionModel::Rows);
        treeView->expandToIndex(index);
    } else {
        // 设置显示
        Manager::getIns().itemMapFind(uuid)->setPen(DISPLAY_PEN);
        // 设置treeview中取消选中
        treeView->selectionModel()->select(index, QItemSelectionModel::Deselect | QItemSelectionModel::Rows);
        treeView->expandToIndex(index);
    }
}

void EditController::onGraphicsItemMouseRelease(UUID uuid) {
    // this->updateTableViewModel();
    this->updateTabWidget();
}

void EditController::onGraphicsItemMousePress(UUID uuid) {
}

EditController &EditController::getIns() {
    return ins;
}
