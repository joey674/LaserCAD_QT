#include "arcitem.h"
#include "logger.h"
#include <polyline.hpp>
#include <polylineoffset.hpp>
#include <polylinecombine.hpp>

bool ArcItem::updateContourFillItem()
{
    //
    if (this->m_contourFillParams.offset == 0 || this->m_contourFillParams.offsetCount == 0) {
        return true;
    }
    this->m_contourFillItemList.clear();
    for (int offsetIndex = 1; offsetIndex <= this->m_contourFillParams.offsetCount; offsetIndex++) {
        // 输入cavc库
        cavc::Polyline<double> input = this->getCavcForm(true);
        input.isClosed() = false;
        std::vector<cavc::Polyline<double>> results
            = cavc::parallelOffset(input, (-1) * this->m_contourFillParams.offset * offsetIndex);
        // 获取结果
        for (const auto &polyline : results) {
            auto item = FromCavcForm(polyline);
            item->setColor(this->getColor());
            this->m_contourFillItemList.push_back(std::move(item));
        }
    }
    return true;
}

bool ArcItem::updateHatchFillItem()
{
    if (m_hatchFillParams.operateCount == 0 || m_hatchFillParams.spacing == 0){
        return true;
    }
    this->m_hatchFillItemList.clear();

    // 输入cavc库
    auto input = this->getCavcForm(true);
    // 自动判断 如果最后一个点与第一个点重合 那么就认为是close;
    auto vertexCount = this->getVertexCount();

    // 获取直径与圆心
    QRectF rect = this->getBoundingRectBasis();
    double w = rect.width();
    double h = rect.height();
    double radius = std::sqrt(w * w + h * h) * 0.5;
    QPointF center = this->getCenterInScene();
    double lineLength = radius * 2.0;
    // 提取角度和间距
    double angleDeg = -this->m_hatchFillParams.startAngle;
    double spacing = this->m_hatchFillParams.spacing;
    // 方向向量（填充线方向）与垂线方向（用于平移）
    double rad = angleDeg * M_PI / 180.0;
    double dx = std::cos(rad), dy = std::sin(rad);
    double pdx = dy, pdy = -dx;
    // 线段数量 = 直径 / spacing（左右平移）
    // 保证生成线段的总宽度能覆盖整个圆
    int numLines = static_cast<int>(std::ceil(lineLength / spacing));
    for (int i = -numLines; i <= numLines; ++i) {
        // 平移后中点
        QPointF mid = center + QPointF(i * spacing * pdx, i * spacing * pdy);
        // 线段两端点
        QPointF p1 = mid + QPointF(-dx * lineLength * 0.5, -dy * lineLength * 0.5);
        QPointF p2 = mid + QPointF(dx * lineLength * 0.5, dy * lineLength * 0.5);
        // 构造 填充线段
        cavc::Polyline<double> rawHatch;
        rawHatch.addVertex(p1.x(), p1.y(),0);
        rawHatch.addVertex(p2.x(), p2.y(),0);
        // 与 polygon 做布尔交集
        input.isClosed() = true;
        rawHatch.isClosed() = true;
        // 执行布尔操作
        cavc::CombineResult < double > result = cavc::combinePolylines(input, rawHatch, cavc::PlineCombineMode::Intersect);
        for (auto &hatch : result.remaining) {
            hatch.isClosed () = false;
            auto item = FromCavcForm(hatch);
            item->setColor(this->getColor());
            this->m_hatchFillItemList.push_back(item);
        }
    }

    return true;
}
