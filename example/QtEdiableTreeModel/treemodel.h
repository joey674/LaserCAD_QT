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
    /// 控制节点的可操作选项;返回什么flag就说明item可以进行什么操作
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    /// 控制拖拽等操作
    Qt::DropActions supportedDropActions() const override;
    QStringList mimeTypes() const override;
    QMimeData *mimeData(const QModelIndexList &indexes) const override
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
    bool canDropMimeData(const QMimeData *data,Qt::DropAction action, int row, int column, const QModelIndex &parentNodeIndex) const override
    {
        Q_UNUSED(action);

        if (!data->hasFormat("application/vnd.text.list"))
            return false;

        if (column > 0) //只允许放在第一列(这里不知道为什么 反正会返回-1/0)
            return false;

        return true;
    }
    /*bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parentNodeIndex) override
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

        // 先插入节点;然后设置节点属性
        insertRows(beginRow, rows, parentNodeIndex);
        for (const QString &line : std::as_const(newItems)) {
            QModelIndex idx = this->index(beginRow, 0, parentNodeIndex);

            auto item = this->getItem(idx);
            QStringList itemList = line.split('|', Qt::SkipEmptyParts);
            qDebug() << "receive" << itemList;

            for (int i=0;i< item->propertyCount();i++){
                item->setProperty(i,itemList[i+1]);
            }

            beginRow++;
        }

        return true;
    }*/
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parentNodeIndex) override
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

        QVector<QPair<TreeItem*, QModelIndex>> parentStack;
        parentStack.push_back(qMakePair(getItem(parentNodeIndex), parentNodeIndex));

        for (const QString &line : std::as_const(newItems)) {
            // 解析层级和节点属性
            QStringList itemList = line.split('|', Qt::SkipEmptyParts);
            int level = itemList[0].toInt();
            itemList.pop_front();

            qDebug() << "Level:" << level << "ItemList:" << itemList;

            while (parentStack.size() > level + 1) {
                parentStack.pop_back();
            }

            TreeItem *parentItem = parentStack.last().first;
            QModelIndex parentIndex = parentStack.last().second;

            int childIndex = parentItem->childCount();
            insertRows(childIndex, 1, parentIndex);

            QModelIndex newIdx = this->index(childIndex, 0, parentIndex);
            TreeItem *item = this->getItem(newIdx);

            for (int i = 0; i < item->propertyCount(); i++) {
                if (i < itemList.size()) {
                    item->setProperty(i, itemList[i]);
                }
            }

            parentStack.push_back(qMakePair(item, newIdx));
            beginRow++;
        }


        return true;
    }
public:
        TreeItem *getItem(const QModelIndex &index) const;

private:
    void setupExemplarModelData();
    void setupModelData(const QList<QStringView> &lines);
    void serializeNodeToStream(TreeItem *item, QDataStream &stream,int currentLevel) const
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

    std::unique_ptr<TreeItem> m_rootItem;// 整个model的信息都存在rootItem里; 现在暂时存了model名字
};

#endif // TREEMODEL_H
