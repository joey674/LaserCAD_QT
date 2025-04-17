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
};

const std::pair < double, double > DisplayPointSize = std::pair < double, double > {1, 1}; /*标准点在x、y方向上的半径*/
const std::pair < double, double > EditPointSize = std::pair < double, double > {4, 4};

/*****************************************************************************
 * GraphicsView
 * 绘制对象使用的画笔
 *****************************************************************************/
const QPen DISPLAY_PEN = []() {
    QPen pen(Qt::black, 1);
    pen.setCosmetic(true);
    return pen;
}
();

const QPen EDIT_PEN = []() {
    QPen pen(Qt::green, 1);
    pen.setCosmetic(true);
    return pen;
}
();

const QPen AXIS_PEN = []() {
    QPen pen(Qt::red, 1);
    pen.setCosmetic(true);
    return pen;
}
();

/*****************************************************************************
 * Manager
 * PropertyMap
 *****************************************************************************/
using UUID = QString;

struct MarkParams {
    double markSpeed = 1000;
    double jumpSpeed = 3000;
    int frequency = 100000;
    int repetTime = 1;
    double power = 0;
    double pulseWidth = 2;
    int wobelAml = 0;
    int wobelFreq = 100;

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

Q_DECLARE_METATYPE(MarkParams);

struct DelayParams {
    int startDelay = 100;
    int endDelay = 120;
    int markDelay = 10;
    int jumpDelay = 20;
    int polygonDelay = 0;

    bool set(const QString& key, const QVariant& val) {
        if (key == "startDelay" || key == "DelayParams: startDelay")     {
            startDelay = val.toInt();
            return true;
        }
        if (key == "endDelay" || key == "DelayParams: endDelay")       {
            endDelay = val.toInt();
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

Q_DECLARE_METATYPE(DelayParams);

enum PropertyIndex {
    Visible,
    Selectable,
    Movable,
    Pen,
    // Position,
    ParallelOffset,
    ParallelOffsetNum,
    // Geometry,
    Mark,
    Delay,
};

inline const std::map < PropertyIndex, QVariant > DefaultPropertyMap
= {{PropertyIndex::Visible, QVariant(true)},
    {PropertyIndex::Selectable, QVariant(true)},
    {PropertyIndex::Movable, QVariant(true)},
    {PropertyIndex::Pen, DISPLAY_PEN},
    // {PropertyIndex::Position, QPointF{}},
    {PropertyIndex::ParallelOffset, 0},
    {PropertyIndex::ParallelOffsetNum, 0},
    // {PropertyIndex::Geometry, QMap < QString, QVariant > ()},
    {PropertyIndex::Mark, QVariant::fromValue (MarkParams{})},
    {PropertyIndex::Delay, QVariant::fromValue (DelayParams{})},
};
/// 暂时不用 先用item自己的get函数就行, 不然要实时更新太麻烦了 到时候再封装manager就行
// inline const QMap < QString, QVariant > GeometryArc = QMap < QString, QVariant > {
//     { "Vertex0", QVariant::fromValue(Vertex{}) },
//     { "Vertex1", QVariant::fromValue(Vertex{}) }
// };
// inline const QMap < QString, QVariant > GeometryLline = QMap < QString, QVariant > {
//     { "Vertex0", QVariant::fromValue(Vertex{}) },
//     { "Vertex1", QVariant::fromValue(Vertex{}) }
// };
// inline const QMap < QString, QVariant > GeometryCircle = QMap < QString, QVariant > {
//     { "Radius", 0}
// };
// inline const QMap < QString, QVariant > GeometryPoint = QMap < QString, QVariant > {
// };

/*****************************************************************************
 * TreeViewModel
 * TreeNode
 *****************************************************************************/
enum class TreeNodePropertyIndex : int {
    Name = 0,       // QString
    Type = 1,         // QString
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
