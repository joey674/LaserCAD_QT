#ifndef COMBINEDITEM_H
#define COMBINEDITEM_H

#include "graphicsitem.h"
#include "logger.h"
#include "utils.hpp"
#include <polylineoffset.hpp>
#include <vector.hpp>

class CombinedItem : public GraphicsItem {
public:
    CombinedItem() {};
    std::shared_ptr < GraphicsItem > clone() const override {
        auto item = std::make_shared < CombinedItem > ();
        item->initFrom(*this);
        item->m_itemList = this->m_itemList;
        item->animate();
        return item;
    }

public:
    bool combinedItem(std::vector < std::shared_ptr < GraphicsItem>> itemList) {
        this->m_itemList = itemList;
        return true;
    }
    std::vector < std::shared_ptr < GraphicsItem>> breakItem()  {
        return std::move(this->m_itemList);
    }
    bool setVertexInScene(const int index, const Vertex vertex) override {
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
    bool rotate(const double angle) override {
        return true;
    }


    std::vector < std::shared_ptr < GraphicsItem>> breakCopiedItem() override {
        // // 获取当前最新的copiedItem
        // this->animate();
        // // 设置Params为空
        // m_vectorCopyParams.setEmpty();
        // m_matrixCopyParams.setEmpty();
        // 获取当前copiedItem  如果没有copiedItem就返回空数组
        std::vector < std::shared_ptr < GraphicsItem>> result;
        // result.reserve(this->m_copiedItemList.size());
        // for (auto &&item : std::move(this->m_copiedItemList)) {
        //     item->setPos(this->pos()); // 把位置也更新了; 作为copiedItem是不会保存这个数据的
        //     result.emplace_back(std::move(item));
        // }
        // m_copiedItemList.clear();
        return result;
    }
    std::vector < std::shared_ptr < GraphicsItem>> breakOffsetItem() override {
        //返回空数组
        std::vector < std::shared_ptr < GraphicsItem>> result;
        return result;
    };

protected:
    bool updateParallelOffsetItem() override {
        return true;
    };
    bool updatePaintItem() override {
        return true;
    }
    bool updateCopiedItem() override {
        // this->m_copiedItemList.clear();
        // //
        // if (this->m_vectorCopyParams.checkEmpty() && this->m_matrixCopyParams.checkEmpty()) {
        //     return true;
        // } else if ((!this->m_vectorCopyParams.checkEmpty())
        //            && (!this->m_matrixCopyParams.checkEmpty())) {
        //     WARN_MSG("should not happen");
        //     return false;
        // }
        // //
        // if (!this->m_vectorCopyParams.checkEmpty()) {
        //     m_copiedItemList.clear();
        //     //
        //     QPointF unitOffset = this->m_vectorCopyParams.dir * this->m_vectorCopyParams.spacing;
        //     for (int i = 1; i <= this->m_vectorCopyParams.count; ++i) {
        //         // DEBUG_VAR(this->getUUID());
        //         auto copiedItem = std::dynamic_pointer_cast < CombinedItem > (this->clone());
        //         QPointF offset = unitOffset * i;
        //         int count = this->getVertexCount();
        //         for (int i = 0; i < count; ++i) {
        //             copiedItem->m_vertexList[i].point += offset;
        //         }
        //         copiedItem->animate();
        //         // DEBUG_VAR(copiedItem->getUUID());
        //         m_copiedItemList.push_back(copiedItem);
        //     }
        //     return true;
        // }
        // //
        // if (!this->m_matrixCopyParams.checkEmpty()) {
        //     m_copiedItemList.clear();
        //     QPointF hOffset = this->m_matrixCopyParams.hVec * this->m_matrixCopyParams. hSpacing;
        //     QPointF vOffset = this->m_matrixCopyParams.vVec * this->m_matrixCopyParams.vSpacing;
        //     std::vector < std::vector < QPointF>> offsetMatrix(this->m_matrixCopyParams.vCount,
        //             std::vector < QPointF > (this->m_matrixCopyParams.hCount));
        //     for (int row = 0; row < this->m_matrixCopyParams.vCount; ++row) {
        //         for (int col = 0; col < this->m_matrixCopyParams.hCount; ++col) {
        //             offsetMatrix[row][col] = hOffset * col + vOffset * row;
        //         }
        //     }
        //     auto insertCopy = [&](int row, int col) {
        //         if (row == 0 && col == 0) {
        //             return;    // 跳过原始位置后开始复制
        //         }
        //         auto copiedItem = std::dynamic_pointer_cast < CombinedItem > (this->clone());
        //         if (!copiedItem) {
        //             return;
        //         }
        //         QPointF offset = offsetMatrix[row][col];
        //         int count = this->getVertexCount();
        //         for (int i = 0; i < count; ++i) {
        //             copiedItem->m_vertexList[i].point += offset;
        //         }
        //         copiedItem->animate();
        //         m_copiedItemList.push_back(copiedItem);
        //     };
        //     switch (this->m_matrixCopyParams.copiedOrder) {
        //         case 0: // 行优先，蛇形
        //             for (int row = 0; row < this->m_matrixCopyParams.vCount; ++row) {
        //                 if (row % 2 == 0) {
        //                     for (int col = 0; col < this->m_matrixCopyParams.hCount; ++col) {
        //                         insertCopy(row, col);
        //                     }
        //                 } else {
        //                     for (int col = this->m_matrixCopyParams.hCount - 1; col >= 0; --col) {
        //                         insertCopy(row, col);
        //                     }
        //                 }
        //             }
        //             break;
        //         case 1: // 列优先，蛇形
        //             for (int col = 0; col < this->m_matrixCopyParams.hCount; ++col) {
        //                 if (col % 2 == 0) {
        //                     for (int row = 0; row < this->m_matrixCopyParams.vCount; ++row) {
        //                         insertCopy(row, col);
        //                     }
        //                 } else {
        //                     for (int row = this->m_matrixCopyParams.vCount - 1; row >= 0; --row) {
        //                         insertCopy(row, col);
        //                     }
        //                 }
        //             }
        //             break;
        //         case 2: // 行优先，顺序
        //             for (int row = 0; row < this->m_matrixCopyParams.vCount; ++row) {
        //                 for (int col = 0; col < this->m_matrixCopyParams.hCount; ++col) {
        //                     insertCopy(row, col);
        //                 }
        //             }
        //             break;
        //         case 3: // 列优先，顺序
        //             for (int col = 0; col < this->m_matrixCopyParams.hCount; ++col) {
        //                 for (int row = 0; row < this->m_matrixCopyParams.vCount; ++row) {
        //                     insertCopy(row, col);
        //                 }
        //             }
        //             break;
        //         default:
        //             WARN_MSG("Unknown copiedOrder value");
        //             break;
        //     }
        //     return true;
        // }
        // return false;
    }
public:
    cavc::Polyline < double > getCavcForm(bool inSceneCoord) const override {
        cavc::Polyline < double > input;
        return input;
    }
    Vertex getVertexInScene(const int index) const override {
        return Vertex{};
    };
    QPointF getCenterInScene() const override {
        QPointF{};
    };
    QString getName() const override {
        return "CombinedItem";
    };
    int type() const override {
        return GraphicsItemType::Combined;
    }
    uint getVertexCount() const override {
        return 0;
    };
    QRectF getBoundingRectBasis() const override {
        if (this->m_itemList.empty()) {
            return QRectF();
        }
        QRectF newRect;
        for (auto& item : this->m_itemList) {
            qreal minX = std::min(newRect.left(), item->boundingRect().left());
            qreal minY = std::min(newRect.top(), item->boundingRect().top());
            qreal maxX = std::max(newRect.right(), item->boundingRect().right());
            qreal maxY = std::max(newRect.bottom(), item->boundingRect().bottom());
            newRect = QRectF(QPointF(minX, minY), QPointF(maxX, maxY));
        }
        return newRect;
    }
public:
    QRectF boundingRect() const override {
        if (this->m_itemList.empty()) {
            return QRectF();
        }
        QRectF newRect;
        for (auto &item : this->m_itemList) {
            qreal minX = std::min(newRect.left(), item->boundingRect().left());
            qreal minY = std::min(newRect.top(), item->boundingRect().top());
            qreal maxX = std::max(newRect.right(), item->boundingRect().right());
            qreal maxY = std::max(newRect.bottom(), item->boundingRect().bottom());
            newRect = QRectF(QPointF(minX, minY), QPointF(maxX, maxY));
        }
        // 包含所有 copiedItem
        // for (const auto &item : m_copiedItemList) {
        //     if (item) {
        //         newRect = newRect.united(item->boundingRect());
        //     }
        // }
        return newRect;
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
        Q_UNUSED(widget);
        // 设置option删去offset线段的选框
        QStyleOptionGraphicsItem optionx(*option);
        optionx.state &= ~QStyle::State_Selected;
        // 绘制线段
        for (auto &item : this->m_itemList) {
            item->paint(painter, &optionx, widget);
        }
        // // 绘制copied
        // for (auto &item : this->m_copiedItemList) {
        //     item->paint(painter, &optionx, widget);
        // }
    }

private:
    std::vector < std::shared_ptr < GraphicsItem>> m_itemList;
    // std::vector < std::shared_ptr < CombinedItem>> m_copiedItemList;
};

#endif // COMBINEDITEM_H
