#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVariant>
#include <QList>
#include "protocol.h"

class TreeModel;

class TreeNode
{
    friend class TreeModel;
public:
    explicit TreeNode(TreeNode *parent = nullptr);

    TreeNode *child(int index);
    TreeNode *parent();

    int childCount() const;
    int indexInParent() const;

    int propertyCount() const;
    QVariant property(NodePropertyIndex index) const;
    QVariant property(int  index) const;// 可能越界的版本;

    QVariantList propertyList() const;
private:
    bool insertChilds(int position, int count);// 只添加新默认节点
    bool removeChilds(int position, int count);

    bool setProperty(NodePropertyIndex index, const QVariant &value);
    bool setProperty(int index, const QVariant &value);
    bool setPropertyList(const QVariantList &value);
private:
    std::vector<std::shared_ptr<TreeNode>> m_childItems;
    QVariantList m_propertyList = QVariantList{"UndefinedName","UndefinedType","UndefinedUUID"};
    TreeNode *m_parentItem;
};



#endif // TREEITEM_H
