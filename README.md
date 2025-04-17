# LaserCAD

## 使用指南
- 绘制图形:  先点击对应的绘制按钮
    - 绘制点: 左键点击绘制
    - 绘制直线: 左键点击设置第一个点;再次点击左键绘制第二个点
    - 绘制弧: 采用三点画弧法, 三次左键点击即可
    - 绘制多段线: 左键点击绘制点, 右键点击绘制最后一个点; 按住ctrl绘制半弧;点按caps切换弧的方向
    - 绘制矩形: 左键两次点击确定矩形左上角和右下角
    - 绘制圆: 左键点击确定圆心 再次点击确定半径
    - 绘制椭圆: 左键点击确定圆心;再两次点击确定互相垂直的两个方向上的轴长
- 编辑功能: 任意情况下右键连击两次,或者点击编辑按钮
    - 只有此模式下可以拖拽图形
- 旋转对象:
- TODO
## DevLogs
https://bo7zwj4hof.larksuite.com/docx/S4YudowaZowtVMxJ7Goua4irsJg?from=from_copylink

## Qt style
- color scheme: style/.xml
- font: Arial Rounded MT
- off (visualize indent)

## 命名
- 普通成员函数:          
    - Camel Case    initTitleBar;
- Qt 框架重载函数:    
    - Camel Case    keyPressEvent;
-  signals函数: 
    - Camel Case    keyPressed;
- slots函数: 
    - Camel Case    onKeyPressed;   

- 成员变量: m_variableA

