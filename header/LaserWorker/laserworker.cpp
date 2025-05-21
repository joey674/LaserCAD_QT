#include "laserworker.h"
#include <QThread>


void LaserWorker::startLaserWorker()
{
    std::call_once(m_startOnce, [this]() {
        m_workerIsRunning = true;
        m_thread = std::thread(&LaserWorker::threadMain, this);
        INFO_MSG("laserworker thread start");
    });
}

void LaserWorker::stopLaserWorker()
{
    m_workerIsRunning = false;
    this->m_device->disconnectCard();
    this->m_device->unloadDLL();
}

///
/// \brief LaserWorker::loadDLL
///
void LaserWorker::threadMain()
{
    while (m_workerIsRunning) {
        if (this->m_device == nullptr) {  // 没设置device就空转;
            continue;
        }

        LaserWorkerState state = m_state.load();
        if (state == LaserWorkerState::Working) {
            LaserDeviceCommand cmd;
            if (m_commandQueue.try_pop(cmd)) {
                while (this->m_device->executeCommand(cmd) == false) {  // 这里返回false可能是rtc的list满了, 需要等待;
                    WARN_MSG("can not execute command; will try again");
                    if (state == LaserWorkerState::Paused) {  // 如果在等待的时候有紧急命令也可以响应
                        this->m_device->pauseExecution ();
                        break;
                    }
                    if (state == LaserWorkerState::Stopped) {
                        break;
                    }
                };
            }
            continue;
        }
        else if (state == LaserWorkerState::Paused) { // 正常打完点时出现的紧急命令响应
            this->m_device->pauseExecution ();
            continue;
        } else if (state == LaserWorkerState::Stopped) {
            continue;
        } else {
            continue;
        }
    }
}



///
/// \brief LaserWorker::ins
///
LaserWorker LaserWorker::ins;

LaserWorker &LaserWorker::getIns()
{
    return ins;
}

LaserWorker::~LaserWorker()
{
    stopLaserWorker();
    if (m_thread.joinable()) {
        m_thread.join();
    }
}
