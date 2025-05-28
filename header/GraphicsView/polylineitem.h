#ifndef POLYLINEITEM_H
#define POLYLINEITEM_H

#include "graphicsitem.h"
#include "logger.h"
#include "utils.hpp"
#include <polylineoffset.hpp>
#include <vector.hpp>
#include <QJsonArray>

class PolylineItem: public GraphicsItem {
public:
    PolylineItem() {};
    std::shared_ptr < GraphicsItem > clone() const override  {
        auto item = std::make_shared < PolylineItem > ();
        item->cloneBaseParams(*this);
        item->m_vertexList = this->m_vertexList;
        item->animate();
        return item;
    }
    std::shared_ptr < GraphicsItem > createFromJson(QJsonObject obj) override {
        auto item = std::make_shared < PolylineItem > ();
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
    bool addVertex(const QPointF point, const double angle) {
        Vertex newVertex = {point, angle};
        m_vertexList.push_back(newVertex);
        animate();
        return true;
    }
    bool setVertexInScene(const int index, const Vertex vertex) override {
        QPointF pos = vertex.point - this->scenePos();
        m_vertexList[index] = Vertex{pos, vertex.angle};
        animate();
        return true;
    }
    bool deleteVetex(const int index) {
        m_vertexList.erase(m_vertexList.begin() + index);
        animate();
        return true;
    }
    bool setCenterInScene(const QPointF point) override {
        DEBUG_MSG("use polyline setCenterInScene");
        QPointF currentCenter = this->getCenterInScene();
        QPointF offset = point - currentCenter;
        DEBUG_VAR(point);
        QString msg = QString("curCenter: (%1, %2), offset: (%3, %4), this->pos: (%5, %6)")
                      .arg(currentCenter.x(), 0, 'f', 2)
                      .arg(currentCenter.y(), 0, 'f', 2)
                      .arg(offset.x(), 0, 'f', 2)
                      .arg(offset.y(), 0, 'f', 2)
                      .arg(this->pos().x(), 0, 'f', 2)
                      .arg(this->pos().y(), 0, 'f', 2);
        DEBUG_MSG(msg);
        this->setPos(this->pos() + offset);
        this->animate();
        return true;
    };
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
    bool updateContourFillItem() override;
    bool updatePaintItem() override {
        if (m_vertexList.size() < 2) {
            return false;
        }
        // 这里实时把vertexlist里的点信息更新到itemlist里；然后paint函数会绘制itemlist里的东西
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
            QPointF unitOffset = this->m_vectorCopyParams.dir * this->m_vectorCopyParams.spacing;
            for (int i = 1; i <= this->m_vectorCopyParams.count; ++i) {
                // DEBUG_VAR(this->getUUID());
                auto copiedItem = std::dynamic_pointer_cast < PolylineItem > (this->clone());
                QPointF offset = unitOffset * i;
                int count = this->getVertexCount();
                for (int i = 0; i < count; ++i) {
                    copiedItem->m_vertexList[i].point += offset;
                }
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
                auto copiedItem = std::dynamic_pointer_cast < PolylineItem > (this->clone());
                if (!copiedItem) {
                    return;
                }
                QPointF offset = offsetMatrix[row][col];
                int count = this->getVertexCount();
                for (int i = 0; i < count; ++i) {
                    copiedItem->m_vertexList[i].point += offset;
                }
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
            // DEBUG_VAR(QString("V%1: (%2, %3), angle=%4")
            //           .arg(i).arg(p1.x ()).arg(p1.y ()).arg(angle));
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
                // DEBUG_VAR(intersectPoint.x());
                // DEBUG_VAR(intersectPoint.y());
                // DEBUG_VAR(newAngle);
            } else {
                double bulge = 0;
                getBulgeFromAngle(angle, bulge);
                input.addVertex(p1.x(), p1.y(), bulge *  (-1));
            }
        }
        // 输出的结果我们的格式是没有ClosedForm的, 不会和cavc一样,设置isClosed的时候使用闭合bulge连接第一个点,而是默认全是开放的;
        // 如果直接输入我们自己的格式时, 最后一个点和第一个点一致说明闭合, 但是cavc会自动闭合这连个点, 就会认为这里时零向量报错;
        // 所以这里需要转换一下, 如果最后一个点和第一个点是一致的, 就说明这个图形是封闭的, 就把最后一个点删了
        if (this->m_vertexList[0].point == this->m_vertexList[count - 1].point) {
            auto &verts = input.vertexes();
            if (!verts.empty()) {
                verts.pop_back(); // 删除最后一个点
            }
        }
        ///********************************************
        /// DEBUG
        // for (std::size_t i = 0; i < input.size(); ++i) {
        //     const auto& v = input[i];
        //     double x = v.x ();
        //     double y = v.y ();
        //     double bulge = v.bulge();
        //     DEBUG_VAR(QString("V%1: (%2, %3), bulge=%4")
        //               .arg(i).arg(x).arg(y).arg(bulge));
        // }
        /// DEBUG
        ///********************************************
        return input;
    }
    Vertex getVertexInScene(const int index) const override;
    QPointF getCenterInScene() const override;
    QString getName() const override;
    int type() const override {
        return GraphicsItemType::Polyline;
    }
    uint getVertexCount() const override;
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
    std::vector<LaserDeviceCommand> getRTC5Command() const override
    {
        auto commandList = GraphicsItem::getRTC5Command();
        auto operateTime = this->getMarkParams().operateTime;

        for (int operateIndex = 0; operateIndex < operateTime; operateIndex++) {
            // 先打本体 遍历每个点;
            int count = this->getVertexCount();
            for (int i = 0; i < count - 1; ++i) {
                QPointF p1, p2;
                p1 = this->getVertexInScene(i).point;
                p2 = this->getVertexInScene(i + 1).point;
                auto angle = this->m_vertexList[i + 1].angle;

                if (i==0) { // 打第一个点的时候jump; 后面默认是连续 就不用jump
                    commandList.emplace_back(JumpCommand{p1.x (),p1.y ()});
                }
                if (angle != 0){// 是圆弧
                    QPointF center;double radius;
                    getCircleFromTwoPointsAndAngle (p1,p2,angle,center,radius);
                    commandList.emplace_back(ArcCommand{center.x (), center.y (), (-1)*angle}); //如果再前面就修改angle 那么计算的圆心是错的
                } else { // 是直线
                    commandList.emplace_back(MarkCommand{p2.x (), p2.y ()});
                }
            }
            // TODO 再打copyitem/contourfill/hatchfill
        }
        return commandList;
    }

public:
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
    std::vector < Vertex > m_vertexList;
    std::vector < std::shared_ptr < QGraphicsItem>> m_paintItemList;
    std::vector < std::shared_ptr < PolylineItem>> m_contourFillItemList;
    std::vector < std::shared_ptr < PolylineItem>> m_copiedItemList;
    std::vector < std::shared_ptr < PolylineItem>> m_hatchFillItemList;
};

inline std::shared_ptr < PolylineItem > FromCavcForm(cavc::Polyline < double > polyline) {
    auto item = std::make_shared < PolylineItem > ();
    // item->LineType = LineType::offsetItem;
    for (size_t i = 0; i < polyline.size(); ++i) {
        auto newPoint = QPointF(polyline.vertexes()[i].x(), polyline.vertexes()[i].y());
        auto newBulge = (i > 0) ? polyline.vertexes()[i - 1].bulge()
                        : polyline.vertexes()[polyline.size() - 1].bulge();
        double newAngle = 0;
        getAngleFromBulge(newBulge * (-1), newAngle);
        item->addVertex(newPoint, newAngle);
    }
    if (polyline.isClosed()) {
        auto newPoint = QPointF(polyline.vertexes()[0].x(), polyline.vertexes()[0].y());
        auto idx = polyline.size() - 1;
        auto newBulge = polyline.vertexes()[idx].bulge();
        double newAngle = 0;
        getAngleFromBulge(newBulge * (-1), newAngle);
        item->addVertex(newPoint, newAngle);
    }
    return item;
}

#endif // POLYLINEITEM_H
