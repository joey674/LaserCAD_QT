#include "treenode.h"
#include "protocol.h"
#include "logger.h"

TreeNode::TreeNode(TreeNode *parent)
    : m_parentItem(parent)
{
    // this->m_propertyList.resize(3);
}

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

QVariant TreeNode::property(NodePropertyIndex index) const
{
    auto idx = static_cast<int>(index);
        // WARN_VAR(idx);
        // WARN_VAR(m_parentItem);
        // WARN_VAR(m_propertyList.size());
        // WARN_VAR(m_propertyList);
    return m_propertyList.value(idx);
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
                            std::make_unique<TreeNode>(this));
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

bool TreeNode::setProperty(NodePropertyIndex index, const QVariant &value)
{
    auto idx = static_cast<int>(index);
    if (idx> 2){
        WARN_VAR(idx);
        FATAL_MSG("exceed property size");
    }
    m_propertyList[idx] = value;
    return true;
}

bool TreeNode::setProperty(int index, const QVariant &value)
{
    if (index> 2){
        WARN_VAR(index);
        FATAL_MSG("exceed property size");
    }
    m_propertyList[index] = value;
    return true;
}

QVariantList TreeNode::propertyList() const
{
    return m_propertyList;
}

///
/// \brief TreeNode::setPropertyList 最好别用
/// \param value
/// \return
///
bool TreeNode::setPropertyList(const QVariantList &value)
{
    m_propertyList = value;

    return true;
}
