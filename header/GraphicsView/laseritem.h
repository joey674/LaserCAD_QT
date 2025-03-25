#ifndef LASERITEM_H
#define LASERITEM_H

#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <QPainter>
#include <QDebug.h>
#include <QStyleOptionGraphicsItem>
#include "graphicsviewprotocol.h"

class LaserItem: public QGraphicsItem
{
public:
    std::pair<double,double> editPointSize = std::pair<double,double>{1,1};
public:
    LaserItem();
    /// \brief control
    /// 直接修改 控制对象
    /// 这里面所有函数结束都要调用animate
    virtual void addVertex(const QPointF& point, const double& angle);
    virtual void editVertex(const int &index, const QPointF& point, const double& angle);
    virtual void deleteVetex(const int &index);
    virtual void createParallelOffset(const double& offset, const double& offsetNum) = 0;
    virtual void rotate(const double& angle) = 0;
    virtual void setColor(Qt::GlobalColor) = 0;
    /// \brief update
    /// 更新函数 不能主动调用update；都在animate中调用
    virtual void updateParallelOffset();
    virtual void updateItemList();
    virtual void animate();
    /// \brief get info
    /// 只获取信息
    virtual double getParallelOffset();
    virtual double getParallelOffsetNum();
    virtual Vertex getVertex(const int& index);
    virtual QPointF getVertexPos(const int& index);
    virtual QPointF getCenterPos();
    virtual QString getName();
    const QString& getUUID();
private:
    QString uuid;
};

#endif // LASERITEM_H
