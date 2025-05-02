#include "EditRect.h"
#include "editcontroller.h"

void EditRect::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    // 忽略右键的操作
    if (event->button() == Qt::LeftButton) {
        if (m_editMode == EditMode::Move) {
            QPointF deltaMove = this->pos() - m_startPos;
            for (auto &item : m_editItems) {
                if (auto gItem = std::dynamic_pointer_cast < GraphicsItem > (item)) {
                    applyMoveToGraphicsItem(*gItem, deltaMove);
                }
            }
        } else if (m_editMode == EditMode::Rotate) {
            qreal deltaRotation = this->rotation() - m_startRotation;
            // 旋转中心
            QPointF center = mapToScene(QPointF(0, 0)); // 当前EditRect中心
            for (auto &item : m_editItems) {
                if (auto gItem = std::dynamic_pointer_cast < GraphicsItem > (item)) {
                    applyRotateToGraphicsItem(*gItem, deltaRotation, center);
                }
            }
        } else if (m_editMode == EditMode::Scale) {
            // 计算缩放比例
            qreal scaleX = m_editRect.width() / m_startEditRect.width();
            qreal scaleY = m_editRect.height() / m_startEditRect.height();
            // 强制等比缩放
            qreal uniformScale = (std::abs(scaleX) < std::abs(scaleY)) ? scaleX : scaleY;
            scaleX = scaleY = uniformScale;
            // 确定固定点
            QPointF startFixedPoint;
            switch (m_currentHandleIndex) {
                case 0:
                    startFixedPoint = m_startEditRect.bottomRight();
                    break;
                case 1:
                    startFixedPoint = m_startEditRect.bottomLeft();
                    break;
                case 2:
                    startFixedPoint = m_startEditRect.topRight();
                    break;
                case 3:
                    startFixedPoint = m_startEditRect.topLeft();
                    break;
                default:
                    startFixedPoint = m_startEditRect.center();
                    break;
            }
            startFixedPoint = mapToScene(startFixedPoint);
            for (auto &item : m_editItems) {
                if (auto gItem = std::dynamic_pointer_cast < GraphicsItem > (item)) {
                    applyScaleToGraphicsItem(*gItem, scaleX, scaleY, startFixedPoint);
                }
            }
            //
            prepareGeometryChange();
            // 计算新的EditRect的中心 (注意是局部的)
            QPointF newCenterInScene = mapToScene(m_editRect.center());
            // 更新自己的位置
            setPos(newCenterInScene);
            // m_editRect中心移动到(0,0)
            m_editRect.moveCenter(QPointF(0, 0));
        }
        // 重置
        m_editMode = EditMode::None;
        m_currentHandleIndex = -1;
    }
    EditController::getIns().updateTabWidget();
    event->accept();
}
