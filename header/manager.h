/*
Manager用于存储与管理数据,并同步
要管理的内容有三块:
    1. ItemMap
    2. TreeViewModel中的节点
    3. Scene

除了一开始的addItem和deleteItem scene和tree可能需要分开处理,后面的都用UUID作为索引;
所有节点 包括layer group都有存itemmap和propertymap;itemmap不使用; propertymap用于存储layer/group的数据信息
*/

#ifndef MANAGER_H
#define MANAGER_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLabel>
#include <qgraphicsitem.h>
#include <memory>
#include "laseritem.h"
#include <QTreeView>
#include <vector>
#include <unordered_map>
#include "logger.h"
#include "scenemanager.h"

const std::map<QString, QVariant> DefaultPropertyMap = {
    {"Visible", QVariant(true)},
    {"Selectable", QVariant(true)},
    {"Movable",QVariant(true)},
    {"Color",QVariant("black")}
};

class Manager
{
public:
    std::unordered_map<QString,std::shared_ptr<LaserItem>> ItemMap;
    std::unordered_map<QString,std::map<QString,QVariant>> PropertyMap;
public:
    /// \brief addItem 将graphicitem添加到 1. ItemMap  2. TreeViewModel ;暂时不考虑3. Scene
    void addItem(std::shared_ptr<LaserItem> ptr);
    /// \brief addItem 将非graphicitem(包括layer node physicItem)添加到 1. ItemMap  2. TreeViewModel ;
    void addItem(QModelIndex position, QString name, QString type);
    /// \brief deleteItem 将graphicitem删除 1. ItemMap  2. TreeViewModel ; 自动包含3. Scene
    void deleteItem(QString UUID);
    /// \brief setItem property
    void setItemVisible(QString UUID,bool status)
    {
        auto propIt = PropertyMap.find(UUID);
        if (propIt == PropertyMap.end()) {
            WARN_MSG("fail to find item");
            return;
        }
        // - ItemMap
        // - PropertyMap
        PropertyMap.find(UUID)->second.find("Visible")->second = status;
        // - TreeViewModel中的节点
        // - Scene

        ItemMap.find(UUID)->second.get()->setVisible(status);
    };
    void setItemSelectable(QString UUID,bool status)
    {
        auto propIt = PropertyMap.find(UUID);
        if (propIt == PropertyMap.end()) {
            WARN_MSG("fail to find item");
            return;
        }
        // - ItemMap
        // - PropertyMap
        PropertyMap.find(UUID)->second.find("Selectable")->second = status;
        // - TreeViewModel中的节点
        // - Scene
        ItemMap.find(UUID)->second.get()->setFlag(QGraphicsItem::ItemIsSelectable, status);
    };
    void setItemMovable(QString UUID,bool status)
    {
        auto propIt = PropertyMap.find(UUID);
        if (propIt == PropertyMap.end()) {
            WARN_MSG("fail to find item");
            return;
        }
        // - ItemMap
        // - PropertyMap
        PropertyMap.find(UUID)->second.find("Movable")->second = status;
        // - TreeViewModel中的节点
        // - Scene
        ItemMap.find(UUID)->second.get()->setFlag(QGraphicsItem::ItemIsMovable, status);
    }
    void setItemColor(QString UUID,Qt::GlobalColor status)
    {
        auto propIt = PropertyMap.find(UUID);
        if (propIt == PropertyMap.end()) {
            WARN_MSG("fail to find item");
            return;
        }
        // - ItemMap
        // - PropertyMap
        QString color;
        if (status == Qt::black)
            color = "black";
        else if (status == Qt::blue)
            color = "blue";
        else if (status == Qt::red)
            color = "red";
        else if (status == Qt::green)
            color = "green";
        else
            FATAL_MSG("Unknow color");
        PropertyMap.find(UUID)->second.find("Color")->second = color;
        // - TreeViewModel中的节点
        // - Scene
        ItemMap.find(UUID)->second.get()->setColor(status);
    }

    QString getItem(QModelIndex index);
    QString getItem(QGraphicsItem* item);

    /// \brief 获得这个图层下的所有节点(包括图层节点);    layer从1开始; 如果输入0, 那么就是返回所有节点(父节点为根节点)
    std::vector<QString> getItemsByLayer(int layer);

    void setVisibleSync(){
        for (int layer = 1;layer <= SceneManager::getIns().layerCount();++layer){
            auto items = getItemsByLayer(layer);
            bool isVisible = PropertyMap.find(items[0])->second.find("Visible")->second.toBool();
            // DEBUG_VAR(layer);
            // DEBUG_VAR(isVisible);
            for (const auto& item: items){
                // DEBUG_VAR(item);
                this->setItemVisible(item,isVisible);
            }
        }
    }
private:
    static Manager ins;
    Manager(){};
    Manager(const Manager&);
    ~Manager(){};
    Manager& operator = (const Manager&);
public:
    static Manager& getIns();
};

#endif // MANAGER_H
