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

    const int axes[] = {AXIS_X, AXIS_Y, AXIS_Z};

    for (int i = 0; i < 3; ++i) {
        int axis = axes[i];

        // 清除各轴的报警和限位
        ErrorCode = GT_ClrSts(1, 8);
        // 伺服使能
        ErrorCode = GT_AxisOn(axis);
        // 位置清零
        ErrorCode = GT_ZeroPos(axis);
        // AXIS轴规划位置清零
        ErrorCode = GT_SetPrfPos(axis, 0);
        // 将AXIS轴设为点位模式
        ErrorCode = GT_PrfTrap(axis);
        // 读取点位运动参数
        ErrorCode = GT_GetTrapPrm(axis, &trap);
        trap.acc = 0.25;
        trap.dec = 0.125;
        trap.smoothTime = 25;
        // 设置点位运动参数
        ErrorCode = GT_SetTrapPrm(axis, &trap);

        // 设置报警
        ErrorCode = GT_AlarmOn (axis);
    }

    INFO_MSG("motion device connect success");
    return true;
}

bool MotionStageDeviceGoogol::disconnect() {
    GT_AxisOff(AXIS_X);
    GT_AxisOff(AXIS_Y);
    GT_AxisOff(AXIS_Z);
    GT_Close ();
    return true;
}

// 脉冲加方向的形式;也就是说 这里的需要转换
bool MotionStageDeviceGoogol::setPos(double x, double y, double z) {
    short ErrorCode;
    const int PULSE_PER_MM = 2000;

    auto dx = x - this->m_x;
    auto dy = x - this->m_y;
    auto dz = x - this->m_z;

    long posX = static_cast<long>(dx * PULSE_PER_MM);
    long posY = static_cast<long>(dy * PULSE_PER_MM);
    long posZ = static_cast<long>(dz * PULSE_PER_MM);

    // 设置目标位置
    ErrorCode = GT_SetPos(AXIS_X, posX);
    DEBUG_MSG("GT_SetPos X " +QString::number(posX) +" ErrorCode:" + QString::number(ErrorCode));

    ErrorCode = GT_SetPos(AXIS_Y, posY);
    DEBUG_MSG("GT_SetPos Y " +QString::number(posY)+" ErrorCode:" + QString::number(ErrorCode));

    ErrorCode = GT_SetPos(AXIS_Z, posZ);
    DEBUG_MSG("GT_SetPos Z " +QString::number(posZ)+" ErrorCode:" + QString::number(ErrorCode));

    // 设置目标速度（单位：pulse/ms）
    ErrorCode = GT_SetVel(AXIS_X, 100);
    // DEBUG_MSG("GT_SetVel X " + QString::number(ErrorCode));

    ErrorCode = GT_SetVel(AXIS_Y, 100);
    // DEBUG_MSG("GT_SetVel Y " + QString::number(ErrorCode));

    ErrorCode = GT_SetVel(AXIS_Z, 100);
    // DEBUG_MSG("GT_SetVel Z " + QString::number(ErrorCode));

    // 同时启动 XYZ 三轴
    int mask = (1 << (AXIS_X - 1)) | (1 << (AXIS_Y - 1)) | (1 << (AXIS_Z - 1));
    ErrorCode = GT_Update(mask);
    // DEBUG_MSG("GT_Update XYZ  ErrorCode:" + QString::number(ErrorCode));

    // 检查状态
    this->checkStatus ();

    this->m_x = x;
    this->m_y = y;
    this->m_z = z;
    return true;
}

bool MotionStageDeviceGoogol::resetPos() {
    // auto ErrorCode = GT_Reset();
    //  DEBUG_MSG("GT_Reset  ErrorCode:" + QString::number(ErrorCode));
    return true;
}

bool MotionStageDeviceGoogol::checkStatus() {
    const int axes[] = {AXIS_X, AXIS_Y, AXIS_Z};

    for (int i = 0; i < 3; ++i) {
        int axis = axes[i];
        long lAxisStatus = 0;
        auto errorCode = GT_GetSts(axis, &lAxisStatus);
        DEBUG_MSG(QString("GT_GetSts axis %1 -> code %2").arg(axis).arg(errorCode));

        if (lAxisStatus & 0x2) {
            printf("轴 %d: 伺服报警\n", axis);
            return false;
        }
        if (lAxisStatus & 0x10) {
            printf("轴 %d: 跟随误差越限\n", axis);
            return false;
        }
        if (lAxisStatus & 0x20) {
            printf("轴 %d: 正限位触发\n", axis);
            return false;
        }
        if (lAxisStatus & 0x40) {
            printf("轴 %d: 负限位触发\n", axis);
            return false;
        }
        if (lAxisStatus & 0x100) {
            printf("轴 %d: 急停触发\n", axis);
            return false;
        }
        if (!(lAxisStatus & 0x200)) {
            printf("轴 %d: 伺服未使能\n", axis);
            return false;
        }

        // 非致命状态，仅提示
        if (lAxisStatus & 0x80)
            printf("轴 %d: 平滑停止触发\n", axis);
        else
            printf("轴 %d: 平滑停止未触发\n", axis);

        if (lAxisStatus & 0x400)
            printf("轴 %d: 正在运动\n", axis);
        else
            printf("轴 %d: 已停止\n", axis);

        GT_ClrSts(axis);
    }

    printf("所有轴状态正常\n");
    return true;
}
