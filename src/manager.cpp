#include "manager.h"
#include "treenode.h"
#include "logger.h"
#include "treemodel.h"
#include "uimanager.h"
#include "scenemanager.h"
#include "polylineitem.h"

 Manager Manager::ins;

Manager &Manager::getIns()
 {
     return ins;
 }

 ///
 /// \brief Manager::addItem
 /// \param ptr
 ///
 void Manager::addItem(std::shared_ptr<LaserItem> ptr)
 {
    auto treeView = UiManager::getIns().UI()->treeView;
     int layer = SceneManager::getIns().getCurrentLayer();
    QString name = ptr->getName();
    QString uuid = ptr->getUUID();

    // 插入ItemMap
    // DEBUG_VAR(ptr.get());
    itemMapInsert(uuid,ptr);

    // 插入propertyMap
    auto map = DefaultPropertyMap;
    propertyMapInsert(uuid,map);
    INFO_MSG("item add: " + ptr->getUUID() + propertyMapFind(ptr->getUUID(),PropertyIndex::Visible).toString());

    // 插入TreeViewModel 注意 这个要最后做 不然会报bug
    TreeModel *model = qobject_cast<TreeModel *>(treeView->model());
    QModelIndex layerNodeIndex = model->index(layer-1,0,QModelIndex());

    auto rowCount = model->rowCount(layerNodeIndex);
    name = name + QString::number(rowCount+1);

    if (!model->insertRow(rowCount, layerNodeIndex))
        FATAL_MSG("insert  child fail");

    const QModelIndex childNodeIndex = model->index(rowCount, 0, layerNodeIndex);
    model->setNodeProperty(childNodeIndex,NodePropertyIndex::Name,name);
    model->setNodeProperty(childNodeIndex,NodePropertyIndex::Type,"Item");
    model->setNodeProperty(childNodeIndex,NodePropertyIndex::UUID,uuid);

    treeView->selectionModel()->setCurrentIndex(model->index(0, 0, childNodeIndex),
                                                QItemSelectionModel::ClearAndSelect);
 }

 void Manager::addItem(QModelIndex position, QString name, QString type)
 {
     TreeModel *model = qobject_cast<TreeModel *>(UiManager::getIns().UI()->treeView->model());
     if (!position.isValid())
         FATAL_MSG("fail add item to manager");


     auto item = std::make_shared<PolylineItem>();
     model->setNodeProperty(position,NodePropertyIndex::Name,name);
     model->setNodeProperty(position,NodePropertyIndex::Type,type);
     model->setNodeProperty(position,NodePropertyIndex::UUID, item.get()->getUUID());
     // 插入ItemMap;
     itemMapInsert(item.get()->getUUID(),item);

     // 插入propertyMap
     auto map = DefaultPropertyMap;
     propertyMapInsert(item->getUUID(),map);
     INFO_MSG("item add: " + item->getUUID() + propertyMapFind(item->getUUID(),PropertyIndex::Visible).toString());
 }

 void Manager::setItemVisible(UUID uuid, bool status)
 {
     // - m_itemMap
     // - m_propertyMap
     propertyMapFind(uuid,PropertyIndex::Visible) = status;
     // - TreeViewModel中的节点
     // - Scene
     itemMapFind(uuid)->setVisible(status);
 }

 void Manager::setItemSelectable(UUID uuid, bool status)
 {
     // - m_itemMap
     // - m_propertyMap
     propertyMapFind(uuid,PropertyIndex::Selectable) = status;
     // - TreeViewModel中的节点
     // - Scene
     itemMapFind(uuid)->setFlag(QGraphicsItem::ItemIsSelectable, status);
 }

 void Manager::setItemMovable(UUID uuid, bool status)
 {
     // - m_itemMap
     // - m_propertyMap
     propertyMapFind(uuid,PropertyIndex::Movable) = status;
     // - TreeViewModel中的节点
     // - Scene
     itemMapFind(uuid)->setFlag(QGraphicsItem::ItemIsMovable, status);
 }

 void Manager::setItemRenderPen(UUID uuid, QPen pen)
 {
     // - m_itemMap
     // - m_propertyMap
     propertyMapFind(uuid,PropertyIndex::Pen) = pen;
     // - TreeViewModel中的节点
     // - Scene
     itemMapFind(uuid)->setPen(pen);
 }

 std::shared_ptr<LaserItem> Manager::itemMapFind(UUID uuid)
 {
     auto it = m_itemMap.find(uuid);
     if (it == m_itemMap.end()) {
         WARN_VAR(uuid);
         FATAL_MSG("fail to find item by uuid");
     }
     return it->second;
 }

 void Manager::itemMapInsert(UUID uuid, std::shared_ptr<LaserItem> ptr)
 {
     m_itemMap.insert({uuid,ptr});
 }

 void Manager::itemMapErase(UUID uuid)
 {
     m_itemMap.erase(uuid);
 }

 QVariant &Manager::propertyMapFind(UUID uuid, PropertyIndex index)
 {
     auto it = m_propertyMap.find(uuid);
     if (it == m_propertyMap.end()) {
         WARN_MSG("target uuid: " + uuid);
         for (const auto& pair : m_propertyMap) {
             WARN_MSG("in map: " + pair.first);
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

 void Manager::propertyMapInsert(UUID uuid, std::map<PropertyIndex, QVariant> map)
 {
     m_propertyMap.insert({uuid,map});
 }

 void Manager::propertyMapErase(UUID uuid)
 {
     m_propertyMap.erase(uuid);
 }

 void Manager::setVisibleSync()
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

 ///
 /// \brief Manager::deleteItem
 /// \param item
 ///
 void Manager::deleteItem(QString uuid)
 {
    auto treeView = UiManager::getIns().UI()->treeView;
    TreeModel *model = qobject_cast<TreeModel *>(treeView->model());

    // 通过遍历所有节点来找到对应节点
    auto allNodes = model->getAllChildNodes(QModelIndex());
    for (const auto& node : allNodes) {
        if(uuid == node->property(NodePropertyIndex::UUID).toString()){
            // DEBUG_MSG("current delete uuid: " + uuid);
            //删除目标节点下所有子节点
            auto nodefamily = model->getAllChildNodes(model->getIndex(node));
            for (auto childNode: nodefamily)
            {
                UUID childUuid = childNode->property(NodePropertyIndex::UUID).toString();
                // DEBUG_MSG("current delete childUuid: " + childUuid);
                auto parentNodeIndex = model->getIndex(childNode->parent());
                if (!model->removeRow(childNode->indexInParent(), parentNodeIndex)) {
                    FATAL_MSG("fail to removeRow");
                }
                itemMapErase(childUuid);
                propertyMapErase(childUuid);
            }

             // 删去在treeViewModel内的节点;
             auto parentNodeIndex = model->getIndex(node->parent());
             if (!model->removeRows(node->indexInParent(),1, parentNodeIndex)) {
                 FATAL_MSG("fail to removeRow");
             }

             // 删去在itemmap中的节点
             itemMapErase(uuid);
             propertyMapErase(uuid);
             break;
         }
     }
 }

 QString Manager::getItem(QModelIndex index)
 {
     auto treeView = UiManager::getIns().UI()->treeView;
     TreeModel *model = qobject_cast<TreeModel *>(treeView->model());

     return model->getNode(index)->property(NodePropertyIndex::UUID).toString();
 }

 QString Manager::getItem(QGraphicsItem *item)
 {
    LaserItem *laseritem = dynamic_cast<LaserItem *>(item);
     return laseritem->getUUID();
 }

 std::vector<QString> Manager::getItemsByLayer(int layer)
 {
    auto treeView = UiManager::getIns().UI()->treeView;
    TreeModel *model = qobject_cast<TreeModel *>(treeView->model());

    QModelIndex nodeIndex;
    auto itemsGroup = std::vector<QString>();
    if (layer==0){
        nodeIndex = QModelIndex();
        // 如果是根节点就不放进来(因为也没有uuid)
    }else {
        if (layer > model->rowCount()){
            FATAL_MSG("input layer exceed the existing layer count");
        }
        nodeIndex = model->index(layer-1,0,QModelIndex());

        auto nodeUUID = model->getNode(nodeIndex)->property(NodePropertyIndex::UUID).toString();
        itemsGroup.push_back(nodeUUID);
    }

    auto nodesGroup = model->getAllChildNodes(nodeIndex);
    for (const auto& node : nodesGroup) {
        itemsGroup.push_back(node->property(NodePropertyIndex::UUID).toString());
    }

    return itemsGroup;
 }
