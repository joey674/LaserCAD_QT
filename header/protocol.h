#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <qgraphicsitem.h>
#include <QPen>

/*****************************************************************************
 * MainWindow
 *****************************************************************************/
enum OperationEvent
{
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
enum MouseEvent
{
    LeftPress,
    RightPress,
    LeftRelease,
    RightRelease,
    MouseMove,
};

/*****************************************************************************
 * GraphicsItem
 *****************************************************************************/
struct Vertex /*标准Vertex代替pointF定义；其中角度代表和上个点之间形成弧的角度，也就是说对于弧（p1，p2），只有p2的angle是有作用的*/
{
    QPointF point;
    double angle;
};
Q_DECLARE_METATYPE(Vertex)

enum LineType /*item内部使用 判断当前item是原生对象还是生成的附属offset对象*/
{
    OriginItem,
    offsetItem,
};

enum ItemTypeId /* 只用于GraphicsItem重载type变量, 用于识别type 不参与实际使用 */
{
    Polyline = 6270,
    Arc = 6271,
    Line = 6272,
    Point = 6273,
    Circle = 6274,
    Spiral =6275,
    Rect = 6276,
    Polygon = 6277,
    Ellipse = 6278,
};

const std::pair<double,double> GeneralPointSize = std::pair<double,double>{1,1}; /*标准点在x、y方向上的半径*/


/*****************************************************************************
 * GraphicsView
 * 绘制对象使用的画笔
 *****************************************************************************/
const QPen DISPLAY_PEN = [](){
    QPen pen(Qt::black, 1);
    pen.setCosmetic(true);
    return pen;
}();

const QPen EDIT_PEN = [](){
    QPen pen(Qt::green, 1);
    pen.setCosmetic(true);
    return pen;
}();

const QPen AXIS_PEN = [](){
    QPen pen(Qt::red, 1);
    pen.setCosmetic(true);
    return pen;
}();

/*****************************************************************************
 * Manager
 * PropertyMap
 *****************************************************************************/
using UUID = QString;

enum PropertyIndex{
    Visible,
    Selectable,
    Movable,
    Pen,
    Position,
    CustomProperty
};
inline const std::map<PropertyIndex, QVariant> DefaultPropertyMap = {
    {PropertyIndex::Visible, QVariant(true)},
    {PropertyIndex::Selectable, QVariant(true)},
    {PropertyIndex::Movable,QVariant(true)},
    {PropertyIndex::Pen,DISPLAY_PEN},
    {PropertyIndex::Position,QPointF{}},
    {PropertyIndex::CustomProperty,QMap<QString,QVariant>()},
};

inline const QMap<QString,QVariant> DefaultCustomPropertyArc = QMap<QString,QVariant>{
                                                                            { "Vertex0", QVariant::fromValue(Vertex{}) },
                                                                            { "Vertex1", QVariant::fromValue(Vertex{}) }};
inline const QMap<QString,QVariant> DefaultCustomPropertyLine = QMap<QString,QVariant>{
                                                                             { "Vertex0", QVariant::fromValue(Vertex{}) },
                                                                             { "Vertex1", QVariant::fromValue(Vertex{}) }};

/*****************************************************************************
 * TreeViewModel
 * TreeNode
 *****************************************************************************/
enum class TreeNodePropertyIndex: int
{
    Name = 0,       // QString
    Type = 1,         // QString
    UUID = 2,        // QString
};

#endif // PROTOCOL_H
