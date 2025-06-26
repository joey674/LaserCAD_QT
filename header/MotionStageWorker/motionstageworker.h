#ifndef MOTIONSTAGEWORKER_H
#define MOTIONSTAGEWORKER_H

#include <QList>
#include <QMutexLocker>
#include <QObject>
#include <QQueue>
#include <QWaitCondition>
#include <mutex>
#include <atomic>
#include <thread>
#include <QTimer>
#include "motionstagedevice.h"

class MotionStageWorker
{
public:
    void start();
    void stop();
public:
    void setPos(double x_mm, double y_mm, double z_mm);
    void setDevice(std::unique_ptr<MotionStageDevice> device);
    bool getDeviceConnectStatus();
    std::tuple<double, double, double> getPos();

private:
    void threadMain();
    std::thread m_thread;
    std::once_flag m_startOnce;
    std::atomic<bool> m_workerIsRunning{false};
    std::unique_ptr<MotionStageDevice> m_device = nullptr;

private:
    static MotionStageWorker ins;
    MotionStageWorker() {};
    MotionStageWorker(const MotionStageWorker &);
    ~MotionStageWorker();
    MotionStageWorker &operator=(const MotionStageWorker &);

public:
    static MotionStageWorker &getIns();
};

#endif // MOTIONSTAGEWORKER_H
