#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QRegularExpression>
#include "itemmanager.h"
#include "logger.h"
#include "utils.hpp"

class TableModel : public QAbstractTableModel {
    Q_OBJECT
public:
    explicit TableModel(QObject *parent = nullptr)
        : QAbstractTableModel(parent) {}

    void setCurrentDisplayItem(const QString &uuid) {
        beginResetModel();
        this->m_propertyList.clear();
        if (uuid.isEmpty()) {
            endResetModel();
            return;
        }
        this->m_uuid = uuid;
        // 几何属性
        auto item = ItemManager::getIns().itemMapFind(this->m_uuid);
        m_propertyList.append({"Position", item->getCenterInScene()});
        // ContourFillParams

        // MarkParams
        const MarkParams& mark = item->getMarkParams();
        m_propertyList.append({ "MarkParams: markSpeed", mark.markSpeed });
        m_propertyList.append({ "MarkParams: jumpSpeed", mark.jumpSpeed });
        m_propertyList.append({ "MarkParams: frequency", mark.frequency });
        m_propertyList.append({ "MarkParams: operateTime", mark.operateTime });
        m_propertyList.append({ "MarkParams: power", mark.power });
        m_propertyList.append({ "MarkParams: pulseLength", mark.pulseLength });
        m_propertyList.append({ "MarkParams: wobelAml", mark.wobelAml });
        m_propertyList.append({ "MarkParams: wobelFreq", mark.wobelFreq });
        // DelayParams
        const DelayParams& delay = item->getDelayParams();
        m_propertyList.append({ "DelayParams: laserOnDelay", delay.laserOnDelay });
        m_propertyList.append({ "DelayParams: laserOffDelay", delay.laserOffDelay });
        m_propertyList.append({ "DelayParams: markDelay", delay.markDelay });
        m_propertyList.append({ "DelayParams: jumpDelay", delay.jumpDelay });
        m_propertyList.append({ "DelayParams: polygonDelay", delay.polygonDelay });
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
                if (key == "Vertex0") {
                    auto pos = ItemManager::getIns().itemMapFind(this->m_uuid)->getVertexInScene(0).point;
                    auto ang = value.value < Vertex > ().angle;
                    return parseVertexToString(Vertex{pos, ang});
                } else if (key == "Vertex1") {
                    auto pos = ItemManager::getIns().itemMapFind(this->m_uuid)->getVertexInScene(1).point;
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

