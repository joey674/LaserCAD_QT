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
     this->container.insert(ptr);

     auto layer = ptr->getLayer();
     auto weak_ptr = std::weak_ptr<LaserItem>(ptr);
     this->layerMap[layer].push_back(weak_ptr);
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
 }

 const std::unordered_set<std::shared_ptr<LaserItem>>& Manager::getContainer()
 {
     return this->container;
 }

 const std::vector<std::weak_ptr<LaserItem> > &Manager::getItemsByGroup(int)
 {

 }

 const std::vector<std::weak_ptr<LaserItem>>& Manager::getItemsByLayer(int index)
 {
     return this->layerMap[index];
 }

