#include "ellipseitem.h"
#include <polyline.hpp>
#include <polylineoffset.hpp>
#include <polylinecombine.hpp>

bool EllipseItem::updateHatchFillItem() {
    this->m_hatchFillItemList.clear();
    if (m_hatchFillParams.operateCount == 0 || m_hatchFillParams.spacing == 0){
        return true;
    }

    // 输入cavc库
    auto input = this->getCavcForm();

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
            // 确保所有hatch的方向一致
            const auto v0 = item->getVertexInScene (0);
            const auto v1 = item->getVertexInScene (1);
            double vx = v1.point.x() - v0.point.x();
            double vy = v1.point.y() - v0.point.y();
            double dot = vx * dx + vy * dy;
            if (dot < 0) {
                item->setVertexInScene (0,v1);
                item->setVertexInScene (1,v0);
            }
            //
            item->setColor(this->getColor());
            item->setMarkParams (this->getMarkParams ());
            item->setDelayParams (this->getDelayParams ());
            this->m_hatchFillItemList.push_back(item);
        }
    }

    return true;
}

