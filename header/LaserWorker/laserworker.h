#ifndef LASERWORKER_H
#define LASERWORKER_H
#include <QList>
#include <QMutexLocker>
#include <QObject>
#include <QPoint>
#include <QQueue>
#include <QWaitCondition>
#include <any>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

enum class LaserCommandType;
struct LaserCommand;

class LaserWorker
{
public:
    void run();
    void stop();
    void postCommand(const LaserCommand &cmd);

private:
    void threadMain();
    void handleCommand(const LaserCommand &cmd);
    void loadDLL();
    void connectCard();
    std::thread _thread;
    std::atomic<bool> _workerIsRunning{false};
    std::once_flag _startOnce;
    std::mutex _mutex;
    std::queue<LaserCommand> _commandQueue;
    std::condition_variable _cv;
    std::atomic<bool> _cardIsConnected{false};

private:
    static LaserWorker ins;
    LaserWorker() {};
    LaserWorker(const LaserWorker &);
    ~LaserWorker();
    LaserWorker &operator=(const LaserWorker &);

public:
    static LaserWorker &getIns();
};

enum class LaserCommandType {
    ConnectCard,
    SetParams,
    Execute,
    Pause,
    Resume,
    Stop,
};

struct LaserCommand
{
    LaserCommandType type;
    std::any data; // 携带参数，如 LaserParams 或点集
};

#endif // LASERWORKER_H
