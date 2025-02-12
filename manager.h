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

    先把键盘状态移过来
private:
    Manager(){};
    ~Manager(){};
    Manager(const Manager&) = delete;
    Manager& operator = (const Manager&) = delete;
};

#endif // MANAGER_H
