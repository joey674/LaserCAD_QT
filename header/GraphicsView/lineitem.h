#ifndef LINEITEM_H
#define LINEITEM_H

#include "protocol.h"
#include "graphicsitem.h"

class LineItem: public GraphicsItem {
public:
    LineItem();
    LineItem(const LineItem &other)
        : m_vertexPair(other.m_vertexPair)
        , m_offset(other.m_offset)
        , m_offsetNum(other.m_offsetNum) {
        m_vertexPair[0].point = other.getVertexPos(0);
        m_vertexPair[1].point = other.getVertexPos(1);
        // 更新出来paintitem和offsetitem
        this->animate();
    }
    std::shared_ptr < GraphicsItem > copy() const  override {
        return std::make_shared < LineItem > (LineItem(*this));
    }
protected:
    friend class Manager;
    friend class DrawManager;
    bool editVertex(const int index, const QPointF point, const double angle = 0) override;
    bool setParallelOffset(const double offset, const double offsetNum) override;
    bool setCenterPos(const QPointF point) override;
    bool rotate(const double angle) override;// TODO
protected:
    bool updateParallelOffset() override;// TODO
    bool updatePaintItem() override;
public:
    double getParallelOffset() const override;
    double getParallelOffsetNum() const override;
    Vertex getVertex(const int index)const override;
    QPointF getVertexPos(const int index)const override;
    QPointF getCenterPos() const override;
    QString getName() const override;
public:
    int type() const override {
        return GraphicsItemType::Line;
    }
protected:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
private:
    ///
    std::array < Vertex, 2 > m_vertexPair = {Vertex{QPointF{0, 0}, 0}, Vertex{QPointF{0, 0}, 0}};
    std::shared_ptr < QGraphicsLineItem > m_paintItem;
    ///
    double m_offset  = 0;
    int m_offsetNum = 0;
    std::vector < std::shared_ptr < LineItem>> m_offsetItemList;
};

#endif // LINEITEM_H
