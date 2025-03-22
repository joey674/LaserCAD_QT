#ifndef PROTOCOL1_H
#define PROTOCOL1_H

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

#endif // PROTOCOL1_H
