#ifndef MANAGER_H
#define MANAGER_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLabel>
#include <qgraphicsitem.h>
#include <vector>
#include <memory>

class Manager
{
private:
    std::vector<std::shared_ptr<QGraphicsItem>> container;
    std::vector<std::weak_ptr<QGraphicsItem>> container2;
    std::vector<std::weak_ptr<QGraphicsItem>> container3;
private:
    QGraphicsScene *scene;
    static Manager ins;
private:
    Manager(){};
    Manager(const Manager&);
    ~Manager(){};
    Manager& operator = (const Manager&);

public:
    static void init(QGraphicsScene *sc)
    {
        ins.scene = sc;
    }
    static Manager& getIns()
    {
        return ins;
    }
    void addItem(QGraphicsItem *);
    void deleteItem(QGraphicsItem *);
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
