#include "combineditem.h"
#include "logger.h"
#include <polylineoffsetislands.hpp>

bool CombinedItem::updateContourFillItem()
{
    // this->m_contourFillItemList.clear();
    // //
    // if (this->m_contourFillParams.offset == 0 || this->m_contourFillParams.offsetCount == 0) {
    //     return true;
    // }

    // cavc::OffsetLoopSet<double> loopSet;

    // cavc::Polyline<double> outerCCWLoop = this->m_itemList[0]->getCavcForm ();
    // outerCCWLoop.isClosed () = true;
    // loopSet.ccwLoops.push_back({0, outerCCWLoop, cavc::createApproxSpatialIndex(outerCCWLoop)});


    // for ( int i = 1; i< this->m_itemList.size (); i++ ){
    //     cavc::Polyline<double> island = this->m_itemList[i]->getCavcForm ();
    //     island.isClosed () = true;
    //     loopSet.cwLoops.push_back({0, island, cavc::createApproxSpatialIndex(island)});
    // }

    // for (int offsetIndex = 1;offsetIndex < this->getContourFillParams ().offsetCount; offsetIndex++){
    //     cavc::ParallelOffsetIslands<double> alg;
    //     const double offsetDelta = this->getContourFillParams ().offset * offsetIndex;
    //     cavc::OffsetLoopSet<double> offsetResult = alg.compute(loopSet, offsetDelta);

    //     auto debugMsg = [this](const std::shared_ptr<PolylineItem> &item) {
    //         // static int a=0;
    //         // DEBUG_MSG("Polyline"+QString::number (a));
    //         // for (std::size_t i = 0; i < item->getVertexCount (); ++i) {
    //         //     const auto &v = item->getVertexInScene (i);
    //         //     DEBUG_MSG(v.point);
    //         // }
    //         // a++;
    //     };

    //     for (const auto &loop : offsetResult.ccwLoops) {
    //         std::shared_ptr<PolylineItem> item = FromCavcForm(loop.polyline);
    //         debugMsg(item);
    //         item->setColor(this->m_color);
    //         item->setMarkParams (this->getMarkParams ());
    //         item->setDelayParams (this->getDelayParams ());
    //         this->m_contourFillItemList.push_back(std::move(item));
    //     }
    //     for (const auto &loop : offsetResult.cwLoops) {
    //         std::shared_ptr<PolylineItem> item = FromCavcForm(loop.polyline);
    //         debugMsg(item);
    //         item->setColor(this->m_color);
    //         item->setMarkParams (this->getMarkParams ());
    //         item->setDelayParams (this->getDelayParams ());
    //         this->m_contourFillItemList.push_back(std::move(item));
    //     }
    // }

    return true;
}

bool CombinedItem::updateCopiedItem(){
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
            auto copiedItem = std::dynamic_pointer_cast < CombinedItem > (this->clone());
            QPointF offset = unitOffset * i;
            int count = this->getVertexCount();
            for (int i = 0; i < count; ++i) {
                auto center = copiedItem->m_itemList[i]->getCenterInScene () + offset;
                copiedItem->m_itemList[i]->setCenterInScene (center);
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
            auto copiedItem = std::dynamic_pointer_cast < CombinedItem > (this->clone());
            if (!copiedItem) {
                return;
            }
            QPointF offset = offsetMatrix[row][col];
            int count = this->getVertexCount();
            for (int i = 0; i < count; ++i) {
                auto center = copiedItem->m_itemList[i]->getCenterInScene () + offset;
                copiedItem->m_itemList[i]->setCenterInScene (center);
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

bool CombinedItem::updateHatchFillItem()
{
    this->m_hatchFillItemList.clear();
    if (m_hatchFillParams.operateCount == 0 || m_hatchFillParams.spacing == 0){
        return true;
    }

    this->m_itemList[0]->setFillParams (this->m_hatchFillParams);
    std::vector<std::shared_ptr<GraphicsItem>>hatchList;
    auto combinedHatchList = this->m_itemList[0]->breakHatchFillItem ();

    for (auto &hatchs: combinedHatchList){
        auto hatchs_combined = std::dynamic_pointer_cast < CombinedItem> (hatchs);
        auto hatchs_graphic = hatchs_combined->breakItem ();
        hatchList.insert (hatchList.end (),hatchs_graphic.begin(),hatchs_graphic.end ());
    }

    for (auto &hatch: hatchList){
        auto aPtr = hatch;
        auto bPtr = this->m_itemList[1];//当前只处理一个嵌套填充; 如果内部有两个island 只处理第一个
        auto aItem = dynamic_cast < GraphicsItem * > (aPtr.get());
        auto bItem = dynamic_cast < GraphicsItem * > (bPtr.get());
        // 转换为 cavc polyline
        auto cavcA = aItem->getCavcForm();
        cavcA.isClosed() = true;
        auto cavcB = bItem->getCavcForm();
        cavcB.isClosed() = true;
        // 执行布尔操作
        cavc::CombineResult < double > result = cavc::combinePolylines(cavcA, cavcB, cavc::PlineCombineMode::Exclude);
        for (auto &pline : result.remaining) {
            pline.isClosed ()=false;
            auto item = FromCavcForm(pline);
            this->m_hatchFillItemList.push_back (item);
        }
    }
    return true;
}
