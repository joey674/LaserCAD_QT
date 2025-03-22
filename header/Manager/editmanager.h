#ifndef EDITMANAGER_H
#define EDITMANAGER_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <qgraphicsitem.h>
#include "polylineitem.h"
#include "arcitem.h"
#include "protocol1.h"
#include "logger.h"
#include "manager.h"
#include "scenemanager.h"
#include "keyboardmanager.h"


class EditManager
{
public: // 操作对象
    void copyItem()
    {

    }
    void deleteItem()
    {

    }
    void setItemStatus(bool visible, bool selectable, bool movable, QGraphicsItem* item)
    {
        item->setVisible(visible);
        item->setFlag(QGraphicsItem::ItemIsMovable, movable);
        item->setFlag(QGraphicsItem::ItemIsSelectable, selectable);
    }
    void setItemsStatus(bool visible,bool selectable, bool movable,const std::vector<std::shared_ptr<LaserItem>>& items)
    {
        for (const auto& item : items)
        {
            if (item)
            {
                item->setVisible(visible);
                item->setFlag(QGraphicsItem::ItemIsMovable, movable);
                item->setFlag(QGraphicsItem::ItemIsSelectable, selectable);
            }
        }
    }

public: // 编辑对象
    QGraphicsItem *currentEditItem = NULL;
    int currentEditPolylineVertexIndex = -1;
    void editItem(QPointF pointCoordscene,MouseEvent event)
    {
        if (SceneManager::getIns().scene->selectedItems().empty())
            return;

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
            ArcItem *Item = static_cast<ArcItem*>(this->currentEditItem);
            this->editArc(pointCoordscene,Item,event);
            break;
        }
        default:
        {
            WARN_MSG("edit undefine object");
        }
        };
    }
    void editPolyline(QPointF pointCoordscene, PolylineItem *, MouseEvent event)
    {
        // if (!item) return;
        // displayOperation("edit polyline, center: " +
        //                  QString::number(item->getCenterPos().x())  +
        //                  " " +
        //                  QString::number(item->getCenterPos().y()));

        // // 图形上直接编辑操作点；
        // if (this->currentEditPolylineVertexIndex == -1 && event == MouseEvent::LeftRelease)
        // {
        //     double minDistance = 100;

        //     for (int i = 0; i < item->getSize(); ++i) {
        //         double distance = QLineF(pointCoordscene, item->getVertexPos(i)).length();
        //         if (distance <= 10.0 && distance < minDistance)
        //         {
        //             minDistance = distance;
        //             this->currentEditPolylineVertexIndex = i;
        //             qDebug() << "setindex to" << this->currentEditPolylineVertexIndex;
        //         }
        //     }
        // }
        // else if (this->currentEditPolylineVertexIndex != -1 && event == MouseEvent::MouseMove)
        // {
        //     double angle = item->getVertex(this->currentEditPolylineVertexIndex).angle;
        //     item->editVertex(this->currentEditPolylineVertexIndex, pointCoordscene, angle);
        //     // 注意这里输入的是绝对坐标 所以要减去相对坐标！
        // }
        // else if (this->currentEditPolylineVertexIndex != -1 && event == MouseEvent::LeftRelease)
        // {
        //     this->currentEditPolylineVertexIndex = -1;
        //     this->currentEditItem =NULL;
        // }
        // else
        // {
        //     displayOperation("unknow edit polyline event");
        // }


        // // 在左侧区域操作参数
        // if (event == MouseEvent::LeftRelease)
        // {
        //     // 先初始化属性栏
        //     UiManager::getIns().UI()->propertyTableWidget->clearContents();
        //     UiManager::getIns().UI()->propertyTableWidget->setRowCount(0);

        //     // 把对象的属性映射到属性修改面板
        //     // 先blocksignal,不然会频繁触发修改属性table的回调
        //     UiManager::getIns().UI()->propertyTableWidget->blockSignals(true);

        //     // 映射属性
        //     int row = UiManager::getIns().UI()->propertyTableWidget->rowCount();
        //     UiManager::getIns().UI()->propertyTableWidget->insertRow(row);
        //     QTableWidgetItem *offsetName = new QTableWidgetItem("offset");
        //     QTableWidgetItem *offsetValue = new QTableWidgetItem(item->getParallelOffset());
        //     offsetName->setFlags(offsetName->flags() & ~Qt::ItemIsEditable);
        //     offsetValue->setFlags(offsetValue->flags() | Qt::ItemIsEditable);
        //     UiManager::getIns().UI()->propertyTableWidget->setItem(row, 0,offsetName);
        //     UiManager::getIns().UI()->propertyTableWidget->setItem(row, 1, offsetValue);

        //     UiManager::getIns().UI()->propertyTableWidget->insertRow(row);
        //     QTableWidgetItem *offsetNumName = new QTableWidgetItem("offsetNum");
        //     QTableWidgetItem *offsetNumValue = new QTableWidgetItem(item->getParallelOffset());
        //     offsetNumName->setFlags(offsetNumName->flags() & ~Qt::ItemIsEditable);
        //     offsetNumValue->setFlags(offsetNumValue->flags() | Qt::ItemIsEditable);
        //     UiManager::getIns().UI()->propertyTableWidget->setItem(row, 0,offsetNumName);
        //     UiManager::getIns().UI()->propertyTableWidget->setItem(row, 1, offsetNumValue);

        //     UiManager::getIns().UI()->propertyTableWidget->blockSignals(false);
        // }
    }
    void editArc(QPointF pointCoordscene, ArcItem *, MouseEvent event)
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

private:
    static EditManager ins;
    EditManager(){};
    EditManager(const EditManager&);
    ~EditManager(){};
    EditManager& operator = (const EditManager&);
public:
    static EditManager& getIns();
};

#endif // EDITMANAGER_H
