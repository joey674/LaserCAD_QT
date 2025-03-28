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
#include "logger.h"
#include "scenemanager.h"


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
    void setItemVisible(UUID uuid,bool status)
    {
        // - m_itemMap
        // - m_propertyMap
        propertyMapFind(uuid,PropertyIndex::Visible) = status;
        // - TreeViewModel中的节点
        // - Scene
        itemMapFind(uuid)->setVisible(status);
    };
    void setItemSelectable(UUID uuid,bool status)
    {
        // - m_itemMap
        // - m_propertyMap
        propertyMapFind(uuid,PropertyIndex::Selectable) = status;
        // - TreeViewModel中的节点
        // - Scene
        itemMapFind(uuid)->setFlag(QGraphicsItem::ItemIsSelectable, status);
    };
    void setItemMovable(UUID uuid,bool status)
    {
        // - m_itemMap
        // - m_propertyMap
        propertyMapFind(uuid,PropertyIndex::Movable) = status;
        // - TreeViewModel中的节点
        // - Scene
        itemMapFind(uuid)->setFlag(QGraphicsItem::ItemIsMovable, status);
    }
    void setItemRenderPen(UUID uuid,QPen pen)
    {
        // - m_itemMap
        // - m_propertyMap
        propertyMapFind(uuid,PropertyIndex::Pen) = pen;
        // - TreeViewModel中的节点
        // - Scene
        itemMapFind(uuid)->setPen(pen);
    }

    /// \brief getItem
    /// \param index
    UUID getItem(QModelIndex index);
    UUID getItem(QGraphicsItem* item);
    /// \brief  getItemsByLayer 获得这个图层下的所有节点(包括图层节点);    layer从1开始; 如果输入0, 那么就是返回所有节点(父节点为根节点)
    std::vector<UUID> getItemsByLayer(int layer);

    /// \brief itemMap 返回item 保护一层 不然老是在这里崩溃 还得debug很久
    /// \param UUID
    std::shared_ptr<LaserItem> itemMapFind(UUID uuid)
    {
        auto it = m_itemMap.find(uuid);
        if (it == m_itemMap.end()) {
            WARN_VAR(uuid);
            FATAL_MSG("fail to find item by uuid");
        }
        return it->second;
    }
    void itemMapInsert(UUID uuid, std::shared_ptr<LaserItem> ptr)
    {
        m_itemMap.insert({uuid,ptr});
    }
    void itemMapErase(UUID uuid)
    {
        m_itemMap.erase(uuid);
    }

    QVariant& propertyMapFind(UUID uuid, PropertyIndex index)
    {
        auto it = m_propertyMap.find(uuid);
        if (it == m_propertyMap.end()) {
            WARN_VAR(uuid);
            for (const auto& pair : m_propertyMap) {
                 WARN_VAR(pair.first);
            }
            FATAL_MSG("fail to find item in this uuid");
        }

        auto& map = it->second;
        auto it1 = map.find(index);
        if (it1 == map.end()) {
            WARN_VAR(index);
            FATAL_MSG("fail to find property in this item");
        }

        return it1->second;
    }
    void propertyMapInsert(UUID uuid, std::map<PropertyIndex,QVariant> map)
    {
        m_propertyMap.insert({uuid,map});
    }
    void propertyMapErase(UUID uuid)
    {
        m_propertyMap.erase(uuid);
    }



    /// \brief setVisibleSync 设置图层以及其下所有对象的visible是同步的
    void setVisibleSync()
    {
        for (int layer = 1;layer <= SceneManager::getIns().layerCount();++layer){
            auto items = getItemsByLayer(layer);
            bool isVisible = propertyMapFind(items[0],PropertyIndex::Visible).toBool();
            // DEBUG_VAR(layer);
            // DEBUG_VAR(isVisible);
            for (const auto& item: items){
                // DEBUG_VAR(item);
                this->setItemVisible(item,isVisible);
            }
        }
    }

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
