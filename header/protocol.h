#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <qgraphicsitem.h>
#include <QPen>

/*****************************************************************************
 * MainWindow
 *****************************************************************************/
enum OperationEvent {
    None,
    // 编辑工具
    DragScene,
    EditProperty,
    // 绘制工具
    DrawLine,
    DrawArc,
    DrawPolyline,
    DrawPoint,
    DrawCircle,
    DrawSpiral,
    DrawRect,
    DrawEllipse,
    DrawPolygon
};
enum MouseEvent {
    LeftPress,
    RightPress,
    LeftRelease,
    RightRelease,
    MouseMove,
};

/*****************************************************************************
 * GraphicsItem
 *****************************************************************************/
struct Vertex { /*标准Vertex代替pointF定义；其中角度代表和上个点之间形成弧的角度，也就是说对于弧（p1，p2），只有p2的angle是有作用的*/
    QPointF point;
    double angle;
};
Q_DECLARE_METATYPE(Vertex)

enum LineType /*item内部使用 判断当前item是原生对象还是生成的附属offset对象*/
{
    OriginItem,
    offsetItem,
};

enum GraphicsItemType /* 用于识别type */
{
    Polyline = 6270,
    Arc = 6271,
    Line = 6272,
    Point = 6273,
    Circle = 6274,
    Spiral = 6275,
    Rect = 6276,
    Polygon = 6277,
    Ellipse = 6278,
    Combined = 6279,
};


/*****************************************************************************
 * Manager
 * editTabWidget
 *****************************************************************************/
using UUID = QString;

struct MarkParams {
    double markSpeed = 1000;
    double jumpSpeed = 3000;
    unsigned int frequency = 100000;
    unsigned int repetTime = 1; // 1代表打1次 n代表打n次
    double power = 0;
    unsigned int pulseWidth = 2;
    unsigned int wobelAml = 0;
    unsigned int wobelFreq = 100;

    bool set(const QString& key, const QVariant& val) {
        if (key == "markSpeed" || key == "MarkParams: markSpeed")        {
            markSpeed = val.toDouble();
            return true;
        }
        if (key == "jumpSpeed" || key == "MarkParams: jumpSpeed")        {
            jumpSpeed = val.toDouble();
            return true;
        }
        if (key == "frequency" || key == "MarkParams: frequency")        {
            frequency = val.toInt();
            return true;
        }
        if (key == "repetTime" || key == "MarkParams: repetTime")        {
            repetTime = val.toInt();
            return true;
        }
        if (key == "power" || key == "MarkParams: power")            {
            power = val.toDouble();
            return true;
        }
        if (key == "pulseWidth" || key == "MarkParams: pulseWidth")       {
            pulseWidth = val.toDouble();
            return true;
        }
        if (key == "wobelAml" || key == "MarkParams: wobelAml")         {
            wobelAml = val.toInt();
            return true;
        }
        if (key == "wobelFreq" || key == "MarkParams: wobelFreq")        {
            wobelFreq = val.toInt();
            return true;
        }
        return false;
    }
};

struct DelayParams {
    unsigned int laserOnDelay = 100;
    unsigned int laserOffDelay = 120;
    unsigned int markDelay = 10;
    unsigned int jumpDelay = 20;
    unsigned int polygonDelay = 0;

    bool set(const QString& key, const QVariant& val) {
        if (key == "laserOnDelay" || key == "DelayParams: laserOnDelay")     {
            laserOnDelay = val.toInt();
            return true;
        }
        if (key == "laserOffDelay" || key == "DelayParams: laserOffDelay")       {
            laserOffDelay = val.toInt();
            return true;
        }
        if (key == "markDelay" || key == "DelayParams: markDelay")      {
            markDelay = val.toInt();
            return true;
        }
        if (key == "jumpDelay" || key == "DelayParams: jumpDelay")      {
            jumpDelay = val.toInt();
            return true;
        }
        if (key == "polygonDelay" || key == "DelayParams: polygonDelay")   {
            polygonDelay = val.toInt();
            return true;
        }
        return false;
    }
};

struct OffsetParams {
    double offset=0;
    int offsetCount=0;
};

struct FillParams{
    double spacing = 0; // 填充线段间隔
    double startAngle = 0;
    double sideLength = 0;// 填充线段相对于填充多边形的距离
    // 均匀打印功能: 可以旋转打印填充线段
    double accumulateAngle = 0;
    int operateCount = 1; // 填充次数(设置为0就是不填充)
};

struct VectorCopyParams {
    QPointF dir = {0,0};
    double spacing = 0;
    int count = 0;

    void setEmpty() {
        dir = QPointF(0, 0);
        spacing = 0.0;
        count = 0;
    }
    bool checkEmpty() const {
        return dir == QPointF(0, 0) && spacing == 0.0 && count == 0;
    }
};

struct MatrixCopyParams {
    QPointF hVec= {0,0};
    QPointF vVec= {0,0};
    double hSpacing = 0;
    double vSpacing=0;
    int hCount=0;
    int vCount=0;
    int copiedOrder=0;

    void setEmpty() {
        hVec = QPointF(0, 0);
        vVec = QPointF(0, 0);
        hSpacing = 0.0;
        vSpacing = 0.0;
        hCount = 0;
        vCount = 0;
        copiedOrder = 0;
    }
    bool checkEmpty() const {
        return hVec == QPointF(0, 0) &&
               vVec == QPointF(0, 0) &&
               hSpacing == 0.0 &&
               vSpacing == 0.0 &&
               hCount == 0 &&
               vCount == 0 &&
               copiedOrder == 0;
    }
};

/*****************************************************************************
 * Hardware
 * systemTabWidgeet
 *****************************************************************************/
struct RTCSettings {
    QString cardType;
    QString correctionFilePath;
    double scale;
    double scaleCorX, scaleCorY;
    double rotation;
    double offsetX, offsetY;
    QString laserMode;
    bool flipX, flipY;
};

/*****************************************************************************
 * TreeViewModel
 * TreeNode
 *****************************************************************************/
enum class TreeNodePropertyIndex : int {
    Name = 0,       // QString
    Type = 1,         // QString: Layer/Group/Item/Signal
    UUID = 2,        // QString
};

/*****************************************************************************
 * Tab与EditController通信
 *****************************************************************************/
struct MultiEditParam {
    QString fieldName;
    QVariant baseValue;
    QVariant deltaValue;
};
#endif // PROTOCOL_H
