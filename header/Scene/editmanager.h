#ifndef EDITMANAGER_H
#define EDITMANAGER_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <qgraphicsitem.h>
#include "polylineitem.h"
#include "arcitem.h"
#include "protocol.h"


class EditManager
{
public: // 编辑对象
    QGraphicsItem *currentEditItem = NULL;
    int currentEditPolylineVertexIndex = -1;
    void editItem(QPointF pointCoordscene,MouseEvent event);
    void editPolyline(QPointF pointCoordscene, PolylineItem *, MouseEvent event);
    void editArc(QPointF pointCoordscene, ArcItem *, MouseEvent event);

private:
    static EditManager ins;
    EditManager(){};
    EditManager(const EditManager&);
    ~EditManager(){};
    EditManager& operator = (const EditManager&);
public:
    static EditManager& getIns();
};

#endif // EDITMANAGER_H
