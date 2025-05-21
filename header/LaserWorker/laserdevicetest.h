#ifndef LASERDEVICETEST_H
#define LASERDEVICETEST_H

#include "laserdevice.h"

class LaserDeviceTest: public LaserDevice
{
public:
    bool loadDLL() override;
    bool unloadDLL() override;
    bool connectCard() override;
    bool disconnectCard() override;
    bool checkCard() override;
    bool executeCommand(const LaserDeviceCommand& cmd) override;
    bool pauseExecution() override;
};

#endif // LASERDEVICETEST_H
