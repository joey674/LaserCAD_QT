/*
    treeitem.cpp

    A container for items of data supplied by the simple tree model.
*/
#include "treeitem.h"


TreeItem::TreeItem(QVariantList property, TreeItem *parent)
    : m_propertyList(std::move(property)), m_parentItem(parent)
{}

TreeItem *TreeItem::child(int index)
{
    return (index >= 0 && index < childCount())
        ? m_childItems.at(index).get() : nullptr;
}

int TreeItem::childCount() const
{
    return int(m_childItems.size());
}

int TreeItem::indexInParent() const
{
    if (!m_parentItem)
        return 0;
    const auto it = std::find_if(m_parentItem->m_childItems.cbegin(), m_parentItem->m_childItems.cend(),
                                 [this](const std::unique_ptr<TreeItem> &treeItem) {
        return treeItem.get() == this;
    });

    if (it != m_parentItem->m_childItems.cend())
        return std::distance(m_parentItem->m_childItems.cbegin(), it);
    Q_ASSERT(false); // should not happen
    return -1;
}

int TreeItem::propertyCount() const
{
    return int(m_propertyList.count());
}

QVariant TreeItem::property(int index) const
{
    return m_propertyList.value(index);
}

bool TreeItem::insertChilds(int position, int count)
{
    if (position < 0 || position > qsizetype(m_childItems.size()))
        return false;

    for (int row = 0; row < count; ++row) {
        m_childItems.insert(m_childItems.cbegin() + position,
                std::make_unique<TreeItem>(QVariantList{"UndefinedName","UndefinedType","UndefinedUUID"}, this));
    }

    return true;
}

TreeItem *TreeItem::parent()
{
    return m_parentItem;
}

bool TreeItem::removeChilds(int position, int count)
{
    if (position < 0 || position + count > qsizetype(m_childItems.size()))
        return false;

    for (int row = 0; row < count; ++row)
        m_childItems.erase(m_childItems.cbegin() + position);

    return true;
}

bool TreeItem::setProperty(int dataIndex, const QVariant &value)
{
    // qDebug() << "treeItem setProperty" << dataIndex;
    // qDebug() << "treeItem setProperty" << m_propertyList.size();
    if (dataIndex < 0 || dataIndex >= m_propertyList.size())
        return false;

    m_propertyList[dataIndex] = value;
    // qDebug() << "treeItem setProperty" << m_propertyList[dataIndex];
    return true;
}

QVariantList TreeItem::propertyList() const
{
    return m_propertyList;
}

bool TreeItem::setPropertyList(const QVariantList &value)
{
    m_propertyList = value;

    return true;
}
