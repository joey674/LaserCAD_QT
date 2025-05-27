#ifndef LINEITEM_H
#define LINEITEM_H

#include "protocol.h"
#include "graphicsitem.h"
#include "polylineitem.h"

class LineItem: public GraphicsItem {
public:
    LineItem();
    LineItem(const LineItem &other) {}
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
        this->m_vertexPair[index].point = vertex.point - this->scenePos();
        this->m_vertexPair[index].angle = vertex.angle;
        animate();
        return true;
    }
    bool setCenterInScene(const QPointF point) override {
        QPointF currentCenter = this->getCenterInScene();
        QPointF offset = point - currentCenter;
        this->setPos(this->pos() + offset);
        this->animate();
        return true;
    }
    bool rotate(const double angle) override {
        return true;    // TODO
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
    std::vector < std::shared_ptr < GraphicsItem>> breakOffsetItem() override {
        // 获取当前最新的copiedItem
        this->animate();
        // 设置Params为空
        m_offsetParams.offset = 0;
        m_offsetParams.offsetCount = 0;
        //获取当前offsetItem  如果没有offsetItem就返回空数组
        std::vector < std::shared_ptr < GraphicsItem>> result;
        result.reserve(this->m_offsetItemList.size());
        for (auto &&item : std::move(this->m_offsetItemList)) {
            item->setPos(this->pos()); // 把位置也更新了; 作为offsetItem是不会保存这个数据的
            result.emplace_back(std::move(item));
        }
        m_offsetItemList.clear();
        return result;
    };
protected:
    bool updateParallelOffsetItem() override {
        //
        if (this->m_offsetParams.offset == 0 || this->m_offsetParams.offsetCount == 0) {
            return true;
        }
        this->m_offsetItemList.clear();
        for (int offsetIndex = 1; offsetIndex <= this->m_offsetParams.offsetCount; offsetIndex++) {
            // 输入cavc库
            cavc::Polyline < double > input = this->getCavcForm(false);
            input.isClosed() = false;
            std::vector < cavc::Polyline < double>> results = cavc::parallelOffset(input, this->m_offsetParams.offset * offsetIndex);
            // 获取结果
            for (const auto& polyline : results) {
                auto item = FromCavcForm(polyline);
                this->m_offsetItemList.push_back(std::move(item));
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
    QRectF getBoundingRectBasis() const override {
        if (!this->m_paintItem) {
            return QRectF();
        }
        QRectF newRect = m_paintItem->boundingRect();
        return newRect;
    }
public:
    cavc::Polyline < double > getCavcForm(bool inSceneCoord) const override {
        // 输入cavc库
        cavc::Polyline < double > input;
        QPointF p1, p2;
        if (inSceneCoord) {
            p1 = this->getVertexInScene(0).point;
            p2 = this->getVertexInScene(1).point;
        } else {
            p1 = m_vertexPair[0].point;
            p2 = m_vertexPair[1].point;
        }
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
        QPointF pos = point + this->scenePos();
        return Vertex{pos, angle};
    }
    QPointF getCenterInScene() const override {
        auto center = QPointF{};
        center = (m_vertexPair[0].point + m_vertexPair[1].point) / 2;
        auto posOffset = this->pos();
        return center + posOffset;
    }
    QString getName() const override {
        return "LineItem";
    }
    uint getVertexCount() const override {
        return 2;
    }
    std::vector<LaserDeviceCommand> getRTC5Command() const override
    {
        auto commandList = GraphicsItem::getRTC5Command();
        auto repeatTime = this->getMarkParams().repetTime;

        const auto &p0 = m_vertexPair[0];
        const auto &p1 = m_vertexPair[1];
        long startPosX = static_cast<long>(p0.point.x());
        long startPosY =static_cast<long>(p0.point.y());
        long endPosX = static_cast<long>(p1.point.x());
        long endPosY =static_cast<long>(p1.point.y());

        for (int i = 0; i < repeatTime; i++) {
            commandList.emplace_back(JumpCommand{startPosX,startPosY});
            commandList.emplace_back(MarkCommand{endPosX,endPosY});
        }
        return commandList;
    }

public:
    int type() const override {
        return GraphicsItemType::Line;
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
        // 绘制顶点
        // painter->setPen(Qt::NoPen);
        // painter->setBrush(Qt::red);
        // for (const auto &vertex : m_vertexPair) {
        //     if (this->m_offsetParams.offsetCount > 0) {
        //         painter->setBrush(Qt::red);
        //         painter->drawEllipse(vertex.point, DisplayPointSize.first, DisplayPointSize.second);
        //     } else {
        //         painter->setBrush(Qt::blue);
        //         painter->drawEllipse(vertex.point, DisplayPointSize.first, DisplayPointSize.second);
        //     }
        // }
        // 绘制offset
        for (auto &item : this->m_offsetItemList) {
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
    std::vector < std::shared_ptr < PolylineItem>> m_offsetItemList;
    std::vector < std::shared_ptr < LineItem>> m_copiedItemList;
};

#endif // LINEITEM_H
