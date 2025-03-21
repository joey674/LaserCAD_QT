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
#include <unordered_map>


class Manager
{
private:
    QTreeView* treeview;
    QGraphicsScene *scene;
    static Manager ins;

    std::unordered_map<QString,std::shared_ptr<LaserItem>> ItemMap;
public:
    void addItem(std::shared_ptr<LaserItem> ptr);
    void deleteItem(LaserItem *item)
    {
        if (!item) return;

        TreeViewModel *model = qobject_cast<TreeViewModel *>(treeview->model());

        // 删去在treeViewModel内的节点;
        QModelIndex nodeIndex = QModelIndex();
        auto nodesGroup = model->getAllChildNodes(nodeIndex);
        for (const auto& node : nodesGroup) {
            if(item->getUUID() == node->property(NodePropertyIndex::UUID).toString()){
                auto parentNodeIndex = model->getIndex(node);

                if (!model->removeRow(node->indexInParent(), parentNodeIndex)) {
                    FATAL_MSG("fail to removeRow");
                }

                break;
            }
        }

        // 删去在map中的节点
        ItemMap.erase(item->getUUID());
    }
    /// 获得这个图层下的所有节点
    /// layer从1开始; 如果输入0, 那么就是返回所有节点(父节点为根节点)
    std::vector<std::shared_ptr<LaserItem>> getItems(int layer);;

private:// manager单例初始化
    Manager(){};
    Manager(const Manager&);
    ~Manager(){};
    Manager& operator = (const Manager&);
public:
    static void init(QGraphicsScene *sc, QTreeView* tv);
    static Manager& getIns();

public:// 键盘控制变量; hold代表长按 pressed代表按下切换一次状态true到false/false到true
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
