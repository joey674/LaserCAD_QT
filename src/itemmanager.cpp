#include "itemmanager.h"
#include "treenode.h"
#include "logger.h"
#include "treemodel.h"
#include "uimanager.h"
#include "scenecontroller.h"
#include "polylineitem.h"

ItemManager ItemManager::ins;

ItemManager &ItemManager::getIns() {
    return ins;
}

///
/// \brief ItemManager::addItem
/// \param ptr
///
UUID ItemManager::addItem(std::shared_ptr < GraphicsItem > ptr) {
    auto treeView = UiManager::getIns(). treeView;
    UUID layerUuid = SceneController::getIns().getCurrentLayer();
    QString name = ptr->getName();
    QString uuid = ptr->getUUID();
    // 插入ItemMap
    itemMapInsert(uuid, ptr);
    // INFO_MSG("item add: " + ptr->getUUID());
    // 插入TreeViewModel 注意 这个要最后做 不然会报bug
    TreeModel *model = qobject_cast < TreeModel * > (treeView->model());
    QModelIndex layerNodeIndex;
    for (int row = 0; row < model->rowCount(); ++row) {
        QModelIndex index = model->index(row, 0, QModelIndex()); // 第 row 行的图层
        TreeNode *node = model->getNode(index);
        if (node && node->property(TreeNodePropertyIndex::Type) == QVariant("Layer")) {
            QString uuid = node->property(TreeNodePropertyIndex::UUID).toString();
            if (uuid == layerUuid) {
                layerNodeIndex = index;
                break;
            }
        }
    }
    auto rowCount = model->rowCount(layerNodeIndex);
    name = name + QString::number(rowCount + 1);
    if (!model->insertRow(rowCount, layerNodeIndex)) {
        WARN_MSG("insert  child fail");
    }
    const QModelIndex childNodeIndex = model->index(rowCount, 0, layerNodeIndex);
    model->setNodeProperty(childNodeIndex, TreeNodePropertyIndex::Name, name);
    model->setNodeProperty(childNodeIndex, TreeNodePropertyIndex::Type, "Item");
    model->setNodeProperty(childNodeIndex, TreeNodePropertyIndex::UUID, uuid);
    treeView->selectionModel()->setCurrentIndex(model->index(0, 0, childNodeIndex),
            QItemSelectionModel::ClearAndSelect);
    // 所有物体都不可以move!!
    this->setItemMovable(uuid, false);
    return uuid;
}

UUID ItemManager::addItem(QString name, QString type, QModelIndex position) {
    TreeModel *model = qobject_cast < TreeModel * > (UiManager::getIns(). treeView->model());
    if (!position.isValid()) {
        WARN_MSG("position is not valid, will add to current layer");
        auto layerUuid = SceneController::getIns().getCurrentLayer();
        auto layerIndex = model->getIndex(layerUuid);
        auto layerNode = model->getNode(layerIndex);
        if (!model->insertRow(layerNode->childCount (), layerIndex)) {
            WARN_MSG("fail insert layer");
        }
        position = model->index(layerNode->childCount () - 1, 0, layerIndex);//
    }
    auto item = std::make_shared < ArcItem > ();
    model->setNodeProperty(position, TreeNodePropertyIndex::Name, name);
    model->setNodeProperty(position, TreeNodePropertyIndex::Type, type);
    model->setNodeProperty(position, TreeNodePropertyIndex::UUID, item.get()->getUUID());
    // 插入ItemMap;
    itemMapInsert(item.get()->getUUID(), item);
    // INFO_MSG("item add: " + item->getUUID());
    return item.get()->getUUID();
}

std::vector < UUID > ItemManager::getChildItems(UUID uuid) {
    TreeModel *model = qobject_cast < TreeModel * > (UiManager::getIns(). treeView->model());
    // model->update();
    QModelIndex nodeIndex;
    std::vector < UUID > uuidGroup;
    // 只有输入特定uuid才能获得根节点 从而返回所有节点
    if (uuid == "0-0-0-0") {
        nodeIndex = QModelIndex{};
    } else if (!itemMapExist(uuid)) {
        WARN_MSG("Unknown UUID");
        return uuidGroup;
    } else {
        nodeIndex = model->getIndex(uuid);
    }
    auto allItems = model->getAllChildNodes(nodeIndex);
    for (const auto &item : allItems) {
        auto uuid = item->property(TreeNodePropertyIndex::UUID).toString();
        uuidGroup.push_back(uuid);
    }
    return uuidGroup;
}

std::shared_ptr < GraphicsItem > ItemManager::itemMapFind(UUID uuid) {
    if (!itemMapExist(uuid)) {
        WARN_MSG("fail to find item by uuid: " + uuid);
    }
    return m_itemMap.find(uuid)->second;
}

void ItemManager::itemMapInsert(UUID uuid, std::shared_ptr < GraphicsItem > ptr) {
    m_itemMap.insert({uuid, ptr});
}

void ItemManager::itemMapErase(UUID uuid) {
    if (!itemMapExist(uuid)) {
        WARN_MSG("fail to find item by uuid: " + uuid);
    }
    m_itemMap.erase(uuid);
}

bool ItemManager::itemMapExist(UUID uuid) {
    auto it = m_itemMap.find(uuid);
    if (it == m_itemMap.end()) {
        return false;
    }
    return true;
}

void ItemManager::setLayerItemStateSync() {
    TreeModel *model = qobject_cast < TreeModel * > (UiManager::getIns(). treeView->model());
    int layerCount = model->rowCount(); // 根节点下的所有一层节点
    for (int row = 0; row < layerCount; ++row) {
        QModelIndex layerIndex = model->index(row, 0, QModelIndex());
        TreeNode *layerNode = model->getNode(layerIndex);
        if (!layerNode) {
            WARN_MSG("");
            continue;
        }
        if (layerNode->property(TreeNodePropertyIndex::Type) != QVariant("Layer")) {
            WARN_MSG("");
            continue;
        }
        // 获取子图形节点
        auto childNodes = model->getAllChildNodes(layerIndex);
        if (childNodes.empty()) {
            continue;
        }
        // 获取layer的状态
        auto layerUuid = layerNode->property(TreeNodePropertyIndex::UUID).toString();
        bool isVisible = this->itemMapFind(layerUuid)->isVisible();
        QColor color = this->itemMapFind(layerUuid)->getColor();
        bool isCurLayer = SceneController::getIns().getCurrentLayer() == layerUuid;
        // 应用到所有子图形
        for (auto *node : childNodes) {
            auto uuid = node->property(TreeNodePropertyIndex::UUID).toString();
            this->setItemVisible(uuid, isVisible);
            this->itemMapFind(uuid)->setColor(color);
            this->setItemSelectable(uuid, isCurLayer);
        }
    }
}


///
/// \brief ItemManager::deleteItem
/// \param item
///
void ItemManager::deleteItem(QString uuid) {
    auto treeView = UiManager::getIns(). treeView;
    TreeModel *model = qobject_cast < TreeModel * > (treeView->model());
    // 通过遍历所有节点来找到对应节点
    auto allNodes = model->getAllChildNodes(QModelIndex());
    for (const auto& node : allNodes) {
        if(uuid == node->property(TreeNodePropertyIndex::UUID).toString()) {
            // 先删除目标节点下所有子节点;
            // 由于getAllChildNodes是顺序添加 那删除就倒序删除就不会出现先删父节点再删子节点
            auto nodefamily = model->getAllChildNodes(model->getIndex(node));
            std::reverse(nodefamily.begin(), nodefamily.end());
            for (auto childNode : nodefamily) {
                UUID childUuid = childNode->property(TreeNodePropertyIndex::UUID).toString();
                auto parentNodeIndex = model->getIndex(childNode->parent());
                if (!model->removeRow(childNode->indexInParent(), parentNodeIndex)) {
                    WARN_MSG("fail to removeRow from childNode");
                }
                /// TODO-------------------------------------
                /// 暂时不释放资源
                auto item = itemMapFind(childUuid);
                // 一个clearSelection的bug,在remove之后还触发了对象的回调 导致空指针
                SceneController::getIns().scene->removeItem(item.get()); //  在场景中删除
                item->setVisible(false);                                 // 并且需要设置unvisible
                this->itemMapErase(childUuid);
                this->m_deletedItemList.push_back(std::move (item));
                /// TODO-------------------------------------
            }
            // 删去目标节点;
            auto parentNodeIndex = model->getIndex(node->parent());
            auto indexInParent = node->indexInParent();
            if (!model->removeRows(indexInParent, 1, parentNodeIndex)) {
                WARN_MSG("fail to removeRow from parentNode");
            }
            /// TODO-------------------------------------
            /// 暂时不释放资源
            auto item = itemMapFind(uuid);
            // 一个clearSelection的bug,在remove之后还触发了对象的回调 导致空指针
            SceneController::getIns().scene->removeItem(item.get()); //  在场景中删除
            item->setVisible(false);                                 // 并且需要设置unvisible
            this->itemMapErase(uuid);
            this->m_deletedItemList.push_back(std::move (item));
            /// TODO-------------------------------------
            break;
        }
    }
}

QString ItemManager::getItem(QModelIndex index) {
    auto treeView = UiManager::getIns(). treeView;
    TreeModel *model = qobject_cast < TreeModel * > (treeView->model());
    return model->getNode(index)->property(TreeNodePropertyIndex::UUID).toString();
}

QString ItemManager::getItem(QGraphicsItem *item) {
    GraphicsItem *laseritem = dynamic_cast < GraphicsItem * > (item);
    return laseritem->getUUID();
}

// std::vector < QString > ItemManager::getItemsByLayer(UUID layerUuid) {
//     auto treeView = UiManager::getIns(). treeView;
//     TreeModel *model = qobject_cast < TreeModel * > (treeView->model());
//     QModelIndex layerNodeIndex = QModelIndex{};
//     auto itemsGroup = std::vector < QString > ();
//     for (int row = 0; row < model->rowCount(); ++row) {
//         QModelIndex index = model->index(row, 0, QModelIndex()); // 第 row 行的图层
//         TreeNode *node = model->getNode(index);
//         if (node && node->property(TreeNodePropertyIndex::Type) == QVariant("Layer")) {
//             QString uuid = node->property(TreeNodePropertyIndex::UUID).toString();
//             if (uuid == layerUuid) {
//                 layerNodeIndex = index;
//                 break;
//             }
//         }
//     }
//     if (layerNodeIndex == QModelIndex{}) { // 没找到
//         return itemsGroup;
//     } else {
//         auto nodesGroup = model->getAllChildNodes(layerNodeIndex);
//         for (const auto& node : nodesGroup) {
//             itemsGroup.push_back(node->property(TreeNodePropertyIndex::UUID).toString());
//         }
//         return itemsGroup;
//     }
// }
