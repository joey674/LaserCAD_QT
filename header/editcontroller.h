#ifndef EDITCONTROLLER_H
#define EDITCONTROLLER_H

#include <QCoreApplication>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QTimer>
#include "arcitem.h"
#include "editrect.h"
#include "ellipseitem.h"
#include "manager.h"
#include "polygonitem.h"
#include "polylineitem.h"
#include "protocol.h"
#include "rectitem.h"
#include "spiralitem.h"
#include <polylinecombine.hpp>
#include <qgraphicsitem.h>

class EditController {
    friend class EditRect;
private:
    std::vector < std::shared_ptr < GraphicsItem> > m_currentEditItemGroup
        = std::vector < std::shared_ptr < GraphicsItem> > ();
    std::unique_ptr < EditRect > m_editRect;
    std::vector < std::shared_ptr < GraphicsItem> > m_currentCutCopyItemGroup
        = std::vector < std::shared_ptr < GraphicsItem> > ();
    /// ********************
    /// 更新对应的编辑Widget
    /// ********************
public:
    void updateTabWidget();
    void updateTableViewModel();
    void updateEditRect() {
        // 初始化
        if (!m_editRect) {
            m_editRect = std::make_unique < EditRect > ();
            SceneController::getIns().scene->addItem(m_editRect.get());
        }
        //
        if (!m_currentEditItemGroup.empty()) {
            m_editRect->setEditItems(m_currentEditItemGroup);
            m_editRect->show();
        } else {
            m_editRect->setEditItems(std::vector < std::shared_ptr < GraphicsItem>>());
            m_editRect->hide();
        }
    }

    /// ********************
    /// 编辑回调
    /// ********************
public:
    /// \brief onTabWidgetCopyTabVectorCopy
    /// tabWidget单个对象编辑的回调;
    void onTabWidgetCopyTabVectorCopy(VectorCopyParams params) {
        //
        if (this->m_currentEditItemGroup.size() != 1) {
            return;
        }
        //
        auto curEditItem = this->m_currentEditItemGroup[0];
        curEditItem->setCopiedItem(params);
    }
    void onTabWidgetCopyTabMatrixCopy(MatrixCopyParams params) {
        if (this->m_currentEditItemGroup.size() != 1) {
            return;
        }
        auto curEditItem = this->m_currentEditItemGroup[0];
        curEditItem->setCopiedItem(params);
    }
    void onTabWidgetOffsetTabParallelOffset(OffsetParams params) {
        //
        if (this->m_currentEditItemGroup.size() != 1) {
            return;
        }
        auto &curEditItem = this->m_currentEditItemGroup[0];
        //
        curEditItem->setOffsetItem(params);
        this->updateTableViewModel();
    }
    void onTabWidgetMarkParamsTab(MarkParams params) {
        //
        if (this->m_currentEditItemGroup.size() != 1) {
            return;
        }
        auto &curEditItem = this->m_currentEditItemGroup[0];
        //
        curEditItem->setMarkParams(params);
        this->updateTableViewModel();
    }
    void onTabWidgetDelayParamsTab(DelayParams params) {
        //
        if (this->m_currentEditItemGroup.size() != 1) {
            return;
        }
        auto &curEditItem = this->m_currentEditItemGroup[0];
        //
        curEditItem->setDelayParams(params);
        this->updateTableViewModel();
    }
    /// \brief onTabWidgetArcGeometryTab
    /// \param start
    void onTabWidgetArcGeometryTab(QPointF start, QPointF end, double angle) {
        //
        if (this->m_currentEditItemGroup.size() != 1) {
            return;
        }
        auto &curEditItem = this->m_currentEditItemGroup[0];
        //
        curEditItem->setVertexInScene(0, Vertex{start, 0});
        curEditItem->setVertexInScene(1, Vertex{end, angle});
        this->updateEditRect();
    }
    void onTabWidgetLineGeometryTab(QPointF start, QPointF end) {
        //
        if (this->m_currentEditItemGroup.size() != 1) {
            return;
        }
        auto &curEditItem = this->m_currentEditItemGroup[0];
        //
        curEditItem->setVertexInScene(0, Vertex{start, 0});
        curEditItem->setVertexInScene(1, Vertex{end, 0});
        this->updateEditRect();
    }
    void onTabWidgetPointGeometryTab(QPointF pos) {
        //
        if (this->m_currentEditItemGroup.size() != 1) {
            return;
        }
        auto &curEditItem = this->m_currentEditItemGroup[0];
        //
        curEditItem->setVertexInScene(0, Vertex{pos, 0});
        this->updateEditRect();
    }
    void onTabWidgetCircleGeometryTab(QPointF pos, double radius) {
        //
        if (this->m_currentEditItemGroup.size() != 1) {
            return;
        }
        auto &curEditItem = this->m_currentEditItemGroup[0];
        //
        CircleItem *item = static_cast < CircleItem * > (curEditItem.get());
        item->setVertexInScene(0, Vertex{pos, 0});
        item->setRadius (radius);
        this->updateEditRect();
    }
    void onTabWidgetPolylineGeometryTab(std::vector < Vertex > vertices) {
        // 只处理单个对象
        if (this->m_currentEditItemGroup.size() != 1) {
            WARN_MSG("Polyline edit only supports single selection.");
            return;
        }
        auto &curEditItemPtr = this->m_currentEditItemGroup[0];
        auto curEditItem = static_cast < PolylineItem * > (curEditItemPtr.get());
        // 顶点数量不匹配时，重建顶点数据
        for (size_t i = 0; i < vertices.size(); ++i) {
            curEditItem->setVertexInScene(static_cast < uint > (i), vertices[i]);
        }
        this->updateEditRect();
    }
    void onTabWidgetRectGeometryTab(QPointF leftTop, QPointF rightBottom)
    {
        if (this->m_currentEditItemGroup.size() != 1) {
            return;
        }
        auto &curEditItem = this->m_currentEditItemGroup[0];
        RectItem *item = static_cast<RectItem *>(curEditItem.get());
        double left = leftTop.x();
        double top = leftTop.y();
        double right = rightBottom.x();
        double bottom = rightBottom.y();
        std::array<QPointF, 5> points = {
            QPointF(left, top),     // 0 左上
            QPointF(right, top),    // 1 右上
            QPointF(right, bottom), // 2 右下
            QPointF(left, bottom),  // 3 左下
            QPointF(left, top)      // 4 回到左上闭合
        };

        for (int i = 0; i < 5; ++i) {
            item->setVertexInScene(i, Vertex{points[i], 0});
        }
        this->updateEditRect();
    }
    void onTabWidgetEllipseGeometryTab(QPointF center,
                                       double radiusX,
                                       double radiusY,
                                       double rotateAngle)
    {
        //
        if (this->m_currentEditItemGroup.size() != 1) {
            return;
        }
        auto &curEditItem = this->m_currentEditItemGroup[0];
        //
        EllipseItem *item = static_cast<EllipseItem *>(curEditItem.get());
        item->setVertexInScene(0, Vertex{center, 0});
        item->setRadiusX(radiusX);
        item->setRadiusY(radiusY);
        item->setRotateAngle(rotateAngle);
        this->updateEditRect();
    }
    void onTabWidgetPolygonGeometryTab(QPointF center, double radius, uint edgeCount, double angle)
    {
        if (this->m_currentEditItemGroup.size() != 1) {
            return;
        }
        auto &curEditItem = this->m_currentEditItemGroup[0];
        PolygonItem *item = static_cast<PolygonItem *>(curEditItem.get());

        item->setVertexInScene(0, Vertex{center, 0});
        item->setRadius(radius);
        item->setEdgeCount(edgeCount);
        item->setRotateAngle(angle);

        this->updateEditRect();
    }
    void onTabWidgetSpiralGeometryTab(
        QPointF center, double r0, double r1, double turns, double stepDeg)
    {
        if (this->m_currentEditItemGroup.size() != 1) {
            return;
        }

        auto &curEditItem = this->m_currentEditItemGroup[0];
        SpiralItem *item = static_cast<SpiralItem *>(curEditItem.get());

        item->setVertexInScene(0, Vertex{center, 0});
        item->setStartRadius(r0);
        item->setEndRadius(r1);
        item->setTurns(turns);
        item->setAngleStepDeg(stepDeg);

        this->updateEditRect();
    }

    /// \brief onTabWidgetMultiItemsEditTab
    /// tabWidget多个对象编辑的回调; 多个对象统一编辑/规律编辑
    void onTabWidgetMultiItemsEditTab(std::vector < MultiEditParam > params) {
        if (this->m_currentEditItemGroup.empty()) {
            return;
        }
        DEBUG_MSG(m_currentEditItemGroup.size());
        for (size_t i = 0; i < m_currentEditItemGroup.size(); ++i) {
            auto item = m_currentEditItemGroup[i];
            MarkParams mark = item->getMarkParams();
            DelayParams delay = item->getDelayParams();
            QPointF pos = item->getCenterInScene();
            for (const MultiEditParam& param : params) {
                QVariant val = param.baseValue;
                QVariant delta = param.deltaValue;
                QVariant finalVal;
                // 处理加法（支持 int 和 double）
                if (val.typeId() == QVariant::Double || delta.typeId() == QVariant::Double) {
                    finalVal = val.toDouble() + i * delta.toDouble();
                } else {
                    finalVal = val.toInt() + static_cast < int > (i) * delta.toInt();
                }
                const QString& key = param.fieldName;
                // --- MarkParams ---
                if (key == "MarkParams: markSpeed" || key == "MarkParams: jumpSpeed"
                        || key == "MarkParams: power" || key == "MarkParams: pulseWidth") {
                    mark.set(key, finalVal);
                } else if (key == "MarkParams: frequency" || key == "MarkParams: repetTime"
                           || key == "MarkParams: wobelAml" || key == "MarkParams: wobelFreq") {
                    mark.set(key, finalVal);
                }
                // --- DelayParams ---
                else if (key == "DelayParams: startDelay" || key == "DelayParams: endDelay"
                         || key == "DelayParams: markDelay" || key == "DelayParams: jumpDelay"
                         || key == "DelayParams: polygonDelay") {
                    delay.set(key, finalVal);
                }
                // --- Position ---
                else if (key == "Position.x") {
                    pos.setX(finalVal.toDouble());
                } else if (key == "Position.y") {
                    pos.setY(finalVal.toDouble());
                }
            }
            item->setMarkParams(mark);
            item->setDelayParams(delay);
            DEBUG_VAR(pos);
            item->setCenterInScene(pos);
        }
        this->updateEditRect();
    }
    /// \brief onTabWidgetMultiCombineTab
    /// 把两个闭合曲线做boolan Operation
    void onTabWidgetDuoItemsBoolOpTab(cavc::PlineCombineMode mode) {
        if (this->m_currentEditItemGroup.size() != 2) {
            WARN_MSG("Boolean operation requires exactly two selected items.");
            return;
        }
        // 获取两个 polyline item
        auto aPtr = this->m_currentEditItemGroup[0];
        auto bPtr = this->m_currentEditItemGroup[1];
        auto aItem = dynamic_cast < GraphicsItem * > (aPtr.get());
        auto bItem = dynamic_cast < GraphicsItem * > (bPtr.get());
        // 转换为 cavc polyline
        auto cavcA = aItem->getCavcForm(true);
        cavcA.isClosed() = true;
        auto cavcB = bItem->getCavcForm(true);
        cavcB.isClosed() = true;
        // 执行布尔操作
        cavc::CombineResult < double > result = cavc::combinePolylines(cavcA, cavcB, mode);
        for (const auto &pline : result.remaining) {
            auto item = FromCavcForm(pline);
            SceneController::getIns().scene->addItem(item.get());
            Manager::getIns().addItem(item);
        }
        this->updateEditRect();
    }

    /// \brief 按钮回调 直接操作当前editItemGroup;
    ///
    void onBreakOffsetItemTriggered() {
        if (EditController::getIns().m_currentEditItemGroup.size() != 1) {
            return;
        }
        auto &curEditItem = EditController::getIns().m_currentEditItemGroup[0];
        auto offsetItems = curEditItem->breakOffsetItem();
        for (auto &item : offsetItems) {
            auto uuid = item->getUUID();
            SceneController::getIns().scene->addItem(item.get());
            Manager::getIns().addItem(std::move(item));
            Manager::getIns().setItemSelectable(uuid, true);
        }
    }
    void onBreakCopiedItemTriggered() {
        if (EditController::getIns().m_currentEditItemGroup.size() != 1) {
            return;
        }
        auto &curEditItem = EditController::getIns().m_currentEditItemGroup[0];
        auto copiedItems = curEditItem->breakCopiedItem();
        for (auto &item : copiedItems) {
            auto uuid = item->getUUID();
            SceneController::getIns().scene->addItem(item.get());
            Manager::getIns().addItem(std::move(item));
            Manager::getIns().setItemSelectable(uuid, true);
        }
    }
    void onCenterToOriginTriggered() {
        if (EditController::getIns().m_currentEditItemGroup.empty ()) {
            return;
        }
        for (auto& item : EditController::getIns().m_currentEditItemGroup) {
            item->setCenterInScene(QPointF{0, 0});
        }
        this->updateEditRect();
        this->updateTabWidget();
    }
    void onMirrorHorizontalTriggered()
    {
        if (EditController::getIns().m_currentEditItemGroup.empty()) {
            return;
        }
        for (auto &item : EditController::getIns().m_currentEditItemGroup) {
            QPointF center = item->getCenterInScene();
            auto vertexCount = item->getVertexCount();
            for (int i = 0; i < vertexCount; i++) {
                Vertex vertex = item->getVertexInScene(i);
                auto newX = 2 * center.x() - vertex.point.x();
                auto newY = vertex.point.y();
                auto newAngle = -vertex.angle;
                Vertex newVertex = Vertex{QPointF{newX, newY}, newAngle};
                item->setVertexInScene(i, newVertex);
            }
            if (item->type() == GraphicsItemType::Ellipse) {
                auto ellipse = static_cast<EllipseItem *>(item.get());
                auto angle = ellipse->getRotateAngle();
                auto mirroredAngle = std::fmod(360.0 - angle, 360.0);
                ellipse->setRotateAngle(mirroredAngle);
            } else if (item->type() == GraphicsItemType::Spiral) {
            }
    }
    this->updateEditRect();
    this->updateTabWidget();
    };
    void onMirrorVerticalTriggered()
    {
        if (EditController::getIns().m_currentEditItemGroup.empty()) {
            return;
        }
        for (auto &item : EditController::getIns().m_currentEditItemGroup) {
            QPointF center = item->getCenterInScene();
            auto vertexCount = item->getVertexCount();
            for (int i = 0; i < vertexCount; i++) {
                Vertex vertex = item->getVertexInScene(i);
                auto newY = 2 * center.y() - vertex.point.y();
                auto newX = vertex.point.x();
                auto newAngle = -vertex.angle;
                Vertex newVertex = Vertex{QPointF{newX, newY}, newAngle};
                item->setVertexInScene(i, newVertex);
            }
            if (item->type() == GraphicsItemType::Ellipse) {
                auto ellipse = static_cast<EllipseItem *>(item.get());
                auto angle = ellipse->getRotateAngle();
                auto mirroredAngle = std::fmod(360.0 - angle, 360.0);
                ellipse->setRotateAngle(mirroredAngle);
            }
        }
        this->updateEditRect();
        this->updateTabWidget();
    };
    void onAlignTriggered()
    {
        if (EditController::getIns().m_currentEditItemGroup.size() <= 2) {
            return;
        }
        for (auto &item : EditController::getIns().m_currentEditItemGroup) {
        }
        this->updateEditRect();
        this->updateTabWidget();
    };
    /// \brief 按钮回调 负责剪切 拷贝 删除 操作editItemGroup/copyCutItemGroup
    ///
    void onDeleteItemsTriggered() {
        //
        if (EditController::getIns().m_currentEditItemGroup.empty()) {
            return;
        }
        // 在manager中删除; 先安全只读,不动 item 对象,最后在一起删除; 这里不要边遍历边删
        std::vector < QString > uuids;
        for (const auto &item : EditController::getIns().m_currentEditItemGroup) {
            uuids.push_back(item->getUUID());
        }
        for (const auto &uuid : uuids) {
            // 一个clearSelection的bug,在remove之后还触发了对象的回调 导致空指针
            auto item = Manager::getIns().itemMapFind(uuid);
            SceneController::getIns().scene->removeItem(item.get());//  在场景中删除
            Manager::getIns().deleteItem(uuid);
            DEBUG_MSG(uuid + " is deleted");
        }
        // 清除editController中的编辑列表
        EditController::getIns().m_currentEditItemGroup.clear();
        // DEBUG
        const auto &items = SceneController::getIns().scene->items();
        INFO_MSG("Scene has " + QString::number(items.size() - 11) + " items");
        //
        this->updateEditRect();
    }
    void onCutItemsTriggered() {
        //
        if (EditController::getIns().m_currentEditItemGroup.empty()) {
            return;
        }
        //
        this->m_currentCutCopyItemGroup.clear();
        for (const auto& item : this->m_currentEditItemGroup) {
            auto newItem = item->clone();
            this->m_currentCutCopyItemGroup.push_back(newItem);
        }
        onDeleteItemsTriggered(); // 触发deletetriggered 删除当前编辑对象
        //
        this->updateEditRect();
    }
    void onCopyItemsTriggered() {
        //
        if (EditController::getIns().m_currentEditItemGroup.empty()) {
            return;
        }
        //
        this->m_currentCutCopyItemGroup.clear();
        for (const auto& item : this->m_currentEditItemGroup) {
            auto newItem = item->clone();
            this->m_currentCutCopyItemGroup.push_back(newItem);
        }
        //
        this->updateEditRect();
    }
    void onPasteItemsTriggered() {
        //
        if (EditController::getIns().m_currentCutCopyItemGroup.empty()) {
            return;
        }
        //
        for (const auto& item : this->m_currentCutCopyItemGroup) {
            auto newItem = item->clone();
            newItem->setColor(SceneController::getIns().getCurrentLayerColor());
            SceneController::getIns().scene->addItem(newItem.get());
            Manager::getIns().addItem(std::move (newItem));
        }
        //
        this->updateEditRect();
    }
/// ********************
/// 在treeView和Scene中控制当前编辑对象的回调
/// ********************
public:
    /// \brief onTreeViewModelClicked
    /// treeView中node点击回调
    void onTreeViewModelClicked(const QModelIndex &index) {}
    /// \brief onTreeViewModelSelectionChanged
    ///  这里的selection不用考虑,因为选中对应graphicsItem的时候, graphicsItem的选中回调会自己排序编辑队列
    void onTreeViewModelSelectionChanged(const QItemSelection &selected,
                                         const QItemSelection &deselected);
    /// \brief onSceneSelectionChanged
    /// Scene的整体变动回调; 全局的管控
    void onSceneSelectionChanged() {}
    /// \brief onGraphicsItemPositionHasChanged
    /// 单个物体位置变换后的回调
    void onGraphicsItemPositionHasChanged(UUID uuid) {
        this->updateTableViewModel();
    }
    /// \brief onGraphicsItemSelectedHasChanged
    /// 单个物体选中状态变化的回调; selected状态可以重叠, 当tree中选中令scene中选中时, scene中的选中回调也会让tree选中; 但是不会触发selectedChanged;
    void onGraphicsItemSelectedHasChanged(UUID uuid, bool selected);
    /// \brief onGraphicsItemMouseRelease
    /// 物体上鼠标release事件; 更新一次tabWidget(尽量不实时更新 减少开销)
    void onGraphicsItemMouseRelease(UUID uuid) {
        // this->updateTableViewModel();
        this->updateTabWidget();
    }
    /// \brief onGraphicsItemMousePress
    /// 物体上鼠标press事件
    void onGraphicsItemMousePress(UUID uuid) {}

/// ********************
/// \brief 编辑模式下在scene中编辑对象
/// \brief editItemInScene     scene中的编辑事件会传入
/// \param pointCoordscene event 接收的是鼠标坐标事件
/// ********************
public:
    void editItemInScene(QPointF pointCoordscene, MouseEvent event);
    int currentEditPolylineVertexIndex = -1;
    void editPolyline(QPointF pointCoordscene, PolylineItem *, MouseEvent event);
    void editArc(QPointF pointCoordscene, ArcItem *, MouseEvent event);
/// ********************
/// 单例初始化
/// ********************
private:
    static EditController ins;
    EditController() {};
    EditController(const EditController &);
    ~EditController() {};
    EditController &operator = (const EditController &);
public:
    static EditController &getIns();
};

#endif // EDITCONTROLLER_H
