#ifndef MANAGER_H
#define MANAGER_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLabel>
#include <qgraphicsitem.h>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include "laseritem.h"

class Manager
{
private:
    std::list<std::shared_ptr<LaserItem>> container;
    std::unordered_map<int,std::list<std::shared_ptr<LaserItem>>> layerMap;
    std::unordered_map<int,std::list<std::shared_ptr<LaserItem>>> groupMap;

private:
    QGraphicsScene *scene;
    static Manager ins;
private:
    Manager(){};
    Manager(const Manager&);
    ~Manager(){};
    Manager& operator = (const Manager&);
public:
    ///
    static void init(QGraphicsScene *sc);
    static Manager& getIns();
    ///
    void addItem(std::shared_ptr<LaserItem>);
    void deleteItem(QGraphicsItem *);
    ///
    const std::list<std::shared_ptr<LaserItem>>& getItems();
    const std::list<std::shared_ptr<LaserItem>>& getItemsByLayer(int);
    const std::list<std::shared_ptr<LaserItem>>& getItemsByGroup(int);
public:
    // 键盘控制变量; hold代表长按 pressed代表按下切换一次状态true到false/false到true
    bool IsControlHold = false;
    bool IsShiftHold = false;
    bool IsCapsLocked = false;
    bool IsXHold = false;
    bool IsZHold = false;
    bool IsYHold = false;
    // 鼠标状态
    bool IsMouseLeftButtonHold = false;
    bool IsMouseRightButtonHold = false;
};

#endif // MANAGER_H
