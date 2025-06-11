#include "hardwarecontroller.h"
#include "scenecontroller.h"
#include "uimanager.h"
#include "treemodel.h"

HardwareController HardwareController::ins;

void HardwareController::setOperationTime(int num)
{
    this->m_operationTime = num;
}

void HardwareController::prepareMarkCurrentLayer()
{
    auto layerUuid = SceneController::getIns().getCurrentLayer();
    auto treeView = UiManager::getIns().treeView;
    TreeModel *model = qobject_cast<TreeModel *>(treeView->model());
    QModelIndex layerIndex = model->getIndex(layerUuid);
    auto childNodeList = model->getAllChildNodes(layerIndex);
    // 总操作次数
    for (int i=0;i<m_operationTime;i++){
        // 把所有命令加载好; 如果不想先执行 就先不设置device为work状态就行
        for (const auto &childNode : childNodeList) {
            if (childNode->property(TreeNodePropertyIndex::Type).toString() == "Item") {
                UUID childUuid = childNode->property(TreeNodePropertyIndex::UUID).toString();
                auto commandList = ItemManager::getIns().itemMapFind(childUuid)->getLaserCommand();
                LaserWorker::getIns().enqueueCommand(commandList);
            }
        }
    }
}

void HardwareController::onMarkButtonClicked(QWidget *widget)
{
    //
    if (!LaserWorker::getIns().getDeviceConnectStatus()) {
        return;
    }
    //
    QDialog dialog(widget);
    dialog.setWindowTitle("MarkPanel");

    QPushButton *startButton = new QPushButton("start");
    QPushButton *pauseButton = new QPushButton("pause");
    QPushButton *resumeButton = new QPushButton("resume");
    QPushButton *abortButton = new QPushButton("abort");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(startButton);
    layout->addWidget(pauseButton);
    layout->addWidget(resumeButton);
    layout->addWidget(abortButton);
    dialog.setLayout(layout);

    QObject::connect(startButton, &QPushButton::clicked, &dialog, [&]() {
        if (!startButton->isEnabled())
            return;
        DEBUG_MSG("start execute LaserDeviceCommand");
        HardwareController::getIns().prepareMarkCurrentLayer();
        LaserWorker::getIns().setDeviceWorking();
        startButton->setEnabled(false);
        QTimer::singleShot(1000, startButton, [startButton]() { startButton->setEnabled(true); });
    });

    QObject::connect(pauseButton, &QPushButton::clicked, &dialog, [&]() {
        if (!pauseButton->isEnabled())
            return;
        DEBUG_MSG("pause execute LaserDeviceCommand");
        LaserWorker::getIns().setDevicePaused();
        pauseButton->setEnabled(false);
        QTimer::singleShot(1000, pauseButton, [pauseButton]() { pauseButton->setEnabled(true); });
    });

    QObject::connect(resumeButton, &QPushButton::clicked, &dialog, [&]() {
        if (!resumeButton->isEnabled())
            return;
        DEBUG_MSG("resume execute LaserDeviceCommand");
        LaserWorker::getIns().setDeviceWorking();
        resumeButton->setEnabled(false);
        QTimer::singleShot(1000, resumeButton, [resumeButton]() { resumeButton->setEnabled(true); });
    });

    QObject::connect(abortButton, &QPushButton::clicked, &dialog, [&]() {
        if (!abortButton->isEnabled())
            return;
        DEBUG_MSG("abort execute LaserDeviceCommand");
        LaserWorker::getIns().setDeviceAbort();
        abortButton->setEnabled(false);
        QTimer::singleShot(1000, abortButton, [abortButton]() { abortButton->setEnabled(true); });
    });

    // 关闭窗口时自动abort当前打印
    QObject::connect(&dialog, &QDialog::finished, &dialog, [](int) {
        DEBUG_MSG("dialog closed, auto abort");
        LaserWorker::getIns().setDeviceAbort();
    });

    dialog.exec();
}

HardwareController &HardwareController::getIns()
{
    return ins;
}
