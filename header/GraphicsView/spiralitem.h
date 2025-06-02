#ifndef SPIRALITEM_H
#define SPIRALITEM_H

#include "graphicsitem.h"
#include "logger.h"
#include "polylineitem.h"
#include "protocol.h"

class SpiralItem : public GraphicsItem {
public:
    SpiralItem() {}
    std::shared_ptr < GraphicsItem > clone() const override {
        auto item = std::make_shared < SpiralItem > ();
        item->cloneBaseParams(*this);
        item->m_center = this->m_center;
        item->m_startRadius = this->m_startRadius;
        item->m_endRadius = this->m_endRadius;
        item->m_turns = this->m_turns;
        item->m_angleStepDeg = this->m_angleStepDeg;
        item->m_rotateAngle = this->m_rotateAngle;
        item->animate();
        return item;
    }
    std::shared_ptr < GraphicsItem > createFromJson(QJsonObject obj) override {
        auto item = std::make_shared < SpiralItem > ();
        item->cloneBaseParamsFromJson(obj);
        if (obj.contains("center")) {
            QJsonObject center = obj["center"].toObject();
            item->m_center.point = QPointF(center["x"].toDouble(), center["y"].toDouble());
            item->m_center.angle = center["angle"].toDouble();
        }
        if (obj.contains("startRadius")) {
            item->m_startRadius = obj["startRadius"].toDouble();
        }
        if (obj.contains("endRadius")) {
            item->m_endRadius = obj["endRadius"].toDouble();
        }
        if (obj.contains("truns")) {
            item->m_turns = obj["truns"].toDouble();
        }
        if (obj.contains("angleStepDeg")) {
            item->m_angleStepDeg = obj["angleStepDeg"].toDouble();
        }
        if (obj.contains("rotateAngle")) {
            item->m_rotateAngle = obj["rotateAngle"].toDouble();
        }
        item->animate();
        return item;
    }
    QJsonObject saveToJson() const override {
        // 保存基类参数
        QJsonObject obj = saveBaseParamsToJson();
        // 保存子类参数
        obj["type"] = getName();
        //
        QJsonObject center;
        center["x"] = m_center.point.x();
        center["y"] = m_center.point.y();
        center["angle"] = m_center.angle;
        obj["center"] = center;
        //
        obj["startRadius"] = m_startRadius;
        obj["endRadius"] = m_endRadius;
        obj["turns"] = m_turns;
        obj["angleStepDeg"] = m_angleStepDeg;
        obj["rotateAngle"] = m_rotateAngle;
        return obj;
    }

public:
    bool setVertexInScene(const int index, const Vertex vertex) override {
        if (index > 1) {
            WARN_VAR(index);
            return false;
        }
        QPointF pos = vertex.point;
        this->m_center = Vertex{pos, 0};
        animate();
        return true;
    }
    void setStartRadius(double r) {
        m_startRadius = r;
        animate();
    }
    void setEndRadius(double r) {
        m_endRadius = r;
        animate();
    }
    void setTurns(double t) {
        m_turns = t;
        animate();
    }
    void setAngleStepDeg(double step) {
        m_angleStepDeg = step;
        animate();
    }
    bool setCenterInScene(const QPointF point) override {
        QPointF currentCenter = this->getCenterInScene();
        QPointF offset = point - currentCenter;
        this->m_center.point = this->m_center.point + offset;
        this->animate();
        return true;
    }
    bool setRotateAngle(double angle) {
        if (angle < 0 || angle >= 360.0) {
            return false;
        }
        m_rotateAngle = angle;
        animate();
        return true;
    }
    std::vector < std::shared_ptr < GraphicsItem>> breakCopiedItem() override {
        // 获取当前最新的copiedItem
        this->animate();
        // 设置Params为空
        m_vectorCopyParams.setEmpty();
        m_matrixCopyParams.setEmpty();
        // 获取当前copiedItem  如果没有copiedItem就返回空数组
        std::vector < std::shared_ptr < GraphicsItem>> result;
        result.reserve(this->m_copiedItemList.size());
        for (auto &&item : std::move(this->m_copiedItemList)) {
            item->setPos(this->pos()); // 把位置也更新了; 作为copiedItem是不会保存这个数据的
            result.emplace_back(std::move(item));
        }
        m_copiedItemList.clear();
        return result;
    }
    std::vector < std::shared_ptr < GraphicsItem>> breakParallelFillItem() override {
        // 获取当前最新的copiedItem
        this->animate();
        // 设置Params为空
        m_offsetParams.offset = 0;
        m_offsetParams.offsetCount = 0;
        //获取当前offsetItem  如果没有offsetItem就返回空数组
        std::vector < std::shared_ptr < GraphicsItem>> result;
        result.reserve(this->m_contourFillItemList.size());
        for (auto &&item : std::move(this->m_contourFillItemList)) {
            item->setPos(this->pos()); // 把位置也更新了; 作为offsetItem是不会保存这个数据的
            result.emplace_back(std::move(item));
        }
        m_contourFillItemList.clear();
        return result;
    };

protected:
    bool updateContourFillItem() override {
        //
        if (this->m_offsetParams.offset == 0 || this->m_offsetParams.offsetCount == 0) {
            return true;
        }
        this->m_contourFillItemList.clear();
        for (int offsetIndex = 1; offsetIndex <= this->m_offsetParams.offsetCount; offsetIndex++) {
            // 输入cavc库
            cavc::Polyline < double > input = this->getCavcForm(false);
            input.isClosed() = false;
            std::vector < cavc::Polyline < double>> results
                = cavc::parallelOffset(input, this->m_offsetParams.offset * offsetIndex);
            // 获取结果
            for (const auto &polyline : results) {
                auto item = FromCavcForm(polyline);
                this->m_contourFillItemList.push_back(std::move(item));
            }
        }
        return true;
    }
    bool updatePaintItem() override {
        this->m_paintItem = std::make_shared < QGraphicsPathItem > ();
        QPainterPath path;
        if (m_startRadius >= m_endRadius || m_turns <= 0 || m_angleStepDeg <= 0) {
            return false;
        }
        const QPointF center = m_center.point;
        const double totalAngleDeg = m_turns * 360.0;
        const double angleStepRad = m_angleStepDeg * M_PI / 180.0;
        const double totalSteps = totalAngleDeg / m_angleStepDeg;
        const double radiusStep = (m_endRadius - m_startRadius) / totalSteps;
        const double baseAngleRad = m_rotateAngle * M_PI / 180.0;
        bool first = true;
        for (int i = 0; i <= totalSteps; ++i) {
            double angle = baseAngleRad + i * angleStepRad;
            double radius = m_startRadius + radiusStep * i;
            QPointF p = center + QPointF(std::cos(angle) * radius, std::sin(angle) * radius);
            if (first) {
                path.moveTo(p);
                first = false;
            } else {
                path.lineTo(p);
            }
        }
        this->m_paintItem->setPath(path);
        this->m_paintItem->setPen(this->getPen());
        return true;
    }
    bool updateCopiedItem() override {
        this->m_copiedItemList.clear();
        //
        if (this->m_vectorCopyParams.checkEmpty() && this->m_matrixCopyParams.checkEmpty()) {
            return true;
        } else if ((!this->m_vectorCopyParams.checkEmpty())
                   && (!this->m_matrixCopyParams.checkEmpty())) {
            WARN_MSG("should not happen");
            return false;
        }
        //
        if (!this->m_vectorCopyParams.checkEmpty()) {
            m_copiedItemList.clear();
            //
            QPointF unitOffset = this->m_vectorCopyParams.dir * this->m_vectorCopyParams.spacing;
            for (int i = 1; i <= this->m_vectorCopyParams.count; ++i) {
                // DEBUG_VAR(this->getUUID());
                auto copiedItem = std::dynamic_pointer_cast < SpiralItem > (this->clone());
                QPointF offset = unitOffset * i;
                copiedItem->m_center.point += offset;
                copiedItem->animate();
                DEBUG_VAR(copiedItem->getUUID());
                m_copiedItemList.push_back(copiedItem);
            }
            return true;
        }
        //
        if (!this->m_matrixCopyParams.checkEmpty()) {
            m_copiedItemList.clear();
            QPointF hOffset = this->m_matrixCopyParams.hVec * this->m_matrixCopyParams.hSpacing;
            QPointF vOffset = this->m_matrixCopyParams.vVec * this->m_matrixCopyParams.vSpacing;
            std::vector < std::vector < QPointF>> offsetMatrix(this->m_matrixCopyParams.vCount,
                    std::vector < QPointF > (
                        this->m_matrixCopyParams.hCount));
            for (int row = 0; row < this->m_matrixCopyParams.vCount; ++row) {
                for (int col = 0; col < this->m_matrixCopyParams.hCount; ++col) {
                    offsetMatrix[row][col] = hOffset * col + vOffset * row;
                }
            }
            auto insertCopy = [&](int row, int col) {
                if (row == 0 && col == 0) {
                    return; // 跳过原始位置后开始复制
                }
                auto copiedItem = std::dynamic_pointer_cast < SpiralItem > (this->clone());
                if (!copiedItem) {
                    return;
                }
                QPointF offset = offsetMatrix[row][col];
                copiedItem->m_center.point += offset;
                copiedItem->animate();
                m_copiedItemList.push_back(copiedItem);
            };
            switch (this->m_matrixCopyParams.copiedOrder) {
                case 0: // 行优先，蛇形
                    for (int row = 0; row < this->m_matrixCopyParams.vCount; ++row) {
                        if (row % 2 == 0) {
                            for (int col = 0; col < this->m_matrixCopyParams.hCount; ++col) {
                                insertCopy(row, col);
                            }
                        } else {
                            for (int col = this->m_matrixCopyParams.hCount - 1; col >= 0; --col) {
                                insertCopy(row, col);
                            }
                        }
                    }
                    break;
                case 1: // 列优先，蛇形
                    for (int col = 0; col < this->m_matrixCopyParams.hCount; ++col) {
                        if (col % 2 == 0) {
                            for (int row = 0; row < this->m_matrixCopyParams.vCount; ++row) {
                                insertCopy(row, col);
                            }
                        } else {
                            for (int row = this->m_matrixCopyParams.vCount - 1; row >= 0; --row) {
                                insertCopy(row, col);
                            }
                        }
                    }
                    break;
                case 2: // 行优先，顺序
                    for (int row = 0; row < this->m_matrixCopyParams.vCount; ++row) {
                        for (int col = 0; col < this->m_matrixCopyParams.hCount; ++col) {
                            insertCopy(row, col);
                        }
                    }
                    break;
                case 3: // 列优先，顺序
                    for (int col = 0; col < this->m_matrixCopyParams.hCount; ++col) {
                        for (int row = 0; row < this->m_matrixCopyParams.vCount; ++row) {
                            insertCopy(row, col);
                        }
                    }
                    break;
                default:
                    WARN_MSG("Unknown copiedOrder value");
                    break;
            }
            return true;
        }
        return false;
    }
    bool updateHatchFillItem() override{ return true;};

public:
    cavc::Polyline < double > getCavcForm(bool inSceneCoord) const override {
        cavc::Polyline < double > polyline;
        if (m_startRadius >= m_endRadius || m_turns <= 0 || m_angleStepDeg <= 0) {
            return polyline;
        }
        const double totalAngleDeg = m_turns * 360.0;
        const double angleStepRad = m_angleStepDeg * M_PI / 180.0;
        const double totalSteps = totalAngleDeg / m_angleStepDeg;
        const double radiusStep = (m_endRadius - m_startRadius) / totalSteps;
        const QPointF center = inSceneCoord ? getCenterInScene() : m_center.point;
        for (int i = 0; i <= totalSteps; ++i) {
            double angle = i * angleStepRad;
            double radius = m_startRadius + radiusStep * i;
            QPointF p = center + QPointF(std::cos(angle) * radius, std::sin(angle) * radius);
            polyline.addVertex(p.x(), p.y(), 0);
        }
        return polyline;
    }
    Vertex getVertexInScene(const int index = 0) const override {
        if (index > 1) {
            assert("false index:only 0");
        }
        QPointF point = m_center.point;
        double angle = m_center.angle;
        return Vertex{point, angle};
    }
    QPointF getCenterInScene() const override { return this->m_center.point; }
    uint getVertexCount() const override {
        return 1;
    }
    QString getName() const override {
        return "SpiralItem";
    }
    int type() const override {
        return GraphicsItemType::Spiral;
    }
    double getStartRadius() const {
        return m_startRadius;
    }
    double getEndRadius() const {
        return m_endRadius;
    }
    double getTurns() const {
        return m_turns;
    }
    double getAngleStepDeg() const {
        return m_angleStepDeg;
    }
    double getRotateAngle() const {
        return m_rotateAngle;
    }
    QRectF getBoundingRectBasis() const override {
        if (!this->m_paintItem) {
            return QRectF();
        }
        QRectF newRect = m_paintItem->boundingRect();
        return newRect;
    }
    std::vector<LaserDeviceCommand> getRTC5Command() const override{}
    std::vector<std::shared_ptr<QGraphicsItem>> getPaintItemList() override
    {
        this->animate();
        std::vector<std::shared_ptr<QGraphicsItem>> list;
        list.push_back(this->m_paintItem);
        return list;
    }

protected:
    QRectF boundingRect() const override {
        if (!this->m_paintItem) {
            return QRectF();
        }
        QRectF newRect = m_paintItem->boundingRect();
        // 包含offsetItem
        newRect = newRect.adjusted(
                      -abs(this->m_offsetParams.offset) * this->m_offsetParams.offsetCount - 1,
                      -abs(this->m_offsetParams.offset) * this->m_offsetParams.offsetCount - 1,
                      abs(this->m_offsetParams.offset) * this->m_offsetParams.offsetCount + 1,
                      abs(this->m_offsetParams.offset) * this->m_offsetParams.offsetCount + 1);
        // 包含所有 copiedItem
        for (const auto &item : m_copiedItemList) {
            if (item) {
                newRect = newRect.united(item->boundingRect());
            }
        }
        return newRect;
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
        Q_UNUSED(widget);
        // 设置option删去offset线段的选框
        QStyleOptionGraphicsItem optionx(*option);
        optionx.state &= ~QStyle::State_Selected;
        // 绘制线段
        this->m_paintItem->paint(painter, &optionx, widget);
        // 绘制offset
        for (auto &item : this->m_contourFillItemList) {
            item->paint(painter, &optionx, widget);
        }
        // 绘制copied
        for (auto &item : this->m_copiedItemList) {
            item->paint(painter, &optionx, widget);
        }
        // 绘制fill
        for (auto &item : this->m_hatchFillItemList) {
            item->paint(painter, &optionx, widget);
        }
    }

private:
    Vertex m_center = Vertex{QPointF{0, 0}, 0};
    double m_startRadius;
    double m_endRadius;
    double m_turns;
    double m_angleStepDeg;
    double m_rotateAngle = 0; // 旋转角度
    //
    std::shared_ptr < QGraphicsPathItem > m_paintItem;
    std::vector < std::shared_ptr < PolylineItem>> m_contourFillItemList;
    std::vector < std::shared_ptr < SpiralItem>> m_copiedItemList;
    std::vector < std::shared_ptr < PolylineItem>> m_hatchFillItemList;
};

#endif // SPIRALITEM_H
