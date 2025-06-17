#include "motionstagedevicetest.h"
#include "logger.h"

bool MotionStageDeviceTest::connect()
{
    INFO_MSG("motion device connect success");
    return true;
}

bool MotionStageDeviceTest::disconnect() {
    return true;
}

bool MotionStageDeviceTest::setPos(double x, double y, double z) {
    short ErrorCode;
    const int PULSE_PER_MM = 2000;

    long posX = static_cast<long>(x * PULSE_PER_MM);
    long posY = static_cast<long>(y * PULSE_PER_MM);
    long posZ = static_cast<long>(z * PULSE_PER_MM);

    return true;
}

