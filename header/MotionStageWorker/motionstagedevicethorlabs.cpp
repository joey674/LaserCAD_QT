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

    // 记录成当前轴位置
    int pos_device;
    double pos_realworld;
    ISC_ClearMessageQueue(m_serialNo);
    pos_device = ISC_GetPosition(m_serialNo);
    ISC_GetRealValueFromDeviceUnit(m_serialNo, pos_device, &pos_realworld, 0);
    this->m_z = pos_realworld;

    // 设置limit
    this->m_maxZ = 45;
    this->m_minZ = 0;

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
    (void)x; (void)y;

    if (z>this->m_maxZ || z< this->m_minZ){
        WARN_MSG("exceed limit; will ignore the operation");
        return false;
    }

    int pos_device = 0;
    int pos_realworld = z;
    if (ISC_GetDeviceUnitFromRealValue(m_serialNo, pos_realworld, &pos_device, 0) != 0)
        return false;

    if (ISC_SetMoveAbsolutePosition(m_serialNo, pos_device) != 0)
        return false;

    if (ISC_MoveAbsolute(m_serialNo) != 0)
        return false;

    while (true) {
        ISC_RequestPosition(m_serialNo);
        int pos_device_cur = ISC_GetPosition(m_serialNo);
        if (pos_device_cur == pos_device) break;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    this->m_z = z;
    INFO_MSG("motion stage of Thorlabs: set pos");
    return true;
}

std::tuple<double, double, double> MotionStageDeviceThorlabs::getPos()
{
    return std::make_tuple(m_x, m_y, m_z);
}
