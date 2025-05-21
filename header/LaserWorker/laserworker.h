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

enum class LaserWorkerState { Working, Paused, Stopped };

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
    void setState(LaserWorkerState state) { m_state.store(state); }
    void setDevice(std::unique_ptr<LaserDevice> device) {
        if (this->m_device != nullptr) {
            this->m_device->disconnectCard();
            this->m_device->unloadDLL();
        }
        this->m_device = std::move(device);
        this->m_device->loadDLL();
        this->m_device->connectCard();
    }
private:
    void threadMain();
    std::thread m_thread;
    std::once_flag m_startOnce;
    std::atomic<bool> m_workerIsRunning{false};
    ThreadSafeQueue<LaserDeviceCommand> m_commandQueue;
    std::unique_ptr<LaserDevice> m_device;
    std::atomic<LaserWorkerState> m_state{LaserWorkerState::Stopped};

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
