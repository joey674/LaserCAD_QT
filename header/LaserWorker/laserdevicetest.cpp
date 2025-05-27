#include "laserdevicetest.h"

bool LaserDeviceTest::loadDLL()
{
    return true;
}

bool LaserDeviceTest::unloadDLL()
{
    INFO_MSG("testDLL.DLL is unloaded");
    return true;
}

bool LaserDeviceTest::connectCard()
{
    INFO_MSG("connect success");
    return true;
}

bool LaserDeviceTest::disconnectCard()
{
        return true;
}


bool LaserDeviceTest::checkCard()
{
        return true;
}
