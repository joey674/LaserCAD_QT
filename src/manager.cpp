#include "manager.h"
#include "treenode.h"
#include "logger.h"
#include "treemodel.h"
#include "uimanager.h"
#include "scenecontroller.h"
#include "polylineitem.h"

Manager Manager::ins;

Manager &Manager::getIns() {
    return ins;
}

///
/// \brief Manager::addItem
/// \param ptr
///
UUID Manager::addItem(std::shared_ptr < GraphicsItem > ptr) {
    auto treeView = UiManager::getIns().UI()->treeView;
    UUID layerUuid = SceneController::getIns().getCurrentLayer();
    QString name = ptr->getName();
    QString uuid = ptr->getUUID();
    // 插入ItemMap
    itemMapInsert(uuid, ptr);
    INFO_MSG("item add: " + ptr->getUUID());
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
        FATAL_MSG("insert  child fail");
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

UUID Manager::addItem(QModelIndex position, QString name, QString type) {
    TreeModel *model = qobject_cast < TreeModel * > (UiManager::getIns().UI()->treeView->model());
    if (!position.isValid()) {
        FATAL_MSG("fail add item to manager");
    }
    auto item = std::make_shared < PolylineItem > ();
    model->setNodeProperty(position, TreeNodePropertyIndex::Name, name);
    model->setNodeProperty(position, TreeNodePropertyIndex::Type, type);
    model->setNodeProperty(position, TreeNodePropertyIndex::UUID, item.get()->getUUID());
    // 插入ItemMap;
    itemMapInsert(item.get()->getUUID(), item);
    INFO_MSG("item add: " + item->getUUID());
    return item.get()->getUUID();
}


std::vector < UUID > Manager::getChildItems(UUID uuid) {
    TreeModel *model = qobject_cast < TreeModel * > (UiManager::getIns().UI()->treeView->model());
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



std::shared_ptr < GraphicsItem > Manager::itemMapFind(UUID uuid) {
    if (!itemMapExist(uuid)) {
        WARN_VAR(uuid);
        FATAL_MSG("fail to find item by uuid");
    }
    return m_itemMap.find(uuid)->second;
}

void Manager::itemMapInsert(UUID uuid, std::shared_ptr < GraphicsItem > ptr) {
    m_itemMap.insert({uuid, ptr});
}

void Manager::itemMapErase(UUID uuid) {
    if (!itemMapExist(uuid)) {
        WARN_VAR(uuid);
        FATAL_MSG("fail to find item by uuid");
    }
    m_itemMap.erase(uuid);
}

bool Manager::itemMapExist(UUID uuid) {
    auto it = m_itemMap.find(uuid);
    if (it == m_itemMap.end()) {
        WARN_VAR(uuid);
        return false;
    }
    return true;
}

void Manager::setLayerItemStateSync() {
    TreeModel *model = qobject_cast < TreeModel * > (UiManager::getIns().UI()->treeView->model());
    int layerCount = model->rowCount(); // 根节点下的所有一层节点
    for (int row = 0; row < layerCount; ++row) {
        QModelIndex layerIndex = model->index(row, 0, QModelIndex());
        TreeNode *layerNode = model->getNode(layerIndex);
        if (!layerNode) {
            FATAL_MSG("");
            continue;
        }
        if (layerNode->property(TreeNodePropertyIndex::Type) != QVariant("Layer")) {
            FATAL_MSG("");
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
/// \brief Manager::deleteItem
/// \param item
///
void Manager::deleteItem(QString uuid) {
    auto treeView = UiManager::getIns().UI()->treeView;
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
                    FATAL_MSG("fail to removeRow from childNode");
                }
                /// TODO-------------------------------------
                /// 暂时不释放资源
                auto item = itemMapFind(childUuid);
                item->setVisible(false);
                this->itemMapErase(childUuid);
                this->m_deletedItemList.push_back(std::move (item));
                /// TODO-------------------------------------
            }
            // 删去目标节点;
            auto parentNodeIndex = model->getIndex(node->parent());
            if (!model->removeRows(node->indexInParent(), 1, parentNodeIndex)) {
                FATAL_MSG("fail to removeRow from parentNode");
            }
            /// TODO-------------------------------------
            /// 暂时不释放资源
            auto item = itemMapFind(uuid);
            item->setVisible(false);
            this->itemMapErase(uuid);
            this->m_deletedItemList.push_back(std::move (item));
            /// TODO-------------------------------------
            break;
        }
    }
}

QString Manager::getItem(QModelIndex index) {
    auto treeView = UiManager::getIns().UI()->treeView;
    TreeModel *model = qobject_cast < TreeModel * > (treeView->model());
    return model->getNode(index)->property(TreeNodePropertyIndex::UUID).toString();
}

QString Manager::getItem(QGraphicsItem *item) {
    GraphicsItem *laseritem = dynamic_cast < GraphicsItem * > (item);
    return laseritem->getUUID();
}

// std::vector < QString > Manager::getItemsByLayer(UUID layerUuid) {
//     auto treeView = UiManager::getIns().UI()->treeView;
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
