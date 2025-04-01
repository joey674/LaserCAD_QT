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

    void setCurrentUUID(const QString &uuid) {
        m_currentUuid = uuid;
        m_propertyMap = Manager::getIns().propertyMapFind(uuid);
        beginResetModel();
        endResetModel();
    }

    int rowCount(const QModelIndex &) const override {
        return m_propertyMap.size();
    }

    int columnCount(const QModelIndex &) const override {
        return 2; // key + value
    }

    QVariant data(const QModelIndex &index, int role) const override {
        if (role != Qt::DisplayRole && role != Qt::EditRole)
            return QVariant();

        auto it = m_propertyMap.begin();
        std::advance(it, index.row());
        if (index.column() == 0)
            return QString::fromStdString(std::string(magic_enum::enum_name(it->first)));
        if (index.column() == 1) {
            const QVariant &value = it->second;
            if (value.canConvert<QPointF>()) {
                QPointF point = value.toPointF();
                return QString("(%1, %2)").arg(point.x(), 0, 'f', 1).arg(point.y(), 0, 'f', 1);
            }
            return value;
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if (role != Qt::DisplayRole) return QVariant();
        return (section == 0) ? "Property" : "Value";
    }

    Qt::ItemFlags flags(const QModelIndex &index) const override {
        if (index.column() == 1)
            return /*Qt::ItemIsSelectable |*/ Qt::ItemIsEditable | Qt::ItemIsEnabled;
        return /*Qt::ItemIsSelectable |*/ Qt::ItemIsEnabled;
    }

    bool setData(const QModelIndex &index, const QVariant &data, int role) override {
        if (role == Qt::EditRole && index.column() == 1) {
            auto it = m_propertyMap.begin();
            std::advance(it, index.row());

            PropertyIndex key = it->first;
            QVariant value = data;

            ///
            ///  写入类型为Position
            ///
            if (key == PropertyIndex::Position) {
                // 从String转换成pointF
                QString text = value.toString();
                value = parseStringToPointF(text);

                // 记得同步更新真实属性(通过manager)
                Manager::getIns().itemMapFind(this->m_currentUuid)->setCenterPos(value.toPointF());
            }
            ///
            /// 写入类型为Visible
            ///
            else if (key == PropertyIndex::Visible) {}
            ///
            /// 写入类型为Visible
            ///
            else if (key == PropertyIndex::Visible) {}



            // 写回 Manager 中的数据
            Manager::getIns().propertyMapFind(this->m_currentUuid,key) = value;

            emit dataChanged(index, index);
            return true;
        }
        return false;
    }

private:
    QString m_currentUuid;
    std::map<PropertyIndex, QVariant> m_propertyMap;
};


#endif // TABLEMODEL_H
