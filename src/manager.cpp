#include "manager.h"

 Manager Manager::ins;


 void Manager::addItem(std::shared_ptr<QGraphicsItem> ptr)
 {
     this->container.push_back(ptr);
     auto weak_ptr = std::weak_ptr<QGraphicsItem>(ptr);
     this->container2.push_back(weak_ptr);
     this->container3.push_back(weak_ptr);
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

 std::vector<std::shared_ptr<QGraphicsItem> > &Manager::getContainer()
 {
     return this->container;
 }
