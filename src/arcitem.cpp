#include "arcitem.h"
#include "logger.h"
#include <polyline.hpp>
#include <polylineoffset.hpp>
#include <polylinecombine.hpp>

bool ArcItem::updateContourFillItem()
{
    this->m_contourFillItemList.clear();
    //
    if (this->m_contourFillParams.offset == 0 || this->m_contourFillParams.offsetCount == 0) {
        return true;
    }

    for (int offsetIndex = 1; offsetIndex <= this->m_contourFillParams.offsetCount; offsetIndex++) {
        // 输入cavc库
        cavc::Polyline<double> input = this->getCavcForm();
        input.isClosed() = false;
        std::vector<cavc::Polyline<double>> results
            = cavc::parallelOffset(input, (-1) * this->m_contourFillParams.offset * offsetIndex);
        // 获取结果
        for (const auto &polyline : results) {
            auto item = FromCavcForm(polyline);
            item->setColor(this->m_color);
            item->setMarkParams (this->getMarkParams ());
            item->setDelayParams (this->getDelayParams ());
            this->m_contourFillItemList.push_back(std::move(item));
        }
    }
    return true;
}

bool ArcItem::updatePaintItem()
{
    //
    this->m_paintItem = nullptr;
    //
    auto v1 = m_vertexPair[0].point;
    auto v2 = m_vertexPair[1].point;
    double angle = m_vertexPair[1].angle;
    QPainterPath arcPath = createArcPath(v1, v2, angle);
    this->m_paintItem = std::make_shared<QGraphicsPathItem>(arcPath);
    this->m_paintItem->setPen(this->getPen());
    return true;
}

bool ArcItem::updateCopiedItem()
{
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
            auto copiedItem = std::dynamic_pointer_cast<ArcItem>(this->clone());
            QPointF offset = unitOffset * i;
            copiedItem->m_vertexPair[0].point += offset;
            copiedItem->m_vertexPair[1].point += offset;
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
        std::vector<std::vector<QPointF>> offsetMatrix(this->m_matrixCopyParams.vCount+1,
                                                       std::vector<QPointF>(
                                                           this->m_matrixCopyParams.hCount+1));
        for (int row = 0; row < this->m_matrixCopyParams.vCount+1; ++row) {
            for (int col = 0; col < this->m_matrixCopyParams.hCount+1; ++col) {
                offsetMatrix[row][col] = hOffset * col + vOffset * row;
            }
        }
        auto insertCopy = [&](int row, int col) {
            if (row == 0 && col == 0) {
                return; // 跳过原始位置后开始复制
            }
            auto copiedItem = std::dynamic_pointer_cast<ArcItem>(this->clone());
            if (!copiedItem) {
                return;
            }
            QPointF offset = offsetMatrix[row][col];
            copiedItem->m_vertexPair[0].point += offset;
            copiedItem->m_vertexPair[1].point += offset;
            copiedItem->animate();
            m_copiedItemList.push_back(copiedItem);
        };
        switch (this->m_matrixCopyParams.copiedOrder) {
        case 0: // 行优先，蛇形
            for (int row = 0; row < this->m_matrixCopyParams.vCount+1; ++row) {
                if (row % 2 == 0) {
                    for (int col = 0; col < this->m_matrixCopyParams.hCount+1; ++col) {
                        insertCopy(row, col);
                    }
                } else {
                    for (int col = this->m_matrixCopyParams.hCount+1 - 1; col >= 0; --col) {
                        insertCopy(row, col);
                    }
                }
            }
            break;
        case 1: // 列优先，蛇形
            for (int col = 0; col < this->m_matrixCopyParams.hCount+1; ++col) {
                if (col % 2 == 0) {
                    for (int row = 0; row < this->m_matrixCopyParams.vCount+1; ++row) {
                        insertCopy(row, col);
                    }
                } else {
                    for (int row = this->m_matrixCopyParams.vCount+1 - 1; row >= 0; --row) {
                        insertCopy(row, col);
                    }
                }
            }
            break;
        case 2: // 行优先，顺序
            for (int row = 0; row < this->m_matrixCopyParams.vCount+1; ++row) {
                for (int col = 0; col < this->m_matrixCopyParams.hCount+1; ++col) {
                    insertCopy(row, col);
                }
            }
            break;
        case 3: // 列优先，顺序
            for (int col = 0; col < this->m_matrixCopyParams.hCount+1; ++col) {
                for (int row = 0; row < this->m_matrixCopyParams.vCount+1; ++row) {
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

bool ArcItem::updateHatchFillItem()
{
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
