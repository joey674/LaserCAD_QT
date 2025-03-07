#include "manager.h"

 Manager Manager::ins;


 void Manager::init(QGraphicsScene *sc)
 {
     ins.scene = sc;
 }

 Manager &Manager::getIns()
 {
     return ins;
 }

 void Manager::addItem(std::shared_ptr<LaserItem> ptr)
 {
    this->container.push_back(ptr);

    auto layer = ptr->getLayer();
    this->layerMap[layer].push_back(ptr);

    ///TODO
    /// GroupAdd
 }

 void Manager::deleteItem(QGraphicsItem *item)
 {
     if (!item) return;

     auto it = std::find_if(this->container.begin(), this->container.end(),
                            [item](const std::shared_ptr<QGraphicsItem>& ptr) {
                                return ptr.get() == item;
                            });
     if (it != this->container.end()) {
         this->container.erase(it);
     }
     ///TODO
     /// GroupDelete
     /// LayerDelete
 }

 const std::list<std::shared_ptr<LaserItem>>& Manager::getItems()
 {
     return this->container;
 }

 const std::list<std::shared_ptr<LaserItem> > &Manager::getItemsByGroup(int)
 {

 }

 const std::list<std::shared_ptr<LaserItem>>& Manager::getItemsByLayer(int index)
 {
     return this->layerMap[index];
 }

