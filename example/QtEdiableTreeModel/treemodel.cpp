#include "treemodel.h"
#include "treenode.h"

using namespace Qt::StringLiterals;

TreeModel::TreeModel(const QString &modelName, QObject *parent)
    : QAbstractItemModel(parent)
{
    QVariantList rootProperty(1);
    rootProperty.push_back(modelName);

    m_rootItem = std::make_unique<TreeNode>(rootProperty);
    setupExemplarModelData();
}

TreeModel::~TreeModel() = default;

QVariant TreeModel::data(const QModelIndex &nodeIndex, int role) const
{
    if (!nodeIndex.isValid())
        return {};

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return {};

    TreeNode *item = getItem(nodeIndex);
    // qDebug() <<  item->property(NodePropertyIndex::Name);

    return item->property(NodePropertyIndex::Name);
}

bool TreeModel::setData(const QModelIndex &nodeIndex, const QVariant &name, int role)
{
    if (role != Qt::EditRole)
        return false;

    TreeNode *item = getItem(nodeIndex);
    bool result = item->setProperty(NodePropertyIndex::Name, name);

    if (result)
        emit dataChanged(nodeIndex, nodeIndex, {Qt::DisplayRole, Qt::EditRole});

    return result;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const // 返回m_rootItem的名字
{
    return (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    ? m_rootItem->property(NodePropertyIndex::Name) : QVariant{};
}

bool TreeModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    const bool result = m_rootItem->setProperty(NodePropertyIndex::Name, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parentIndex) const
{
    if (parentIndex.isValid() && parentIndex.column() != 0)
        return {};

    TreeNode *parentItem = getItem(parentIndex);
    if (!parentItem)
        return {};

    if (auto *childItem = parentItem->child(row))
        return createIndex(row, column, childItem);
    return {};
}

QModelIndex TreeModel::parent(const QModelIndex &nodeIndex) const
{
    if (!nodeIndex.isValid())
        return {};

    TreeNode *childItem = getItem(nodeIndex);
    TreeNode *parentItem = childItem ? childItem->parent() : nullptr;

    return (parentItem != m_rootItem.get() && parentItem != nullptr)
               ? createIndex(parentItem->indexInParent(), 0, parentItem) : QModelIndex{};
}

int TreeModel::rowCount(const QModelIndex &nodeIndex) const
{
    if (nodeIndex.isValid() && nodeIndex.column() > 0)
        return 0;

    const TreeNode *nodeItem = getItem(nodeIndex);

    return nodeItem ? nodeItem->childCount() : 0;
}

int TreeModel::columnCount(const QModelIndex &nodeIndex) const
{
    Q_UNUSED(nodeIndex)
    return 1;
}

bool TreeModel::insertRows(int insertPosition, int nodeCount, const QModelIndex &nodeIndex)
{
    TreeNode *nodeItem = getItem(nodeIndex);
    if (!nodeItem)
        return false;

    beginInsertRows(nodeIndex, insertPosition, insertPosition + nodeCount - 1);
    const bool success = nodeItem->insertChilds(insertPosition,nodeCount);
    endInsertRows();

    return success;
}

bool TreeModel::removeRows(int removePosition, int nodeCount, const QModelIndex &nodeIndex)
{
    TreeNode *nodeItem = getItem(nodeIndex);
    if (!nodeItem)
        return false;

    beginRemoveRows(nodeIndex, removePosition, removePosition + nodeCount - 1);
    const bool success = nodeItem->removeChilds(removePosition, nodeCount);
    endRemoveRows();

    return success;
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    // 如果是Layer节点, 不允许拖拽移动,但是可以接受drop和edit
    auto node = getItem(index);
    if(node->property(NodePropertyIndex::Type) == QVariant("Layer"))
        return Qt::ItemIsDropEnabled | Qt::ItemIsEditable | QAbstractItemModel::flags(index);
    // 如果是Item节点, 不允许接收drop, 但是可以drag和edit
    if(node->property(NodePropertyIndex::Type) == QVariant("Item"))
        return Qt::ItemIsDragEnabled | Qt::ItemIsEditable | QAbstractItemModel::flags(index);

    return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

TreeNode *TreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        if (auto *item = static_cast<TreeNode*>(index.internalPointer()))
            return item;
    }
    return m_rootItem.get();
}

void TreeModel::setupExemplarModelData()
{
    m_rootItem->insertChilds(m_rootItem->childCount(),1);
    auto layer1 =  m_rootItem->child(m_rootItem->childCount() - 1);
    layer1->setProperty(NodePropertyIndex::Name, "Layer1");
    layer1->setProperty(NodePropertyIndex::Type, "Layer");

    m_rootItem->insertChilds(m_rootItem->childCount(),1);
    auto layer2 =  m_rootItem->child(m_rootItem->childCount() - 1);
    layer2->setProperty(NodePropertyIndex::Name, "Layer2");
    layer2->setProperty(NodePropertyIndex::Type, "Layer");

    m_rootItem->insertChilds(m_rootItem->childCount(),1);
    auto layer3 =  m_rootItem->child(m_rootItem->childCount() - 1);
    layer3->setProperty(NodePropertyIndex::Name, "Layer3");
    layer3->setProperty(NodePropertyIndex::Type, "Layer");

    for (int i=0;i<10;i++)
    {
        layer1->insertChilds(layer1->childCount(),1);
        auto item = layer1->child(layer1->childCount() - 1);
        QString name = "Item" + QString::number(i);
        item->setProperty(NodePropertyIndex::Name,name);
        item->setProperty(NodePropertyIndex::Type,"Item");
    }

    for (int i=0;i<10;i++)
    {
        layer2->insertChilds(layer2->childCount(),1);
        auto group = layer2->child(layer2->childCount() - 1);
        QString name = "Group" + QString::number(i);
        group->setProperty(NodePropertyIndex::Name,name);
        group->setProperty(NodePropertyIndex::Type,"Group");

        for (int i=0;i<10;i++)
        {
            group->insertChilds(group->childCount(),1);
            auto item = group->child(group->childCount() - 1);
            QString name = "Item" + QString::number(i);
            item->setProperty(NodePropertyIndex::Name,name);
            item->setProperty(NodePropertyIndex::Type,"Item");
        }
    }
}

void TreeModel::setupModelData(const QList<QStringView> &lines)
{
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

void TreeModel::serializeNodeToStream(TreeNode *item, QDataStream &stream, int currentLevel) const
{
    QString line;
    line += QString::number(currentLevel);
    line += "|";
    for (int i = 0; i < item->propertyCount(); i++) {
        line += item->property(i).toString();
        line += "|";
    }

    qDebug() <<"send"<< line;
    stream << line;

    for (int i = 0; i < item->childCount(); i++) {
        int nextLevel = currentLevel+1;
        serializeNodeToStream(item->child(i), stream,nextLevel);
    }
}

Qt::DropActions TreeModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

QStringList TreeModel::mimeTypes() const
{
    QStringList types;
    types << "application/vnd.text.list";
    return types;
}

QMimeData *TreeModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData;
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    for (const QModelIndex &index : indexes) { // 处理多选items
        if (index.isValid()) {
            auto item =  this->getItem(index);
            serializeNodeToStream(item,stream,0);
        }
    }

    mimeData->setData("application/vnd.text.list", encodedData);
    return mimeData;
}

bool TreeModel::canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parentNodeIndex) const
{
    Q_UNUSED(action);

    if (!data->hasFormat("application/vnd.text.list"))
        return false;

    if (column > 0) //只允许放在第一列(这里不知道为什么 反正会返回-1/0)
        return false;

    return true;
}

bool TreeModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parentNodeIndex)
{
    if (!canDropMimeData(data, action, row, column, parentNodeIndex))
        return false;

    if (action == Qt::IgnoreAction)
        return true;

    int beginRowInTopLevel;
    if (row != -1) // 如果是parent节点当前没有子节点, row会设置成-1
        beginRowInTopLevel = row;
    else // 如果parent节点有子节点,row设置成节点个数,也就是存到parent节点下的最后一位
        beginRowInTopLevel = rowCount(parentNodeIndex);

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

    QVector<QPair<TreeNode*, QModelIndex>> parentStack;
    parentStack.push_back(qMakePair(getItem(parentNodeIndex), parentNodeIndex));

    for (const QString &line : std::as_const(newItems)) {
        // 解析层级和节点属性
        QStringList itemList = line.split('|', Qt::SkipEmptyParts);
        int level = itemList[0].toInt();
        itemList.pop_front();

        // qDebug() << "Level:" << level << "ItemList:" << itemList;

        while (parentStack.size() > level + 1) {
            parentStack.pop_back();
        }

        TreeNode *parentItem = parentStack.last().first;
        QModelIndex parentIndex = parentStack.last().second;

        int childIndex = parentItem->childCount();
        if (level == 0) // 如果level是0,那么就用我们指示的插入位置;如果是大于0 也就是子节点, 就按照最后位置去插入位置
            childIndex = beginRowInTopLevel;

        insertRows(childIndex, 1, parentIndex);
        QModelIndex newIdx = this->index(childIndex, 0, parentIndex);
        TreeNode *item = this->getItem(newIdx);

        for (int i = 0; i < item->propertyCount(); i++) {
            if (i < itemList.size()) {
                item->setProperty(i, itemList[i]);
            }
        }

        parentStack.push_back(qMakePair(item, newIdx));

        beginRowInTopLevel++;
    }

    return true;
}












