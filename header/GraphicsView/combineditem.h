#ifndef COMBINEDITEM_H
#define COMBINEDITEM_H

#include "graphicsitem.h"
#include "logger.h"
#include "utils.hpp"
#include <polylineoffset.hpp>
#include <vector.hpp>

class CombinedItem : public GraphicsItem {
public:
    CombinedItem() {}
    std::shared_ptr<GraphicsItem> clone() const override
    {
        // auto item = std::make_shared<CombinedItem>();
        // // 拷贝基类字段
        // item->cloneBaseParams(*this);
        // item->animate();
        // return item;
    }
    std::shared_ptr<GraphicsItem> createFromJson(QJsonObject obj) override
    {
        // return std::make_shared<CombinedItem>();
    }
    QJsonObject saveToJson() const override { /*return QJsonObject{}; */}

public:
    // 功能是设置第n个item的中心的位置
    bool setVertexInScene(const int index, const Vertex vertex) override
    {
        this->m_itemList[index]->setCenterInScene(vertex.point);
        this->animate();
        return true;
    }
    // 功能是设置整体combinedItem的中心位置
    bool setCenterInScene(const QPointF point) override
    {
        QPointF combinedCenter = this->getCenterInScene();
        QPointF offset = point - combinedCenter;

        for (auto &item: this->m_itemList){
            auto center = item->getCenterInScene ();
            item->setCenterInScene (center + offset);
        }
        this->animate();
        return true;
    }
    // deprecated
    std::vector<std::shared_ptr<GraphicsItem>> breakCopiedItem() override
    {
        return std::vector<std::shared_ptr<GraphicsItem>>();
    }
    std::vector<std::shared_ptr<GraphicsItem>> breakParallelFillItem() override
    {
        return std::vector<std::shared_ptr<GraphicsItem>>();
    };
    // 添加item/解散item
    bool combinedItem(std::vector<std::shared_ptr<GraphicsItem>> itemList)
    {
        this->m_itemList = itemList;
        return true;
    }
    std::vector<std::shared_ptr<GraphicsItem>> breakItem()
    {
        auto itemList = this->m_itemList;
        this->m_itemList.clear();
        return itemList;
    }

protected:
    bool updatePaintItem() override
    {
        this->m_paintItemList.clear();
        for (auto &item : this->m_itemList) {
            // 设置颜色要调用外部接口
            item->setColor(this->getColor());
            // 获取paintItem使用接口
            auto sList = item->getPaintItemList();
            this->m_paintItemList.insert(this->m_paintItemList.end(), sList.begin(), sList.end());
        }
        return true;
    }
    // deprecated
    bool updateContourFillItem() override { return true; };
    bool updateCopiedItem() override { return true; }
    bool updateHatchFillItem() override { return true; };

public:
    cavc::Polyline<double> getCavcForm(bool inSceneCoord) const override
    {
        return cavc::Polyline<double>();
    }
    // 获得第n个item的位置
    Vertex getVertexInScene(const int index) const override
    {
        auto center = this->m_itemList[index]->getCenterInScene();
        return Vertex{center, 0};
    }
    QPointF getCenterInScene() const override
    {
        auto rect = getBoundingRectBasis();
        QPointF pos = rect.center();
        return pos;
    }
    QString getName() const override { return "CombinedItem"; }
    int type() const override { return GraphicsItemType::Combined; }
    uint getVertexCount() const override { return m_itemList.size(); }
    QRectF getBoundingRectBasis() const override
    {
        // 用于给editRect使用的绘制编辑边框的(也就是不考虑额外的复制/填充线段, 对象本体的rect)
        if (this->m_itemList.empty()) {
            return QRectF();
        }
        QRectF newRect;
        for (const auto &item : m_itemList) {
            newRect = newRect.united(item->getBoundingRectBasis());
        }
        return newRect;
    }
    std::vector<LaserDeviceCommand> getLaserCommand() override
    {
        std::vector<LaserDeviceCommand> commandList;
        auto repeatTime = this->getMarkParams().operateTime;

        for (int i = 0; i < repeatTime; i++) {
            for (auto &item: this->m_itemList){
                auto cmd=item->getLaserCommand ();
                commandList.insert (commandList.end (),cmd.begin(),cmd.end ());
            }
        }
        return commandList;
    }

protected:
    QRectF boundingRect() const override
    {
        if (this->m_itemList.empty()) {
            return QRectF();
        }
        QRectF newRect;
        for (const auto &item : m_itemList) {
            newRect = newRect.united(item->boundingRect());
        }
        return newRect;
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
    {
        Q_UNUSED(widget);
        // 设置option删去线段的选框
        QStyleOptionGraphicsItem optionx(*option);
        optionx.state &= ~QStyle::State_Selected;
        // 绘制包含的线段对象
        for (auto &item : this->m_paintItemList) {
            item->paint(painter, &optionx, widget);
        }
    }

private:
    std::vector<std::shared_ptr<GraphicsItem>> m_itemList;
    std::vector<std::shared_ptr<QGraphicsItem>> m_paintItemList;
};

#endif // COMBINEDITEM_H
