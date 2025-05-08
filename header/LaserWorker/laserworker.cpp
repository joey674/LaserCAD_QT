#include "laserworker.h"
#include "logger.h"
#include <RTC5expl.h>
#include <QThread>

LaserWorker::LaserWorker() {
    // 这里的初始化只调用一次,没有重连机制
    // 包含内容有: dll, connect
    bool ErrorCode = initDLL();
    if (!ErrorCode) {
        return;
    }
}

void LaserWorker::run() {
    while (true) {
        // 断连重连机制
        mutex.lock();
        if (requestedCard == -1) {
            waitForSettingInput.wait(&mutex);
        }
        int card = requestedCard;
        mutex.unlock();
        if (connectCard()) {
        } else {
            QThread::sleep(2);
            continue;
        }
        // 连接成功后进入运行状态
        while (true) {
            //打标逻辑TODO
            // 等之后完成了再把sleep删掉
            //
            if (n_get_last_error(card)) {
                WARN_MSG("connect fail, will reconnect");
                connected = false;
                break;
            }
            QThread::msleep(500);
        }
    }
}

bool LaserWorker::connectCard() {
    set_rtc4_mode();
    if (select_rtc(requestedCard) != requestedCard) {
        return false;
    }
    if (load_program_file(0) != 0) {
        return false;
    }
    if (load_correction_file(0, 1, 2) != 0) {
        return false;
    }
    select_cor_table(1, 0);
    reset_error(-1);
    connected = true;
    return true;
}

void LaserWorker::setCard(int index) {
    QMutexLocker locker(&mutex);
    requestedCard = index;
    waitForSettingInput.wakeAll();
}

bool LaserWorker::initDLL() {
    INFO_MSG("Initializing the RTC5 DLL");
    if (RTC5open()) {
        terminateDLL();
        WARN_MSG("RTC5DLLx64.DLL not found");
    }
    // 出错了, 找具体错误原因
    if (init_rtc5_dll() != 0U) {
        UINT count = rtc5_count_cards();
        if (count > 0) {
            UINT AccError = 0U;
            for (UINT i = 0; i < count; ++i) {
                UINT err = n_get_last_error(i);
                if (err) {
                    AccError |= err;
                    WARN_MSG("card load error");
                    n_reset_error(i, err);
                }
            }
            if (AccError) {
                WARN_MSG("init dll fail");
                return false;
            }
        } else {
            WARN_MSG("can not find cards");
            return false;
        }
    }
    return true;
}

void LaserWorker::terminateDLL() {
    INFO_MSG("terminate the RTC5 DLL");
    free_rtc5_dll();
    RTC5close();
}
