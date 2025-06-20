#ifndef POLYGONITEM_H
#define POLYGONITEM_H

#include "graphicsitem.h"
#include "logger.h"
#include "polylineitem.h"
#include "protocol.h"
#include "combineditem.h"

class PolygonItem : public GraphicsItem {
public:
    PolygonItem() {};
    std::shared_ptr < GraphicsItem > clone() const override {
        auto item = std::make_shared < PolygonItem > ();
        item->cloneBaseParams(*this);
        item->m_center = this->m_center;
        item->m_edgeCount = this->m_edgeCount;
        item->m_radius = this->m_radius;
        item->m_rotateAngle = this->m_rotateAngle;
        item->animate();
        return item;
    }
    std::shared_ptr < GraphicsItem > createFromJson(QJsonObject obj) override {
        auto item = std::make_shared < PolygonItem > ();
        // 加载基类参数
        item->cloneBaseParamsFromJson(obj);
        //
        QJsonObject center = obj["center"].toObject();
        item->m_center.point = QPointF(center["x"].toDouble(), center["y"].toDouble());
        item->m_center.angle = center["angle"].toDouble();
        //
        item->m_radius = obj["radius"].toDouble();
        item->m_edgeCount = static_cast < uint > (obj["edgeCount"].toInt());
        item->m_rotateAngle = obj["rotateAngle"].toDouble();
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
        obj["edgeCount"] = static_cast < int > (m_edgeCount);
        obj["rotateAngle"] = m_rotateAngle;
        return obj;
    }

public:
    bool setVertexInScene(const int index, const Vertex vertex) override { /*编辑中心*/
        if (index > 1) {
            WARN_VAR(index);
            return false;
        }
        QPointF pos = vertex.point;
        this->m_center = Vertex{pos, 0};
        animate();
        return true;
    }
    bool setRadius(const double radius) { /*编辑半径*/
        if (radius < 0) {
            return false;
        }
        this->m_radius = radius;
        animate();
        return true;
    }
    bool setEdgeCount(uint count) {
        if (count < 3) {
            return false;
        }
        m_edgeCount = count;
        animate();
        return true;
    }
    bool setRotateAngle(double angle) {
        if (angle < 0.0 || angle >= 360.0) {
            return false;
        }
        m_rotateAngle = angle;
        animate();
        return true;
    }
    bool setCenterInScene(const QPointF point) override {
        QPointF currentCenter = this->getCenterInScene();
        QPointF offset = point - currentCenter;
        this->m_center.point = this->m_center.point + offset;
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
    std::vector < std::shared_ptr < GraphicsItem>> breakHatchFillItem() override {
        // DEBUG_MSG("break hatch");
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
        // DEBUG_VAR(result.size ());
        this->m_hatchFillParams.startAngle = startAngle;
        this->m_hatchFillParams.operateCount = 0;
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
            cavc::Polyline < double > input = this->getCavcForm();
            input.isClosed() = true;
            std::vector < cavc::Polyline < double>> results
                = cavc::parallelOffset(input, this->m_contourFillParams.offset * offsetIndex);
            // 获取结果
            for (const auto &polyline : results) {
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
        this->m_paintItem = std::make_shared < QGraphicsPathItem > ();
        QPainterPath path;
        if (m_edgeCount < 3 || m_radius <= 0) {
            return false; // 无效参数
        }
        const double angleStep = 2 * M_PI / m_edgeCount;
        const double rotateRad = m_rotateAngle * M_PI / 180.0; // 角度转弧度
        const QPointF center = m_center.point;
        // 起始点
        QPointF firstPoint = center
                             + QPointF(std::cos(rotateRad) * m_radius,
                                       std::sin(rotateRad) * m_radius);
        path.moveTo(firstPoint);
        for (uint i = 1; i < m_edgeCount; ++i) {
            double angle = rotateRad + angleStep * i;
            QPointF p = center + QPointF(std::cos(angle) * m_radius, std::sin(angle) * m_radius);
            path.lineTo(p);
        }
        path.closeSubpath();
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
                auto copiedItem = std::dynamic_pointer_cast < PolygonItem > (this->clone());
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
                auto copiedItem = std::dynamic_pointer_cast < PolygonItem > (this->clone());
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

public:
    cavc::Polyline < double > getCavcForm() const override {
        cavc::Polyline < double > polyline;
        if (m_edgeCount < 3 || m_radius <= 0) {
            return polyline;
        }
        const double angleStep = 2 * M_PI / m_edgeCount;
        const double rotateRad = m_rotateAngle * M_PI / 180.0;
        QPointF center =  m_center.point;
        for (uint i = 0; i < m_edgeCount; ++i) {
            double angle = rotateRad + angleStep * i;
            QPointF p = center + QPointF(std::cos(angle) * m_radius, std::sin(angle) * m_radius);
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
    QString getName() const override {
        return "PolygonItem";
    }
    int type() const override {
        return GraphicsItemType::Polygon;
    }
    double getRadius() {
        return this->m_radius;
    }
    uint getEdgeCount() {
        return this->m_edgeCount;
    }
    uint getVertexCount() const override {
        return 1;
    }
    double getRotateAngle() const {
        return m_rotateAngle;
    }
    QRectF getBoundingRectBasis() const override {
        QPointF center = this->m_center.point;
        double radius = this->m_radius;

        QRectF newRect(center.x() - radius,
                       center.y() - radius,
                       2 * radius,
                       2 * radius);
        return newRect;
    }
    std::vector<LaserDeviceCommand> getLaserCommand() override{
        this->animate ();
        auto commandList = GraphicsItem::getLaserCommand();
        auto repeatTime = this->getMarkParams().operateTime;

        const double angleStep = 2 * M_PI / m_edgeCount;
        const double rotateRad = m_rotateAngle * M_PI / 180.0;
        const QPointF center = m_center.point;
        std::vector<QPointF> points;
        for (uint i = 0; i < m_edgeCount; ++i) {
            double angle = rotateRad + angleStep * i;
            QPointF p = center + QPointF(std::cos(angle) * m_radius,
                                         std::sin(angle) * m_radius);
            points.push_back(p);
        }

        for (int i = 0; i < repeatTime; i++) {
            // 打印自身Item
            commandList.emplace_back(JumpCommand{points[0].x(), points[0].y()});
            for (size_t i = 1; i < points.size(); ++i) {
                commandList.emplace_back(MarkCommand{points[i].x(), points[i].y()});
            }
            commandList.emplace_back(MarkCommand{points[0].x(), points[0].y()});
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
        QRectF newRect = this->getBoundingRectBasis ();
        // 包含offsetItem
        newRect = newRect.adjusted(
                      -abs(this->m_contourFillParams.offset) * this->m_contourFillParams.offsetCount ,
                      -abs(this->m_contourFillParams.offset) * this->m_contourFillParams.offsetCount ,
                      abs(this->m_contourFillParams.offset) * this->m_contourFillParams.offsetCount ,
                      abs(this->m_contourFillParams.offset) * this->m_contourFillParams.offsetCount );
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
    uint m_edgeCount = 3;
    double m_rotateAngle = 0;
    //
    std::shared_ptr < QGraphicsPathItem > m_paintItem;
    std::vector < std::shared_ptr < PolylineItem>> m_contourFillItemList;
    std::vector < std::shared_ptr < PolygonItem>> m_copiedItemList;
    std::vector < std::shared_ptr < PolylineItem>> m_hatchFillItemList;
};
#endif // POLYGONITEM_H
