#ifndef POINTITEM_H
#define POINTITEM_H

#include "protocol.h"
#include "graphicsitem.h"
#include "logger.h"
#include "polylineitem.h"

const std::pair < double, double > DisplayPointSize = std::pair < double, double > {0.1, 0.1}; /*标准点在x、y方向上的半径*/
const std::pair < double, double > EditPointSize = std::pair < double, double > {1, 1};

class PointItem: public GraphicsItem {
public:
    PointItem() {}
    std::shared_ptr < GraphicsItem > clone() const override {
        auto item = std::make_shared < PointItem > ();
        item->cloneBaseParams(*this);
        item->m_vertex = this->m_vertex;
        item->animate();
        return item;
    }
    std::shared_ptr < GraphicsItem > createFromJson(QJsonObject obj) override {
        auto item = std::make_shared < PointItem > ();
        // 加载基类参数
        item->cloneBaseParamsFromJson(obj);
        if (obj.contains("v0") && obj.contains("v1")) {
            QJsonObject v0 = obj["v0"].toObject();
            item->m_vertex.point = QPointF(v0["x"].toDouble(), v0["y"].toDouble());
            item->m_vertex.angle = v0["angle"].toDouble();
        }
        item->animate();
        return item;
    }
    QJsonObject saveToJson() const override {
        // 保存基类参数
        QJsonObject obj = saveBaseParamsToJson();
        // 保存子类参数 m_vertexPair
        obj["type"] = getName();
        QJsonObject v0;
        v0["x"] = m_vertex.point.x ();
        v0["y"] = m_vertex.point.y();
        v0["angle"] = m_vertex.angle;
        obj["v0"] = v0;
        return obj;
    }

public:
    bool setVertexInScene(const int index, const Vertex vertex) override {
        if (index >= 1) {
            WARN_MSG("index can only be 0 for point");
            return false;
        }
        this->m_vertex.point = vertex.point;
        this->m_vertex.angle = vertex.angle;
        animate();
        return true;
    }
    bool setCenterInScene(const QPointF point) override {
        QPointF currentCenter = this->getCenterInScene();
        QPointF offset = point - currentCenter;
        this->m_vertex.point = this->m_vertex.point + offset;
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
        return true;
    }
    bool updatePaintItem() override {
        // 这里判断是不是为编辑模式 如果是的话就画一个大一点的圆
        auto pointSize = DisplayPointSize;
        if (m_isEditMode) {
            pointSize = EditPointSize;
        }
        // 这里实时把vertexlist里的点信息更新到itemlist里；然后paint函数会绘制itemlist里的东西
        this->m_paintItem = nullptr;
        this->m_paintItem = std::make_shared < QGraphicsEllipseItem > ();
        double rx = pointSize.first;
        double ry = pointSize.second;
        this->m_paintItem->setRect(QRectF(
                                       m_vertex.point.x() - rx,
                                       m_vertex.point.y() - ry,
                                       rx * 2,
                                       ry * 2));
        this->m_paintItem->setBrush(QBrush(Qt::red));
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
                auto copiedItem = std::dynamic_pointer_cast < PointItem > (this->clone());
                QPointF offset = unitOffset * i;
                copiedItem->m_vertex.point += offset;
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
                auto copiedItem = std::dynamic_pointer_cast < PointItem > (this->clone());
                if (!copiedItem) {
                    return;
                }
                QPointF offset = offsetMatrix[row][col];
                copiedItem->m_vertex.point += offset;
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
    bool updateHatchFillItem() override {return true;};

public:
    cavc::Polyline < double > getCavcForm(bool inSceneCoord) const override {
        return cavc::Polyline < double > ();
    }
    Vertex getVertexInScene(const int index) const override {
        if (index > 1) {
            WARN_MSG("false index:only 0");
        }
        QPointF point = m_vertex.point;
        double angle = m_vertex.angle;
        return Vertex{point, angle};
    }
    QPointF getCenterInScene() const override {
        auto center = QPointF{};
        center = m_vertex.point;
        return center;
    }
    QString getName() const override {
        return "PointItem";
    }
    int type() const override {
        return GraphicsItemType::Point;
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
    std::vector<LaserDeviceCommand> getRTC5Command() const override{
        return std::vector<LaserDeviceCommand>();
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
        // 绘制圆点
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
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override {
        // 先执行父类
        QVariant result = GraphicsItem::itemChange(change, value);
        // 再执行自己的重载
        if (change == QGraphicsItem::ItemSelectedHasChanged) {
            bool selected = value.toBool();
            if (selected) {
                m_isEditMode = true;
            } else {
                m_isEditMode = false;
            }
            animate ();
        }
        return result;
    }
private:
    Vertex m_vertex = Vertex{QPointF{0, 0}, 0};
    bool m_isEditMode = false;

    std::shared_ptr < QGraphicsEllipseItem > m_paintItem;
    std::vector < std::shared_ptr < PointItem>> m_contourFillItemList;
    std::vector < std::shared_ptr < PointItem>> m_copiedItemList;
    std::vector < std::shared_ptr < PolylineItem>> m_hatchFillItemList;
};

#endif // POINTITEM_H
