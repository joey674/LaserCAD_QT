#include "treemodel.h"
#include <QColorDialog>
#include "logger.h"
#include "manager.h"
#include "polylineitem.h"
#include "scenecontroller.h"
#include "treenode.h"

using namespace Qt::StringLiterals;

TreeModel::TreeModel(const QString &modelName, QObject *parent)
    : QAbstractItemModel(parent) {
    m_rootItem = std::make_shared < TreeNode > ();
    m_rootItem->setProperty(TreeNodePropertyIndex::Name, modelName);
}

TreeModel::~TreeModel() = default;

QVariant TreeModel::data(const QModelIndex &nodeIndex, int role) const {
    if (!nodeIndex.isValid())
        return {};
    // 获取当前选中的图层
    UUID curlayer = SceneController::getIns().getCurrentLayer();
    TreeNode *node = getNode(nodeIndex);
    QString itemName = node->property(TreeNodePropertyIndex::Name).toString();
    QString itemType = node->property(TreeNodePropertyIndex::Type).toString();
    QString itemUUID = node->property(TreeNodePropertyIndex::UUID).toString();
    bool isVisible = Manager::getIns().itemMapFind(itemUUID)->isVisible();
    QColor color = Manager::getIns().itemMapFind(itemUUID)->getColor();
    // 第0列显示名称 表示树状结构
    if (nodeIndex.column() == 0) {
        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            return node->property(TreeNodePropertyIndex::Name);
        }
    }
    // 第1列为可选中按钮 显示layer是否可视
    else if (nodeIndex.column() == 1) {
        if (role == Qt::CheckStateRole && itemType == "Layer") {
            return isVisible ? Qt::Checked : Qt::Unchecked;
        }
    }
    // 第2列为当前工作图层
    else if (nodeIndex.column() == 2) {
        if (role == Qt::CheckStateRole && itemType == "Layer") {
            bool isCurrent = ( itemUUID == SceneController::getIns ().getCurrentLayer () );
            return isCurrent ? Qt::Checked : Qt::Unchecked;
        }
    }
    // 第3列显示颜色
    else if (nodeIndex.column() == 3) {
        if (role == Qt::BackgroundRole && itemType == "Layer") {
            return QBrush(color);
        } else {
            return QBrush(Qt::white);
        }
    }
    return {};
}

bool TreeModel::setData(const QModelIndex & nodeIndex, const QVariant & value, int role) {
    if (!nodeIndex.isValid()) {
        return false;
    }
    TreeNode *node = getNode(nodeIndex);
    if (!node) {
        return false;
    }
    auto uuid = node->property(TreeNodePropertyIndex::UUID).toString();
    QString itemType = node->property(TreeNodePropertyIndex::Type).toString();
    // auto color = Manager::getIns().itemMapFind(uuid)->getColor();
    // 第 0 列编辑名字
    if (nodeIndex.column() == 0 && role == Qt::EditRole) {
        bool result = node->setProperty(TreeNodePropertyIndex::Name, value);
        if (result)
            emit dataChanged(nodeIndex, nodeIndex, {Qt::DisplayRole, Qt::EditRole});
        return result;
    }
    // 第 1 列设置layer可视状态
    else if (nodeIndex.column() == 1 && role == Qt::CheckStateRole) {
        bool isVisible = (value.toInt() == Qt::Checked);
        auto nodeList = this->getAllChildNodes(nodeIndex);
        nodeList.push_back(node);
        for (const auto &curNode : nodeList) {
            auto uuid = curNode->property(TreeNodePropertyIndex::UUID).toString();
            DEBUG_VAR(uuid);
            DEBUG_VAR(isVisible);
            Manager::getIns().setItemVisible(uuid, isVisible);
        }
        emit dataChanged(nodeIndex, nodeIndex, {Qt::CheckStateRole});
        return true;
    }
    // 第2列设置当前可编辑layer
    else if (nodeIndex.column() == 2 && role == Qt::CheckStateRole) {
        // 只响应 Qt::Checked，忽略取消（因为是互斥）
        if (value.toInt() != Qt::Checked) {
            return false;
        }
        // 设置当前节点
        TreeNode *node = getNode(nodeIndex);
        auto uuid = node->property(TreeNodePropertyIndex::UUID).toString ();
        SceneController::getIns().setCurrentLayer(uuid);
        // 通知整列刷新
        emit dataChanged(this->index(0, 2), this->index(rowCount() - 1, 2), {Qt::CheckStateRole});
        return true;
    }
    // 第3列设置当前layer颜色
    else if (nodeIndex.column() == 3 && role == Qt::BackgroundRole && itemType == "Layer") {
        QColor color = value.value < QColor > ();
        DEBUG_VAR(color);
        std::vector < TreeNode * > nodeList = this->getAllChildNodes(nodeIndex);
        nodeList.push_back(node);
        for (const auto node : nodeList) {
            auto childUuid = node->property(TreeNodePropertyIndex::UUID).toString();
            Manager::getIns().itemMapFind(childUuid)->setColor(color);
        }
        emit dataChanged(nodeIndex, nodeIndex, {Qt::BackgroundRole});
        return true;
    }
    return false;
}
QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
        return {};
    if (section == 0) {
        return m_rootItem->property(TreeNodePropertyIndex::Name);
    } else if (section == 1) {
        return "Visible";
    } else if (section == 2) {
        return "CurLayer";
    } else if (section == 3) {
        return "Color";
    }
    return {};
}
bool TreeModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant & value, int role) {
    if (role != Qt::EditRole || orientation != Qt::Horizontal) {
        return false;
    }
    if (section == 0) {
        bool result = m_rootItem->setProperty(TreeNodePropertyIndex::Name, value);
        if (result) {
            emit headerDataChanged(orientation, section, section);
        }
        return result;
    }
    return false;
}
QModelIndex TreeModel::index(int row, int column, const QModelIndex & parentIndex) const {
    if (parentIndex.isValid() && parentIndex.column() != 0)
        return {};
    TreeNode *parentItem = getNode(parentIndex);
    if (!parentItem)
        return {};
    if (auto *childItem = parentItem->child(row)) {
        return createIndex(row, column, childItem);
    }
    return {};
}
QModelIndex TreeModel::parent(const QModelIndex & nodeIndex) const {
    if (!nodeIndex.isValid())
        return {};
    TreeNode *childItem = getNode(nodeIndex);
    TreeNode *parentItem = childItem ? childItem->parent() : nullptr;
    return (parentItem != m_rootItem.get() && parentItem != nullptr)
           ? createIndex(parentItem->indexInParent(), 0, parentItem) : QModelIndex{};
}
int TreeModel::rowCount(const QModelIndex & nodeIndex) const {
    if (nodeIndex.isValid() && nodeIndex.column() > 0) {
        return 0;
    }
    const TreeNode *nodeItem = getNode(nodeIndex);
    return nodeItem ? nodeItem->childCount() : 0;
}
int TreeModel::columnCount(const QModelIndex & nodeIndex) const {
    Q_UNUSED(nodeIndex)
    return 4;
}
bool TreeModel::insertRows(int insertPosition, int nodeCount, const QModelIndex & nodeIndex) {
    TreeNode *nodeItem = getNode(nodeIndex);
    if (!nodeItem) {
        return false;
    }
    beginInsertRows(nodeIndex, insertPosition, insertPosition + nodeCount - 1);
    const bool success = nodeItem->insertChilds(insertPosition, nodeCount);
    endInsertRows();
    return success;
}
bool TreeModel::removeRows(int removePosition, int nodeCount, const QModelIndex & nodeIndex) {
    TreeNode *nodeItem = getNode(nodeIndex);
    if (!nodeItem) {
        return false;
    }
    beginRemoveRows(nodeIndex, removePosition, removePosition + nodeCount - 1);
    const bool success = nodeItem->removeChilds(removePosition, nodeCount);
    endRemoveRows();
    //     DEBUG_MSG("after moved");
    Manager::getIns().setLayerItemStateSync();
    return success;
}
Qt::ItemFlags TreeModel::flags(const QModelIndex & index) const {
    if (!index.isValid()) {
        return Qt::NoItemFlags;
    }
    Qt::ItemFlags defaultFlags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    auto node = getNode(index);
    // 第0列
    if (index.column() == 0) {
        // 如果是Layer节点, 不允许拖拽移动和编辑,但是可以接受drop
        if (node->property(TreeNodePropertyIndex::Type) == QVariant("Layer")) {
            defaultFlags |= Qt::ItemIsDropEnabled
                            | QAbstractItemModel::flags(index);
        }
        // 如果是Item节点, 不允许接收drop, 但是可以drag和edit
        else if (node->property(TreeNodePropertyIndex::Type) == QVariant("Item")) {
            defaultFlags |= Qt::ItemIsDragEnabled
                            // | Qt::ItemIsEditable
                            | QAbstractItemModel::flags(index);
        } else if (node->property(TreeNodePropertyIndex::Type) == QVariant("Group")) {
            defaultFlags |= Qt::ItemIsDragEnabled
                            | Qt::ItemIsDropEnabled
                            // | Qt::ItemIsEditable
                            | QAbstractItemModel::flags(index);
        } else if (node->property(TreeNodePropertyIndex::Type) == QVariant("Signal")) {
            defaultFlags |= Qt::ItemIsDragEnabled
                            | Qt::ItemIsDropEnabled
                            | QAbstractItemModel::flags(index);
        } else {
            WARN_VAR(node->property(TreeNodePropertyIndex::Type));
            return Qt::NoItemFlags;
        }
    }
    //第1列
    else if (index.column() == 1) {
        // 如果是Layer节点, 可以设置可视
        if (node->property(TreeNodePropertyIndex::Type) == QVariant("Layer")) {
            defaultFlags |= Qt::ItemIsUserCheckable;
        } else {
            return Qt::NoItemFlags;
        }
    }
    //第2列
    else if (index.column() == 2) {
        // 如果是Layer节点, 可以设置工作图层
        if (node->property(TreeNodePropertyIndex::Type) == QVariant("Layer")) {
            defaultFlags |= Qt::ItemIsUserCheckable;
        } else {
            return Qt::NoItemFlags;
        }
    }
    //第3列
    else if (index.column() == 3) {
        // 如果是layer节点,可以编辑颜色
        if (node->property(TreeNodePropertyIndex::Type) == QVariant("Layer")) {
            defaultFlags |= Qt::ItemIsEditable;
        } else {
            return Qt::NoItemFlags;
        }
    }
    // 其他列
    else {
        FATAL_MSG("Unknown index column");
    }
    return defaultFlags;
}

QVariant TreeModel::nodeProperty(const QModelIndex & nodeIndex, const TreeNodePropertyIndex propertyIndex) {
    auto node = getNode(nodeIndex);
    if (!node) {
        FATAL_MSG("nodeindex not found");
    }
    return node->property(propertyIndex);
}

void TreeModel::update() {
    QModelIndex rootIndex = QModelIndex();
    int topLevelCount = rowCount(rootIndex);
    for (int row = 0; row < topLevelCount; ++row) {
        QModelIndex topIndex = index(row, 0, rootIndex);
        if (topIndex.isValid()) {
            emit dataChanged(topIndex, topIndex);
        }
    }
}
void TreeModel::setupExemplarModelData() {
    m_rootItem->insertChilds(m_rootItem->childCount(), 1);
    auto layer1 =  m_rootItem->child(m_rootItem->childCount() - 1);
    layer1->setProperty(TreeNodePropertyIndex::Name, "Layer1");
    layer1->setProperty(TreeNodePropertyIndex::Type, "Layer");
    m_rootItem->insertChilds(m_rootItem->childCount(), 1);
    auto layer2 =  m_rootItem->child(m_rootItem->childCount() - 1);
    layer2->setProperty(TreeNodePropertyIndex::Name, "Layer2");
    layer2->setProperty(TreeNodePropertyIndex::Type, "Layer");
    m_rootItem->insertChilds(m_rootItem->childCount(), 1);
    auto layer3 =  m_rootItem->child(m_rootItem->childCount() - 1);
    layer3->setProperty(TreeNodePropertyIndex::Name, "Layer3");
    layer3->setProperty(TreeNodePropertyIndex::Type, "Layer");
    for (int i = 0; i < 10; i++) {
        layer1->insertChilds(layer1->childCount(), 1);
        auto item = layer1->child(layer1->childCount() - 1);
        QString name = "Item" + QString::number(i);
        item->setProperty(TreeNodePropertyIndex::Name, name);
        item->setProperty(TreeNodePropertyIndex::Type, "Item");
    }
    for (int i = 0; i < 10; i++) {
        layer2->insertChilds(layer2->childCount(), 1);
        auto group = layer2->child(layer2->childCount() - 1);
        QString name = "Group" + QString::number(i);
        group->setProperty(TreeNodePropertyIndex::Name, name);
        group->setProperty(TreeNodePropertyIndex::Type, "Group");
        for (int i = 0; i < 10; i++) {
            group->insertChilds(group->childCount(), 1);
            auto item = group->child(group->childCount() - 1);
            QString name = "Item" + QString::number(i);
            item->setProperty(TreeNodePropertyIndex::Name, name);
            item->setProperty(TreeNodePropertyIndex::Type, "Item");
        }
    }
}
void TreeModel::setupDefaultModelData() {
    m_rootItem->insertChilds(m_rootItem->childCount(), 1);
    auto layer1 = m_rootItem->child(m_rootItem->childCount() - 1);
    auto uuid = Manager::getIns().addItem("Layer1", "Layer", getIndex(layer1));
    SceneController::getIns().initLayerUuid(uuid);
}
void TreeModel::setupModelData(const QList < QStringView > &lines) {
    // struct ParentIndentation
    // {
    //     TreeNode *parent;
    //     qsizetype indentation;
    // };
    // QList<ParentIndentation> state{{rootItem.get(), 0}};
    // for (const auto &line : lines) {
    //     qsizetype position = 0;
    //     for ( ; position < line.length() && line.at(position).isSpace(); ++position) {
    //     }
    //     const QStringView lineData = line.sliced(position).trimmed();
    //     if (!lineData.isEmpty()) {
    //         // Read the column data from the rest of the line.
    //         const auto columnStrings = lineData.split(u'\t', Qt::SkipEmptyParts);
    //         QVariantList columnData;
    //         columnData.reserve(columnStrings.count());
    //         for (const auto &columnString : columnStrings)
    //             columnData << columnString.toString();
    //         if (position > state.constLast().indentation) {
    //             // The last child of the current parent is now the new parent
    //             // unless the current parent has no children.
    //             auto *lastParent = state.constLast().parent;
    //             if (lastParent->childCount() > 0)
    //                 state.append({lastParent->child(lastParent->childCount() - 1), position});
    //         } else {
    //             while (position < state.constLast().indentation && !state.isEmpty())
    //                 state.removeLast();
    //         }
    //         // Append a new item to the current parent's list of children.
    //         auto *parent = state.constLast().parent;
    //         parent->insertChildren(parent->childCount(), 1, rootItem->columnCount());
    //         for (int column = 0; column < columnData.size(); ++column)
    //             parent->child(parent->childCount() - 1)->setData(column, columnData.at(column));
    //     }
    // }
}
void TreeModel::serializeNodeToStream(TreeNode * item, QDataStream & stream, int currentLevel) const {
    QString line;
    line += QString::number(currentLevel);
    line += "|";
    for (int i = 0; i < item->propertyCount(); i++) {
        line += item->property(i).toString();
        line += "|";
    }
    stream << line;
    for (int i = 0; i < item->childCount(); i++) {
        int nextLevel = currentLevel + 1;
        serializeNodeToStream(item->child(i), stream, nextLevel);
    }
}
Qt::DropActions TreeModel::supportedDropActions() const {
    return Qt::CopyAction | Qt::MoveAction;
}
QStringList TreeModel::mimeTypes() const {
    QStringList types;
    types << "application/vnd.text.list";
    return types;
}
QMimeData *TreeModel::mimeData(const QModelIndexList & indexes) const {
    QMimeData *mimeData = new QMimeData;
    QByteArray encodedData;
    QDataStream stream(&encodedData, QIODevice::WriteOnly);
    for (const QModelIndex &index : indexes) { // 处理多选items
        if (index.isValid()) {
            auto item =  this->getNode(index);
            serializeNodeToStream(item, stream, 0);
        }
    }
    mimeData->setData("application/vnd.text.list", encodedData);
    return mimeData;
}
bool TreeModel::canDropMimeData(const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parentNodeIndex) const {
    Q_UNUSED(action);
    if (!data->hasFormat("application/vnd.text.list")) {
        return false;
    }
    if (column > 0) { //只允许放在第一列(这里不知道为什么 反正会返回-1/0)
        return false;
    }
    return true;
}
bool TreeModel::dropMimeData(const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parentNodeIndex) {
    if (!canDropMimeData(data, action, row, column, parentNodeIndex)) {
        return false;
    }
    if (action == Qt::IgnoreAction) {
        return true;
    }
    int beginRowInTopLevel;
    if (row != -1) { // 如果是parent节点当前没有子节点, row会设置成-1
        beginRowInTopLevel = row;
    } else { // 如果parent节点有子节点,row设置成节点个数,也就是存到parent节点下的最后一位
        beginRowInTopLevel = rowCount(parentNodeIndex);
    }
    QByteArray encodedData = data->data("application/vnd.text.list");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);
    QStringList newItems;
    int rows = 0;
    while (!stream.atEnd()) {
        QString line;
        stream >> line;
        newItems << line;
        ++rows;
    }
    // 保存父节点和索引的栈
    QVector < QPair < TreeNode *, QModelIndex>> parentStack;
    parentStack.push_back(qMakePair(getNode(parentNodeIndex), parentNodeIndex));
    int currentLevel = 0; // 当前处理的层级
    int childIndex = beginRowInTopLevel;
    for (const QString &line : std::as_const(newItems)) {
        // 解析层级和节点属性
        QStringList itemList = line.split('|', Qt::SkipEmptyParts);
        int level = itemList[0].toInt();
        itemList.pop_front();
        // DEBUG_VAR(level);
        // DEBUG_VAR(itemList);
        // 如果当前级别比之前低，说明需要退回到父节点
        while (parentStack.size() > level + 1) {
            parentStack.pop_back();
        }
        // 重新计算父节点和插入位置
        TreeNode *parentItem = parentStack.last().first;
        QModelIndex parentIndex = parentStack.last().second;
        // 如果层级为 0，则说明是根节点，需要重新计算根节点插入位置
        if (level == 0) {
            childIndex = beginRowInTopLevel++;
        } else {
            // 非根节点，按照子节点数量排列
            childIndex = parentItem->childCount();
        }
        // 插入新节点
        insertRows(childIndex, 1, parentIndex);
        QModelIndex newIdx = this->index(childIndex, 0, parentIndex);
        TreeNode *item = this->getNode(newIdx);
        // 更新节点属性
        for (int i = 0; i < item->propertyCount(); i++) {
            if (i < itemList.size()) {
                item->setProperty(i, itemList[i]);
            }
        }
        // 压入栈中以便子节点正确嵌套
        parentStack.push_back(qMakePair(item, newIdx));
        // 更新当前层级
        currentLevel = level;
    }
    return true;
}
TreeNode *TreeModel::getNode(const QModelIndex &index) const {
    // 明确是根节点
    if (index == QModelIndex()) {
        Q_ASSERT(m_rootItem);
        return m_rootItem.get();
    }
    // 其他无效 index（不是根节点），这是异常
    if (!index.isValid()) {
        WARN_MSG("getNode: received invalid index (but not root)");
        return nullptr;
    }
    // index 有效，检查内部指针
    void *ptr = index.internalPointer();
    if (!ptr) {
        WARN_MSG("getNode: internalPointer is null!");
        return nullptr;
    }
    return static_cast < TreeNode * > (ptr);
}

QModelIndex TreeModel::getIndex(const TreeNode * node) const {
    auto index = node->indexInParent();
    return createIndex(index, 0, node);
}
QModelIndex TreeModel::getIndex(const UUID uuid) const {
    auto allNodes = this->getAllChildNodes(QModelIndex());
    for (auto node : allNodes) {
        if (node->property(TreeNodePropertyIndex::UUID) == uuid) {
            auto index = this->getIndex(node);
            return index;
        }
    }
    return QModelIndex{};
}
std::vector < TreeNode * > TreeModel::getAllChildNodes(const QModelIndex &nodeIndex) const {
    std::vector < TreeNode * > children;
    // 返回node都返回第0列的
    auto baseIndex = nodeIndex.sibling(nodeIndex.row(), 0);
    TreeNode* baseNode = getNode(baseIndex);
    if (!baseNode) {
        WARN_MSG("null node");
        return children;
    }
    int childCount = rowCount(baseIndex);
    for (int row = 0; row < childCount; ++row) {
        QModelIndex childIndex = index(row, 0, baseIndex);
        TreeNode* childNode = getNode(childIndex);
        if (!childNode) {
            continue;
        }
        children.push_back(childNode);
        auto subChildren = getAllChildNodes(childIndex);
        children.insert(children.end(), subChildren.begin(), subChildren.end());
    }
    return children;
}

std::vector < QModelIndex > TreeModel::getAllChildIndexs(const QModelIndex &nodeIndex) const {
    std::vector < QModelIndex > children;
    QModelIndex baseIndex = nodeIndex.sibling(nodeIndex.row(), 0);
    TreeNode *baseNode = getNode(baseIndex);
    if (!baseNode) {
        return children; // 可能是无效索引或错误节点
    }
    int childCount = rowCount(baseIndex);
    for (int row = 0; row < childCount; ++row) {
        QModelIndex childIndex = this->index(row, 0, baseIndex);
        if (!childIndex.isValid()) {
            continue;
        }
        children.push_back(childIndex);
        auto subChildren = getAllChildIndexs(childIndex);
        children.insert(children.end(), subChildren.begin(), subChildren.end());
    }
    return children;
}

void TreeModel::setNodeProperty(const QModelIndex & nodeIndex, const TreeNodePropertyIndex propertyIndex, const QVariant & value) {
    auto node = getNode(nodeIndex);
    if (!node) {
        FATAL_MSG("nodeindex not found");
    }
    node->setProperty(propertyIndex, value);
}
