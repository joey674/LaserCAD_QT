#ifndef LINEITEM_H
#define LINEITEM_H

#include "protocol.h"
#include "graphicsitem.h"
#include "polylineitem.h"

class LineItem: public GraphicsItem {
public:
    LineItem() {};
    std::shared_ptr < GraphicsItem > clone() const  override {
        auto item = std::make_shared < LineItem > ();
        item->cloneBaseParams(*this);
        item->m_vertexPair = this->m_vertexPair;
        item->animate();
        return item;
    }
    std::shared_ptr < GraphicsItem > createFromJson(QJsonObject obj) override {
        auto item = std::make_shared < LineItem > ();
        // 加载基类参数
        item->cloneBaseParamsFromJson(obj);
        if (obj.contains("v0") && obj.contains("v1")) {
            QJsonObject v0 = obj["v0"].toObject();
            QJsonObject v1 = obj["v1"].toObject();
            item->m_vertexPair[0].point = QPointF(v0["x"].toDouble(), v0["y"].toDouble());
            item->m_vertexPair[0].angle = v0["angle"].toDouble();
            item->m_vertexPair[1].point = QPointF(v1["x"].toDouble(), v1["y"].toDouble());
            item->m_vertexPair[1].angle = v1["angle"].toDouble();
        }
        item->animate();
        return item;
    }
    QJsonObject saveToJson() const override {
        // 保存基类参数
        QJsonObject obj = saveBaseParamsToJson();
        // 保存子类参数 m_vertexPair
        obj["type"] = getName();
        QJsonObject v0, v1;
        v0["x"] = m_vertexPair[0].point.x ();
        v0["y"] = m_vertexPair[0].point.y();
        v0["angle"] = m_vertexPair[0].angle;
        v1["x"] = m_vertexPair[1].point.x();
        v1["y"] = m_vertexPair[1].point.y();
        v1["angle"] = m_vertexPair[1].angle;
        obj["v0"] = v0;
        obj["v1"] = v1;
        return obj;
    }

public:
    bool setVertexInScene(const int index, const Vertex vertex) override {
        if (index > 1) {
            return false;
        }
        this->m_vertexPair[index].point = vertex.point;
        this->m_vertexPair[index].angle = vertex.angle;
        animate();
        return true;
    }
    bool setCenterInScene(const QPointF point) override {
        QPointF currentCenter = this->getCenterInScene();
        QPointF offset = point - currentCenter;
        for (auto &vertex : this->m_vertexPair) {
            vertex.point = vertex.point + offset;
        }
        this->animate();
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

            result.emplace_back(std::move(item));
        }
        m_contourFillItemList.clear();
        return result;
    };
    std::vector < std::shared_ptr < GraphicsItem>> breakHatchFillItem() override {
        std::vector < std::shared_ptr < GraphicsItem>> result;
        return result;
    };

protected:
    bool updateContourFillItem() override {
        this->m_contourFillItemList.clear();
        //
        if (this->m_contourFillParams.offset == 0 || this->m_contourFillParams.offsetCount == 0) {
            return true;
        }
        for (int offsetIndex = 1; offsetIndex <= this->m_contourFillParams.offsetCount;
             offsetIndex++) {
            // 输入cavc库
            cavc::Polyline < double > input = this->getCavcForm();
            input.isClosed() = false;
            std::vector<cavc::Polyline<double>> results
                = cavc::parallelOffset(input, this->m_contourFillParams.offset * offsetIndex);
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
        auto v1 = m_vertexPair[0].point;
        auto v2 = m_vertexPair[1].point;
        this->m_paintItem = std::make_shared < QGraphicsLineItem > (QLineF(v1, v2));
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
                auto copiedItem = std::dynamic_pointer_cast < LineItem > (this->clone());
                QPointF offset = unitOffset * i;
                copiedItem->m_vertexPair[0].point += offset;
                copiedItem->m_vertexPair[1].point += offset;
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
                auto copiedItem = std::dynamic_pointer_cast < LineItem > (this->clone());
                if (!copiedItem) {
                    return;
                }
                QPointF offset = offsetMatrix[row][col];
                copiedItem->m_vertexPair[0].point += offset;
                copiedItem->m_vertexPair[1].point += offset;
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
    bool updateHatchFillItem() override{return true;}; // line没有填充

public:
    cavc::Polyline < double > getCavcForm() const override {
        // 输入cavc库
        cavc::Polyline < double > input;
        QPointF p1, p2;
            p1 = m_vertexPair[0].point;
            p2 = m_vertexPair[1].point;
        input.addVertex(p1.x(), p1.y(), 0);
        input.addVertex(p2.x(), p2.y(), 0);
        return input;
    }
    Vertex getVertexInScene(const int index) const override {
        if (index > 1) {
            assert("false index:only 0,1");
        }
        QPointF point = m_vertexPair[index].point;
        double angle = m_vertexPair[index].angle;
        return Vertex{point, angle};
    }
    QPointF getCenterInScene() const override {
        auto center = QPointF{};
        center = (m_vertexPair[0].point + m_vertexPair[1].point) / 2;
        return center;
    }
    QString getName() const override {
        return "LineItem";
    }
    int type() const override {
        return GraphicsItemType::Line;
    }
    uint getVertexCount() const override {
        return 2;
    }
    QRectF getBoundingRectBasis() const override {
        QPointF p1 = this->getVertexInScene(0).point;
        QPointF p2 = this->getVertexInScene(1).point;

        qreal left   = std::min(p1.x(), p2.x());
        qreal right  = std::max(p1.x(), p2.x());
        qreal top    = std::min(p1.y(), p2.y());
        qreal bottom = std::max(p1.y(), p2.y());

        qreal width = right - left;
        qreal height = bottom - top;

        // 如果是横线或竖线，宽或高为 0 则设为 0.01
        if (width == 0) {
            left -= 0.05;
            // right += 0.05;
            width = 0.1;
        }
        if (height == 0) {
            top -= 0.05;
            // bottom += 0.05;
            height = 0.1;
        }

        return QRectF(QPointF(left, top), QSizeF(width, height));
    }

    std::vector<LaserDeviceCommand> getLaserCommand() override
    {
        this->animate ();
        auto commandList = GraphicsItem::getLaserCommand();
        auto operateTime = this->getMarkParams().operateTime;

        const auto &p0 = m_vertexPair[0];
        const auto &p1 = m_vertexPair[1];
        const auto startPosX = p0.point.x();
        const auto startPosY = p0.point.y();
        const auto endPosX = p1.point.x();
        const auto endPosY = p1.point.y();

        for (int i = 0; i < operateTime; i++) {
            // 打印本体
            commandList.emplace_back(JumpCommand{startPosX,startPosY});
            commandList.emplace_back(MarkCommand{endPosX,endPosY});
            // 打印copyItem
            for (const auto copyItem : m_copiedItemList){
                const auto &cP0 = copyItem->getVertexInScene (0);
                const auto &cP1 = copyItem->getVertexInScene (1);
                const auto cStartPosX = cP0.point.x();
                const auto cStartPosY = cP0.point.y();
                const auto cEndPosX = cP1.point.x();
                const auto cEndPosY = cP1.point.y();
                commandList.emplace_back(JumpCommand{cStartPosX,cStartPosY});
                commandList.emplace_back(MarkCommand{cEndPosX,cEndPosY});
            }
            // 打印offsetItem
            for (const auto offsetItem : m_contourFillItemList){
                const auto &oP0 = offsetItem->getVertexInScene (0);
                const auto &oP1 = offsetItem->getVertexInScene (1);
                const auto oStartPosX = oP0.point.x();
                const auto oStartPosY = oP0.point.y();
                const auto oEndPosX = oP1.point.x();
                const auto oEndPosY = oP1.point.y();
                commandList.emplace_back(JumpCommand{oStartPosX,oStartPosY});
                commandList.emplace_back(MarkCommand{oEndPosX,oEndPosY});
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
        QRectF newRect = this->getBoundingRectBasis ();
        // 包含contourFillItem
        newRect = newRect.adjusted(
            -abs(this->m_contourFillParams.offset) * this->m_contourFillParams.offsetCount,
            -abs(this->m_contourFillParams.offset) * this->m_contourFillParams.offsetCount,
            abs(this->m_contourFillParams.offset) * this->m_contourFillParams.offsetCount,
            abs(this->m_contourFillParams.offset) * this->m_contourFillParams.offsetCount);
        // 包含copiedItem
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
        // 绘制self
        this->m_paintItem->paint(painter, &optionx, widget);
        // 绘制contour
        for (auto &item : this->m_contourFillItemList) {
            item->paint(painter, &optionx, widget);
        }
        // 绘制hatch
        for (auto &item : this->m_hatchFillItemList) {
            item->paint(painter, &optionx, widget);
        }
        // 绘制copied
        for (auto &item : this->m_copiedItemList) {
            item->paint(painter, &optionx, widget);
        }
    }

private:
    std::array < Vertex, 2 > m_vertexPair = {Vertex{QPointF{0, 0}, 0}, Vertex{QPointF{0, 0}, 0}};
    std::shared_ptr < QGraphicsLineItem > m_paintItem;
    std::vector < std::shared_ptr < PolylineItem>> m_contourFillItemList;
    std::vector < std::shared_ptr < LineItem>> m_copiedItemList;
    std::vector < std::shared_ptr < PolylineItem>> m_hatchFillItemList;
};

#endif // LINEITEM_H
