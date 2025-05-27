#include "hardwarecontroller.h"

HardwareController HardwareController::ins;
HardwareController &HardwareController::getIns() {
    return ins;
}

