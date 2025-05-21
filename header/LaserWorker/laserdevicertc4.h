#ifndef LASERDEVICERTC4_H
#define LASERDEVICERTC4_H
#include "laserdevice.h"

class LaserDeviceRTC4: public LaserDevice
    {
    public:
        bool loadDLL() override;
        bool unloadDLL() override;
        bool connectCard() override;
        bool disconnectCard() override;
        bool checkCard() override;
        bool executeCommand(const LaserDeviceCommand &cmd) override;
        bool pauseExecution() override;
    };

#endif // LASERDEVICERTC4_H
