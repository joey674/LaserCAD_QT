#ifndef HARDWARECONTROLLER_H
#define HARDWARECONTROLLER_H

#include "scenecontroller.h"
#include "uimanager.h"
#include "treemodel.h"

class HardwareController
{
public:
    void markCurrentLayer() {
        auto layerUuid = SceneController::getIns().getCurrentLayer();
        auto treeView = UiManager::getIns().treeView;
        TreeModel *model = qobject_cast<TreeModel *>(treeView->model());
        QModelIndex layerIndex = model->getIndex(layerUuid);
        auto childNodeList = model->getAllChildNodes(layerIndex);
        // 把所有命令加载好; 如果不想先执行 就先不设置device为work状态就行
        for (const auto &childNode : childNodeList) {
            if (childNode->property(TreeNodePropertyIndex::Type).toString() == "Item") {
                UUID childUuid = childNode->property(TreeNodePropertyIndex::UUID).toString();
                auto commandList = ItemManager::getIns().itemMapFind(childUuid)->getRTC5Command();
                LaserWorker::getIns().enqueueCommand(commandList);
            }
        }
        LaserWorker::getIns().setDeviceWorking();
    }

private:
    static HardwareController ins;
    HardwareController() {};
    HardwareController(const HardwareController &);
    ~HardwareController() {};
    HardwareController &operator = (const HardwareController &);
public:
    static HardwareController &getIns();
};

#endif // HARDWARECONTROLLER_H
