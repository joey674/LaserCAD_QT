#ifndef LASERITEM_H
#define LASERITEM_H

#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <QPainter>
#include <QDebug.h>
#include <QStyleOptionGraphicsItem>
#include "protocol.h"

class LaserItem: public QGraphicsItem
{
public:
    std::pair<double,double> editPointSize = std::pair<double,double>{1,1};
public:
    LaserItem();
    /// \brief control
    /// 直接修改 控制对象
    /// 这里面所有函数结束都要调用animate
    virtual void createParallelOffset(const double& offset, const double& offsetNum) = 0;
    virtual void rotate(const double& angle) = 0;
    void setColor(Qt::GlobalColor setColor){
        this->color = setColor;
        this->animate();
    }
    /// \brief update
    /// 更新函数 不能主动调用update；都在animate中调用
    virtual void updateParallelOffset() = 0;
    virtual void updatePaintItem() = 0;
    virtual void animate() = 0;
    /// \brief get info
    /// 只获取信息
    virtual double getParallelOffset() = 0;
    virtual double getParallelOffsetNum() = 0;
    virtual Vertex getVertex(const int& index) = 0;
    virtual QPointF getVertexPos(const int& index) = 0;
    virtual QPointF getCenterPos() = 0;
    virtual QString getName()
    {
        return "LaserItem";
    }
    const QString getUUID()
    {
        return this->uuid;
    }
    const Qt::GlobalColor getColor(){
        return this->color;
    };
private:
    QString uuid;
    Qt::GlobalColor color = DisplayColor;
};

#endif // LASERITEM_H
