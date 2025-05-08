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
    LaserWorker();

public slots:
    void run();
    void setCard(int index);

private:
    // 初始化dll并尝试找卡
    bool initDLL();
    bool connectCard();
    void reconnectIfNeeded();
    void terminateDLL();

    QMutex mutex;
    QWaitCondition waitForSettingInput;

    // card
    int requestedCard = -1;
    //
    bool connected = false;
    bool needReconnect = false;
};

#endif // LASERWORKER_H
