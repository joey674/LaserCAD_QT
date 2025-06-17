#include "motionstagedevicegoogol.h"
#include "logger.h"
#include "gts.h"

bool MotionStageDeviceGoogol::connect()
{
    short ErrorCode;
    TTrapPrm trap;

    // 打开运动控制器
    ErrorCode = GT_Open();
    if (ErrorCode != 0){
        WARN_MSG("GT_Open "+QString::number (ErrorCode));
        return false;
    }

    // 清除各轴的报警和限位
    ErrorCode = GT_ClrSts(1, 8);
    DEBUG_MSG("GT_ClrSts "+QString::number (ErrorCode));

    // 设置xyz轴
    ErrorCode = GT_AxisOn(AXIS_X);
    DEBUG_MSG("GT_AxisOn "+QString::number (ErrorCode));
    ErrorCode = GT_ZeroPos(AXIS_X);
    DEBUG_MSG("GT_ZeroPos "+QString::number (ErrorCode));
    ErrorCode = GT_SetPrfPos(AXIS_X, 0);
    DEBUG_MSG("GT_SetPrfPos "+QString::number (ErrorCode));
    ErrorCode = GT_PrfTrap(AXIS_X);
    DEBUG_MSG("GT_PrfTrap "+QString::number (ErrorCode));
    ErrorCode = GT_GetTrapPrm(AXIS_X, &trap);
    DEBUG_MSG("GT_GetTrapPrm "+QString::number (ErrorCode));
    trap.acc = 0.25;
    trap.dec = 0.125;
    trap.smoothTime = 25;
    ErrorCode = GT_SetTrapPrm(AXIS_X, &trap);
    DEBUG_MSG("GT_SetTrapPrm "+QString::number (ErrorCode));

    ErrorCode = GT_AxisOn(AXIS_Y);
    DEBUG_MSG("GT_AxisOn "+QString::number (ErrorCode));
    ErrorCode = GT_ZeroPos(AXIS_Y);
    DEBUG_MSG("GT_ZeroPos "+QString::number (ErrorCode));
    ErrorCode = GT_SetPrfPos(AXIS_Y, 0);
    DEBUG_MSG("GT_SetPrfPos "+QString::number (ErrorCode));
    ErrorCode = GT_PrfTrap(AXIS_Y);
    DEBUG_MSG("GT_PrfTrap "+QString::number (ErrorCode));
    ErrorCode = GT_GetTrapPrm(AXIS_Y, &trap);
    DEBUG_MSG("GT_GetTrapPrm "+QString::number (ErrorCode));
    trap.acc = 0.25;
    trap.dec = 0.125;
    trap.smoothTime = 25;
    ErrorCode = GT_SetTrapPrm(AXIS_Y, &trap);
    DEBUG_MSG("GT_SetTrapPrm "+QString::number (ErrorCode));

    ErrorCode = GT_AxisOn(AXIS_Z);
    DEBUG_MSG("GT_AxisOn "+QString::number (ErrorCode));
    ErrorCode = GT_ZeroPos(AXIS_Z);
    DEBUG_MSG("GT_ZeroPos "+QString::number (ErrorCode));
    ErrorCode = GT_SetPrfPos(AXIS_Z, 0);
    DEBUG_MSG("GT_SetPrfPos "+QString::number (ErrorCode));
    ErrorCode = GT_PrfTrap(AXIS_Z);
    DEBUG_MSG("GT_PrfTrap "+QString::number (ErrorCode));
    ErrorCode = GT_GetTrapPrm(AXIS_Z, &trap);
    DEBUG_MSG("GT_GetTrapPrm "+QString::number (ErrorCode));
    trap.acc = 0.25;
    trap.dec = 0.125;
    trap.smoothTime = 25;
    ErrorCode = GT_SetTrapPrm(AXIS_Z, &trap);
    DEBUG_MSG("GT_SetTrapPrm "+QString::number (ErrorCode));

    INFO_MSG("motion device connect success");
    return true;
}

bool MotionStageDeviceGoogol::disconnect() {
    GT_AxisOff(AXIS_X);
    GT_AxisOff(AXIS_Y);
    GT_AxisOff(AXIS_Z);
    return true;
}

bool MotionStageDeviceGoogol::setPos(double x, double y, double z) {
    short ErrorCode;
    const int PULSE_PER_MM = 2000;

    long posX = static_cast<long>(x * PULSE_PER_MM);
    long posY = static_cast<long>(y * PULSE_PER_MM);
    long posZ = static_cast<long>(z * PULSE_PER_MM);

    // 设置目标位置
    ErrorCode = GT_SetPos(AXIS_X, posX);
    DEBUG_MSG("GT_SetPos X " + QString::number(ErrorCode));

    ErrorCode = GT_SetPos(AXIS_Y, posY);
    DEBUG_MSG("GT_SetPos Y " + QString::number(ErrorCode));

    ErrorCode = GT_SetPos(AXIS_Z, posZ);
    DEBUG_MSG("GT_SetPos Z " + QString::number(ErrorCode));

    // 设置目标速度（单位：pulse/ms）
    ErrorCode = GT_SetVel(AXIS_X, 100);
    DEBUG_MSG("GT_SetVel X " + QString::number(ErrorCode));

    ErrorCode = GT_SetVel(AXIS_Y, 100);
    DEBUG_MSG("GT_SetVel Y " + QString::number(ErrorCode));

    ErrorCode = GT_SetVel(AXIS_Z, 100);
    DEBUG_MSG("GT_SetVel Z " + QString::number(ErrorCode));

    // 同时启动 XYZ 三轴
    int mask = (1 << (AXIS_X - 1)) | (1 << (AXIS_Y - 1)) | (1 << (AXIS_Z - 1));
    ErrorCode = GT_Update(mask);
    DEBUG_MSG("GT_Update XYZ " + QString::number(ErrorCode));

    return true;
}

