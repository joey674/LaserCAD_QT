#ifndef LASERWORKER_H
#define LASERWORKER_H
#include <QObject>
#include <QMutexLocker>
#include <QWaitCondition>
#include <QQueue>
#include <QList>
#include <QPoint>

class LaserWorker : public QObject {
    Q_OBJECT

public:
    LaserWorker() {
        initRTC5();
    }

    ~LaserWorker() {
        terminateRTC5();
    }

public slots:
    void run() {
        while (true) {
            QMutexLocker locker(&queueMutex);
            if (commandQueue.isEmpty()) {
                queueNotEmpty.wait(&queueMutex);
                continue;
            }
            auto command = commandQueue.dequeue();
            locker.unlock();
            processCommand(command);
        }
    }

    void enqueueCommand(const QVector < QPoint > & figure) {
        QMutexLocker locker(&queueMutex);
        commandQueue.enqueue(figure);
        queueNotEmpty.wakeAll();
    }

private:
    QQueue < QVector < QPoint>> commandQueue;
    QMutex queueMutex;
    QWaitCondition queueNotEmpty;

    void initRTC5();

    void terminateRTC5();

    void processCommand(const QVector < QPoint > & figure) {
    }
};

#endif // LASERWORKER_H
