// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "treemodel.h"
#include "treeitem.h"

using namespace Qt::StringLiterals;

//! [0]
TreeModel::TreeModel(const QStringList &headersGroup, const QString &data, QObject *parent)
    : QAbstractItemModel(parent)
{
    QVariantList rootData;
    for (const QString &header : headersGroup)
        rootData << header;

    rootItem = std::make_unique<TreeItem>(rootData);
    setupModelData(QStringView{data}.split(u'\n'));
}
//! [0]

//! [1]
TreeModel::~TreeModel() = default;
//! [1]

//! [2]
int TreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return rootItem->columnCount();
}
//! [2]

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return {};

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return {};

    TreeItem *item = getItem(index);

    return item->data(index.column());
}

//! [3]
Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}
//! [3]

//! [4]
TreeItem *TreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        if (auto *item = static_cast<TreeItem*>(index.internalPointer()))
            return item;
    }
    return rootItem.get();
}
//! [4]

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    return (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        ? rootItem->data(section) : QVariant{};
}

//! [5]
QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return {};
//! [5]

//! [6]
    TreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return {};

    if (auto *childItem = parentItem->child(row))
        return createIndex(row, column, childItem);
    return {};
}
//! [6]

bool TreeModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    beginInsertColumns(parent, position, position + columns - 1);
    const bool success = rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool TreeModel::insertRows(int positionIndex, int IndexNum, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginInsertRows(parent, positionIndex, positionIndex + IndexNum - 1);
    const bool success = parentItem->insertChildren(positionIndex,
                                                    IndexNum,
                                                    rootItem->columnCount());
    endInsertRows();

    return success;
}

//! [7]
QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return {};

    TreeItem *childItem = getItem(index);
    TreeItem *parentItem = childItem ? childItem->parent() : nullptr;

    return (parentItem != rootItem.get() && parentItem != nullptr)
        ? createIndex(parentItem->row(), 0, parentItem) : QModelIndex{};
}
//! [7]

bool TreeModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    beginRemoveColumns(parent, position, position + columns - 1);
    const bool success = rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if (rootItem->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}

bool TreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginRemoveRows(parent, position, position + rows - 1);
    const bool success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
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

    for (const QModelIndex &index : indexes) {
        if (index.isValid()) {
            QString text = data(index, Qt::DisplayRole).toString();
            stream << text;
        }
    }

    mimeData->setData("application/vnd.text.list", encodedData);
    return mimeData;
}

bool TreeModel::canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(action);
    Q_UNUSED(row);
    Q_UNUSED(parent);

    qDebug() << "drop column" << column;

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

    int beginRow;
    if (row != -1) // 如果是parent节点当前没有子节点, row会设置成-1
        beginRow = row;
    else // 如果parent节点有子节点,row设置成节点个数,也就是存到parent节点下的最后一位
        beginRow = rowCount(parentNodeIndex);

    qDebug() << "row" << row;
    qDebug() <<   "beginRow" << beginRow;
    qDebug() << parentNodeIndex.data() << this->getItem(parentNodeIndex)->uuid;


    QByteArray encodedData = data->data("application/vnd.text.list");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);
    QStringList newItems;
    int rows = 0;
    while (!stream.atEnd()) {
        QString text;
        stream >> text;
        newItems << text;
        ++rows;
    }

    insertRows(beginRow, rows, parentNodeIndex);
    for (const QString &text : std::as_const(newItems)) {
        QModelIndex idx = this->index(beginRow, 0, parentNodeIndex);
        setData(idx, text);
        beginRow++;
    }

    return true;
}



//! [8]
int TreeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() > 0)
        return 0;

    const TreeItem *parentItem = getItem(parent);

    return parentItem ? parentItem->childCount() : 0;
}
//! [8]

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    TreeItem *item = getItem(index);
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});

    return result;
}

bool TreeModel::setHeaderData(int section, Qt::Orientation orientation,
                              const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    const bool result = rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}

void TreeModel::setupModelData(const QList<QStringView> &lines)
{
    struct ParentIndentation
    {
        TreeItem *parent;
        qsizetype indentation;
    };

    QList<ParentIndentation> state{{rootItem.get(), 0}};

    for (const auto &line : lines) {
        qsizetype position = 0;
        for ( ; position < line.length() && line.at(position).isSpace(); ++position) {
        }

        const QStringView lineData = line.sliced(position).trimmed();
        if (!lineData.isEmpty()) {
            // Read the column data from the rest of the line.
            const auto columnStrings = lineData.split(u'\t', Qt::SkipEmptyParts);
            QVariantList columnData;
            columnData.reserve(columnStrings.count());
            for (const auto &columnString : columnStrings)
                columnData << columnString.toString();

            if (position > state.constLast().indentation) {
                // The last child of the current parent is now the new parent
                // unless the current parent has no children.
                auto *lastParent = state.constLast().parent;
                if (lastParent->childCount() > 0)
                    state.append({lastParent->child(lastParent->childCount() - 1), position});
            } else {
                while (position < state.constLast().indentation && !state.isEmpty())
                    state.removeLast();
            }

            // Append a new item to the current parent's list of children.
            auto *parent = state.constLast().parent;
            parent->insertChildren(parent->childCount(), 1, rootItem->columnCount());
            for (int column = 0; column < columnData.size(); ++column)
                parent->child(parent->childCount() - 1)->setData(column, columnData.at(column));
        }
    }
}
