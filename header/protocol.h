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
    DrawCircle,
    DrawPolyline,
    DrawSpiral,
    DrawArc,
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
struct Vertex
{
    QPointF point;
    double angle;
};
Q_DECLARE_METATYPE(Vertex)

enum LineType
{
    OriginItem,
    offsetItem,
};

enum ItemTypeId /* 只用于GraphicsItem重载type变量, 用于识别type 不参与实际使用 */
{
    Polyline = 6270,
    Arc = 6271,
    Line = 6272
};


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
const std::map<PropertyIndex, QVariant> DefaultPropertyMap = {
    {PropertyIndex::Visible, QVariant(true)},
    {PropertyIndex::Selectable, QVariant(true)},
    {PropertyIndex::Movable,QVariant(true)},
    {PropertyIndex::Pen,DISPLAY_PEN},
    {PropertyIndex::Position,QPointF{}},
    {PropertyIndex::CustomProperty,QMap<QString,QVariant>()},
};

const QMap<QString,QVariant> DefaultCustomPropertyArc = QMap<QString,QVariant>{
                                                                            { "Vertex0", QVariant::fromValue(Vertex{}) },
                                                                            { "Vertex1", QVariant::fromValue(Vertex{}) }};
const QMap<QString,QVariant> DefaultCustomPropertyLine = QMap<QString,QVariant>{
                                                                             { "Vertex0", QVariant::fromValue(Vertex{}) },
                                                                             { "Vertex1", QVariant::fromValue(Vertex{}) }};

/*****************************************************************************
 * TreeViewModel
 * TreeNode
 *****************************************************************************/
enum class NodePropertyIndex: int
{
    Name = 0,       // QString
    Type = 1,         // QString
    UUID = 2,        // QString
};

#endif // PROTOCOL_H
