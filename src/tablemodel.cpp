#include "tablemodel.h"



QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    if (orientation == Qt::Horizontal) {
        return (section == 0) ? "Property" : "Value";
    } else if (orientation == Qt::Vertical) {
        return QString(" %1").arg(section + 1);
    }
    return QVariant();
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const {
    if (index.column() == 1) {
        return  /*Qt::ItemIsEditable |*/ Qt::ItemIsEnabled;
    } else {
        return Qt::ItemIsEnabled;
    }
}

void TableModel::clear() {
    beginResetModel();
    m_uuid.clear();
    m_propertyList.clear();
    endResetModel();
}

void TableModel::update() {
    setCurrentDisplayItem(this->m_uuid);
    beginResetModel();
    endResetModel();
}
