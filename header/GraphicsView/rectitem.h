#ifndef RECTITEM_H
#define RECTITEM_H

#include "protocol.h"
#include "graphicsitem.h"
#include "logger.h"
#include "polylineitem.h"
#include <QJsonArray>

class RectItem : public GraphicsItem {
public:
    RectItem() {};
    std::shared_ptr < GraphicsItem > clone() const  override {
        auto item = std::make_shared < RectItem > ();
        item->cloneBaseParams(*this);
        item->m_vertexList = this->m_vertexList;
        item->animate();
        return item;
    }
    std::shared_ptr < GraphicsItem > createFromJson(QJsonObject obj) override {
        auto item = std::make_shared < RectItem > ();
        item->cloneBaseParamsFromJson(obj);
        // 加载 vertexList
        if (obj.contains("vertexList")) {
            QJsonArray vertexArray = obj["vertexList"].toArray();
            item->m_vertexList.clear();
            for (const auto &val : vertexArray) {
                QJsonObject v = val.toObject();
                Vertex vert;
                vert.point = QPointF(v["x"].toDouble(), v["y"].toDouble());
                vert.angle = v["angle"].toDouble();
                item->m_vertexList.push_back(vert);
            }
        }
        item->animate();
        return item;
    }
    QJsonObject saveToJson() const override {
        QJsonObject obj = saveBaseParamsToJson();
        obj["type"] = getName();
        // 保存 vertexList
        QJsonArray vertexArray;
        for (const auto &v : m_vertexList) {
            QJsonObject vert;
            vert["x"] = v.point.x();
            vert["y"] = v.point.y();
            vert["angle"] = v.angle;
            vertexArray.append(vert);
        }
        obj["vertexList"] = vertexArray;
        return obj;
    }

public:
    /// 编辑vertex; 0是左上坐标,2是右下坐标: 0,1,2,3,4
    bool setVertexInScene(const int index, const Vertex vertex) override {
        if (index > 4) {
            return false;
        }
        this->m_vertexList[index].point = vertex.point;
        this->m_vertexList[index].angle = vertex.angle;
        animate();
        return true;
    }
    bool setCenterInScene(const QPointF point) override {
        QPointF currentCenter = this->getCenterInScene();
        QPointF offset = point - currentCenter;
        for (auto &vertex : this->m_vertexList) {
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
        //
        if (this->m_contourFillParams.offset == 0 || this->m_contourFillParams.offsetCount == 0) {
            return true;
        }
        this->m_contourFillItemList.clear();
        for (int offsetIndex = 1; offsetIndex <= this->m_contourFillParams.offsetCount; offsetIndex++) {
            // 输入cavc库
            cavc::Polyline < double > input = this->getCavcForm(false);
            input.isClosed() = true;
            std::vector < cavc::Polyline < double>> results = cavc::parallelOffset(input, (-1)*this->m_contourFillParams.offset * offsetIndex);
            // 获取结果
            for (const auto& polyline : results) {
                auto item = FromCavcForm(polyline);
                item->setColor(this->getColor());
                this->m_contourFillItemList.push_back(std::move(item));
            }
        }
        return true;
    }
    bool updatePaintItem() override {
        m_paintItemList.clear();
        for (size_t i = 0; i < m_vertexList.size() - 1; ++i) {
            QPointF v1 = m_vertexList[i].point;
            QPointF v2 = m_vertexList[i + 1].point;
            double angle = m_vertexList[i + 1].angle;
            if (std::abs(angle) < 1e-20) {
                auto lineItem = std::make_shared < QGraphicsLineItem > (
                                    QLineF(v1, v2)
                                );
                lineItem->setPen(this->getPen());
                m_paintItemList.push_back(std::move(lineItem));
            } else {
                QPainterPath arcPath = createArcPath(v1, v2, angle);
                auto pathItem = std::make_shared < QGraphicsPathItem > (arcPath);
                pathItem->setPen(this->getPen());
                m_paintItemList.push_back(std::move(pathItem));
            }
        }
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
                auto copiedItem = std::dynamic_pointer_cast < RectItem > (this->clone());
                QPointF offset = unitOffset * i;
                copiedItem->m_vertexList[0].point += offset;
                copiedItem->m_vertexList[1].point += offset;
                copiedItem->m_vertexList[2].point += offset;
                copiedItem->m_vertexList[3].point += offset;
                copiedItem->m_vertexList[4].point += offset;
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
                auto copiedItem = std::dynamic_pointer_cast < RectItem > (this->clone());
                if (!copiedItem) {
                    return;
                }
                QPointF offset = offsetMatrix[row][col];
                copiedItem->m_vertexList[0].point += offset;
                copiedItem->m_vertexList[1].point += offset;
                copiedItem->m_vertexList[2].point += offset;
                copiedItem->m_vertexList[3].point += offset;
                copiedItem->m_vertexList[4].point += offset;
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

public:
    cavc::Polyline < double > getCavcForm(bool inSceneCoord) const override {
        cavc::Polyline < double > input;
        int count = this->getVertexCount();
        for (int i = 0; i < count; ++i) {
            QPointF p1, p2;
            if (inSceneCoord) {
                p1 = this->getVertexInScene(i).point;
                p2 = this->getVertexInScene((i + 1) % count).point;
            } else {
                p1 = this->m_vertexList[i].point;
                p2 = this->m_vertexList[(i + 1) % count].point;
            }
            auto angle = this->m_vertexList[(i + 1) % count].angle;
            if (angle > 180.01 || angle < -180.01) {
                auto sign = angle > 0 ? 1 : -1;
                input.addVertex(p1.x(), p1.y(), sign * (-1)); /*先走180度*/
                QPointF intersectPoint = QPointF{};
                double newAngle = 0;
                double newBulge = 0;
                getIntersectPoint(p1, p2, angle, 180, intersectPoint);
                newAngle = angle - sign * 180;
                getBulgeFromAngle(newAngle, newBulge);
                input.addVertex(intersectPoint.x(), intersectPoint.y(), newBulge *  (-1));
            } else {
                double bulge = 0;
                getBulgeFromAngle(angle, bulge);
                input.addVertex(p1.x(), p1.y(), bulge *  (-1));
            }
        }
        if (this->m_vertexList[0].point == this->m_vertexList[count - 1].point) {
            auto &verts = input.vertexes();
            if (!verts.empty()) {
                verts.pop_back(); // 删除最后一个点
            }
        }
        return input;
    }
    Vertex getVertexInScene(const int index) const override {
        if (index > 4) {
            assert("false index:only 0,1,2,3,4");
        }
        QPointF point = m_vertexList[index].point;
        double angle = m_vertexList[index].angle;
        return Vertex{point, angle};
    }
    QPointF getCenterInScene() const override {
        auto rect = getBoundingRectBasis();
        QPointF pos = rect.center();
        return pos;
    }
    QString getName() const override {
        return "RectItem";
    }
    int type() const override {
        return GraphicsItemType::Rect;
    }
    uint getVertexCount() const override {
        return 5;
    }
    QRectF getBoundingRectBasis() const override {
        if (this->m_paintItemList.empty()) {
            return QRectF();
        }
        QRectF newRect = m_paintItemList[0]->boundingRect();
        for (auto& item : this->m_paintItemList) {
            qreal minX = std::min(newRect.left(), item->boundingRect().left());
            qreal minY = std::min(newRect.top(), item->boundingRect().top());
            qreal maxX = std::max(newRect.right(), item->boundingRect().right());
            qreal maxY = std::max(newRect.bottom(), item->boundingRect().bottom());
            newRect = QRectF(QPointF(minX, minY), QPointF(maxX, maxY));
        }
        return newRect;
    }
    std::vector<LaserDeviceCommand> getLaserCommand() override{
        return std::vector<LaserDeviceCommand>();
    }
    std::vector<std::shared_ptr<QGraphicsItem>> getPaintItemList() override
    {
        this->animate();
        std::vector<std::shared_ptr<QGraphicsItem>> list = m_paintItemList;
        list.insert(list.end(), m_contourFillItemList.begin(), m_contourFillItemList.end());
        list.insert(list.end(), m_copiedItemList.begin(), m_copiedItemList.end());
        list.insert(list.end(), m_hatchFillItemList.begin(), m_hatchFillItemList.end());
        return list;
    }

protected:
    QRectF boundingRect() const override {
        if (this->m_paintItemList.empty()) {
            return QRectF();
        }
        QRectF newRect = m_paintItemList[0]->boundingRect();
        for (auto &item : this->m_paintItemList) {
            qreal minX = std::min(newRect.left(), item->boundingRect().left());
            qreal minY = std::min(newRect.top(), item->boundingRect().top());
            qreal maxX = std::max(newRect.right(), item->boundingRect().right());
            qreal maxY = std::max(newRect.bottom(), item->boundingRect().bottom());
            newRect = QRectF(QPointF(minX, minY), QPointF(maxX, maxY));
        }
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
        for (auto &item : this->m_paintItemList) {
            item->paint(painter, &optionx, widget);
        }
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
    std::vector < Vertex > m_vertexList = {
        Vertex{QPointF(0, 0), 0},
        Vertex{QPointF(100, 0), 0},
        Vertex{QPointF(100, 100), 0},
        Vertex{QPointF(0, 100), 0},
        Vertex{QPointF(0, 0), 0},
    };
    std::vector < std::shared_ptr < QGraphicsItem>> m_paintItemList;
    std::vector < std::shared_ptr < PolylineItem>> m_contourFillItemList;
    std::vector < std::shared_ptr < RectItem>> m_copiedItemList;
    std::vector < std::shared_ptr < PolylineItem>> m_hatchFillItemList;
};
#endif // RECTITEM_H
