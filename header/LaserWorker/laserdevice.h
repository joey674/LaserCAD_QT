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
    virtual bool pauseExecution() = 0;
};

#endif // LASERDEVICE_H
