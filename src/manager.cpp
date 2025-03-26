#include "manager.h"
#include "treenode.h"
#include "logger.h"
#include "treemodel.h"
#include "uimanager.h"
#include "scenemanager.h"
#include "utils.hpp"
#include "polylineitem.h"
#include "arcitem.h"

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
    QString UUID = ptr->getUUID();

    // 插入TreeViewModel
    TreeModel *model = qobject_cast<TreeModel *>(treeView->model());
    QModelIndex layerNodeIndex = model->index(layer-1,0,QModelIndex());
    // DEBUG_VAR(model->getNode(layerNodeIndex)->propertyList());

    auto rowCount = model->rowCount(layerNodeIndex);
    name = name + QString::number(rowCount+1);

    if (!model->insertRow(rowCount, layerNodeIndex))
     FATAL_MSG("insert  child fail");

    const QModelIndex childNodeIndex = model->index(rowCount, 0, layerNodeIndex);
    model->setNodeProperty(childNodeIndex,NodePropertyIndex::Name,name);
    model->setNodeProperty(childNodeIndex,NodePropertyIndex::Type,"Item");
    model->setNodeProperty(childNodeIndex,NodePropertyIndex::UUID,UUID);

    treeView->selectionModel()->setCurrentIndex(model->index(0, 0, childNodeIndex),
                                                 QItemSelectionModel::ClearAndSelect);

    // 插入ItemMap
    // DEBUG_VAR(ptr.get());
    ItemMap.insert({UUID,ptr});

    // 插入propertyMap
    auto map = DefaultPropertyMap;
    PropertyMap.insert({UUID,map});
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
     // 插入ItemMap
     // DEBUG_VAR(ptr.get());
     ItemMap.insert({item.get()->getUUID(),item});

     // 插入propertyMap
     auto map = DefaultPropertyMap;
     PropertyMap.insert({item.get()->getUUID(),map});
 }

 ///
 /// \brief Manager::deleteItem
 /// \param item
 ///
 void Manager::deleteItem(QString UUID)
 {
    auto treeView = UiManager::getIns().UI()->treeView;
    TreeModel *model = qobject_cast<TreeModel *>(treeView->model());

    // 删去在treeViewModel内的节点;通过遍历所有节点来找到对应节点
    QModelIndex nodeIndex = QModelIndex();
    auto allNodes = model->getAllChildNodes(nodeIndex);
    for (const auto& node : allNodes) {
        if(UUID == node->property(NodePropertyIndex::UUID).toString()){
            //删除目标节点下所有子节点
            auto nodefamily = model->getAllChildNodes(model->getIndex(node));
            for (auto childNode: nodefamily)
            {
                auto parentNodeIndex = model->getIndex(childNode->parent());
                if (!model->removeRow(childNode->indexInParent(), parentNodeIndex)) {
                    FATAL_MSG("fail to removeRow");
                }
                ItemMap.erase(childNode->property(NodePropertyIndex::UUID).toString());
                PropertyMap.erase(childNode->property(NodePropertyIndex::UUID).toString());
            }

             // 删除目标节点(不能先删 不然的话treenode直接被model给清空了)
             auto parentNodeIndex = model->getIndex(node->parent());
             if (!model->removeRow(node->indexInParent(), parentNodeIndex)) {
                 FATAL_MSG("fail to removeRow");
             }

             ItemMap.erase(UUID);
             PropertyMap.erase(UUID);
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
