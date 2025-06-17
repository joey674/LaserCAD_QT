#ifndef MOTIONSTAGEDEVICEGOOGOL_H
#define MOTIONSTAGEDEVICEGOOGOL_H

#include "motionstagedevice.h"

#define AXIS_X  1
#define AXIS_Y  2
#define AXIS_Z  3

class MotionStageDeviceGoogol: public MotionStageDevice
{
public:
    bool connect() override;
    bool disconnect() override;
    bool setPos(double x,double y,double z) override;
};

#endif // MOTIONSTAGEDEVICEGOOGOL_H
