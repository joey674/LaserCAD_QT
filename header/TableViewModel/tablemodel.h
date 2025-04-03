#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QRegularExpression>
#include "manager.h"
#include "magic_enum.hpp"
#include "logger.h"
#include "utils.hpp"

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TableModel(QObject *parent = nullptr)
        : QAbstractTableModel(parent) {}

    void setCurrentEditItem(const QString &uuid) {
        m_uuid = uuid;
        beginResetModel();
        m_propertyList.clear();

        if (!uuid.isEmpty()) {
            const auto& map = Manager::getIns().propertyMapCopy(uuid);

            for (const auto& [key, val] : map) {
                QString keyName = QString::fromStdString(std::string(magic_enum::enum_name(key)));

                if (val.type() == QVariant::Map) {
                    QVariantMap subMap = val.toMap();
                    for (auto it = subMap.begin(); it != subMap.end(); ++it) {
                        m_propertyList.append({ keyName + "." + it.key(), it.value() });
                    }
                } else {
                    m_propertyList.append({ keyName, val });
                }
            }
        }

        endResetModel();
    }
    /// 删除当前修改对象，且更新table
    void clear();
    /// 不删除当前修改对象，只更新table
    void update();

    int rowCount(const QModelIndex &) const override {
        if (this->m_uuid.isEmpty()){
            return 0;
        }
        else{
            return m_propertyList.size();
        }
    }

    int columnCount(const QModelIndex &) const override {
        return 2; // key + value
    }

    QVariant data(const QModelIndex &index, int role) const override {
        if (role != Qt::DisplayRole && role != Qt::EditRole)
            return QVariant();

        if (index.row() < 0 || index.row() >= m_propertyList.size())
            return QVariant();

        const auto& row = m_propertyList[index.row()];

        if (index.column() == 0)
            return row.first;

        if (index.column() == 1) {
            const QVariant &value = row.second;

            if (value.canConvert<QPointF>()) {
                return parsePointFToString(value.toPointF());
            }

            return value;
        }

        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool setData(const QModelIndex &index, const QVariant &data, int role) override {
        if (role != Qt::EditRole || index.column() != 1)
            return false;

        if (index.row() < 0 || index.row() >= m_propertyList.size())
            return false;

        auto& row = m_propertyList[index.row()];
        QString key = row.first;
        QVariant value = data;

        // 解析 key（如 Position、CustomProperty.width）
        if (key == "Position") {
            value = parseStringToPointF(data.toString());
            Manager::getIns().setItemPosition(m_uuid, value.toPointF());
        }
        else if (key == "Visible") {
            Manager::getIns().setItemVisible(m_uuid, value.toBool());
        }
        // 可以继续扩展其它类型，如 Selectable、Pen 等
        // else if (key == "Selectable") { ... }

        // 更新本地值
        row.second = value;

        emit dataChanged(index, index);
        return true;
    }
private:
    QString m_uuid;
    QList<std::pair<QString, QVariant>> m_propertyList;
};

#endif // TABLEMODEL_H

