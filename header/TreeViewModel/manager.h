/*
Manager用于存储与管理节点;
*/

#ifndef MANAGER_H
#define MANAGER_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLabel>
#include <qgraphicsitem.h>
#include <memory>
#include "laseritem.h"
#include <QTreeView>
#include <vector>
#include <unordered_map>


class Manager
{
public:
    std::unordered_map<QString,std::shared_ptr<LaserItem>> ItemMap;
public:
    void addItem(std::shared_ptr<LaserItem> ptr);
    void deleteItem(LaserItem *item);
    /// \brief 获得这个图层下的所有节点;    layer从1开始; 如果输入0, 那么就是返回所有节点(父节点为根节点)
    std::vector<std::shared_ptr<LaserItem>> getItems(int layer);

private:
    static Manager ins;
    Manager(){};
    Manager(const Manager&);
    ~Manager(){};
    Manager& operator = (const Manager&);
public:
    static Manager& getIns();
};

#endif // MANAGER_H
