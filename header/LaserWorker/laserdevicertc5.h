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
    QString executeMode;
};

const unsigned int List1Size = 10000U;
const unsigned int List2Size = 10000U;// 如果使用双链表切换 就用这个

class LaserDeviceRTC5: public LaserDevice
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

    bool configList();
    bool executeCommand(const LaserDeviceCommand &cmd);//
    bool executeCommandListBySingleList(const std::vector<LaserDeviceCommand> &cmdList);
    bool executeCommandListByDoubleLists(const std::vector<LaserDeviceCommand> &cmdList);
    bool executeCommandListByCircleList(const std::vector<LaserDeviceCommand> &cmdList);
public:
    RTCSettings m_settings;
    uint32_t m_calibrationFactor=0;
    uint32_t m_focalLength=0;
};

#endif // LASERDEVICERTC5_H
