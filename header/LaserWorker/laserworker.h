#ifndef LASERWORKER_H
#define LASERWORKER_H
#include <QList>
#include <QMutexLocker>
#include <QObject>
#include <QPoint>
#include <QQueue>
#include <QWaitCondition>
#include "RTC5protocol.h"
#include "threadsafequeue.h"
#include <atomic>
#include <thread>
#include <variant>

enum class UserCommandType;
struct UserCommand;
enum class RTC5State { Working, Paused, Stopped };

class LaserWorker
{
public:
    void startLaserWorker();
    void stopLaserWorker();
    void enqueueCommand(const RTC5Command &cmd) { m_RTC5CommandQueue.push(cmd); }
    void setState(RTC5State state) { m_RTC5State.store(state); }

private:
    void threadMain();
    void loadDLL();
    bool connectCard();
    bool checkCard();
    bool executeRTC5Command(const RTC5Command &cmd);
    std::thread m_thread;
    std::once_flag m_startOnce;
    std::atomic<bool> m_workerIsRunning{false};
    ThreadSafeQueue<RTC5Command> m_RTC5CommandQueue;
    std::atomic<RTC5State> m_RTC5State{RTC5State::Stopped};

private:
    static LaserWorker ins;
    LaserWorker() {};
    LaserWorker(const LaserWorker &);
    ~LaserWorker();
    LaserWorker &operator=(const LaserWorker &);

public:
    static LaserWorker &getIns();
};

enum class UserCommandType {
    // 可以延迟执行
    Void,
    SetCardParams, // 设置rtc5参数
    Execute,       // 开始执行
    Pause,         // 暂停打标
    Resume,        // 继续打标
    Terminate,     // 结束整个打标过程
};

struct UserCommand
{
    UserCommandType type;
    // data
};

#endif // LASERWORKER_H
