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
        if (this->m_device == nullptr) {
            continue;
        }
        LaserWorkerState state = m_state.load();
        if (state == LaserWorkerState::Working) {
            std::vector<LaserDeviceCommand> cmdList;
            LaserDeviceCommand cmd;
            while (m_commandQueue.try_pop(cmd)) {
                cmdList.push_back(std::move(cmd));
            }
            if (cmdList.empty()) {
                continue;
            }
            // 执行command; 这一步是把cmd推进rtc的list中然后直接返回;如果没推成功,说明rtcList是满的 那这里就持续等待再尝试
            while (!this->m_device->executeCommand(cmdList)) {
                WARN_MSG("cannot push command to rtc device; will try again");
                state = m_state.load();
                if (state == LaserWorkerState::Paused) {
                    this->m_device->pauseExecution();
                    break;
                }
                if (state == LaserWorkerState::Stopped) {
                    break;
                }
            }
            continue;
        }
        else if (state == LaserWorkerState::Paused) {
            this->m_device->pauseExecution();
            continue;
        }
        else if (state == LaserWorkerState::Stopped) {
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
