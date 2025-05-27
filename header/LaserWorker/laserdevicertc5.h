#ifndef LASERDEVICERTC5_H
#define LASERDEVICERTC5_H

#include "laserdevice.h"

struct RTCSettings {
    QString cardType;
    QString correctionFilePath;
    double scale;
    double scaleCorX, scaleCorY;
    double rotation;
    double offsetX, offsetY;
    QString laserMode;
    bool flipX, flipY;
};

class LaserDeviceRTC5: public LaserDevice
{
public:
    bool loadDLL() override;
    bool unloadDLL() override;
    bool connectCard() override;
    bool disconnectCard() override;
    bool checkCard() override;
    bool executeCommand(const std::vector<LaserDeviceCommand> &cmdList) override;
    bool pauseExecution() override;
public:
    RTCSettings m_settings;
};



#endif // LASERDEVICERTC5_H
