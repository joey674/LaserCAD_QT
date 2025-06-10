#include "graphicsitem.h"
#include "editcontroller.h"

void GraphicsItem::cloneBaseParamsFromJson(const QJsonObject &obj) {
    // m_color
    if (obj.contains("color")) {
        m_color = QColor(obj["color"].toString());
    }
    if (obj.contains("markParams")) {
        QJsonObject m = obj["markParams"].toObject();
        m_markParams.markSpeed = m["markSpeed"].toDouble();
        m_markParams.jumpSpeed = m["jumpSpeed"].toDouble();
        m_markParams.frequency = m["frequency"].toInt();
        m_markParams.operateTime = m["operateTime"].toInt();
        m_markParams.power = m["power"].toDouble();
        m_markParams.pulseLength = m["pulseLength"].toDouble();
        m_markParams.wobelAml = m["wobelAml"].toInt();
        m_markParams.wobelFreq = m["wobelFreq"].toInt();
    }
    // m_delayParams
    if (obj.contains("delayParams")) {
        QJsonObject d = obj["delayParams"].toObject();
        m_delayParams.laserOnDelay = d["laserOnDelay"].toInt();
        m_delayParams.laserOffDelay = d["laserOffDelay"].toInt();
        m_delayParams.markDelay = d["markDelay"].toInt();
        m_delayParams.jumpDelay = d["jumpDelay"].toInt();
        m_delayParams.polygonDelay = d["polygonDelay"].toInt();
    }
    // m_contourFillParams
    if (obj.contains("offsetParams")) {
        QJsonObject o = obj["offsetParams"].toObject();
        m_contourFillParams.offset = o["offset"].toDouble();
        m_contourFillParams.offsetCount = o["offsetCount"].toInt();
    }
    // m_vectorCopyParams
    if (obj.contains("vectorCopyParams")) {
        QJsonObject v = obj["vectorCopyParams"].toObject();
        m_vectorCopyParams.dir = QPointF(v["dirX"].toDouble(), v["dirY"].toDouble());
        m_vectorCopyParams.spacing = v["spacing"].toDouble();
        m_vectorCopyParams.count = v["count"].toInt();
    }
    // m_matrixCopyParams
    if (obj.contains("matrixCopyParams")) {
        QJsonObject m = obj["matrixCopyParams"].toObject();
        m_matrixCopyParams.hVec = QPointF(m["hVecX"].toDouble(), m["hVecY"].toDouble());
        m_matrixCopyParams.vVec = QPointF(m["vVecX"].toDouble(), m["vVecY"].toDouble());
        m_matrixCopyParams.hSpacing = m["hSpacing"].toDouble();
        m_matrixCopyParams.vSpacing = m["vSpacing"].toDouble();
        m_matrixCopyParams.hCount = m["hCount"].toInt();
        m_matrixCopyParams.vCount = m["vCount"].toInt();
        m_matrixCopyParams.copiedOrder = m["copiedOrder"].toInt();
    }
}

QJsonObject GraphicsItem::saveBaseParamsToJson() const {
    QJsonObject obj;
    // --- Color ---
    obj["color"] = m_color.name ();
    // --- MarkParams ---
    QJsonObject mark;
    mark["markSpeed"] = QJsonValue(static_cast<int>(m_markParams.markSpeed));
    mark["jumpSpeed"] = m_markParams.jumpSpeed;
    mark["frequency"] = QJsonValue(static_cast<int>(m_markParams.frequency));
    mark["operateTime"] = QJsonValue(static_cast<int>(m_markParams.operateTime));
    mark["power"] = m_markParams.power;
    mark["pulseLength"] = QJsonValue(static_cast<int>(m_markParams.pulseLength));
    mark["wobelAml"] = QJsonValue(static_cast<int>(m_markParams.wobelAml));
    mark["wobelFreq"] = QJsonValue(static_cast<int>(m_markParams.wobelFreq));
    obj["markParams"] = mark;
    // --- DelayParams ---
    QJsonObject delay;
    delay["laserOnDelay"] = QJsonValue(static_cast<int>(m_delayParams.laserOnDelay));
    delay["laserOffDelay"] = QJsonValue(static_cast<int>(m_delayParams.laserOffDelay));
    delay["markDelay"] = QJsonValue(static_cast<int>(m_delayParams.markDelay));
    delay["jumpDelay"] = QJsonValue(static_cast<int>(m_delayParams.jumpDelay));
    delay["polygonDelay"] = QJsonValue(static_cast<int>(m_delayParams.polygonDelay));
    obj["delayParams"] = delay;
    // --- ContourFillParams ---
    QJsonObject offset;
    offset["offset"] = m_contourFillParams.offset;
    offset["offsetCount"] = m_contourFillParams.offsetCount;
    obj["offsetParams"] = offset;
    // --- VectorCopyParams ---
    QJsonObject vector;
    vector["dirX"] = m_vectorCopyParams.dir.x();
    vector["dirY"] = m_vectorCopyParams.dir.y();
    vector["spacing"] = m_vectorCopyParams.spacing;
    vector["count"] = m_vectorCopyParams.count;
    obj["vectorCopyParams"] = vector;
    // --- MatrixCopyParams ---
    QJsonObject matrix;
    matrix["hVecX"] = m_matrixCopyParams.hVec.x();
    matrix["hVecY"] = m_matrixCopyParams.hVec.y();
    matrix["vVecX"] = m_matrixCopyParams.vVec.x();
    matrix["vVecY"] = m_matrixCopyParams.vVec.y();
    matrix["hSpacing"] = m_matrixCopyParams.hSpacing;
    matrix["vSpacing"] = m_matrixCopyParams.vSpacing;
    matrix["hCount"] = m_matrixCopyParams.hCount;
    matrix["vCount"] = m_matrixCopyParams.vCount;
    matrix["copiedOrder"] = m_matrixCopyParams.copiedOrder;
    obj["matrixCopyParams"] = matrix;
    return obj;
}

QString GraphicsItem::getName() const {
    return "GraphicsItem";
}

const QString GraphicsItem::getUUID()const {
    return this->m_uuid;
}



QVariant GraphicsItem::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == QGraphicsItem::ItemPositionHasChanged) {
        EditController::getIns().onGraphicsItemPositionHasChanged(this->getUUID());
    }
    if (change == QGraphicsItem::ItemSelectedHasChanged) {
        bool selected = value.toBool();
        EditController::getIns().onGraphicsItemSelectedHasChanged(this->getUUID(), selected);
    }
    return QGraphicsItem::itemChange(change, value);
}

void GraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseReleaseEvent(event);
    EditController::getIns().onGraphicsItemMouseRelease(this->getUUID());
}

void GraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mousePressEvent(event);
    EditController::getIns().onGraphicsItemMousePress(this->getUUID ());
}

