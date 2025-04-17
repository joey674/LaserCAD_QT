#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QRegularExpression>
#include "manager.h"
#include "magic_enum.hpp"
#include "logger.h"
#include "utils.hpp"

class TableModel : public QAbstractTableModel {
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
                if (val.typeId() == QVariant::Map) {
                    QVariantMap subMap = val.toMap();
                    for (auto it = subMap.begin(); it != subMap.end(); ++it) {
                        m_propertyList.append({ it.key(), it.value() });
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
        if (this->m_uuid.isEmpty()) {
            return 0;
        } else {
            return m_propertyList.size();
        }
    }

    int columnCount(const QModelIndex &) const override {
        return 2; // key + value
    }

    QVariant data(const QModelIndex &index, int role) const override {
        if (role != Qt::DisplayRole && role != Qt::EditRole) {
            return QVariant();
        }
        if (index.row() < 0 || index.row() >= m_propertyList.size()) {
            return QVariant();
        }
        const auto& row = m_propertyList[index.row()];
        if (index.column() == 0) {
            return row.first;
        }
        if (index.column() == 1) {
            const QString key = row.first;
            const QVariant &value = row.second;
            ///
            ///
            if (value.canConvert < QPointF > ()) {
                return parsePointFToString(value.toPointF());
            }
            if (value.canConvert < Vertex > ()) {
                // 注意 这里显示为Scene内坐标
                if (key == "Vertex0") {
                    auto pos = Manager::getIns().itemMapFind(this->m_uuid)->getVertexPos(0);
                    auto ang = value.value < Vertex > ().angle;
                    return parseVertexToString(Vertex{pos, ang});
                } else if (key == "Vertex1") {
                    auto pos = Manager::getIns().itemMapFind(this->m_uuid)->getVertexPos(1);
                    auto ang = value.value < Vertex > ().angle;
                    return parseVertexToString(Vertex{pos, ang});
                }
            }
            ///
            ///
            return value;
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool setData(const QModelIndex &index, const QVariant &data, int role) override {
        if (role != Qt::EditRole || index.column() != 1) {
            return false;
        }
        if (index.row() < 0 || index.row() >= m_propertyList.size()) {
            return false;
        }
        auto& row = m_propertyList[index.row()];
        QString key = row.first;
        QVariant value = data;
        // 解析 key(不写的就代表不处理)
        // if (key == "Position") {
        //     value = parseStringToPointF(data.toString());
        //     Manager::getIns().setItemPosition(m_uuid, value.toPointF());
        // }
        // if (key == "Vertex0") {
        //     value.setValue(parseStringToVertex(data.toString()));
        //     // 更新自定property
        //     Manager::getIns().setItemGeometry(m_uuid, "Vertex0", value);
        //     // 还影响到了pos,所以也要更新
        //     auto pos = Manager::getIns().itemMapFind(m_uuid)->getCenterPos();
        //     Manager::getIns().propertyMapFind(m_uuid, PropertyIndex::Position) = pos;
        // } else if (key == "Vertex1") {
        //     value.setValue(parseStringToVertex(data.toString()));
        //     Manager::getIns().setItemGeometry(m_uuid, "Vertex1", value);
        //     // 还影响到了pos,所以也要更新
        //     auto pos = Manager::getIns().itemMapFind(m_uuid)->getCenterPos();
        //     Manager::getIns().propertyMapFind(m_uuid, PropertyIndex::Position) = pos;
        // }
        // // 更新本地值
        row.second = value;
        emit dataChanged(index, index);
        return true;
    }
private:
    QString m_uuid;
    QList < std::pair < QString, QVariant>> m_propertyList;
};

#endif // TABLEMODEL_H

