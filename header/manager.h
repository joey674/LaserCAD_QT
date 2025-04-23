#ifndef MANAGER_H
#define MANAGER_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLabel>
#include <qgraphicsitem.h>
#include <memory>
#include "graphicsitem.h"
#include <QTreeView>
#include <vector>
#include <unordered_map>
#include "logger.h"
#include "arcitem.h"
#include "lineitem.h"
#include "pointitem.h"
#include "polylineitem.h"
#include "circleitem.h"
#include "scenemanager.h"


class Manager {
private:
    std::unordered_map < UUID, std::shared_ptr < GraphicsItem>> m_itemMap;

public:
    /// \brief addItem 添加graphicitem
    void addItem(std::shared_ptr < GraphicsItem > ptr);
    /// \brief addItem 添加非graphicitem(包括layer node physicItem)
    void addItem(QModelIndex position, QString name, QString type);
    /// \brief deleteItem 删除item
    void deleteItem(UUID uuid);
    /// \brief copyItem 复制graphicitem
    UUID copyItem(UUID uuid) {
        auto itemptr = itemMapFind(uuid);
        auto  item = (dynamic_cast < GraphicsItem* > (itemptr.get()))->clone();
        SceneManager::getIns().scene->addItem(item.get());
        this->addItem(item);
        setItemSelectable(item->getUUID(), true);
        setItemMovable(item->getUUID(), true);
        return item->getUUID();
    };
    /// \brief setItem property
    void setItemVisible(UUID uuid, bool status);
    void setItemSelectable(UUID uuid, bool status);
    void setItemMovable(UUID uuid, bool status);
    /// \brief getItem
    /// \param index
    UUID getItem(QModelIndex index);
    UUID getItem(QGraphicsItem* item);
    /// \brief  getItemsByLayer
    /// 获得这个图层下的所有节点(包括图层节点);    layer从1开始; 如果输入0, 那么就是返回所有节点(父节点为根节点)
    std::vector < UUID > getItemsByLayer(int layer);
public:
/// \brief itemMap 返回item 保护一层 不然老是在这里崩溃 还得debug很久
/// \param UUID
    std::shared_ptr < GraphicsItem > itemMapFind(UUID uuid);
    void itemMapInsert(UUID uuid, std::shared_ptr < GraphicsItem > ptr);
    void itemMapErase(UUID uuid);
    bool itemMapExist(UUID uuid);
/// \brief setVisibleSync 设置图层以及其下所有对象的visible是同步的
    void setVisibleSync();

private:
    static Manager ins;
    Manager() {};
    Manager(const Manager &);
    ~Manager() {};
    Manager &operator = (const Manager &);
public:
    static Manager &getIns();
};

#endif // MANAGER_H
