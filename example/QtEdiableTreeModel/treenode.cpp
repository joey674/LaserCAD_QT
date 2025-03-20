#include "treenode.h"


TreeNode::TreeNode(QVariantList property, TreeNode *parent)
    : m_propertyList(std::move(property)), m_parentItem(parent)
{}

TreeNode *TreeNode::child(int index)
{
    return (index >= 0 && index < childCount())
        ? m_childItems.at(index).get() : nullptr;
}

int TreeNode::childCount() const
{
    return int(m_childItems.size());
}

int TreeNode::indexInParent() const
{
    if (!m_parentItem)
        return 0;
    const auto it = std::find_if(m_parentItem->m_childItems.cbegin(), m_parentItem->m_childItems.cend(),
                                 [this](const std::unique_ptr<TreeNode> &treeItem) {
        return treeItem.get() == this;
    });

    if (it != m_parentItem->m_childItems.cend())
        return std::distance(m_parentItem->m_childItems.cbegin(), it);
    Q_ASSERT(false); // should not happen
    return -1;
}

int TreeNode::propertyCount() const
{
    return int(m_propertyList.count());
}

QVariant TreeNode::property(int index) const
{
    return m_propertyList.value(index);
}

bool TreeNode::insertChilds(int position, int count)
{
    if (position < 0 || position > qsizetype(m_childItems.size()))
        return false;

    for (int row = 0; row < count; ++row) {
        m_childItems.insert(m_childItems.cbegin() + position,
                std::make_unique<TreeNode>(DefaultNodeProperty, this));
    }
    return true;
}

TreeNode *TreeNode::parent()
{
    return m_parentItem;
}

bool TreeNode::removeChilds(int position, int count)
{
    if (position < 0 || position + count > qsizetype(m_childItems.size()))
        return false;

    for (int row = 0; row < count; ++row)
        m_childItems.erase(m_childItems.cbegin() + position);

    return true;
}

bool TreeNode::setProperty(int dataIndex, const QVariant &value)
{
    if (dataIndex < 0 || dataIndex >= m_propertyList.size())
        return false;

    m_propertyList[dataIndex] = value;
    return true;
}

QVariantList TreeNode::propertyList() const
{
    return m_propertyList;
}

bool TreeNode::setPropertyList(const QVariantList &value)
{
    m_propertyList = value;

    return true;
}
