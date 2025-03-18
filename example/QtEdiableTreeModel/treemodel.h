// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QMimeData>
#include <QIODevice>
#include "treeitem.h"


//! [0]
class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    Q_DISABLE_COPY_MOVE(TreeModel)

    TreeModel(const QStringList &header, const QString &data,
              QObject *parent = nullptr);
    ~TreeModel() override;
//! [0] //! [1]

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = {}) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = {}) const override;
    int columnCount(const QModelIndex &parent = {}) const override;
//! [1]

//! [2]
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    bool setHeaderData(int section, Qt::Orientation orientation,
                       const QVariant &value, int role = Qt::EditRole) override;

    bool insertColumns(int position, int columns,
                       const QModelIndex &parent = {}) override; // deprecate 都只用第一列columns存数状结构；
    bool removeColumns(int position, int columns,
                       const QModelIndex &parent = {}) override; // deprecate
    bool insertRows(int position, int rows,
                    const QModelIndex &parent = {}) override;
    bool removeRows(int position, int rows,
                    const QModelIndex &parent = {}) override;


//! [3]
    Qt::DropActions supportedDropActions() const override
    {
        return Qt::CopyAction | Qt::MoveAction;
    }
    QStringList mimeTypes() const override
    {
        QStringList types;
        types << "application/vnd.text.list";
        return types;
    }
    QMimeData *mimeData(const QModelIndexList &indexes) const override
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
    bool canDropMimeData(const QMimeData *data,Qt::DropAction action, int row, int column, const QModelIndex &parent) const override
    {
        Q_UNUSED(action);
        Q_UNUSED(row);
        Q_UNUSED(parent);

        if (!data->hasFormat("application/vnd.text.list"))
            return false;

        if (column > 0) //只允许放在第一列
            return false;

        return true;
    }
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parentNodeIndex) override
    {
        if (!canDropMimeData(data, action, row, column, parentNodeIndex))
            return false;

        if (action == Qt::IgnoreAction)
            return true;

        int beginRow;
        if (row != -1) // 如果是成为子节点， 那么row会被设置成-1
            beginRow = row;
        else
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

private:
    void setupModelData(const QList<QStringView> &lines);
    TreeItem *getItem(const QModelIndex &index) const;

    std::unique_ptr<TreeItem> rootItem;
};
//! [2]

#endif // TREEMODEL_H
