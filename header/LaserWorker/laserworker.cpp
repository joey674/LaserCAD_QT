#include "laserworker.h"
#include "logger.h"
#include <RTC5expl.h>

void LaserWorker::initRTC5() {
    INFO_MSG("Initializing the RTC5 DLL");
    if (RTC5open()) {
        terminateRTC5();
        FATAL_MSG("Error: RTC5DLL.DLL not found\n");
    }
    UINT errorCode;
    errorCode = init_rtc5_dll();
    DEBUG_VAR(errorCode);
}

void LaserWorker::terminateRTC5() {
    INFO_MSG("terminate the RTC5 DLL");
    free_rtc5_dll();
    RTC5close();
}
