#ifndef MOTIONSTAGEDEVICETHORLABS_H
#define MOTIONSTAGEDEVICETHORLABS_H

#include "motionstagedevice.h"
#include <vector>

class MotionStageDeviceThorlabs: public MotionStageDevice
{
public:
    static std::vector<std::string> getStageList();
    bool connect() override;
    bool disconnect() override;
    bool setPos(double x,double y,double z) override;
    virtual std::tuple<double, double, double> getPos() override;
public:
    char m_serialNo[16] = "00";
};

#endif // MOTIONSTAGEDEVICETHORLABS_H
