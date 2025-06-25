#include "motionstageworker.h"
#include "logger.h"

void MotionStageWorker::start()
{
    std::call_once(m_startOnce, [this]() {
        m_workerIsRunning = true;
        m_thread = std::thread(&MotionStageWorker::threadMain, this);
        INFO_MSG("MotionStageWorker thread start");
    });
}

void MotionStageWorker::stop()
{
    if (this->m_device){
        this->m_device->disconnect ();
    }
    m_workerIsRunning = false;
}

void MotionStageWorker::setPos(double x_mm, double y_mm, double z_mm)
{
    if (!this->m_device) {
        return;
    }
    this->m_device->setPos (x_mm,y_mm,z_mm);
}

void MotionStageWorker::setDevice(std::unique_ptr<MotionStageDevice> device)
{
    if (this->m_device != nullptr) {
        this->m_device->disconnect ();
    }
    this->m_device = std::move(device);

    if (!this->m_device->connect ()) {
        WARN_MSG("fail to connect");
        this->m_device->disconnect ();
        this->m_device = nullptr;
        return;
    }

    this->setPos (0,0,0);

    INFO_MSG("set stage device success");
}

bool MotionStageWorker::getDeviceConnectStatus()
{
    if (this->m_device) {
        return true;
    } else {
        return false;
    }
}

void MotionStageWorker::threadMain()
{
}

MotionStageWorker MotionStageWorker::ins;

MotionStageWorker &MotionStageWorker::getIns()
{
    return ins;
}

MotionStageWorker::~MotionStageWorker()
{
    stop();
    if (m_thread.joinable()) {
        m_thread.join();
    }
}
