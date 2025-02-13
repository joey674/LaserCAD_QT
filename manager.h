#ifndef MANAGER_H
#define MANAGER_H

class Manager
{
public:
    static Manager& getIns()
    {
        static Manager ins;
        return ins;
    }

    // 先把键盘状态移过来
    // 键盘控制变量; hold代表长按 pressed代表按下切换一次状态true到false/false到true
    bool IsControlHold = false;
    bool IsShiftHold = false;
    bool IsCapsLocked = false;
    bool IsXHold = false;
    bool IsZHold = false;
    bool IsYHold = false;


private:
    Manager(){};
    ~Manager(){};
    Manager(const Manager&) = delete;
    Manager& operator = (const Manager&) = delete;
};

#endif // MANAGER_H
