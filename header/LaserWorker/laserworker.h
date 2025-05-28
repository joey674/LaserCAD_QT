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
#include <QTimer>
#include "laserdevice.h"

enum class DeviceStatus {Working,Paused,Free};

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
        DeviceStatus prev = m_deviceStatus.load();
        if (prev == DeviceStatus::Free) {
            DEBUG_MSG("Device: Free → Working (start)");
            m_deviceStatus = DeviceStatus::Working;
            // 设置状态为working, 主线程就会自动执行缓存指令 不需要主动触发;

            // 创建一个周期性定时器检测状态
            QTimer *timer = new QTimer();
            timer->setInterval(100);
            QObject::connect(timer, &QTimer::timeout, [this, timer]() {
                if (m_device->getListStatus() == 0) {
                    DEBUG_MSG("Device: Working → Free (finish)");
                    m_deviceStatus = DeviceStatus::Free;
                    timer->stop();
                    timer->deleteLater();
                }
            });
            timer->start();
        } else if (prev == DeviceStatus::Paused) {
            DEBUG_MSG("Device: Paused → Working (resume)");
            m_deviceStatus = DeviceStatus::Working;
            m_device->resumeExecution();
        } else {
            DEBUG_MSG("Device: Already Working, no action");
        }
    }
    void setDevicePaused() {
        if (m_deviceStatus == DeviceStatus::Working) {
            DEBUG_MSG("Device: Working → Paused (pause)");
            m_deviceStatus = DeviceStatus::Paused;
            m_device->pauseExecution();
        } else {
            DEBUG_MSG("Pause ignored: not in Working state");
        }
    }
    void setDeviceAbort() {
        DeviceStatus prev = m_deviceStatus.exchange(DeviceStatus::Free);
        if (prev == DeviceStatus::Working || prev == DeviceStatus::Paused) {
            DEBUG_MSG("Device: " + QString::fromStdString(
                          (prev == DeviceStatus::Working ? "Working" : "Paused")) + " → Free (abort)");
            m_device->abortExecution();
        } else {
            DEBUG_MSG("Abort ignored: already Free");
        }
    }

    /// \brief get
    ///
    bool getDeviceConnectStatus(){
        if (m_device){
            return true;
        } else {
            return false;
        }
    }
    DeviceStatus getDeviceStatus () {
        return this->m_deviceStatus.load ();
    }


private:
    void threadMain();
    std::thread m_thread;
    std::once_flag m_startOnce;
    std::atomic<bool> m_workerIsRunning{false};
    ThreadSafeQueue<LaserDeviceCommand> m_commandQueue;
    std::unique_ptr<LaserDevice> m_device = nullptr;
    std::atomic<DeviceStatus> m_deviceStatus{DeviceStatus::Free};

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
