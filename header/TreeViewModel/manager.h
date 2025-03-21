#ifndef MANAGER_H
#define MANAGER_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLabel>
#include <qgraphicsitem.h>
#include <memory>
#include "laseritem.h"
#include <QTreeView>
#include "logger.h"
#include "treeviewmodel.h"
#include <vector>


class Manager
{
private:
    QTreeView* treeview;
    QGraphicsScene *scene;
    static Manager ins;
public:
    void addItem(std::shared_ptr<LaserItem> ptr)
    {
        int layer = ptr->getLayer();
        QString name = ptr->getName();

        TreeViewModel *model = qobject_cast<TreeViewModel *>(treeview->model());
        auto rootNode = model->getItem(QModelIndex());
        auto layerNodeIndex = model->getIndex(layer-1,0,rootNode);

        // 确保columnCount = 1
        // if (model->columnCount(layerNodeIndex) == 0) {
        //     if (!model->insertColumn(0, layerNodeIndex))
        //         FATAL_MSG("columnCount = 0");
        // }

        if (!model->insertRow(0, layerNodeIndex))
            FATAL_MSG("insert  child fail");

        const QModelIndex childNodeIndex = model->index(0, 0, layerNodeIndex);
        model->setProperty(childNodeIndex,NodePropertyIndex::Name,name);
        model->setProperty(childNodeIndex,NodePropertyIndex::Type,"Item");
        model->setProperty(childNodeIndex,NodePropertyIndex::UUID,"123");
        model->setProperty(childNodeIndex,NodePropertyIndex::GraphicsViewItem,pointerToString(ptr.get()));

        treeview->selectionModel()->setCurrentIndex(model->index(0, 0, childNodeIndex),
                                                QItemSelectionModel::ClearAndSelect);
    }
    void deleteItem(QGraphicsItem *item)
    {
        // if (!item) return;

        // auto it = std::find_if(this->container.begin(), this->container.end(),
        //                        [item](const std::shared_ptr<QGraphicsItem>& ptr) {
        //                            return ptr.get() == item;
        //                        });
        // if (it != this->container.end()) {
        //     this->container.erase(it);
        // }
        ///TODO
        /// GroupDelete
        /// LayerDelete
    }

    /*std::vector<LaserItem*> getItems(int layer){
    };*/
    /*std::vector<LaserItem*> getItemsByLayer(int layer){
        TreeViewModel *model = qobject_cast<TreeViewModel *>(treeview->model());
        auto rootNode = model->getItem(QModelIndex());
        auto layerNodeIndex = model->getIndex(layer-1,0,rootNode);

        auto itemGroup = std::vector<LaserItem*>();
        for (int i=0;i<rootNode->childCount();++i)
        {
            auto childNodeIndex = model->index(i,0,layerNodeIndex);
            auto ptr = stringToPointer(model->getProperty(childNodeIndex,NodePropertyIndex::GraphicsViewItem).toString());
            itemGroup.push_back(ptr);
        }

        return itemGroup;

        / TODO
            / 循环遍历整个节点
    };*/

    QString pointerToString(const LaserItem* ptr)
    {
        return QString::number(reinterpret_cast<quintptr>(ptr), 16);
    }
    LaserItem* stringToPointer(const QString& str)
    {
        bool ok;
        quintptr address = str.toULongLong(&ok, 16);
        if (!ok) {
            FATAL_MSG( "Invalid pointer string");// 可能会有group节点的未知转换
        }

        LaserItem* rawPtr = reinterpret_cast<LaserItem*>(address);
        return rawPtr;
    }


/// manager单例初始化
private:
    Manager(){};
    Manager(const Manager&);
    ~Manager(){};
    Manager& operator = (const Manager&);
public:
    static void init(QGraphicsScene *sc, QTreeView* tv)
    {
        ins.scene = sc;
        ins.treeview = tv;
    }
    static Manager& getIns();

/// 键盘控制变量; hold代表长按 pressed代表按下切换一次状态true到false/false到true
public:
    bool IsControlHold = false;
    bool IsShiftHold = false;
    bool IsCapsLocked = false;
    bool IsXHold = false;
    bool IsZHold = false;
    bool IsYHold = false;
    // 鼠标状态
    bool IsMouseLeftButtonHold = false;
    bool IsMouseRightButtonHold = false;
};

#endif // MANAGER_H
