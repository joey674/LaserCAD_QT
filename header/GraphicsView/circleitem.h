#ifndef CIRCLEITEM_H
#define CIRCLEITEM_H

#include "protocol.h"
#include "graphicsitem.h"
#include "logger.h"
#include "polylineitem.h"
#include "combineditem.h"

class CircleItem : public GraphicsItem {
public:
    CircleItem() {};
    CircleItem(const CircleItem &other) {}
    std::shared_ptr < GraphicsItem > clone() const override {
        auto item = std::make_shared < CircleItem > ();
        item->cloneBaseParams(*this);
        item->m_center = this->m_center;
        item->m_radius = this->m_radius;
        item->animate();
        return item;
    }
    std::shared_ptr < GraphicsItem > createFromJson(QJsonObject obj) override {
        auto item = std::make_shared < CircleItem > ();
        item->cloneBaseParamsFromJson(obj);
        if (obj.contains("center")) {
            QJsonObject center = obj["center"].toObject();
            item->m_center.point = QPointF(center["x"].toDouble(), center["y"].toDouble());
            item->m_center.angle = center["angle"].toDouble();
        }
        if (obj.contains("radius")) {
            item->m_radius = obj["radius"].toDouble();
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
        obj["radius"] = m_radius;
        return obj;
    }

public:
    /// 编辑圆心
    bool setVertexInScene(const int index, const Vertex vertex) override {
        if (index > 1) {
            WARN_VAR(index);
            return false;
        }
        QPointF pos = vertex.point /* - this->scenePos()*/;
        this->m_center = Vertex{pos, 0};
        animate();
        return true;
    }
    /// 编辑半径
    bool setRadius(const double radius) {
        if (radius < 0) {
            return false;
        }
        this->m_radius = radius;
        animate();
        return true;
    }
    bool setCenterInScene(const QPointF point) override {
        this->m_center = Vertex{point, 0};
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
    std::vector < std::shared_ptr < GraphicsItem>> breakContourFillItem() override {
        // 获取当前最新的copiedItem
        this->animate();
        // 设置Params为空
        m_contourFillParams.offset = 0;
        m_contourFillParams.offsetCount = 0;
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
        this->m_contourFillItemList.clear();
        //
        if (this->m_contourFillParams.offset == 0 || this->m_contourFillParams.offsetCount == 0) {
            return true;
        }
        for (int offsetIndex = 1; offsetIndex <= this->m_contourFillParams.offsetCount; offsetIndex++) {
            // 输入cavc库
            cavc::Polyline < double > input = this->getCavcForm(false);
            input.isClosed() = true;
            std::vector < cavc::Polyline < double>> results = cavc::parallelOffset(input,
                                                                               (-1)* this->m_contourFillParams.offset * offsetIndex);
            // 获取结果
            for (const auto& polyline : results) {
                auto item = FromCavcForm(polyline);
                item->setColor(this->getColor());
                item->setMarkParams (this->getMarkParams ());
                item->setDelayParams (this->getDelayParams ());
                this->m_contourFillItemList.push_back(std::move(item));
            }
        }
        return true;
    }
    bool updatePaintItem() override {
        // 这里实时把vertexlist里的点信息更新到itemlist里；然后paint函数会绘制itemlist里的东西
        this->m_paintItem = nullptr;
        this->m_paintItem = std::make_shared < QGraphicsEllipseItem > ();
        QRectF rect(
            m_center.point.x() - m_radius,
            m_center.point.y() - m_radius,
            m_radius * 2,
            m_radius * 2
        );
        this->m_paintItem->setRect(rect);
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
            QPointF unitOffset =
                this->m_vectorCopyParams.dir * this->m_vectorCopyParams.spacing;
            for (int i = 1; i <= this->m_vectorCopyParams.count; ++i) {
                // DEBUG_VAR(this->getUUID());
                auto copiedItem = std::dynamic_pointer_cast < CircleItem > (this->clone());
                QPointF offset = unitOffset * i;
                copiedItem->m_center.point += offset;
                copiedItem->animate();
                // DEBUG_VAR(copiedItem->getUUID());
                m_copiedItemList.push_back(copiedItem);
            }
            return true;
        }
        //
        if (!this->m_matrixCopyParams.checkEmpty()) {
            m_copiedItemList.clear();
            QPointF hOffset = this->m_matrixCopyParams.hVec * this->m_matrixCopyParams. hSpacing;
            QPointF vOffset = this->m_matrixCopyParams.vVec * this->m_matrixCopyParams.vSpacing;
            std::vector < std::vector < QPointF>> offsetMatrix(this->m_matrixCopyParams.vCount,
                    std::vector < QPointF > (this->m_matrixCopyParams.hCount));
            for (int row = 0; row < this->m_matrixCopyParams.vCount; ++row) {
                for (int col = 0; col < this->m_matrixCopyParams.hCount; ++col) {
                    offsetMatrix[row][col] = hOffset * col + vOffset * row;
                }
            }
            auto insertCopy = [&](int row, int col) {
                if (row == 0 && col == 0) {
                    return;    // 跳过原始位置后开始复制
                }
                auto copiedItem = std::dynamic_pointer_cast < CircleItem > (this->clone());
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
    bool updateHatchFillItem() override;
    std::vector < std::shared_ptr < GraphicsItem>> breakHatchFillItem() override {
        DEBUG_MSG("break hatch");
        std::vector < std::shared_ptr < GraphicsItem>> result;
        //
        auto startAngle = this->m_hatchFillParams.startAngle;
        for (int hatchIdx = 0; hatchIdx < this->m_hatchFillParams.operateCount; hatchIdx++) {
            this->updateHatchFillItem ();
            auto combinedItem = std::make_shared<CombinedItem>();
            // 转换类型
            std::vector < std::shared_ptr < GraphicsItem>> graphicsItems;
            graphicsItems.reserve(this->m_hatchFillItemList.size());
            for (const auto& item : this->m_hatchFillItemList) {
                graphicsItems.push_back(std::static_pointer_cast<GraphicsItem>(item));
            }
            // 装进combinedItem,然后装进result
            combinedItem->combinedItem (graphicsItems);
            result.push_back (combinedItem);
            this->m_hatchFillParams.startAngle += this->m_hatchFillParams.accumulateAngle;
        }
        DEBUG_VAR(result.size ());
        this->m_hatchFillParams.startAngle = startAngle;
        this->m_hatchFillParams.operateCount = 0;
        return result;
    };

public:
    cavc::Polyline < double > getCavcForm(bool inSceneCoord) const override {
        cavc::Polyline < double > input;
        QPointF p1, p2;
        if (inSceneCoord) {
            p1 = this->getVertexInScene(0).point - QPointF{this->m_radius, 0};
            p2 = this->getVertexInScene(1).point + QPointF{this->m_radius, 0};
        } else {
            p1 = m_center.point - QPointF{this->m_radius, 0};
            p2 = m_center.point + QPointF{this->m_radius, 0};
        }
        input.addVertex(p1.x(), p1.y(), -1);
        input.addVertex(p2.x(), p2.y(), -1);
        return input;
    }
    Vertex getVertexInScene(const int index = 0) const override {
        if (index > 1) {
            assert("false index:only 0");
        }
        QPointF point = m_center.point;
        return Vertex{point, 0};
    }
    QPointF getCenterInScene() const override { return this->m_center.point; }
    double getRadius() {
        return this->m_radius;
    }
    QString getName() const override {
        return "CircleItem";
    }
    int type() const override {
        return GraphicsItemType::Circle;
    }
    uint getVertexCount() const override {
        return 1;
    }
    QRectF getBoundingRectBasis() const override {
        if (!this->m_paintItem) {
            return QRectF();
        }
        QRectF newRect = m_paintItem->boundingRect();
        return newRect;
    }
    std::vector<LaserDeviceCommand> getLaserCommand() override{
        this->animate ();
        auto commandList = GraphicsItem::getLaserCommand();
        auto repeatTime = this->getMarkParams().operateTime;

        const auto center =this->getCenterInScene ();
        const auto radius = this->m_radius;
        const auto p0 = QPointF{center.x () - radius, center.y ()};
        const auto angle = (-1) * (360);

        for (int i = 0; i < repeatTime; i++) {
            // 打印自身Item
            commandList.emplace_back(JumpCommand{p0.x (),p0.y ()});
            commandList.emplace_back(ArcCommand{center.x (), center.y (), angle});
            // 打印 CONTOUR FillItem
            for (const auto& contourFillItem : m_contourFillItemList){
                auto cmdList1 = contourFillItem->getLaserCommand ();
                commandList.insert(commandList.end(), cmdList1.begin(), cmdList1.end());
            }
            // 打印 HATCH FillItem (这里通过更新startAngle来获取累进的hatch,最后再改回去)
            auto startAngle = this->m_hatchFillParams.startAngle;
            for (int hatchIdx = 0; hatchIdx < this->m_hatchFillParams.operateCount; hatchIdx++) {
                for (const auto& hatchFillItem : m_hatchFillItemList){
                    auto cmdList2 = hatchFillItem->getLaserCommand ();
                    commandList.insert(commandList.end(), cmdList2.begin(), cmdList2.end());
                }
                this->m_hatchFillParams.startAngle += this->m_hatchFillParams.accumulateAngle;
                this->updateHatchFillItem ();
            }
            this->m_hatchFillParams.startAngle = startAngle;
            // 打印COPY Item
            for (const auto& copyItem : m_copiedItemList){
                auto cmd = copyItem->getLaserCommand ();
                commandList.insert (commandList.end (),cmd.begin (),cmd.end ());
            }
        }
        return commandList;
    }
    std::vector<std::shared_ptr<QGraphicsItem>> getPaintItemList() override
    {
        this->animate();
        std::vector<std::shared_ptr<QGraphicsItem>> list;
        list.push_back(this->m_paintItem);
        list.insert(list.end(), m_contourFillItemList.begin(), m_contourFillItemList.end());
        list.insert(list.end(), m_copiedItemList.begin(), m_copiedItemList.end());
        list.insert(list.end(), m_hatchFillItemList.begin(), m_hatchFillItemList.end());
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
                      -abs(this->m_contourFillParams.offset) * this->m_contourFillParams.offsetCount - 1,
                      -abs(this->m_contourFillParams.offset) * this->m_contourFillParams.offsetCount - 1,
                      abs(this->m_contourFillParams.offset) * this->m_contourFillParams.offsetCount + 1,
                      abs(this->m_contourFillParams.offset) * this->m_contourFillParams.offsetCount + 1);
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
    double m_radius = 0;
    //
    std::shared_ptr < QGraphicsEllipseItem > m_paintItem;
    std::vector < std::shared_ptr < PolylineItem>> m_contourFillItemList;
    std::vector < std::shared_ptr < CircleItem>> m_copiedItemList;
    std::vector < std::shared_ptr < PolylineItem>> m_hatchFillItemList;
};

#endif // CIRCLEITEM_H
