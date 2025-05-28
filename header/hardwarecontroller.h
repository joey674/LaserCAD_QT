#ifndef HARDWARECONTROLLER_H
#define HARDWARECONTROLLER_H

///
/// 主要是用于切割ui和hardware操作
///

class HardwareController
{
private:
    int m_operationTime = 1;

public:
    void setOperationTime(int num);
    void markCurrentLayer();

private:
    static HardwareController ins;
    HardwareController() {};
    HardwareController(const HardwareController &);
    ~HardwareController() {};
    HardwareController &operator = (const HardwareController &);
public:
    static HardwareController &getIns();
};

#endif // HARDWARECONTROLLER_H
