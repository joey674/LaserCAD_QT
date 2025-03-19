/*
 * 这个model里,不再使用column;永远只在column第一格内;
 * node的所有column都只获得node的name
 */

#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QMimeData>
#include <QIODevice>
#include "treeitem.h"


class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    Q_DISABLE_COPY_MOVE(TreeModel)

    TreeModel(const QString &modelName, QObject *parent = nullptr);
    ~TreeModel() override;

    /// 获取/修改node名字
    QVariant data(const QModelIndex &nodeIndex, int role) const override;
    bool setData(const QModelIndex &nodeIndex, const QVariant &name,int role = Qt::EditRole) override;

    /// 获取/修改model名字
    QVariant headerData(int section, Qt::Orientation orientation,int role = Qt::DisplayRole) const override;
    bool setHeaderData(int section, Qt::Orientation orientation,const QVariant &value, int role = Qt::EditRole) override;

    /// 获取node的QModelIndex
    QModelIndex index(int row, int column,const QModelIndex &parentIndex = {}) const override;
    /// 获取node父节点的QModelIndex
    QModelIndex parent(const QModelIndex &nodeIndex) const override;
    /// 获取node的子节点个数
    int rowCount(const QModelIndex &nodeIndex = {}) const override;
    /// 只使用column0 所以返回columnCount = 1
    int columnCount(const QModelIndex &nodeIndex = QModelIndex()) const override;;

    /// 插入/删除子节点
    bool insertRows(int insertPosition, int nodeCount, const QModelIndex &nodeIndex = {}) override;
    bool removeRows(int removePosition,int nodeCount,const QModelIndex &nodeIndex = {}) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    Qt::DropActions supportedDropActions() const override;
    QStringList mimeTypes() const override;
    QMimeData *mimeData(const QModelIndexList &indexes) const override;
    bool canDropMimeData(const QMimeData *data,Qt::DropAction action, int row, int column, const QModelIndex &nodeIndex) const override;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parentNodeIndex) override;

public:
        TreeItem *getItem(const QModelIndex &index) const;

private:
    void setupExemplarModelData();
    void setupModelData(const QList<QStringView> &lines);

    std::unique_ptr<TreeItem> m_rootItem;// 整个model的信息都存在rootItem里; 现在暂时存了model名字
};

#endif // TREEMODEL_H
