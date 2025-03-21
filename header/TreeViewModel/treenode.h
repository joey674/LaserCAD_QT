// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVariant>
#include <QList>

enum NodePropertyIndex: int
{
    Name = 0,
    Type = 1,
    UUID = 2,// 可能不用
    GraphicsViewItem = 3
};

static const QVariantList DefaultNodeProperty = QVariantList{"UndefinedName","UndefinedType","UndefinedUUID","UndefinedGraphicsViewItem"};

class TreeViewModel;

class TreeNode
{
    friend class TreeViewModel;
public:
    explicit TreeNode(QVariantList property = DefaultNodeProperty, TreeNode *parent = nullptr);

    TreeNode *child(int index);
    TreeNode *parent();

    int childCount() const;
    int indexInParent() const;

    int propertyCount() const;
    QVariant property(int index) const;

    QVariantList propertyList() const;
private:
    bool insertChilds(int position, int count);// 只添加新默认节点
    bool removeChilds(int position, int count);

    bool setProperty(int index, const QVariant &value);
    bool setPropertyList(const QVariantList &value);
private:
    std::vector<std::unique_ptr<TreeNode>> m_childItems;
    QVariantList m_propertyList;
    TreeNode *m_parentItem;
};



#endif // TREEITEM_H
