#include "manager.h"
#include "treenode.h"
#include "logger.h"
#include "treemodel.h"
#include "uimanager.h"
#include "scenemanager.h"

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

 ///
 /// \brief Manager::deleteItem
 /// \param item
 ///
 void Manager::deleteItem(LaserItem *item)
 {
     if (!item) return;

    auto treeView = UiManager::getIns().UI()->treeView;
    TreeModel *model = qobject_cast<TreeModel *>(treeView->model());

     // 删去在treeViewModel内的节点;
     QModelIndex nodeIndex = QModelIndex();
     auto allNodes = model->getAllChildNodes(nodeIndex);
     for (const auto& node : allNodes) {
         if(item->getUUID() == node->property(NodePropertyIndex::UUID).toString()){
             auto parentNodeIndex = model->getIndex(node->parent());

             if (!model->removeRow(node->indexInParent(), parentNodeIndex)) {
                 FATAL_MSG("fail to removeRow");
             }

             break;
         }
     }

     // 删去在map中的节点
     ItemMap.erase(item->getUUID());
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

 std::vector<QString> Manager::getItems(int layer)
 {
     auto treeView = UiManager::getIns().UI()->treeView;
     TreeModel *model = qobject_cast<TreeModel *>(treeView->model());

     QModelIndex nodeIndex;
     if (layer==0){
         nodeIndex = QModelIndex();
     }else {
         if (layer > model->rowCount()){
             FATAL_MSG("input layer exceed the existing layer count");
         }
         nodeIndex = model->index(layer-1,0,QModelIndex());
     }
     auto nodesGroup = model->getAllChildNodes(nodeIndex);
     auto itemsGroup = std::vector<QString>();


     for (const auto& node : nodesGroup) {
         itemsGroup.push_back(node->property(NodePropertyIndex::UUID).toString());
     }

     if (layer>0)
        itemsGroup.push_back("Layer"+QString::number(layer)+"UUID");

     return itemsGroup;
 }
