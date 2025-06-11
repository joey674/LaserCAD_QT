#include "css.h"
#include <QApplication>
#include <QFont>

void initGlobalStyle()
{
    // 设置全局字体
    QFont font("Microsoft YaHei", 10);
    font.setWeight(QFont::Normal);
    qApp->setFont(font);

    // 设置全局样式表
    qApp->setStyleSheet(R"(
        QPushButton {
            background-color: #4CAF50;
            color: white;
            border: none;
            padding: 6px 12px;
            border-radius: 4px;
        }
        QPushButton:hover {
            background-color: #45A049;
        }
        QPushButton:pressed {
            background-color: #3e8e41;
        }
        QPushButton:disabled {
            background-color: #9E9E9E;
            color: #ffffff;
            border: none;
        }

        QLabel {
            color: #222222;
        }

        QLineEdit {
            border: 1px solid #ccc;
            border-radius: 4px;
            padding: 4px;
        }

        QMainWindow {
            background-color:#EDEDED /*#F5F5F5*/;
        }
    )");
}

const QString buttonStyle1 = R"(
        QToolButton {
            border-radius: 15px;
            background-color: #d0d0d0;
            color: black;
            padding: 5px;
            margin: 0px;
        }
        QToolButton:hover {
            background-color: #c0c0c0;
        }
        QToolButton:pressed {
            background-color: #b0b0b0;
        }
        QToolButton:checked {
            background-color: #b0b0b0;
        }
    )";

const QString buttonStyle2 = R"(
        QPushButton{
            background-color: skyblue;
            border: none;
            border-radius: 12px;
            color:white;
            padding: 15px 32px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            font-size: 16px;
            margin: 4px 2px;
            cursor: pointer;
            transition-duration: 0.4s;
        }
        QPushButton:hover{
            box-shadow: 0 12px 16px 0 rgba(0,0,0,.24),
            0 17px 50px 0 rgba(0,0,0,.19);
        }
    )";

const QString comboBoxStyle1 = R"(
    QComboBox {
        border: 1px solid transparent;
        border-radius: 15px;
        background-color: #d0d0d0;
        color: black;
        padding: 5px;
        min-width: 6em;
    }

    QComboBox:hover {
        background-color: #c0c0c0;
    }

    QComboBox:pressed, QComboBox:on {
        background-color: #b0b0b0;
    }

    QComboBox::drop-down {
        subcontrol-origin: padding;
        subcontrol-position: top right;
        width: 20px;
        border-left: 1px solid gray;
    }
)";

const QString treeViewModelStyle1 = (R"(
    QTreeView {
        font-size: 13px;   /* 设置字体大小 */
    }
    QTreeView::item {
        min-height: 20px;  /* 设置每一行的最小高度 */
    }
    QTreeView::item:selected {
        background: #3399FF;  /* 选中时的背景颜色 */
        color: white;
    }
)");

const QString drawSpiralButtonToolTip("<html><head/>"
                                      "<body>"
                                      "<p><span style=\"font-weight:700;\">螺旋线工具</span></p>"
                                      "<p>绘制螺旋线</p>"
                                      "<p>左键点击设置多边形中心；左键再次点击设置多边形大小</p>"
                                      "<p>按w添加多边形边数；按s减少多边形变数（最小为3）</p>"
                                      "</body></html>");

const QString drawPolygonButtonToolTip("<html><head/>"
                                       "<body>"
                                       "<p><span style=\"font-weight:700;\">正多边形工具</span></p>"
                                       "<p>绘制正多边形</p>"
                                       "<p>按w添加多边形边数；按s减少多边形变数（最小为3）</p>"
                                       "</body></html>");

const QString drawRectButtonToolTip("<html><head/>"
                                    "<body>"
                                    "<p><span style=\"font-weight:700;\">矩形工具</span></p>"
                                    "<p>绘制矩形</p>"
                                    "<p>左键点击设置矩形左上顶点，左键再次点击设置矩形右下顶点</p>"
                                    "</body></html>");

const QString drawEllipseButtonToolTip(
    "<html><head/>"
    "<body>"
    "<p><span style=\"font-weight:700;\">椭圆工具</span></p>"
    "<p>绘制椭圆</p>"
    "<p>"
    "左键点击设置圆心；左键再次点击确定一个方向上的椭圆半径；再次拉动"
    "鼠标点击确定垂直方向上的另一个椭圆半径</p>"
    "</body></html>");

const QString drawCircleButtonToolTip("<html><head/>"
                                      "<body>"
                                      "<p><span style=\"font-weight:700;\">圆形工具</span></p>"
                                      "<p>绘制圆</p>"
                                      "<p>左键点击设置圆心；左键再次点击设置圆弧大小</p>"
                                      "</body></html>");
const QString drawArcButtonToolTip("<html><head/>"
                                   "<body>"
                                   "<p><span style=\"font-weight:700;\">弧形工具</span></p>"
                                   "<p>绘制半弧</p>"
                                   "<p>左键点击设置初始点；左键再次点击设置结束点</p>"
                                   "</body></html>");
const QString drawLineButtonToolTip("<html><head/>"
                                    "<body>"
                                    "<p><span style=\" font-weight:700;\">直线工具</span></p>"
                                    "<p>绘制直线</p>"
                                    "</p><p>长按x/y锁定绘制方向</p></body></html>"
                                    "</body></html>");

const QString drawPolylineButtonToolTip("<html><head/>"
                                        "<body>"
                                        "<p><span style=\" font-weight:700;\">多段线工具</span></p>"
                                        "<p>绘制多段线</p>"
                                        "<p>长按ctrl切换绘制直线/圆弧；"
                                        "</p><p>按下capslock切换圆弧方向；"
                                        "</p><p>长按x/y锁定绘制方向</p></body></html>"
                                        "</body></html>");
