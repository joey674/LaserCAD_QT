#include "hardwarecontroller.h"
#include "scenecontroller.h"
#include "uimanager.h"
#include "treemodel.h"

HardwareController HardwareController::ins;

void HardwareController::setOperationTime(int num)
{
    this->m_operationTime = num;
}

void HardwareController::markCurrentLayer()
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
    LaserWorker::getIns().setDeviceWorking();
}

HardwareController &HardwareController::getIns()
{
    return ins;
}
