#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <utility>
#include "sceneprotocol.h"
#include "uimanager.h"
#include "treemodel.h"
#include "manager.h"

class SceneManager
{
public:
    /// scene
    QGraphicsScene *scene;
    OperationEvent currentOperationEvent = None;
    /// scene scale
    std::pair<double,double> sceneScale = {1,1};
    void setSceneScale(double x, double y);
    std::pair<double, double> getSceneScale();
    /// layer
    void setCurrentLayer(int layer){
        this->currentLayer = layer;

        TreeModel *model = qobject_cast<TreeModel *>(UiManager::getIns().UI()->treeView->model());
        model->update();

        auto inLayerItems = Manager::getIns().getItems(this->currentLayer);
        auto allItems = Manager::getIns().getItems(0);
        for (const auto& item : allItems) {
            Manager::getIns().setItemSelectable(item,false);
            Manager::getIns().setItemMovable(item,false);
            Manager::getIns().setItemColor(item,DisplayColor);
        }
        for (const auto& item : inLayerItems) {
            Manager::getIns().setItemSelectable(item,true);
            Manager::getIns().setItemMovable(item,true);
        }
    };
    int getCurrentLayer(){
        return currentLayer;
    };
    int layerCount();
    /// drag scene
    QPointF dragScenePoint = QPointF(0,0);
    void dragScene(QPointF pointCoordView,  MouseEvent event);
private:
    int currentLayer = 1;
private:
    static SceneManager ins;
    SceneManager(){};
    SceneManager(const SceneManager&);
    ~SceneManager(){};
    SceneManager& operator = (const SceneManager&);
public:
    static SceneManager& getIns();
};
#endif // SCENEMANAGER_H
