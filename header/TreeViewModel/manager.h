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
        auto rootNode = model->getNode(QModelIndex());
        auto layerNodeIndex = model->getIndex(layer-1,rootNode);

        // 确保columnCount = 1
        // if (model->columnCount(layerNodeIndex) == 0) {
        //     if (!model->insertColumn(0, layerNodeIndex))
        //         FATAL_MSG("columnCount = 0");
        // }

        if (!model->insertRow(0, layerNodeIndex))
            FATAL_MSG("insert  child fail");

        const QModelIndex childNodeIndex = model->index(0, 0, layerNodeIndex);
        model->setNodeProperty(childNodeIndex,NodePropertyIndex::Name,name);
        model->setNodeProperty(childNodeIndex,NodePropertyIndex::Type,"Item");
        model->setNodeProperty(childNodeIndex,NodePropertyIndex::UUID,"123");
        model->setNodeProperty(childNodeIndex,NodePropertyIndex::GraphicsViewItem,pointerToString(ptr.get()));

        treeview->selectionModel()->setCurrentIndex(model->index(0, 0, childNodeIndex),
                                                QItemSelectionModel::ClearAndSelect);
    }
    void deleteItem(LaserItem *item)
    {
        if (!item) return;

        TreeViewModel *model = qobject_cast<TreeViewModel *>(treeview->model());

        QModelIndex nodeIndex = QModelIndex();
        auto nodesGroup = model->getAllChildNodes(nodeIndex);
        for (const auto& node : nodesGroup) {
            auto itemInString = pointerToString(item);
            auto item = stringToPointer(node->property(NodePropertyIndex::GraphicsViewItem).toString());
        }

    }
    /// 获得这个图层下的所有节点
    /// layer从1开始; 如果输入0, 那么就是返回所有节点(父节点为根节点)
    std::vector<LaserItem*> getItems(int layer)
    {
        TreeViewModel *model = qobject_cast<TreeViewModel *>(treeview->model());

        QModelIndex nodeIndex;
        if (layer==0){
                nodeIndex = QModelIndex();
        }else {
            if (layer > model->rowCount())
                FATAL_MSG("input layer exceed the existing layer count");
            nodeIndex = model->index(layer-1,0,QModelIndex());
        }
        auto nodesGroup = model->getAllChildNodes(nodeIndex);
        auto itemsGroup = std::vector<LaserItem*>();
        for (const auto& node : nodesGroup) {
            if(node->property(NodePropertyIndex::Type).toString() != "Item")
                continue;
            auto item = stringToPointer(node->property(NodePropertyIndex::GraphicsViewItem).toString());
            itemsGroup.push_back(item);
        }

        return itemsGroup;
    };

    QString pointerToString(const LaserItem* ptr)
    {
        return QString::number(reinterpret_cast<quintptr>(ptr), 16);
    }
    LaserItem* stringToPointer(const QString& str)
    {
        bool ok;
        quintptr address = str.toULongLong(&ok, 16);
        if (!ok) {
            WARN_MSG( "Invalid pointer string");// 可能会有group节点的未知转换
            WARN_VAR(str);
            FATAL_MSG("");
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
