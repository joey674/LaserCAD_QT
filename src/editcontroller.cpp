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
    if (this->currentEditItem) {
        // 处理scene中编辑
        switch (this->currentEditItem->type()) {
            case GraphicsItemType::Polyline: {
                    PolylineItem *item = static_cast < PolylineItem * > (this->currentEditItem);
                    this->editPolyline(pointCoordscene, item, event);
                    break;
                }
            case GraphicsItemType::Arc: {
                    ArcItem *item = static_cast < ArcItem * > (this->currentEditItem);
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
    if (!this->currentEditItem) {
        // WARN_MSG("no current edititem");
        return;
    }
    switch (this->currentEditItem->type()) {
        case GraphicsItemType::Arc:
            UiManager::getIns().UI()->tabWidget->addArcGeometryTab(this->currentEditItem->getUUID ());
            break;
        case GraphicsItemType::Circle:
            UiManager::getIns().UI()->tabWidget->addCircleGeometryTab(this->currentEditItem->getUUID ());
            break;
        case GraphicsItemType::Line:
            UiManager::getIns().UI()->tabWidget->addLineGeometryTab(this->currentEditItem->getUUID ());
            break;
        case GraphicsItemType::Point:
            UiManager::getIns().UI()->tabWidget->addPointGeometryTab(this->currentEditItem->getUUID ());
            break;
        case GraphicsItemType::Polyline:
            UiManager::getIns().UI()->tabWidget->addPolylineGeometryTab(this->currentEditItem->getUUID ());
            break;
        default:
            break;
    }
    UiManager::getIns().UI()->tabWidget->addCopyTab(this->currentEditItem->getUUID ());
    UiManager::getIns().UI()->tabWidget->addOffsetTab(this->currentEditItem->getUUID ());
}

void EditController::updateTableViewModel() {
    TableModel* model = qobject_cast < TableModel * > (UiManager::getIns().UI()->tableView->model());
    model->clear();
    if (!this->currentEditItem) {
        // WARN_MSG("no current edititem");
        return;
    }
    model->setCurrentEditItem(this->currentEditItem->getUUID());
}

void EditController::onSceneSelectionChanged() {
    // selectedItems个数为1时设置为当前编辑对象
    if (SceneManager::getIns().scene->selectedItems().size() == 1) {
        auto qtItem = SceneManager::getIns().scene->selectedItems().at(0);
        this->currentEditItem = static_cast < GraphicsItem * > (qtItem);
    }
    // selectedItems没有时设为空指针
    else if (SceneManager::getIns().scene->selectedItems().isEmpty()) {
        this->currentEditItem = nullptr;
    }
    // 多选时
    else {
    }
    // 更新tabwidget
    updateTabWidget();
    // 更新tablemodel
    updateTableViewModel();
}

void EditController::onTabWidgetCopyTabVectorCopy(QPointF dir, double spacing, int count) {
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
        QPointF offset = unitOffset * i;
        // Manager::getIns().setItemPosition(copiedItem->getUUID(),  item->getCenterPos() + offset);
        copiedItem->setCenterPos(item->getCenterPos() + offset);
    }
}

void EditController::onTabWidgetCopyTabMatrixCopy(
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
            // Manager::getIns().setItemPosition(copiedItem->getUUID(), origin + offset);
            copiedItem->setCenterPos(origin + offset);
        }
    }
}

void EditController::onGraphicsItemPositionHasChanged(UUID uuid) {
    // auto item = Manager::getIns().itemMapFind(uuid);
    // Manager::getIns().setItemPosition (uuid, item->getCenterPos());
    this->updateTableViewModel();
    this->updateTabWidget();
}

void EditController::onGraphicsItemSelectedHasChanged(UUID uuid, bool selected) {
    auto treeView = UiManager::getIns().UI()->treeView;
    TreeModel *model = qobject_cast < TreeModel * > (treeView->model());
    QModelIndex index = model->getIndex(uuid);
    if (selected) {
        // 设置显示
        Manager::getIns().setItemRenderPen(uuid, EDIT_PEN);
        // 设置treeview中选中
        treeView->selectionModel()->select(index, QItemSelectionModel::Select | QItemSelectionModel::Rows);
        treeView->expandToIndex(index);
    } else {
        // 设置显示
        Manager::getIns().setItemRenderPen(uuid, DISPLAY_PEN);
        // 设置treeview中取消选中
        treeView->selectionModel()->select(index, QItemSelectionModel::Deselect | QItemSelectionModel::Rows);
        treeView->expandToIndex(index);
    }
}

void EditController::onGraphicsItemMouseRelease(UUID uuid) {
    this->updateTabWidget();
}

void EditController::onGraphicsItemMousePress(UUID uuid) {
}

EditController &EditController::getIns() {
    return ins;
}
