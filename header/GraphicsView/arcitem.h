#ifndef ARCITEM_H
#define ARCITEM_H

#include "protocol.h"
#include "graphicsitem.h"
#include "graphicsmath.h"
#include "logger.h"

class ArcItem: public GraphicsItem {
/// ********************
/// 暂存一些计算变量
/// 不属于状态，不参与实际更新
/// 只用于在绘制时提供一些绘制信息
/// ********************
public:
    /// 绘制时记录当前第几次点击
    int operateIndex = 0;
    /// 绘制时记录中间的暂存点
    QPointF assistPoint = QPointF{};
public:
    ArcItem();
    ArcItem(const ArcItem& other):
        m_vertexPair(other.m_vertexPair),
        m_offset(other.m_offset),
        m_offsetNum(other.m_offsetNum) {
        m_vertexPair[0].point = other.getVertexPos(0);
        m_vertexPair[1].point = other.getVertexPos(1);
        // 更新出来paintitem和offsetitem
        this->animate();
        // 更新出来paintitem和offsetitem
        this->animate();
    }

    std::shared_ptr < GraphicsItem > copy() const  override {
        return std::make_shared < ArcItem > (ArcItem(*this));
    }
/// ********************
/// \brief control
/// 直接修改 控制对象
/// 这里面所有函数结束都要调用animate
/// ********************
public:
    bool editVertex(const int index, const QPointF point, const double angle) override {
        if (index > 1 || angle >= 360 || angle <= -360) {
            WARN_VAR(index);
            WARN_VAR(angle);
            return false;
        }
        QPointF pos = point - this->scenePos();
        this->m_vertexPair[index] = Vertex{pos, angle};
        animate();
        return true;
    }
    bool setParallelOffset(const double offset, const double offsetNum) override {
        this->m_offset = offset;
        this->m_offsetNum = offsetNum;
        this->animate();
        return true;
    }
    bool setCenterPos(const QPointF point) override {
        DEBUG_MSG("use arc setCenterPos");
        QPointF currentCenter = this->getCenterPos();
        QPointF offset = point - currentCenter;
        this->setPos(this->pos() + offset);
        this->animate();
        return true;
    }
    bool rotate(const double angle) override { //TODO
        return true;
    }
/// ********************
/// \brief update
/// 更新函数 不能主动调用update；都在animate中调用
/// ********************
public:
    bool updateParallelOffset() override {
        // if (this->m_offset == 0) return;
        // this->m_offsetItemList.clear();
        // qDebug() << "update offset";
        // for (int offsetIndex = 1;offsetIndex <= this->m_offsetNum; offsetIndex++)
        // {
        //     cavc::Polyline<double> input;
        //     input.addVertex(
        //         this->m_vertexPair[0].point.x(),
        //         this->m_vertexPair[0].point.y(),
        //             this->m_vertexPair[1].angle
        //         );
        //     input.addVertex(
        //         this->m_vertexPair[1].point.x(),
        //         this->m_vertexPair[1].point.y(),
        //         this->m_vertexPair[0].angle
        //         );
        //     input.isClosed() = false;
        //     std::vector<cavc::Polyline<double>> results = cavc::parallelOffset(input, this->m_offset * offsetIndex);
        //     for (const auto& polyline : results) {
        //         auto item = std::make_shared<ArcItem>();
        //         item->LineType = LineType::offsetItem;
        //         for (size_t i = 0; i < 2; ++i) {
        //             auto newPoint = QPointF(polyline.vertexes()[i].x(), polyline.vertexes()[i].y());
        //             auto newangle = (i > 0) ?  polyline.vertexes()[i-1].angle()
        //                                     :   polyline.vertexes()[polyline.size()-1].angle();
        //             // qDebug() << " add vertex " << i << ":" << newPoint << newangle ;
        //             item->editVertex(i,newPoint,newangle);
        //         }
        //         this->m_offsetItemList.push_back(std::move(item));
        //     }
        // }
        return true;
    }
    bool updatePaintItem() override {
        // 这里实时把vertexlist里的点信息更新到itemlist里；然后paint函数会绘制itemlist里的东西
        this->m_paintItem = nullptr;
        auto v1 = m_vertexPair[0].point;
        auto v2 = m_vertexPair[1].point;
        double angle = m_vertexPair[1].angle;
        QPainterPath arcPath = createArcPath(v1, v2, angle);
        this->m_paintItem = std::make_shared < QGraphicsPathItem > (arcPath);
        this->m_paintItem->setPen(this->getPen());
        return true;
    }
/// ********************
/// \brief get info
/// 只获取信息
/// ********************
public:
    double getParallelOffset() const override {
        return this->m_offset;
    }
    double getParallelOffsetNum() const override {
        return this->m_offsetNum;
    }
    Vertex getVertex(const int index) const override {
        if (index > 1) {
            assert("false index:only 0,1");
        }
        return m_vertexPair[index];
    }
    QPointF getVertexPos(const int index) const override {
        if (index > 1) {
            assert("false index:only 0,1");
        }
        QPointF point = m_vertexPair[index].point;
        QPointF pos = point + this->scenePos();
        return pos;
    }
    QPointF getCenterPos() const override {
        auto center = QPointF{};
        double radius = 0;
        getCircleFromTwoPointsAndAngle(this->m_vertexPair[0].point, this->m_vertexPair[1].point, this->m_vertexPair[1].angle, center, radius);
        auto posOffset = this->pos();
        return center + posOffset;
    }
    QString getName() const override {
        return "ArcItem";
    }
/// ********************
/// \brief overload
/// 重载基于QGraphicsitem的一些性质
/// ********************
public:
    enum { Type = ItemTypeId::Arc };
    int type() const override;
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
/// ********************
/// private variable
/// ********************
private:
    ///
    std::array < Vertex, 2 > m_vertexPair = {Vertex{QPointF{0, 0}, 0}, Vertex{QPointF{0, 0}, 0}};
    std::shared_ptr < QGraphicsPathItem > m_paintItem;
    ///
    double m_offset  = 0;
    int m_offsetNum = 1;
    std::vector < std::shared_ptr < ArcItem>> m_offsetItemList;
};

#endif // ARCITEM_H
