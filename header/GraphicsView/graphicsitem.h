#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H

#include <QDebug.h>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include "protocol.h"
#include "utils.hpp"
#include <polylineoffset.hpp>
#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <QJsonObject>

class GraphicsItem : public QGraphicsItem {
    // Q_OBJECT
public:
    GraphicsItem() {
        this->m_uuid = GenerateUUID();
        this->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    };
    GraphicsItem(const GraphicsItem &) = delete;
    GraphicsItem &operator=(const GraphicsItem &) = delete;
    //
    void cloneBaseParams(const GraphicsItem &other) {
        // 拷贝基础字段;  不可以拷贝copyparams/offsetparams; 如果有需要再说
        this->m_uuid = GenerateUUID();
        this->m_color = other.getColor();
        this->setFlags(other.flags());
        this->m_markParams = other.m_markParams;
        this->m_delayParams = other.m_delayParams;
    }
    virtual std::shared_ptr < GraphicsItem > clone() const = 0;
    //
    void cloneBaseParamsFromJson(const QJsonObject &obj);
    QJsonObject saveBaseParamsToJson() const;

    virtual std::shared_ptr < GraphicsItem > createFromJson(QJsonObject) {
        WARN_MSG("undefined");
    };
    virtual QJsonObject saveToJson() const {
        WARN_MSG("undefined");
    };
/// ********************
/// \brief control
/// 直接修改 控制对象
/// 这里面所有函数结束都要调用animate
/// 这里存的vertex以及获得的pos都是真实scene位置; 都已经经过变换, 不用再考虑锚点
/// ********************
public:
    /// \brief setVertexInScene
    /// \param point 这里输入的是scene真实位置；不考虑锚点位置;禁止直接修改vertex
    virtual bool setVertexInScene(const int index, const Vertex vertex) = 0;
    /// \brief setCenterInScene
    /// \param point 这里输入的是scene真实位置；不考虑锚点位置;禁止直接修改vertex
    virtual bool setCenterInScene(const QPointF point) = 0;
    /// \brief setOffsetItem
    /// \param offset
    virtual bool setOffsetItem(OffsetParams params) {
        this->m_offsetParams = params;
        this->animate();
        return true;
    }
    /// \brief setCopiedItem
    /// \param items
    bool setCopiedItem(VectorCopyParams params) {
        this->m_vectorCopyParams = params;
        this->m_matrixCopyParams.setEmpty();
        this->animate();
        return true;
    };
    bool setCopiedItem(MatrixCopyParams params) {
        this->m_matrixCopyParams = params;
        this->m_vectorCopyParams.setEmpty();
        this->animate();
        return true;
    };
    /// \brief rotate
    /// \param angle
    virtual bool rotate(const double angle) = 0;
    virtual std::vector < std::shared_ptr < GraphicsItem>> breakCopiedItem() = 0;
    virtual std::vector < std::shared_ptr < GraphicsItem>> breakOffsetItem() = 0;
    /// \brief setPen
    /// \param
    bool setColor(QColor color) {
        this->m_color = color;
        this->animate();
        return true;
    };
    bool setMarkParams(const MarkParams params) {
        this->m_markParams = params;
        return true;
    }
    bool setDelayParams(const DelayParams params) {
        this->m_delayParams = params;
        return true;
    }
/// ********************
/// \brief update
/// 更新函数 不能主动调用update；都在animate中调用
/// ********************
protected:
    /// \brief updateParallelOffsetItem
    /// 注意 在调用内部paint函数的时候, 是基于锚点绘制的;所以使用的不可以是真实坐标, 而是记录坐标;
    virtual bool updateParallelOffsetItem() = 0;
    /// \brief updatePaintItem
    /// 注意 在调用内部paint函数的时候, 是基于锚点绘制的;所以使用的不可以是真实坐标, 而是记录坐标;
    virtual bool updatePaintItem() = 0;
    /// \brief updateCopiedItem
    /// 注意 在调用内部paint函数的时候, 是基于锚点绘制的;所以使用的不可以是真实坐标, 而是记录坐标;
    virtual bool updateCopiedItem() = 0;
    /// \brief animate
    ///
    virtual bool animate() {
        // 这里实时把vertexlist里的点信息更新到itemlist里；然后paint函数会绘制itemlist里的东西
        this->updatePaintItem();
        // 更新offsetitem
        this->updateParallelOffsetItem();
        // 更新copiedItem
        this->updateCopiedItem();
        // 通知qt boundingRect变化 更新区域
        prepareGeometryChange();
        update();
        return true;
    }
/// ********************
/// \brief get info
/// 只获取信息
/// ********************
public:
    /// \brief getOffset
    /// \return
    virtual cavc::Polyline < double > getCavcForm(bool inSceneCoord) const = 0;
    /// \brief getVertexInScene
    /// \return 这里返回的是在scene中vertex的真实位置;不考虑锚点位置;禁止直接修改vertex
    virtual Vertex getVertexInScene(const int index) const = 0;
    /// \brief getCenterInScene
    /// \return 这里返回的是scene真实位置;不考虑锚点位置;禁止直接修改vertex
    virtual QPointF getCenterInScene() const = 0;
    virtual QString getName() const;
    const QString getUUID() const;
    const QColor getColor() const {
        return this->m_color;
    }
    const QPen getPen() const {
        QPen pen(this->m_color, 1);
        pen.setCosmetic(true);
        return pen;
    }
    virtual uint getVertexCount() const = 0;
    virtual QRectF getBoundingRectBasis() const = 0;
    const MarkParams getMarkParams() const {
        return this->m_markParams;
    }
    const DelayParams getDelayParams() const {
        return this->m_delayParams;
    }
    const OffsetParams getOffsetParams() const {
        return this->m_offsetParams;
    }
    const VectorCopyParams getVectorCopyParams() const {
        return this->m_vectorCopyParams;
    }
    const MatrixCopyParams getMatrixCopyParams() const {
        return this->m_matrixCopyParams;
    }
/// ********************
/// \brief overload
/// 重载基于QGraphicsitem的一些性质
/// ********************
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
/// ********************
/// private variable
/// ********************
protected:
    QString m_uuid;
    QColor m_color = Qt::black;
    MarkParams m_markParams;
    DelayParams m_delayParams;
    OffsetParams m_offsetParams  = OffsetParams {0, 0};
    VectorCopyParams m_vectorCopyParams  = VectorCopyParams {QPointF{0, 0}, 0, 0};
    MatrixCopyParams m_matrixCopyParams  = MatrixCopyParams {QPointF{0, 0}, QPointF{0, 0}, 0, 0, 0, 0, 0};
};

#endif // GRAPHICSITEM_H
