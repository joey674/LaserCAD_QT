#include "treenode.h"

TreeNode::TreeNode(QVariantList data, TreeNode *parent)
    : m_itemData(std::move(data)), m_parentItem(parent)
{}

void TreeNode::appendChild(std::unique_ptr<TreeNode> &&child)
{
    m_childItems.push_back(std::move(child));
}

TreeNode *TreeNode::child(int row)
{
    return row >= 0 && row < childCount() ? m_childItems.at(row).get() : nullptr;
}

int TreeNode::childCount() const
{
    return int(m_childItems.size());
}

int TreeNode::columnCount() const
{
    return int(m_itemData.count());
}

QVariant TreeNode::data(int column) const
{
    return m_itemData.value(column);
}

TreeNode *TreeNode::parentItem()
{
    return m_parentItem;
}

int TreeNode::row() const
{
    if (m_parentItem == nullptr)
        return 0;
    const auto it = std::find_if(m_parentItem->m_childItems.cbegin(), m_parentItem->m_childItems.cend(),
                                 [this](const std::unique_ptr<TreeNode> &TreeNode) {
                                     return TreeNode.get() == this;
                                 });

    if (it != m_parentItem->m_childItems.cend())
        return std::distance(m_parentItem->m_childItems.cbegin(), it);
    Q_ASSERT(false); // should not happen
    return -1;
}
