#ifndef LASERDEVICE_H
#define LASERDEVICE_H
#include "laserdeviceprotocol.h"

class LaserDevice {
public:
    virtual ~LaserDevice() = default;
    virtual bool loadDLL() = 0;
    virtual bool unloadDLL() = 0;
    virtual bool connectCard() = 0;
    virtual bool checkCard() = 0;
    virtual bool disconnectCard() = 0;
    virtual bool executeCommand(const std::vector<LaserDeviceCommand> &cmdList) { return true;};
    // 执行不需要额外写操作, 因为只要是working就会一直从worker缓冲队列里提命令执行
    virtual void resumeExecution() {};// 继续执行rtc列表
    virtual void pauseExecution() {}; // 暂停rtc列表
    virtual void abortExecution() {};// 清空rtc列表
    virtual void getListStatus(){};//
};

#endif // LASERDEVICE_H
