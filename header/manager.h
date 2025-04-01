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
private:
    std::unordered_map<UUID,std::shared_ptr<LaserItem>> m_itemMap;
    std::unordered_map<UUID,std::map<PropertyIndex,QVariant>> m_propertyMap;
public:
    /// \brief addItem 将graphicitem添加到 1. m_itemMap  2. TreeViewModel ;暂时不考虑3. Scene
    void addItem(std::shared_ptr<LaserItem> ptr);
    /// \brief addItem 将非graphicitem(包括layer node physicItem)添加到 1. m_itemMap  2. TreeViewModel ;
    void addItem(QModelIndex position, QString name, QString type);
    /// \brief deleteItem 将graphicitem删除 1. m_itemMap  2. TreeViewModel ; 自动包含3. Scene
    void deleteItem(UUID uuid);
    /// \brief setItem property
    void setItemVisible(UUID uuid,bool status);
    void setItemSelectable(UUID uuid,bool status);
    void setItemMovable(UUID uuid,bool status);
    void setItemRenderPen(UUID uuid,QPen pen);

    /// \brief getItem
    /// \param index
    UUID getItem(QModelIndex index);
    UUID getItem(QGraphicsItem* item);
    /// \brief  getItemsByLayer 获得这个图层下的所有节点(包括图层节点);    layer从1开始; 如果输入0, 那么就是返回所有节点(父节点为根节点)
    std::vector<UUID> getItemsByLayer(int layer);

    /// \brief itemMap 返回item 保护一层 不然老是在这里崩溃 还得debug很久
    /// \param UUID
    std::shared_ptr<LaserItem> itemMapFind(UUID uuid);
    void itemMapInsert(UUID uuid, std::shared_ptr<LaserItem> ptr);
    void itemMapErase(UUID uuid);
    /// \brief propertyMap 返回item 保护一层 不然老是在这里崩溃 还得debug很久
    /// \param UUID
    QVariant& propertyMapFind(UUID uuid, PropertyIndex index);
    void propertyMapInsert(UUID uuid, std::map<PropertyIndex,QVariant> map);
    void propertyMapErase(UUID uuid);

    /// \brief setVisibleSync 设置图层以及其下所有对象的visible是同步的
    void setVisibleSync();

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
