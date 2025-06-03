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
    bool executeCommandList(const std::vector<LaserDeviceCommand> &cmdList) override;
    void resumeExecution() override;
    void pauseExecution() override;
    void abortExecution() override;
    bool getListStatus() override;
};

#endif // LASERDEVICETEST_H
