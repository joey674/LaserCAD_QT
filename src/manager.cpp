#include "manager.h"
#include "treenode.h"

 Manager Manager::ins;

 void Manager::addItem(std::shared_ptr<LaserItem> ptr)
 {
     int layer = ptr->getLayer();
     QString name = ptr->getName();
     QString UUID = ptr->getUUID();

     // 插入TreeViewModel
     TreeViewModel *model = qobject_cast<TreeViewModel *>(treeview->model());
     QModelIndex layerNodeIndex = model->index(layer-1,0,QModelIndex());
     // DEBUG_VAR(model->getNode(layerNodeIndex)->propertyList());

     auto rowCount = model->rowCount(layerNodeIndex);

     if (!model->insertRow(rowCount, layerNodeIndex))
         FATAL_MSG("insert  child fail");

     const QModelIndex childNodeIndex = model->index(rowCount, 0, layerNodeIndex);
     model->setNodeProperty(childNodeIndex,NodePropertyIndex::Name,name);
     model->setNodeProperty(childNodeIndex,NodePropertyIndex::Type,"Item");
     model->setNodeProperty(childNodeIndex,NodePropertyIndex::UUID,UUID);

     treeview->selectionModel()->setCurrentIndex(model->index(0, 0, childNodeIndex),
                                                 QItemSelectionModel::ClearAndSelect);

     // 插入ItemMap
    DEBUG_VAR(ptr.get());
     ItemMap.insert({UUID,ptr});
 }

 void Manager::deleteItem(LaserItem *item)
 {
     if (!item) return;

     TreeViewModel *model = qobject_cast<TreeViewModel *>(treeview->model());

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

 std::vector<std::shared_ptr<LaserItem> > Manager::getItems(int layer)
 {
     TreeViewModel *model = qobject_cast<TreeViewModel *>(treeview->model());

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
     auto itemsGroup = std::vector<std::shared_ptr<LaserItem>>();
     for (const auto& node : nodesGroup) {
         if(node->property(NodePropertyIndex::Type).toString() != "Item")
             continue;
         auto item = ItemMap.find(node->property(NodePropertyIndex::UUID).toString())->second;
         itemsGroup.push_back(item);
     }

     return itemsGroup;
 }

 void Manager::init(QGraphicsScene *sc, QTreeView *tv)
 {
     ins.scene = sc;
     ins.treeview = tv;
 }

 Manager &Manager::getIns()
 {
     return ins;
 }

 

 
