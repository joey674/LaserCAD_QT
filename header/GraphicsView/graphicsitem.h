#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H

#include <QDebug.h>
#include <QJsonObject>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QPropertyAnimation>
#include "laserworker.h"
#include "protocol.h"
#include "utils.hpp"
#include <polylineoffset.hpp>
#include <qgraphicsitem.h>
#include <qgraphicsscene.h>

class GraphicsItem : public QGraphicsObject {
    Q_OBJECT
    Q_PROPERTY(QColor color READ getAnimateColor WRITE setAnimateColor)
    friend class CombinedItem;
public:
    GraphicsItem() {
        this->m_uuid = GenerateUUID();
        this->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    };
    GraphicsItem(const GraphicsItem &) = delete;
    GraphicsItem &operator=(const GraphicsItem &) = delete;
    void cloneBaseParams(const GraphicsItem &other) {
        // 拷贝基础字段;  不可以拷贝copyparams
        this->m_uuid = GenerateUUID();
        this->m_color = other.getColor();
        this->m_animateColor = other.getColor ();
        this->setFlags(other.flags());
        this->m_markParams = other.m_markParams;
        this->m_delayParams = other.m_delayParams;
        this->m_contourFillParams = other.m_contourFillParams;
        this->m_hatchFillParams = other.m_hatchFillParams;
    }
    virtual std::shared_ptr < GraphicsItem > clone() const = 0;
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
    virtual std::vector < std::shared_ptr < GraphicsItem>> breakCopiedItem() = 0;
    virtual std::vector < std::shared_ptr < GraphicsItem>> breakContourFillItem() = 0;
    virtual std::vector < std::shared_ptr < GraphicsItem>> breakHatchFillItem() {};
    bool setColor(QColor color) {
        this->m_color = color;
        this->m_animateColor = color;
        this->animate();
        return true;
    };
    bool setAnimateColor(QColor color) {
        this->m_animateColor = color;
        this->animate();
        return true;
    };
    bool setMarkParams(const MarkParams params) {
        this->m_markParams = params;
        this->animate();
        return true;
    }
    bool setDelayParams(const DelayParams params) {
        this->m_delayParams = params;
        this->animate();
        return true;
    }
    bool setCopiedParams(VectorCopyParams params) {
        this->m_vectorCopyParams = params;
        this->m_matrixCopyParams.setEmpty();
        this->animate();
        return true;
    };
    bool setCopiedParams(MatrixCopyParams params) {
        this->m_matrixCopyParams = params;
        this->m_vectorCopyParams.setEmpty();
        this->animate();
        return true;
    };
    bool setFillParams(ContourFillParams params) {
        this->m_contourFillParams = params;
        this->animate();
        return true;
    }
    bool setFillParams(HatchFillParams params){
        this->m_hatchFillParams = params;
        this->animate ();
        return true;
    }
    void setSelectedAnimation(bool isSelected) {
        if (isSelected) {
            // 若已有旧动画，先停止
            if (m_selectAnim) {
                m_selectAnim->stop();
                m_selectAnim->deleteLater();
                m_selectAnim = nullptr;
            }

            m_selectAnim = new QPropertyAnimation(this, "color");
            m_selectAnim->setDuration(1000);
            m_selectAnim->setStartValue(this->m_color);
            m_selectAnim->setKeyValueAt(0.3, QColor(Qt::lightGray));
            m_selectAnim->setKeyValueAt(0.5, QColor(Qt::darkGray));
            m_selectAnim->setKeyValueAt(0.7, QColor(Qt::darkGray));
            m_selectAnim->setEndValue(this->m_color);
            m_selectAnim->setEasingCurve(QEasingCurve::InOutSine);
            m_selectAnim->setLoopCount(-1);
            m_selectAnim->start();

        } else {
            if (m_selectAnim) {
                m_selectAnim->stop();
                m_selectAnim->deleteLater();
                m_selectAnim = nullptr;
            }
            this->setColor(this->m_color);
        }
    }
/// ********************
/// \brief update
/// 更新函数 不能主动调用update；都在animate中调用
/// 注意 在调用内部paint函数的时候, 是基于锚点绘制的;所以使用的不可以是真实坐标, 而是记录坐标;
/// ********************
protected:
    virtual bool updateContourFillItem() = 0;
    virtual bool updatePaintItem() = 0;
    virtual bool updateCopiedItem() = 0;
    virtual bool updateHatchFillItem() = 0;
    virtual bool animate() {
        // 这里实时把vertexlist里的点信息更新到itemlist里；然后paint函数会绘制itemlist里的东西
        this->updatePaintItem();
        // 更新offsetitem
        this->updateContourFillItem();
        // 更新copiedItem
        this->updateCopiedItem();
        // 更新copiedItem
        this->updateHatchFillItem();
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
    virtual cavc::Polyline < double > getCavcForm() const = 0;
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
    const QColor getAnimateColor() const {
        return this->m_animateColor;
    }
    const QPen getPen() const {
        QPen pen(this->m_animateColor, 1);
        pen.setCosmetic(true);
        return pen;
    }
    virtual uint getVertexCount() const = 0;
    /// \brief getBoundingRectBasis 获取除去copyitem等等的附属items后 本身paintitem的boundingrect
    virtual QRectF getBoundingRectBasis() const = 0;
    const MarkParams getMarkParams() const {
        return this->m_markParams;
    }
    const DelayParams getDelayParams() const {
        return this->m_delayParams;
    }
    const ContourFillParams getContourFillParams() const { return this->m_contourFillParams; }
    const HatchFillParams getFillParams() const { return this->m_hatchFillParams; }
    const VectorCopyParams getVectorCopyParams() const { return this->m_vectorCopyParams; }
    const MatrixCopyParams getMatrixCopyParams() const { return this->m_matrixCopyParams; }
    virtual std::vector<LaserDeviceCommand> getLaserCommand()
    {
        std::vector<LaserDeviceCommand> commandList;

        commandList.emplace_back(SetLaserPulsesCommand{m_markParams.frequency, m_markParams.pulseLength});
        commandList.emplace_back (SetLaserPowerCommand{1,m_markParams.power});
        commandList.emplace_back(SetScannerDelaysCommand{m_delayParams.jumpDelay,
                                                         m_delayParams.markDelay,
                                                         m_delayParams.polygonDelay});
        commandList.emplace_back(
            SetLaserDelaysCommand{m_delayParams.laserOnDelay, m_delayParams.laserOffDelay});

        commandList.emplace_back(
            SetJumpSpeedCommand{m_markParams.jumpSpeed});
        commandList.emplace_back(
            SetMarkSpeedCommand{m_markParams.markSpeed});

        return commandList;
    }
    /// \brief getPaintItemList 服务combinedItem的; 需要包括所有copied/fill/paintitem
    virtual std::vector<std::shared_ptr<QGraphicsItem>> getPaintItemList()
    {
        return std::vector<std::shared_ptr<QGraphicsItem>>();
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
    QColor m_animateColor= Qt::black;
    QPropertyAnimation* m_selectAnim = nullptr;
    MarkParams m_markParams;
    DelayParams m_delayParams;
    ContourFillParams m_contourFillParams;
    HatchFillParams m_hatchFillParams;
    VectorCopyParams m_vectorCopyParams;
    MatrixCopyParams m_matrixCopyParams;
};

#endif // GRAPHICSITEM_H
