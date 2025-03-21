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
     DEBUG_VAR(model->getNode(layerNodeIndex)->propertyList());

     if (!model->insertRow(0, layerNodeIndex))
         FATAL_MSG("insert  child fail");

     const QModelIndex childNodeIndex = model->index(0, 0, layerNodeIndex);
     model->setNodeProperty(childNodeIndex,NodePropertyIndex::Name,name);
     model->setNodeProperty(childNodeIndex,NodePropertyIndex::Type,"Item");
     model->setNodeProperty(childNodeIndex,NodePropertyIndex::UUID,UUID);

     treeview->selectionModel()->setCurrentIndex(model->index(0, 0, childNodeIndex),
                                                 QItemSelectionModel::ClearAndSelect);

     // 插入ItemMap
     ItemMap.insert({UUID,ptr});
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

 

 
