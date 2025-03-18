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

    TreeModel(const QStringList &headersGroup, const QString &data,
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
    Qt::DropActions supportedDropActions() const override;
    QStringList mimeTypes() const override;
    QMimeData *mimeData(const QModelIndexList &indexes) const override;
    bool canDropMimeData(const QMimeData *data,Qt::DropAction action, int row, int column, const QModelIndex &parent) const override;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parentNodeIndex) override;

private:
    void setupModelData(const QList<QStringView> &lines);
    TreeItem *getItem(const QModelIndex &index) const;

    std::unique_ptr<TreeItem> rootItem;
};
//! [2]

#endif // TREEMODEL_H
