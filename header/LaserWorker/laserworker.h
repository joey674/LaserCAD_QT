#ifndef LASERWORKER_H
#define LASERWORKER_H
#include <QList>
#include <QMutexLocker>
#include <QObject>
#include <QPoint>
#include <QQueue>
#include <QWaitCondition>
#include "laserdeviceprotocol.h"
#include "threadsafequeue.h"
#include <atomic>
#include <thread>
#include "laserdevice.h"

enum class DeviceState {Working,Paused,Free};

class LaserWorker
{
public:
    void startLaserWorker();
    void stopLaserWorker();
    void enqueueCommand(const LaserDeviceCommand &cmd) { this->m_commandQueue.push(cmd); }
    void enqueueCommand(const std::vector<LaserDeviceCommand> &cmdList)
    {
        this->m_commandQueue.push(cmdList);
    }
    void setDevice(std::unique_ptr<LaserDevice> device) {
        if (this->m_device != nullptr) {
            this->m_device->disconnectCard();
            this->m_device->unloadDLL();
        }
        this->m_device = std::move(device);

        if (! this->m_device->loadDLL()) {
            WARN_MSG("fail to load dll");
            this->m_device = nullptr;
            return;
        }
        if (! this->m_device->connectCard()) {
            WARN_MSG("fail to connect card");
            this->m_device = nullptr;
            return;
        }

        INFO_MSG("set device success");
    }
    /// \brief setDeviceWorking
    /// 这三个函数是在主线程调用 随时更改device的状态
    void setDeviceWorking() {
        DeviceState prev = m_deviceState.load();
        if (prev == DeviceState::Free) {
            DEBUG_MSG("Device: Free → Working (start)");
            m_deviceState = DeviceState::Working;
        } else if (prev == DeviceState::Paused) {
            DEBUG_MSG("Device: Paused → Working (resume)");
            m_deviceState = DeviceState::Working;
            m_device->resumeExecution();
        } else {
            DEBUG_MSG("Device: Already Working, no action");
        }
    }
    void setDevicePaused() {
        if (m_deviceState == DeviceState::Working) {
            DEBUG_MSG("Device: Working → Paused (pause)");
            m_deviceState = DeviceState::Paused;
            m_device->pauseExecution();
        } else {
            DEBUG_MSG("Pause ignored: not in Working state");
        }
    }
    void setDeviceAbort() {
        DeviceState prev = m_deviceState.exchange(DeviceState::Free);
        if (prev == DeviceState::Working || prev == DeviceState::Paused) {
            DEBUG_MSG("Device: " + QString::fromStdString(
                          (prev == DeviceState::Working ? "Working" : "Paused")) + " → Free (abort)");
            m_device->abortExecution();
        } else {
            DEBUG_MSG("Abort ignored: already Free");
        }
    }

    DeviceState getDeviceState () {
        return this->m_deviceState.load ();
    }

private:
    void threadMain();
    std::thread m_thread;
    std::once_flag m_startOnce;
    std::atomic<bool> m_workerIsRunning{false};
    ThreadSafeQueue<LaserDeviceCommand> m_commandQueue;
    std::unique_ptr<LaserDevice> m_device = nullptr;
    std::atomic<DeviceState> m_deviceState{DeviceState::Free};

private:
    static LaserWorker ins;
    LaserWorker() {};
    LaserWorker(const LaserWorker &);
    ~LaserWorker();
    LaserWorker &operator=(const LaserWorker &);

public:
    static LaserWorker &getIns();
};

#endif // LASERWORKER_H
