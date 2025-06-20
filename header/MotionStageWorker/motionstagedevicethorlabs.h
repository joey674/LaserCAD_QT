#ifndef MOTIONSTAGEDEVICETHORLABS_H
#define MOTIONSTAGEDEVICETHORLABS_H

#include "motionstagedevice.h"

class MotionStageDeviceThorlabs: public MotionStageDevice
{
public:
    bool connect() override;
    bool disconnect() override;
    bool setPos(double x,double y,double z) override;
public:
    char m_serialNo[16] = "00";
};

#endif // MOTIONSTAGEDEVICETHORLABS_H
