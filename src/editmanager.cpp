#include "editmanager.h"
#include "polylineitem.h"
#include "arcitem.h"
#include "protocol.h"
#include "logger.h"
#include "scenemanager.h"
#include "treemodel.h"
#include "uimanager.h"
#include "tablemodel.h"

EditManager EditManager::ins;

///
/// \brief EditManager::editItem
/// \param pointCoordscene
/// \param event
///
void EditManager::editItem(QPointF pointCoordscene, MouseEvent event) {
    if (this->currentEditItem) {
        // 处理scene中编辑
        switch (this->currentEditItem->type()) {
            case ItemTypeId::Polyline: {
                    PolylineItem *item = static_cast < PolylineItem * > (this->currentEditItem);
                    this->editPolyline(pointCoordscene, item, event);
                    break;
                }
            case ItemTypeId::Arc: {
                    ArcItem *item = static_cast < ArcItem * > (this->currentEditItem);
                    this->editArc(pointCoordscene, item, event);
                    break;
                }
            case ItemTypeId::Line: {
                    break;
                }
                // TODO
        };
    }
}

///
/// \brief EditManager::editArc
/// \param pointCoordscene
/// \param item
/// \param event
///
void EditManager::editArc(QPointF pointCoordscene, ArcItem* item, MouseEvent event) {
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

void EditManager::editPolyline(QPointF pointCoordscene, PolylineItem* item, MouseEvent event) {
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
        this->currentEditItem = NULL;
    }
}

///
/// \brief EditManager::updateTabWidget
///
void EditManager::updateTabWidget() {
    UiManager::getIns().UI()->tabWidget->clearAllTabs();
    if (!this->currentEditItem) {
        WARN_MSG("no current edititem");
        return;
    }
    UiManager::getIns().UI()->tabWidget->addCopyTab();
    UiManager::getIns().UI()->tabWidget->addOffsetTab();
}

void EditManager::updateTableViewModel() {
    TableModel* model = qobject_cast < TableModel * > (
                            UiManager::getIns().UI()->tableView->model());
    model->clear();
    if (!this->currentEditItem) {
        WARN_MSG("no current edititem");
        return;
    }
    GraphicsItem *item = static_cast < GraphicsItem * > (this->currentEditItem);
    model->setCurrentEditItem(item->getUUID());
}

void EditManager::onSceneSelectionChanged() {
    // 只要不是1, 大于1或者为0都不设置当前editItem
    if (SceneManager::getIns().scene->selectedItems().size() == 1) {
        this->currentEditItem = SceneManager::getIns().scene->selectedItems().at(0);
    } else {
        this->currentEditItem = nullptr;
    }
    // 在treeview中选中对象
    auto treeView = UiManager::getIns().UI()->treeView;
    TreeModel *model = qobject_cast < TreeModel * > (treeView->model());
    treeView->selectionModel()->clearSelection();
    if (SceneManager::getIns().scene->selectedItems().size() >= 1) {
        auto editItemGroup = SceneManager::getIns().scene->selectedItems();
        for (const auto &editItem : editItemGroup) {
            GraphicsItem *item = static_cast < GraphicsItem * > (editItem);
            auto allNodes = model->getAllChildNodes(QModelIndex());
            for (auto node : allNodes) {
                if (node->property(TreeNodePropertyIndex::UUID) == item->getUUID()) {
                    auto index = model->getIndex(node);
                    treeView->selectionModel()->select(index,
                                                       QItemSelectionModel::Select
                                                       | QItemSelectionModel::Rows);
                }
            }
        }
    }
    //
    // 更新tabwidget
    updateTabWidget();
    // 更新tablemodel
    updateTableViewModel();
}

void EditManager::onTabWidgetCopyTabVectorCopy(QPointF dir, double spacing, int count) {
    if (!this->currentEditItem ) {
        return;
    }
    GraphicsItem* item = static_cast < GraphicsItem * > (this->currentEditItem);
    QPointF unitOffset = dir * spacing;
    for (int i = 1; i <= count; ++i) {
        auto uuid = Manager::getIns().copyItem(item->getUUID());
        auto copiedItem = Manager::getIns().itemMapFind(uuid);
        if (!copiedItem) {
            continue;
        }
        QPointF center = copiedItem->getCenterPos();
        QPointF offset = unitOffset * i;
        copiedItem->setCenterPos(center + offset);
    }
}

void EditManager::onTabWidgetCopyTabMatrixCopy(
    QPointF hVec, QPointF vVec,
    double hSpacing, double vSpacing,
    int hCount, int vCount) {
    if (!this->currentEditItem) {
        return;
    }
    GraphicsItem* item = static_cast < GraphicsItem * > (this->currentEditItem);
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
            copiedItem->setCenterPos(origin + offset);
        }
    }
}


EditManager &EditManager::getIns() {
    return ins;
}
