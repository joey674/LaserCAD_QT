#ifndef MOTIONSTAGEDEVICETEST_H
#define MOTIONSTAGEDEVICETEST_H

#include "motionstagedevice.h"

class MotionStageDeviceTest: public MotionStageDevice
{
public:
    bool connect() override;
    bool disconnect() override;
    bool setPos(double x,double y,double z) override;
};

#endif // MOTIONSTAGEDEVICETEST_H
