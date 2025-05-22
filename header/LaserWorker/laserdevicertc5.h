#ifndef LASERDEVICERTC5_H
#define LASERDEVICERTC5_H

#include "laserdevice.h"

class LaserDeviceRTC5: public LaserDevice
{
public:
    bool loadDLL() override;
    bool unloadDLL() override;
    bool connectCard() override;
    bool disconnectCard() override;
    bool checkCard() override;
    bool executeCommand(const LaserDeviceCommand &cmd) override;
    bool pauseExecution() override;
public:
    char* m_correctionFile;
    char* m_programFile = 0;
    unsigned int m_laserMode;
};

#endif // LASERDEVICERTC5_H
