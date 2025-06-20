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
        auto bPtr = this->m_itemList[1];//
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
