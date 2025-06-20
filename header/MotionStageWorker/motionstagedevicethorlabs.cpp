#include "MotionStageDeviceThorlabs.h"
#include <ThorlabsMotion.h>
#include <cstring>
#include <thread>
#include <chrono>
#include "logger.h"

bool MotionStageDeviceThorlabs::connect() {
    if (TLI_BuildDeviceList() != 0) return false;

    if (ISC_Open(m_serialNo) != 0) return false;

    if (!ISC_LoadSettings(m_serialNo)) return false;

    ISC_StartPolling(m_serialNo, 200);

    INFO_MSG("motion stage of Thorlabs  is connected");
    return true;
}

bool MotionStageDeviceThorlabs::disconnect() {
    ISC_StopPolling(m_serialNo);
    ISC_Close(m_serialNo);
    INFO_MSG("motion stage of Thorlabs  is disconnected");
    return true;
}

bool MotionStageDeviceThorlabs::setPos(double x, double y, double z) {
    (void)y; (void)z;

    int deviceUnit = 0;
    if (ISC_GetDeviceUnitFromRealValue(m_serialNo, x, &deviceUnit, 0) != 0)
        return false;

    if (ISC_SetMoveAbsolutePosition(m_serialNo, deviceUnit) != 0)
        return false;

    if (ISC_MoveAbsolute(m_serialNo) != 0)
        return false;

    while (true) {
        ISC_RequestPosition(m_serialNo);
        int cur = ISC_GetPosition(m_serialNo);
        if (cur == deviceUnit) break;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    INFO_MSG("motion stage of Thorlabs: set pos");
    return true;
}
