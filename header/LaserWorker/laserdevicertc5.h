#ifndef LASERDEVICERTC5_H
#define LASERDEVICERTC5_H

#include "laserdevice.h"

struct RTCSettings {
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
    void resumeExecution() override;
    void pauseExecution() override;
    void abortExecution() override;
    bool getListStatus() override;
public:
    RTCSettings m_settings;
    unsigned int m_calibrationFactor=0;
    unsigned int m_focalLength=0;
};



#endif // LASERDEVICERTC5_H
