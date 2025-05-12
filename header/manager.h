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
#include "scenecontroller.h"


class Manager {
    friend class ProjectManager;
private:
    std::unordered_map < UUID, std::shared_ptr < GraphicsItem>> m_itemMap;
    std::vector < std::shared_ptr < GraphicsItem>> m_deletedItemList;
public:
    /// \brief addItem 添加graphicitem
    UUID addItem(std::shared_ptr < GraphicsItem > ptr);
    /// \brief addItem 添加非graphicitem(包括layer node physicItem)
    UUID addItem(QString name, QString type, QModelIndex position = QModelIndex{} );
    /// \brief deleteItem 删除item; 并且会删除其下所有子节点
    void deleteItem(UUID uuid);
    /// \brief copyItem 复制graphicitem
    UUID copyItem(UUID uuid) {
        auto itemptr = itemMapFind(uuid);
        auto  item = (dynamic_cast < GraphicsItem* > (itemptr.get()))->clone();
        SceneController::getIns().scene->addItem(item.get());
        this->addItem(item);
        return item->getUUID();
    };
    /// \brief setItem property
    void setItemVisible(UUID uuid, bool status) {
        itemMapFind(uuid)->setVisible(status);
    }
    void setItemSelectable(UUID uuid, bool status) {
        itemMapFind(uuid)->setFlag(QGraphicsItem::ItemIsSelectable, status);
    }
    /// \brief getItem
    /// \param index
    UUID getItem(QModelIndex index);
    UUID getItem(QGraphicsItem* item);
    /// \brief getChildItems
    /// \param uuid 输入"0-0-0-0"是获取所有节点; 其他未知节点返回空数组
    std::vector < UUID > getChildItems(UUID uuid);
private:
    void setItemMovable(UUID uuid, bool status) {
        itemMapFind(uuid)->setFlag(QGraphicsItem::ItemIsMovable, status);
    }

public:
/// \brief itemMap 返回item 保护一层 不然老是在这里崩溃 还得debug很久
/// \param UUID
    std::shared_ptr < GraphicsItem > itemMapFind(UUID uuid);
    void itemMapInsert(UUID uuid, std::shared_ptr < GraphicsItem > ptr);
    void itemMapErase(UUID uuid);
    bool itemMapExist(UUID uuid);
/// \brief setVisibleSync 设置图层以及其下所有对象的visible/color/selectable是同步的
    void setLayerItemStateSync();

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
