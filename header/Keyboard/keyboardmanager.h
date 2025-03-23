#ifndef KEYBOARDMANAGER_H
#define KEYBOARDMANAGER_H

class KeyboardManager
{
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


private:
    static KeyboardManager ins;
    KeyboardManager(){};
    KeyboardManager(const KeyboardManager&);
    ~KeyboardManager(){};
    KeyboardManager& operator = (const KeyboardManager&);
public:
    static KeyboardManager& getIns();
};


#endif // KEYBOARDMANAGER_H
