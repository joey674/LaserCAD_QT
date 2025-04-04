#include "editmanager.h"
#include "logger.h"
#include "manager.h"
#include "uimanager.h"
#include "scenemanager.h"
#include "tablemodel.h"
#include "treemodel.h"

EditManager EditManager::ins;

void EditManager::editItem(QPointF pointCoordscene, MouseEvent event)
{
    // 获取treemodel
    auto treeView = UiManager::getIns().UI()->treeView;
    TreeModel *model = qobject_cast<TreeModel *>(treeView->model());
    treeView->selectionModel()->clearSelection();

    // 只处理颜色显示；
    if (SceneManager::getIns().scene->selectedItems().size()>=1) {
        for (const auto& editItem: SceneManager::getIns().scene->selectedItems()){
            switch (editItem->type())
            {
             case PolylineItem::Type:
                 {
                    // 在treeview中选中对象
                    PolylineItem *item = static_cast<PolylineItem*>(editItem);
                    auto allNodes = model->getAllChildNodes(QModelIndex());
                    for (auto node:allNodes){
                        if(node->property(TreeNodePropertyIndex::UUID) == item->getUUID()){
                            auto index = model->getIndex(node);
                            treeView->selectionModel()->select(index ,QItemSelectionModel::Select | QItemSelectionModel::Rows);
                        }
                    }

                    break;
                }
            case ArcItem::Type:
            {
                ArcItem *item = static_cast<ArcItem*>(editItem);
                // item->setPen(EDIT_PEN);

                // 在treeview中选中对象
                auto treeView = UiManager::getIns().UI()->treeView;
                TreeModel *model = qobject_cast<TreeModel *>(treeView->model());
                auto allNodes = model->getAllChildNodes(QModelIndex());
                for (auto node:allNodes){
                    if(node->property(TreeNodePropertyIndex::UUID) == item->getUUID()){
                        auto index = model->getIndex(node);
                        treeView->selectionModel()->select(index ,QItemSelectionModel::Select | QItemSelectionModel::Rows);
                    }
                }
                break;
            }
            };
        }
    }

    // 当编辑单一对象时
    if (SceneManager::getIns().scene->selectedItems().size() == 1) {
        this->currentEditItem = SceneManager::getIns().scene->selectedItems()[0];
        switch (this->currentEditItem->type())
        {
        case PolylineItem::Type:
        {
            PolylineItem *item = static_cast<PolylineItem*>(this->currentEditItem);
            this->editPolyline(pointCoordscene,item,event);
            break;
        }
        case ArcItem::Type:
        {
            ArcItem *item = static_cast<ArcItem*>(this->currentEditItem);
            this->editArc(pointCoordscene,item,event);
            break;
        }
        };
    }
}

void EditManager::editArc(QPointF pointCoordscene, ArcItem* item, MouseEvent event)
{
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

void EditManager::editPolyline(QPointF pointCoordscene, PolylineItem* item, MouseEvent event)
{
    if (!item) return;

    // 图形上直接编辑操作点
    if (this->currentEditPolylineVertexIndex == -1 && event == MouseEvent::LeftRelease)
    {
        double minDistance = 50;

        for (int i = 0; i < item->getVertexCount(); ++i) {
            double distance = QLineF(pointCoordscene, item->getVertexPos(i)).length();
            if (distance <= 10.0 && distance < minDistance)
            {
                minDistance = distance;
                this->currentEditPolylineVertexIndex = i;
                DEBUG_MSG("set vertex index" +  QString::number(this->currentEditPolylineVertexIndex));
            }
        }
    }
    else if (this->currentEditPolylineVertexIndex != -1 && event == MouseEvent::MouseMove)
    {
        double angle = item->getVertex(this->currentEditPolylineVertexIndex).angle;
        item->editVertex(this->currentEditPolylineVertexIndex, pointCoordscene, angle);
        // 注意这里输入的是绝对坐标 所以要减去相对坐标！
    }
    else if (this->currentEditPolylineVertexIndex != -1 && event == MouseEvent::LeftRelease)
    {
        this->currentEditPolylineVertexIndex = -1;
        this->currentEditItem =NULL;
    }
}

EditManager &EditManager::getIns()
{
    return ins;
}
