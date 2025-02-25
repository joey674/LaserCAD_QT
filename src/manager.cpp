#include "manager.h"

 Manager Manager::ins;


 void Manager::addItem(QGraphicsItem *item)
 {
     if (!item) return;

     auto ptr = std::make_shared<QGraphicsItem>(std::move(item));// ??可能有bug
     this->scene->addItem(ptr.get());
     this->container.push_back(ptr);

     auto weak_ptr = std::weak_ptr<QGraphicsItem>(ptr);
     this->container2.push_back(weak_ptr);
     this->container3.push_back(weak_ptr);
 }


 void Manager::deleteItem(QGraphicsItem *item)
 {
     if (!item) return;

     this->scene->removeItem(item);

     auto it = std::find_if(this->container.begin(), this->container.end(),
                            [item](const std::unique_ptr<QGraphicsItem>& ptr) {
                                return ptr.get() == item;
                            });
     if (it != this->container.end()) {
         this->container.erase(it);
     }
 }
