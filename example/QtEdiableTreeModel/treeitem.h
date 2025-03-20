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
    UUID = 2
};

class TreeItem
{
public:
    explicit TreeItem(QVariantList property = QVariantList{"UndefinedName","UndefinedType","UndefinedUUID"}, TreeItem *parent = nullptr);

    TreeItem *child(int index);
    TreeItem *parent();

    int childCount() const;
    bool insertChilds(int position, int count);// 只添加新默认节点
    bool removeChilds(int position, int count);
    int indexInParent() const;

    int propertyCount() const;
    QVariant property(int index) const;
    bool setProperty(int index, const QVariant &value);
    QVariantList propertyList() const{
        return m_propertyList;
    }
    bool setPropertyList(const QVariantList &value){
        m_propertyList = value;

        return true;
    }


private:
    std::vector<std::unique_ptr<TreeItem>> m_childItems;
    QVariantList m_propertyList;
    TreeItem *m_parentItem;
};



#endif // TREEITEM_H
