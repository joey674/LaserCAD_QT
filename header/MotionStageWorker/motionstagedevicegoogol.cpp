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
    /*ErrorCode = */GT_ClrSts(1, 8);

    //
    /*ErrorCode = */  GT_Reset();

    //
    const int axes[] = {AXIS_X, AXIS_Y, AXIS_Z};
    for (int i = 0; i < 3; ++i) {
        int axis = axes[i];

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

bool MotionStageDeviceGoogol::setPos(double x, double y, double z) {
    short ErrorCode;
    const int PULSE_PER_MM = 2000;

    long x_pulse = static_cast<long>((x) * PULSE_PER_MM);
    long y_pulse = static_cast<long>((y) * PULSE_PER_MM);
    long z_pulse = static_cast<long>((z) * PULSE_PER_MM);

    if (x_pulse != 0) {
        ErrorCode = GT_SetPos(AXIS_X, x_pulse);
        DEBUG_MSG("GT_SetPos X " + QString::number(x_pulse) + " ErrorCode:" + QString::number(ErrorCode));

        GT_SetVel(AXIS_X, 100);
        GT_Update(1 << (AXIS_X - 1));

        long sts;
        double prfPos;
        do
        {
            // 读取AXIS轴的状态
            /*ErrorCode = */GT_GetSts(AXIS_X, &sts);
            // 读取AXIS轴的规划位置
            /*ErrorCode = */GT_GetPrfPos(AXIS_X, &prfPos);
            printf("sts=0x%-10lxprfPos=%-10.1lf\r", sts, prfPos);
        }while(sts&0x400);// 等待AXIS轴规划停止
    }

    if (y_pulse != 0) {
        ErrorCode = GT_SetPos(AXIS_Y, y_pulse);
        DEBUG_MSG("GT_SetPos Y " + QString::number(y_pulse) + " ErrorCode:" + QString::number(ErrorCode));

        GT_SetVel(AXIS_Y, 100);
        GT_Update(1 << (AXIS_Y - 1));

        long sts;
        double prfPos;
        do
        {
            // 读取AXIS轴的状态
            /*ErrorCode = */GT_GetSts(AXIS_Y, &sts);
            // 读取AXIS轴的规划位置
            /*ErrorCode = */GT_GetPrfPos(AXIS_Y, &prfPos);
            printf("等待AXIS轴规划停止 sts=0x%-10lxprfPos=%-10.1lf\r", sts, prfPos);
        }while(sts&0x400);
    }

    if (z_pulse != 0) {
        ErrorCode = GT_SetPos(AXIS_Z, z_pulse);
        DEBUG_MSG("GT_SetPos Z " + QString::number(z_pulse) + " ErrorCode:" + QString::number(ErrorCode));

        GT_SetVel(AXIS_Z, 100);
        GT_Update(1 << (AXIS_Z - 1));

        long sts;
        double prfPos;
        do
        {
            // 读取AXIS轴的状态
            /*ErrorCode = */GT_GetSts(AXIS_Z, &sts);
            // 读取AXIS轴的规划位置
            /*ErrorCode = */GT_GetPrfPos(AXIS_Z, &prfPos);
            printf("等待AXIS轴规划停止 sts=0x%-10lxprfPos=%-10.1lf\r", sts, prfPos);
        }while(sts&0x400);
    }


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
