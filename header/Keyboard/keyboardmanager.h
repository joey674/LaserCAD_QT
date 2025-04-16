#ifndef KEYBOARDMANAGER_H
#define KEYBOARDMANAGER_H

#include <QKeyEvent>
#include "scenemanager.h"
#include "uimanager.h"
#include "logger.h"

class KeyboardManager {
public:// 键盘控制变量; hold代表长按 pressed代表按下切换一次状态true到false/false到true
    bool IsControlHold = false;
    bool IsShiftHold = false;
    bool IsCapsLocked = false;
    bool IsXHold = false;
    bool IsZHold = false;
    bool IsYHold = false;
    // 鼠标状态
    bool IsMouseLeftButtonHold = false;
    bool IsMouseRightButtonHold = false;

public:
    void  onGraphicsViewKeyPressEvent(QKeyEvent * event) {
        DEBUG_MSG("GraphicsView KeyPress");
        switch(event->key()) {
            case Qt::Key_Shift: {
                    KeyboardManager::getIns().IsShiftHold = true;
                    break;
                }
            case Qt::Key_Control: {
                    KeyboardManager::getIns().IsControlHold = true;
                    break;
                }
            case Qt::Key_X: {
                    KeyboardManager::getIns().IsXHold = true;
                    break;
                }
            case Qt::Key_Y: {
                    KeyboardManager::getIns().IsYHold = true;
                    break;
                }
            case Qt::Key_Z: {
                    KeyboardManager::getIns().IsZHold = true;
                    break;
                }
            case Qt::Key_CapsLock: {
                    KeyboardManager::getIns().IsCapsLocked = !KeyboardManager::getIns().IsCapsLocked;
                    break;
                }
            case Qt::Key_W: {
                    // ->polygonEdgeNum +=1;
                    break;
                }
            case Qt::Key_S: {
                    // if (this->polygonEdgeNum>3){
                    //     this->polygonEdgeNum -=1;
                    // }
                    // break;
                }
            case Qt::Key_A: {
                    break;
                }
            case Qt::Key_D: {
                    break;
                }
            case Qt::Key_1: {
                    break;
                }
            case Qt::Key_2: {
                    break;
                }
            case Qt::Key_3: {
                    break;
                }
            case Qt::Key_Right: {
                    auto delta = QPointF(-1, 0);
                    break;
                }
            case Qt::Key_Left: {
                    auto delta = QPointF(1, 0);
                    break;
                }
            case Qt::Key_Up: {
                    auto delta = QPointF(0, 10);
                    break;
                }
            case Qt::Key_Down: {
                    auto delta = QPointF(0, -1);
                    break;
                }
            default: {
                    break;
                }
        }
    }
    void  onGraphicsViewKeyReleaseEvent(QKeyEvent * event) {
        switch(event->key()) {
            case Qt::Key_Shift: {
                    KeyboardManager::getIns().IsShiftHold = false;
                    break;
                }
            case Qt::Key_Control: {
                    KeyboardManager::getIns().IsControlHold = false;
                    break;
                }
            case Qt::Key_X: {
                    KeyboardManager::getIns().IsXHold = false;
                    break;
                }
            case Qt::Key_Y: {
                    KeyboardManager::getIns().IsYHold = false;
                    break;
                }
            case Qt::Key_Z: {
                    KeyboardManager::getIns().IsZHold = false;
                    break;
                }
        }
    }

    void  onMainWindowKeyPressEvent(QKeyEvent * event) {
    }
    void  onMainWindowKeyReleaseEvent(QKeyEvent * event) {
    }
    void  onTreeViewKeyPressEvent(QKeyEvent * event) {
        // DEBUG_MSG("TreeView KeyPress");
        switch(event->key()) {
            case Qt::Key_Control: {
                    KeyboardManager::getIns().IsControlHold = true;
                    break;
                }
            default: {
                    break;
                }
        }
    }
    void  onTreeViewKeyReleaseEvent(QKeyEvent * event) {
        switch(event->key()) {
            case Qt::Key_Control: {
                    KeyboardManager::getIns().IsControlHold = false;
                    break;
                }
            default: {
                    break;
                }
        }
    }

private:
    static KeyboardManager ins;
    KeyboardManager() {};
    KeyboardManager(const KeyboardManager &);
    ~KeyboardManager() {};
    KeyboardManager &operator = (const KeyboardManager &);
public:
    static KeyboardManager &getIns();
};


#endif // KEYBOARDMANAGER_H
