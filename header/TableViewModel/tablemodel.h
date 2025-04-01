#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TableModel(QObject *parent = nullptr)
        : QAbstractTableModel(parent) {}

    void setCurrentUUID(const QString &uuid) {
        currentUuid = uuid;
        // propertyMap = Manager::getIns().propertyMapFor(uuid); // 拉取属性
        beginResetModel();
        endResetModel();
    }

    int rowCount(const QModelIndex &) const override {
        return propertyMap.size();
    }

    int columnCount(const QModelIndex &) const override {
        return 2; // key + value
    }

    QVariant data(const QModelIndex &index, int role) const override {
        if (role != Qt::DisplayRole && role != Qt::EditRole)
            return QVariant();

        auto it = propertyMap.begin();
        std::advance(it, index.row());
        if (index.column() == 0) return it->first;
        if (index.column() == 1) return it->second;
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if (role != Qt::DisplayRole) return QVariant();
        return (section == 0) ? "Property" : "Value";
    }

    Qt::ItemFlags flags(const QModelIndex &index) const override {
        if (index.column() == 1)
            return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    }

    bool setData(const QModelIndex &index, const QVariant &value, int role) override {
        if (role == Qt::EditRole && index.column() == 1) {
            auto it = propertyMap.begin();
            std::advance(it, index.row());
            it->second = value;

            // 写回 Manager 中的数据
            // Manager::getIns().setProperty(currentUuid, it->first, value);

            emit dataChanged(index, index);
            return true;
        }
        return false;
    }

private:
    QString currentUuid;
    std::map<QString, QVariant> propertyMap;
};


#endif // TABLEMODEL_H
