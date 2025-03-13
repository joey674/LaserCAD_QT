#ifndef TREE_H
#define TREE_H

#include <QVariant>
#include <QList>

class TreeNode
{
public:
    explicit TreeNode(QVariantList data, TreeNode *parentItem = nullptr);

    void appendChild(std::unique_ptr<TreeNode> &&child);

    TreeNode *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TreeNode *parentItem();

private:
    std::vector<std::unique_ptr<TreeNode>> m_childItems;
    QVariantList m_itemData;
    TreeNode *m_parentItem;
};

#endif // TREE_H
