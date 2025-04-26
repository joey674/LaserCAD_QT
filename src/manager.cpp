#include "manager.h"
#include "treenode.h"
#include "logger.h"
#include "treemodel.h"
#include "uimanager.h"
#include "scenemanager.h"
#include "polylineitem.h"

Manager Manager::ins;

Manager &Manager::getIns() {
    return ins;
}

///
/// \brief Manager::addItem
/// \param ptr
///
void Manager::addItem(std::shared_ptr < GraphicsItem > ptr) {
    auto treeView = UiManager::getIns().UI()->treeView;
    int layer = SceneManager::getIns().getCurrentLayer();
    QString name = ptr->getName();
    QString uuid = ptr->getUUID();
    auto type = ptr->type();
    // 插入ItemMap
    itemMapInsert(uuid, ptr);
    INFO_MSG("item add: " + ptr->getUUID());
    // 插入TreeViewModel 注意 这个要最后做 不然会报bug
    TreeModel *model = qobject_cast < TreeModel * > (treeView->model());
    QModelIndex layerNodeIndex = model->index(layer - 1, 0, QModelIndex());
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
}

void Manager::addItem(QModelIndex position, QString name, QString type) {
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
}

void Manager::setItemVisible(UUID uuid, bool status) {
    itemMapFind(uuid)->setVisible(status);
}

void Manager::setItemSelectable(UUID uuid, bool status) {
    // TODO
    status = true;
    itemMapFind(uuid)->setFlag(QGraphicsItem::ItemIsSelectable, status);
}

void Manager::setItemMovable(UUID uuid, bool status) {
    // TODO
    status = false;
    itemMapFind(uuid)->setFlag(QGraphicsItem::ItemIsMovable, status);
}

std::shared_ptr < GraphicsItem > Manager::itemMapFind(UUID uuid) {
    auto it = m_itemMap.find(uuid);
    if (it == m_itemMap.end()) {
        WARN_VAR(uuid);
        FATAL_MSG("fail to find item by uuid");
    }
    return it->second;
}

void Manager::itemMapInsert(UUID uuid, std::shared_ptr < GraphicsItem > ptr) {
    m_itemMap.insert({uuid, ptr});
}

void Manager::itemMapErase(UUID uuid) {
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

void Manager::setVisibleSync() {
    for (int layer = 1; layer <= SceneManager::getIns().layerCount(); ++layer) {
        auto uuids = getItemsByLayer(layer);
        bool isVisible = this->itemMapFind(uuids[0])->isVisible();
        // DEBUG_VAR(layer);
        // DEBUG_VAR(isVisible);
        for (const auto &uuid : uuids) {
            // DEBUG_VAR(item);
            this->setItemVisible(uuid, isVisible);
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
            //先删除目标节点下所有子节点;
            // 由于getAllChildNodes是顺序添加 那删除就倒序删除就不会出现先删父节点再删子节点
            auto nodefamily = model->getAllChildNodes(model->getIndex(node));
            std::reverse(nodefamily.begin(), nodefamily.end());
            for (auto childNode : nodefamily) {
                UUID childUuid = childNode->property(TreeNodePropertyIndex::UUID).toString();
                auto parentNodeIndex = model->getIndex(childNode->parent());
                if (!model->removeRow(childNode->indexInParent(), parentNodeIndex)) {
                    FATAL_MSG("fail to removeRow from childNode");
                }
                itemMapErase(childUuid);
            }
            // 删去目标节点;
            auto parentNodeIndex = model->getIndex(node->parent());
            if (!model->removeRows(node->indexInParent(), 1, parentNodeIndex)) {
                FATAL_MSG("fail to removeRow from parentNode");
            }
            itemMapErase(uuid);
            //
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

std::vector < QString > Manager::getItemsByLayer(int layer) {
    auto treeView = UiManager::getIns().UI()->treeView;
    TreeModel *model = qobject_cast < TreeModel * > (treeView->model());
    QModelIndex nodeIndex;
    auto itemsGroup = std::vector < QString > ();
    if (layer == 0) {
        nodeIndex = QModelIndex();
        // 如果是根节点就不放进来(因为也没有uuid)
    } else {
        if (layer > model->rowCount()) {
            FATAL_MSG("input layer exceed the existing layer count");
        }
        nodeIndex = model->index(layer - 1, 0, QModelIndex());
        auto nodeUUID = model->getNode(nodeIndex)->property(TreeNodePropertyIndex::UUID).toString();
        itemsGroup.push_back(nodeUUID);
    }
    auto nodesGroup = model->getAllChildNodes(nodeIndex);
    for (const auto& node : nodesGroup) {
        itemsGroup.push_back(node->property(TreeNodePropertyIndex::UUID).toString());
    }
    return itemsGroup;
}
