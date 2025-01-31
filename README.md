# LaserCAD

## Qt style

- color scheme: style/.xml
- font: consolas

## 命名

- Qt 框架重载函数: Camel Case;
- 普通成员函数: Camel Case;
- 自定义 signals/函数: Snake Case;

## TODO

- 优先教程
- LaserItem
  重载 itemPos():先算出中心,再每次根据 item->itemPos()计算更新(itemPos 每次初始值都会设置在 0,0 而不是物体中心);
