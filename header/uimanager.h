#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <QGridLayout>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QSpacerItem>
#include <QStatusBar>
#include <QToolButton>
#include <QWidget>
#include "graphicsview.h"
#include "tabwidget.h"
#include "treeview.h"
#include "css.h"
#include "motionstageworker.h"
#include  "motionstagedevicegoogol.h"
#include "motionstagedevicethorlabs.h"
#include "motionstagedevicetest.h"
#include "laserdevicertc5.h"
#include "hardwarecontroller.h"
#include "laserdevicetest.h"

class UiManager {
private:
    std::vector < QToolButton * > m_drawButtons;
    std::vector < QToolButton * > m_toolButtons;

public:
    // ProjectButton
    QToolButton *openProjectButton;
    QToolButton *saveProjectButton;
    QToolButton *createProjectButton;
    // LayerButton
    QToolButton *addLayerButton;
    QToolButton *deleteLayerButton;
    // ItemButton
    QToolButton *copyButton;
    QToolButton *cutButton;
    QToolButton *deleteButton;
    QToolButton *pasteButton;
    // combine/breakButton
    QToolButton *combineButton;
    QToolButton *breakButton;
    QToolButton *breakCopiedItemButton;
    QToolButton *breakContourFillItemButton;
    QToolButton *breakHatchFillItemButton;
    // ToolButton
    QToolButton *editButton;
    QToolButton *centerButton;
    QToolButton *mirrorHorizontalButton;
    QToolButton *mirrorVerticalButton;
    // SceneButton
    QToolButton *dragSceneButton;
    QToolButton *redoButton;
    QToolButton *undoButton;
    QToolButton *drawTestLineButton;
    // HardwareButton
    QToolButton *delayTimeButton;
    QToolButton *digitalInButton;
    QToolButton *digitalOutButton;
    QToolButton *doPauseButton;
    QToolButton *loopButton;
    QToolButton *motionButton;
    // DrawButton
    QToolButton *drawArcButton;
    QToolButton *drawCircleButton;
    QToolButton *drawEllipseButton;
    QToolButton *drawLineButton;
    QToolButton *drawPointButton;
    QToolButton *drawPolygonButton;
    QToolButton *drawPolylineButton;
    QToolButton *drawRectButton;
    QToolButton *drawSpiralButton;
    // Widget
    GraphicsView *graphicsView;
    TreeView *treeView;
    QStatusBar *statusBar;
    TabWidget *editTabWidget;
    TabWidget *systemTabWidget;

public:
    void initLayout(QWidget *parent)
    {
        // 设置全局layout
        this->setBasicLayout (parent);

        //设置组件样式

        // 设置按钮样式
        this->setDrawToolButtonStyle();
        this->setEditToolButtonStyle ();
        this->setLayerButtonStyle ();
        this->setSignalButtonStyle ();
        this->setProjectButtonStyle ();
    }

private:
    void setBasicLayout(QWidget *parent)
    {
        // 左侧栏容器
        QWidget *sideBar = new QWidget;
        sideBar->setFixedWidth(150);
        sideBar->setStyleSheet(R"(
            background-color: #2b2b2b;
        )");

        QVBoxLayout *btnLayout = new QVBoxLayout(sideBar);
        btnLayout->setSpacing(10);
        btnLayout->setContentsMargins(0, 20, 0, 20);

        auto createButton = [](const QString &text) {
            QToolButton *btn = new QToolButton;
            btn->setText(text);
            btn->setCheckable(true);
            btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
            btn->setMinimumHeight(50);
            btn->setStyleSheet(R"(
            QToolButton {
                color: white;
                background: transparent;
                font-size: 18px;
                font-weight: bold;
                border: none;
                qproperty-iconSize: 24px;
                text-align: center;
            }
            QToolButton:hover {
                background-color: #444;
            }
            QToolButton:checked {
                background-color: #007acc;
            }
        )");
            return btn;
        };

        QToolButton *btnDraw = createButton("Draw");
        QToolButton *btnControl = createButton("Control");
        QToolButton *btnSetting = createButton("Setting");

        QToolButton *markButton = createLabeledIconButton("Mark", ":/button/markButton.png");

        btnDraw->setChecked(true);

        btnLayout->addWidget(btnDraw);
        btnLayout->addWidget(btnControl);
        btnLayout->addWidget(btnSetting);
        btnLayout->addStretch();
        btnLayout->addWidget(markButton);

        QStackedWidget *stack = new QStackedWidget;
        stack->addWidget(createDrawPage());
        stack->addWidget(createControlPage());
        stack->addWidget (createSettingPage());

        QHBoxLayout *mainLayout = new QHBoxLayout(parent);
        mainLayout->setMargin(0);
        mainLayout->setSpacing(0);
        mainLayout->addWidget(sideBar);
        mainLayout->addWidget(stack);

        // 信号
        parent->connect(btnDraw, &QToolButton::clicked, parent, [=]() {
            btnDraw->setChecked(true);
            btnControl->setChecked(false);
            btnSetting->setChecked(false);
            stack->setCurrentIndex(0);
        });
        parent->connect(btnControl, &QToolButton::clicked, parent, [=]() {
            btnControl->setChecked(true);
            btnDraw->setChecked(false);
            btnSetting->setChecked(false);
            stack->setCurrentIndex(1);
        });
        parent->connect(btnSetting, &QToolButton::clicked, parent, [=]() {
            btnControl->setChecked(false);
            btnDraw->setChecked(false);
            btnSetting->setChecked(true);
            stack->setCurrentIndex(2);
        });

        QObject::connect(markButton, &QToolButton::clicked, parent, [=]() {
            HardwareController::getIns ().onMarkButtonClicked (parent);
        });
    }

    QWidget *createDrawPage()
    {
        QWidget *page = new QWidget;
        QGridLayout *mainGLayout = new QGridLayout(page);
        page->setLayout(mainGLayout);

        /* *******************************************************************************
        第一行按钮布局
        ******************************************************************************* */
        QHBoxLayout *buttonHLayout1 = new QHBoxLayout();

        // projectButton
        createProjectButton = new QToolButton(page);
        buttonHLayout1->addWidget(createProjectButton);
        openProjectButton = new QToolButton(page);
        buttonHLayout1->addWidget(openProjectButton);
        saveProjectButton = new QToolButton(page);
        buttonHLayout1->addWidget(saveProjectButton);

        // 分隔线
        QFrame *splitLine1 = new QFrame(page);
        splitLine1->setFrameShape(QFrame::VLine);
        splitLine1->setFrameShadow(QFrame::Sunken);
        buttonHLayout1->addWidget(splitLine1);

        // layerButton
        addLayerButton = new QToolButton(page);
        buttonHLayout1->addWidget(addLayerButton);
        deleteLayerButton = new QToolButton(page);
        buttonHLayout1->addWidget(deleteLayerButton);

        // 剩余区域补齐
        buttonHLayout1->addSpacerItem(
            new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
        mainGLayout->addLayout(buttonHLayout1, 0, 0);

        /* *******************************************************************************
        第二行按钮布局
        ******************************************************************************* */
        QHBoxLayout *buttonHLayout2 = new QHBoxLayout();

        // copy/pasteButton
        copyButton = new QToolButton(page);
        buttonHLayout2->addWidget(copyButton);
        cutButton = new QToolButton(page);
        buttonHLayout2->addWidget(cutButton);
        pasteButton = new QToolButton(page);
        buttonHLayout2->addWidget(pasteButton);
        deleteButton = new QToolButton(page);
        buttonHLayout2->addWidget(deleteButton);

        QFrame *splitLine3 = new QFrame(page); // 插入分隔线
        splitLine3->setFrameShape(QFrame::VLine);
        splitLine3->setFrameShadow(QFrame::Sunken);
        buttonHLayout2->addWidget(splitLine3);

        // combined break button
        combineButton = new QToolButton(page);
        buttonHLayout2->addWidget(combineButton);
        breakButton = new QToolButton(page);
        buttonHLayout2->addWidget(breakButton);
        breakCopiedItemButton = new QToolButton(page);
        buttonHLayout2->addWidget(breakCopiedItemButton);
        breakContourFillItemButton = new QToolButton(page);
        buttonHLayout2->addWidget(breakContourFillItemButton);
        breakHatchFillItemButton = new QToolButton(page);
        buttonHLayout2->addWidget(breakHatchFillItemButton);

        QFrame *splitLine3_1 = new QFrame(page); // 插入分隔线
        splitLine3_1->setFrameShape(QFrame::VLine);
        splitLine3_1->setFrameShadow(QFrame::Sunken);
        buttonHLayout2->addWidget(splitLine3_1);

        // toolButton
        editButton = new QToolButton(page);
        buttonHLayout2->addWidget(editButton);
        mirrorHorizontalButton = new QToolButton(page);
        buttonHLayout2->addWidget(mirrorHorizontalButton);
        mirrorVerticalButton = new QToolButton(page);
        buttonHLayout2->addWidget(mirrorVerticalButton);
        centerButton = new QToolButton(page);
        buttonHLayout2->addWidget(centerButton);

        QFrame *splitLine4 = new QFrame(page); // 插入分隔线
        splitLine4->setFrameShape(QFrame::VLine);
        splitLine4->setFrameShadow(QFrame::Sunken);
        buttonHLayout2->addWidget(splitLine4);

        // sceneButton
        dragSceneButton = new QToolButton(page);
        buttonHLayout2->addWidget(dragSceneButton);

        // utilsButton
        drawTestLineButton = new QToolButton(page);
        buttonHLayout2->addWidget(drawTestLineButton);
        // redoButton = new QToolButton(page);
        // buttonHLayout2->addWidget(redoButton);
        // undoButton = new QToolButton(page);
        // buttonHLayout2->addWidget(undoButton);

        QFrame *splitLine5 = new QFrame(page); // 插入分隔线
        splitLine5->setFrameShape(QFrame::VLine);
        splitLine5->setFrameShadow(QFrame::Sunken);
        buttonHLayout2->addWidget(splitLine5);

        // signalButton
        delayTimeButton = new QToolButton(page);
        buttonHLayout2->addWidget(delayTimeButton);
        digitalInButton = new QToolButton(page);
        buttonHLayout2->addWidget(digitalInButton);
        digitalOutButton = new QToolButton(page);
        buttonHLayout2->addWidget(digitalOutButton);
        doPauseButton = new QToolButton(page);
        buttonHLayout2->addWidget(doPauseButton);
        loopButton = new QToolButton(page);
        buttonHLayout2->addWidget(loopButton);
        motionButton = new QToolButton(page);
        buttonHLayout2->addWidget(motionButton);

        QFrame *splitLine6 = new QFrame(page); // 插入分隔线
        splitLine6->setFrameShape(QFrame::VLine);
        splitLine6->setFrameShadow(QFrame::Sunken);
        buttonHLayout2->addWidget(splitLine6);

        //
        buttonHLayout2->addSpacerItem(
            new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

        mainGLayout->addLayout(buttonHLayout2, 1, 0);

        /* *******************************************************************************
        第三行控件布局
        ******************************************************************************* */
        QHBoxLayout *widgetBLayout3 = new QHBoxLayout();
        QWidget *container1 = new QWidget(page);

        // 第一列控件
        QVBoxLayout *container1Layout = new QVBoxLayout(container1);

        treeView = new TreeView(page);
        container1Layout->addWidget(treeView, /*stretch=*/1);

        editTabWidget = new TabWidget(page); // 下方TabWidget
        editTabWidget->setMinimumWidth (400);
        editTabWidget->setMinimumHeight (600);
        container1Layout->addWidget(editTabWidget, /*stretch=*/1);

        widgetBLayout3->addWidget(container1, /*stretch=*/1);

        // 第二列控件 graphicview
        graphicsView = new GraphicsView(page); // 右：GraphicsView，占比 3
        widgetBLayout3->addWidget(graphicsView, /*stretch=*/3);

        // 第三列控件 buttons
        QVBoxLayout *drawButtonLayout = new QVBoxLayout(); // 最右：绘图按钮栏，占最小固定宽度
        drawPointButton = new QToolButton(page);
        drawButtonLayout->addWidget(drawPointButton);
        drawLineButton = new QToolButton(page);
        drawButtonLayout->addWidget(drawLineButton);
        drawArcButton = new QToolButton(page);
        drawButtonLayout->addWidget(drawArcButton);
        drawPolylineButton = new QToolButton(page);
        drawButtonLayout->addWidget(drawPolylineButton);
        drawCircleButton = new QToolButton(page);
        drawButtonLayout->addWidget(drawCircleButton);
        drawRectButton = new QToolButton(page);
        drawButtonLayout->addWidget(drawRectButton);
        drawEllipseButton = new QToolButton(page);
        drawButtonLayout->addWidget(drawEllipseButton);
        drawPolygonButton = new QToolButton(page);
        drawButtonLayout->addWidget(drawPolygonButton);
        drawSpiralButton = new QToolButton(page);
        drawButtonLayout->addWidget(drawSpiralButton);
        drawButtonLayout->addSpacerItem(
            new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
        QWidget *drawContainer = new QWidget(page);
        drawContainer->setLayout(drawButtonLayout);
        drawContainer->setMinimumWidth(60);
        widgetBLayout3->addWidget(drawContainer, /*stretch=*/0);

        //
        mainGLayout->addLayout(widgetBLayout3, 2, 0);

        //
        return page;
    }

    QWidget *createControlPage()
    {
        QWidget *page = new QWidget;
        QHBoxLayout *mainLayout = new QHBoxLayout(page);
        page->setLayout(mainLayout);

        mainLayout->addWidget(wrapWithTitle("System Control", createSystemControlWidget()));
        mainLayout->addWidget(createVerticalLine());

        mainLayout->addWidget(wrapWithTitle("Stage Control", createMotionStageControlWidget()));
        mainLayout->addWidget(createVerticalLine());

        mainLayout->addStretch();

        return page;
    }

    QWidget *createSettingPage()
    {
        QWidget *page = new QWidget;
        QHBoxLayout *mainLayout = new QHBoxLayout(page);
        page->setLayout(mainLayout);

        mainLayout->addWidget(wrapWithTitle("RTC Setting", createRTCSettingWidget()));
        mainLayout->addWidget(createVerticalLine());

        mainLayout->addWidget(wrapWithTitle("MotionStage Setting", createMotionStageSettingWidget()));
        mainLayout->addWidget(createVerticalLine());

        mainLayout->addStretch();

        return page;
    }


    QFrame *createVerticalLine(QWidget *parent = nullptr) {
        QFrame *line = new QFrame(parent);
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        line->setLineWidth(1);
        return line;
    }

    QWidget *wrapWithTitle(const QString &title, QWidget *contentWidget)
    {
        QWidget *container = new QWidget;
        container->setMaximumWidth (600);
        QVBoxLayout *layout = new QVBoxLayout(container);
        layout->setSpacing(5);
        layout->setContentsMargins(0, 0, 0, 0);

        QLabel *label = new QLabel(title);
        label->setAlignment(Qt::AlignHCenter);
        label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        label->setStyleSheet("font-weight: bold; font-size: 20px;");

        layout->addWidget(label);
        layout->addWidget(contentWidget);

        return container;
    }

    QToolButton *createLabeledIconButton(const QString &title, const QString &iconPath)
    {
        QToolButton *button = new QToolButton;
        button->setText(title);
        button->setIcon(QIcon(iconPath));
        button->setIconSize(QSize(60, 60));
        button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        button->setFixedSize(150, 100);
        button->setStyleSheet(R"(
        QToolButton {
            background: transparent;
            border: none;
            color: white;
            font-weight: bold;
            font-size: 18px;
        }
        QToolButton:hover {
            background-color: #444;
        }
    )");
        return button;
    }

    void setDrawToolButtonStyle() {
        QString buttonStyle = buttonStyle1;
        // 绘制工具
        QToolButton *drawPolylineButton = this-> drawPolylineButton;
        drawPolylineButton->setIcon(QIcon(":/button/drawPolylineButton.svg"));
        drawPolylineButton->setIconSize(QSize(30, 30));
        drawPolylineButton->setStyleSheet(buttonStyle);
        drawPolylineButton->setCheckable(true);
        drawPolylineButton->setAutoExclusive(false);
        drawPolylineButton->setToolTip(drawPolylineButtonToolTip);
        this->registerDrawButton(drawPolylineButton);
        //
        QToolButton *drawLineButton = this-> drawLineButton;
        drawLineButton->setIcon(QIcon(":/button/drawLineButton.svg"));
        drawLineButton->setIconSize(QSize(30, 30));
        drawLineButton->setStyleSheet(buttonStyle);
        drawLineButton->setCheckable(true);
        drawLineButton->setAutoExclusive(false);
        drawLineButton->setToolTip(drawLineButtonToolTip);
        this->registerDrawButton(drawLineButton);
        //
        QToolButton *drawArcButton = this-> drawArcButton;
        drawArcButton->setIcon(QIcon(":/button/drawArcButton.svg"));
        drawArcButton->setIconSize(QSize(30, 30));
        drawArcButton->setStyleSheet(buttonStyle);
        drawArcButton->setCheckable(true);
        drawArcButton->setAutoExclusive(false);
        drawArcButton->setToolTip(drawArcButtonToolTip);
        this->registerDrawButton(drawArcButton);
        //
        QToolButton *drawPointButton = this-> drawPointButton;
        drawPointButton->setIcon(QIcon(":/button/drawPointButton.svg"));
        drawPointButton->setIconSize(QSize(30, 30));
        drawPointButton->setStyleSheet(buttonStyle);
        drawPointButton->setCheckable(true);
        drawPointButton->setAutoExclusive(false);
        this->registerDrawButton(drawPointButton);
        //
        QToolButton *drawCircleButton = this-> drawCircleButton;
        drawCircleButton->setIcon(QIcon(":/button/drawCircleButton.svg"));
        drawCircleButton->setIconSize(QSize(30, 30));
        drawCircleButton->setStyleSheet(buttonStyle);
        drawCircleButton->setCheckable(true);
        drawCircleButton->setAutoExclusive(false);
        drawCircleButton->setToolTip(drawCircleButtonToolTip);
        this->registerDrawButton(drawCircleButton);
        //
        QToolButton *drawEllipseButton = this-> drawEllipseButton;
        drawEllipseButton->setIcon(QIcon(":/button/drawEllipseButton.svg"));
        drawEllipseButton->setIconSize(QSize(30, 30));
        drawEllipseButton->setStyleSheet(buttonStyle);
        drawEllipseButton->setCheckable(true);
        drawEllipseButton->setAutoExclusive(false);
        drawEllipseButton->setToolTip(drawEllipseButtonToolTip);
        this->registerDrawButton(drawEllipseButton);
        //
        QToolButton *drawRectButton = this-> drawRectButton;
        drawRectButton->setIcon(QIcon(":/button/drawRectButton.svg"));
        drawRectButton->setIconSize(QSize(30, 30));
        drawRectButton->setStyleSheet(buttonStyle);
        drawRectButton->setCheckable(true);
        drawRectButton->setAutoExclusive(false);
        drawRectButton->setToolTip(drawRectButtonToolTip);
        this->registerDrawButton(drawRectButton);
        //
        QToolButton *drawPolygonButton = this-> drawPolygonButton;
        drawPolygonButton->setIcon(QIcon(":/button/drawPolygonButton.svg"));
        drawPolygonButton->setIconSize(QSize(30, 30));
        drawPolygonButton->setStyleSheet(buttonStyle);
        drawPolygonButton->setCheckable(true);
        drawPolygonButton->setAutoExclusive(false);
        drawPolygonButton->setToolTip(drawPolygonButtonToolTip);
        this->registerDrawButton(drawPolygonButton);
        //
        QToolButton *drawSpiralButton = this-> drawSpiralButton;
        drawSpiralButton->setIcon(QIcon(":/button/drawSpiralButton.svg"));
        drawSpiralButton->setIconSize(QSize(30, 30));
        drawSpiralButton->setStyleSheet(buttonStyle);
        drawSpiralButton->setCheckable(true);
        drawSpiralButton->setAutoExclusive(false);
        drawSpiralButton->setToolTip(drawSpiralButtonToolTip);
        this->registerDrawButton(drawSpiralButton);
    }

    void setEditToolButtonStyle() {
        QString buttonStyle = buttonStyle1;
        //
        QToolButton *editButton = this-> editButton;
        editButton->setIcon(QIcon(":/button/editButton.svg"));
        editButton->setIconSize(QSize(30, 30));
        editButton->setStyleSheet(buttonStyle);
        editButton->setCheckable(true);
        editButton->setAutoExclusive(false);
        editButton->setToolTip("编辑模式");
        this->registerToolButton(editButton);
        //
        QToolButton *dragSceneButton = this-> dragSceneButton;
        dragSceneButton->setIcon(QIcon(":/button/dragSceneButton.svg"));
        dragSceneButton->setIconSize(QSize(30, 30));
        dragSceneButton->setStyleSheet(buttonStyle);
        dragSceneButton->setCheckable(true);
        dragSceneButton->setAutoExclusive(false);
        dragSceneButton->setToolTip("拖动画布；左键拖拽");
        this->registerToolButton(dragSceneButton);
        //
        QToolButton *deleteButton = this-> deleteButton;
        deleteButton->setIcon(QIcon(":/button/deleteButton.svg"));
        deleteButton->setIconSize(QSize(30, 30));
        deleteButton->setStyleSheet(buttonStyle);
        deleteButton->setCheckable(true);
        deleteButton->setAutoExclusive(false);
        deleteButton->setToolTip("删除对象");
        this->registerToolButton(deleteButton);
        //
        QToolButton *drawTestLineButton = this-> drawTestLineButton;
        drawTestLineButton->setIcon(QIcon(":/button/drawTestLineButton.svg"));
        drawTestLineButton->setIconSize(QSize(30, 30));
        drawTestLineButton->setStyleSheet(buttonStyle);
        drawTestLineButton->setCheckable(true);
        drawTestLineButton->setAutoExclusive(false);
        drawTestLineButton->setToolTip("测试按钮");
        this->registerToolButton(drawTestLineButton);
        //
        QToolButton *centerButton = this-> centerButton;
        centerButton->setIcon(QIcon(":/button/centerButton.svg"));
        centerButton->setIconSize(QSize(30, 30));
        centerButton->setStyleSheet(buttonStyle);
        centerButton->setCheckable(true);
        centerButton->setAutoExclusive(false);
        centerButton->setToolTip("移动对象到中心点");
        this->registerToolButton(centerButton);
        //
        // QToolButton *redoButton = this-> redoButton;
        // redoButton->setIcon(QIcon(":/button/redoButton.svg"));
        // redoButton->setIconSize(QSize(30, 30));
        // redoButton->setStyleSheet(buttonStyle);
        // redoButton->setCheckable(true);
        // redoButton->setAutoExclusive(false);
        // redoButton->setToolTip("");
        // this->registerToolButton(redoButton);
        // connect(redoButton, &QToolButton::clicked, this, &MainWindow::onRedoButtonClicked);
        //
        // QToolButton *undoButton = this-> undoButton;
        // undoButton->setIcon(QIcon(":/button/undoButton.svg"));
        // undoButton->setIconSize(QSize(30, 30));
        // undoButton->setStyleSheet(buttonStyle);
        // undoButton->setCheckable(true);
        // undoButton->setAutoExclusive(false);
        // undoButton->setToolTip("");
        // this->registerToolButton(undoButton);
        // connect(undoButton, &QToolButton::clicked, this, &MainWindow::onUndoButtonClicked);
        //
        QToolButton *breakCopiedItemButton = this-> breakCopiedItemButton;
        breakCopiedItemButton->setIcon(QIcon(":/button/breakCopiedItemButton.png"));
        breakCopiedItemButton->setIconSize(QSize(30, 30));
        breakCopiedItemButton->setStyleSheet(buttonStyle);
        breakCopiedItemButton->setCheckable(true);
        breakCopiedItemButton->setAutoExclusive(false);
        breakCopiedItemButton->setToolTip("打散复制对象组");
        this->registerToolButton(breakCopiedItemButton);
        //
        QToolButton *breakContourFillItemButton = this-> breakContourFillItemButton;
        breakContourFillItemButton->setIcon(QIcon(":/button/breakContourFillItemButton.png"));
        breakContourFillItemButton->setIconSize(QSize(30, 30));
        breakContourFillItemButton->setStyleSheet(buttonStyle);
        breakContourFillItemButton->setCheckable(true);
        breakContourFillItemButton->setAutoExclusive(false);
        breakContourFillItemButton->setToolTip("打散轮廓填充");
        this->registerToolButton(breakContourFillItemButton);
        //
        QToolButton *breakHatchFillItemButton = this-> breakHatchFillItemButton;
        breakHatchFillItemButton->setIcon(QIcon(":/button/breakHatchFillItemButton.png"));
        breakHatchFillItemButton->setIconSize(QSize(30, 30));
        breakHatchFillItemButton->setStyleSheet(buttonStyle);
        breakHatchFillItemButton->setCheckable(true);
        breakHatchFillItemButton->setAutoExclusive(false);
        breakHatchFillItemButton->setToolTip("打散线段填充");
        this->registerToolButton(breakHatchFillItemButton);
        /// 粘贴 复制 剪切
        ///
        ///
        QToolButton *cutButton = this-> cutButton;
        cutButton->setIcon(QIcon(":/button/cutButton.png"));
        cutButton->setIconSize(QSize(30, 30));
        cutButton->setStyleSheet(buttonStyle);
        cutButton->setCheckable(true);
        cutButton->setAutoExclusive(false);
        cutButton->setToolTip("");
        this->registerToolButton(cutButton);
        //
        QToolButton *copyButton = this-> copyButton;
        copyButton->setIcon(QIcon(":/button/copyButton.png"));
        copyButton->setIconSize(QSize(30, 30));
        copyButton->setStyleSheet(buttonStyle);
        copyButton->setCheckable(true);
        copyButton->setAutoExclusive(false);
        copyButton->setToolTip("");
        this->registerToolButton(copyButton);
        //
        QToolButton *pasteButton = this-> pasteButton;
        pasteButton->setIcon(QIcon(":/button/pasteButton.png"));
        pasteButton->setIconSize(QSize(30, 30));
        pasteButton->setStyleSheet(buttonStyle);
        pasteButton->setCheckable(true);
        pasteButton->setAutoExclusive(false);
        pasteButton->setToolTip("");
        this->registerToolButton(pasteButton);
        //
        QToolButton *combineButton = this->combineButton;
        combineButton->setIcon(QIcon(":/button/combineButton.png"));
        combineButton->setIconSize(QSize(30, 30));
        combineButton->setStyleSheet(buttonStyle);
        combineButton->setCheckable(true);
        combineButton->setAutoExclusive(false);
        combineButton->setToolTip("");
        //
        QToolButton *breakButton = this->breakButton;
        breakButton->setIcon(QIcon(":/button/breakButton.png"));
        breakButton->setIconSize(QSize(30, 30));
        breakButton->setStyleSheet(buttonStyle);
        breakButton->setCheckable(true);
        breakButton->setAutoExclusive(false);
        breakButton->setToolTip("");
        //
        //
        QToolButton *mirrorHorizontalButton = this-> mirrorHorizontalButton;
        mirrorHorizontalButton->setIcon(QIcon(":/button/mirrorHorizontalButton.png"));
        mirrorHorizontalButton->setIconSize(QSize(30, 30));
        mirrorHorizontalButton->setStyleSheet(buttonStyle);
        mirrorHorizontalButton->setCheckable(true);
        mirrorHorizontalButton->setAutoExclusive(false);
        mirrorHorizontalButton->setToolTip("");
        this->registerToolButton(mirrorHorizontalButton);
        //
        QToolButton *mirrorVerticalButton = this-> mirrorVerticalButton;
        mirrorVerticalButton->setIcon(QIcon(":/button/mirrorVerticalButton.png"));
        mirrorVerticalButton->setIconSize(QSize(30, 30));
        mirrorVerticalButton->setStyleSheet(buttonStyle);
        mirrorVerticalButton->setCheckable(true);
        mirrorVerticalButton->setAutoExclusive(false);
        mirrorVerticalButton->setToolTip("");
        this->registerToolButton(mirrorVerticalButton);
    }

    void setLayerButtonStyle() {
        auto buttonStyle = buttonStyle1;
        //
        QToolButton *addLayerButton = this-> addLayerButton;
        addLayerButton->setIcon(QIcon(":/button/addLayerButton.png"));
        addLayerButton->setIconSize(QSize(30, 30));
        addLayerButton->setStyleSheet(buttonStyle);
        addLayerButton->setCheckable(false);
        addLayerButton->setToolTip("");
        this->registerToolButton(addLayerButton);
        //
        QToolButton *deleteLayerButton = this-> deleteLayerButton;
        deleteLayerButton->setIcon(QIcon(":/button/deleteLayerButton.png"));
        deleteLayerButton->setIconSize(QSize(30, 30));
        deleteLayerButton->setStyleSheet(buttonStyle);
        deleteLayerButton->setCheckable(false);
        deleteLayerButton->setToolTip("");
        this->registerToolButton(deleteLayerButton);
        //
        // QToolButton *setLayerColorButton = this-> setLayerColorButton;
        // setLayerColorButton->setIcon(QIcon(":/button/setLayerColorButton.png"));
        // setLayerColorButton->setIconSize(QSize(30, 30));
        // setLayerColorButton->setStyleSheet(buttonStyle);
        // setLayerColorButton->setCheckable(false);
        // setLayerColorButton->setToolTip("");
        // this->registerToolButton(setLayerColorButton);
        // connect(breakContourFillItemButton, &QToolButton::clicked,
        //         this, &MainWindow::onBreakContourFillItemButtonClicked);
        //
    }

    void setSignalButtonStyle() {
        QString buttonStyle = buttonStyle1;
        QToolButton *digitalInButton = this-> digitalInButton;
        digitalInButton->setIcon(QIcon(":/button/digitalInButton.png"));
        digitalInButton->setIconSize(QSize(30, 30));
        digitalInButton->setStyleSheet(buttonStyle);
        digitalInButton->setCheckable(true);
        digitalInButton->setAutoExclusive(false);
        digitalInButton->setToolTip("");
        this->registerToolButton(digitalInButton);
        //
        QToolButton *digitalOutButton = this-> digitalOutButton;
        digitalOutButton->setIcon(QIcon(":/button/digitalOutButton.png"));
        digitalOutButton->setIconSize(QSize(30, 30));
        digitalOutButton->setStyleSheet(buttonStyle);
        digitalOutButton->setCheckable(true);
        digitalOutButton->setAutoExclusive(false);
        digitalOutButton->setToolTip("");
        this->registerToolButton(digitalOutButton);
        //
        QToolButton *doPauseButton = this-> doPauseButton;
        doPauseButton->setIcon(QIcon(":/button/doPauseButton.png"));
        doPauseButton->setIconSize(QSize(30, 30));
        doPauseButton->setStyleSheet(buttonStyle);
        doPauseButton->setCheckable(true);
        doPauseButton->setAutoExclusive(false);
        doPauseButton->setToolTip("");
        this->registerToolButton(doPauseButton);
        //
        QToolButton *delayTimeButton = this-> delayTimeButton;
        delayTimeButton->setIcon(QIcon(":/button/delayTimeButton.png"));
        delayTimeButton->setIconSize(QSize(30, 30));
        delayTimeButton->setStyleSheet(buttonStyle);
        delayTimeButton->setCheckable(true);
        delayTimeButton->setAutoExclusive(false);
        delayTimeButton->setToolTip("");
        this->registerToolButton(delayTimeButton);
        //
        QToolButton *motionButton = this-> motionButton;
        motionButton->setIcon(QIcon(":/button/motionButton.png"));
        motionButton->setIconSize(QSize(30, 30));
        motionButton->setStyleSheet(buttonStyle);
        motionButton->setCheckable(true);
        motionButton->setAutoExclusive(false);
        motionButton->setToolTip("");
        this->registerToolButton(motionButton);
        //
        QToolButton *loopButton = this-> loopButton;
        loopButton->setIcon(QIcon(":/button/loopButton.png"));
        loopButton->setIconSize(QSize(30, 30));
        loopButton->setStyleSheet(buttonStyle);
        loopButton->setCheckable(true);
        loopButton->setAutoExclusive(false);
        loopButton->setToolTip("");
        this->registerToolButton(loopButton);
    }

    void setProjectButtonStyle() {
        QString buttonStyle = buttonStyle1;
        //
        QToolButton *createProjectButton = UiManager::getIns(). createProjectButton;
        createProjectButton->setIcon(QIcon(":/button/createProjectButton.png"));
        createProjectButton->setIconSize(QSize(30, 30));
        createProjectButton->setStyleSheet(buttonStyle1);
        createProjectButton->setCheckable(false);
        createProjectButton->setAutoExclusive(false);
        createProjectButton->setToolTip("");
        //
        //
        QToolButton *openProjectButton = UiManager::getIns(). openProjectButton;
        openProjectButton->setIcon(QIcon(":/button/openProjectButton.png"));
        openProjectButton->setIconSize(QSize(30, 30));
        openProjectButton->setStyleSheet(buttonStyle1);
        openProjectButton->setCheckable(false);
        openProjectButton->setAutoExclusive(false);
        openProjectButton->setToolTip("");
        //
        //
        QToolButton *saveProjectButton = UiManager::getIns(). saveProjectButton;
        saveProjectButton->setIcon(QIcon(":/button/saveProjectButton.png"));
        saveProjectButton->setIconSize(QSize(30, 30));
        saveProjectButton->setStyleSheet(buttonStyle1);
        saveProjectButton->setCheckable(false);
        saveProjectButton->setAutoExclusive(false);
        saveProjectButton->setToolTip("");
    }


    QWidget* createSystemControlWidget(){
        QWidget *widget = new QWidget();
        QVBoxLayout *mainLayout = new QVBoxLayout(widget);

        /* *******************************************************************************
         Hardware Status Group
        ******************************************************************************* */
        QGroupBox *hardwareStatusGroup = new QGroupBox("Hardware Status");
        QVBoxLayout *hardwareLayout = new QVBoxLayout(hardwareStatusGroup);

        QHBoxLayout *laserLayout = new QHBoxLayout();
        QLabel *labelLaser = new QLabel("LaserDevice");
        QLabel *statusIndicator = new QLabel();
        statusIndicator->setFixedSize(16, 16);
        statusIndicator->setStyleSheet("background-color: red; border-radius: 8px;");
        laserLayout->addWidget(labelLaser);
        laserLayout->addWidget(statusIndicator);
        hardwareLayout->addLayout(laserLayout);

        QHBoxLayout *motionaxisLayout = new QHBoxLayout();
        QLabel *labelMotionAxis = new QLabel("MotionAxis");
        QLabel *statusIndicator1 = new QLabel();
        statusIndicator1->setFixedSize(16, 16);
        statusIndicator1->setStyleSheet("background-color: red; border-radius: 8px;");
        motionaxisLayout->addWidget(labelMotionAxis);
        motionaxisLayout->addWidget(statusIndicator1);
        hardwareLayout->addLayout(motionaxisLayout);

        mainLayout->addWidget(hardwareStatusGroup);

        /* *******************************************************************************
         参数输入
        ******************************************************************************* */
        QGroupBox *controlGroup = new QGroupBox("Control Parameters");
        QHBoxLayout *controlLayout = new QHBoxLayout(controlGroup);
        mainLayout->addWidget(controlGroup);

        // 执行次数
        QLabel *timesLabel = new QLabel("Total Executions:");
        QLineEdit *timesInput = new QLineEdit();
        timesInput->setText("1");
        timesInput->setValidator(new QIntValidator(1, 9999, timesInput));
        controlLayout->addWidget(timesLabel);
        controlLayout->addWidget(timesInput);

        // apply按钮
        QPushButton *applyButton = new QPushButton("Apply");
        controlLayout->addWidget(applyButton);
        QObject::connect(applyButton, &QPushButton::clicked, widget, [=]() {
            // 执行次数
            int value = timesInput->text().toInt();
            if (value <= 0) {
                WARN_MSG("Invalid execution count");
                return;
            }
            HardwareController::getIns().setOperationTime(value);
        });

        // 填充空白
        mainLayout->addStretch ();

        /* *******************************************************************************
         状态定时监视器
        ******************************************************************************* */
        QTimer *statusTimer = new QTimer(widget);
        statusTimer->setInterval(1000);
        QObject::connect(statusTimer, &QTimer::timeout, widget, [=]() {
            bool isLaserWorkerConnected = LaserWorker::getIns().getDeviceConnectStatus();
            if (isLaserWorkerConnected)
                statusIndicator->setStyleSheet("background-color: green; border-radius: 8px;");
            else
                statusIndicator->setStyleSheet("background-color: red; border-radius: 8px;");

            bool isStageWorkerConnected = MotionStageWorker::getIns().getDeviceConnectStatus();
            if (isStageWorkerConnected)
                statusIndicator1->setStyleSheet("background-color: green; border-radius: 8px;");
            else
                statusIndicator1->setStyleSheet("background-color: red; border-radius: 8px;");
        });
        statusTimer->start();

        return widget;
    };

    QWidget* createMotionStageControlWidget()
    {
        QWidget* widget = new QWidget();
        QVBoxLayout* mainLayout = new QVBoxLayout(widget);

        double* curX = new double(0);
        double* curY = new double(0);
        double* curZ = new double(0);

        // XY按钮区域
        QGroupBox* xyGroup = new QGroupBox("XY Move");
        QGridLayout* moveLayout = new QGridLayout(xyGroup);

        QPushButton* btnXPos = new QPushButton("X+");
        QPushButton* btnXNeg = new QPushButton("X-");
        QPushButton* btnYPos = new QPushButton("Y+");
        QPushButton* btnYNeg = new QPushButton("Y-");

        moveLayout->addWidget(btnYPos, 0, 1);
        moveLayout->addWidget(btnXNeg, 1, 0);
        moveLayout->addWidget(btnXPos, 1, 2);
        moveLayout->addWidget(btnYNeg, 2, 1);

        mainLayout->addWidget(xyGroup);

        // Z按钮区域
        QGroupBox* zGroup = new QGroupBox("Z Move");
        QVBoxLayout* zLayout = new QVBoxLayout(zGroup);

        QPushButton* btnZPos = new QPushButton("Z+");
        QPushButton* btnZNeg = new QPushButton("Z-");
        zLayout->addWidget(btnZPos);
        zLayout->addWidget(btnZNeg);

        mainLayout->addWidget(zGroup);

        // 步长输入区域
        QGroupBox* stepGroup = new QGroupBox("Step Size (mm)");
        QHBoxLayout* stepLayout = new QHBoxLayout(stepGroup);

        QLineEdit* stepEdit = new QLineEdit("5.0");
        stepEdit->setValidator(new QDoubleValidator(0.01, 1000.0, 2, stepEdit));
        stepLayout->addWidget(new QLabel("Step:"));
        stepLayout->addWidget(stepEdit);

        mainLayout->addWidget(stepGroup);

        // 显示区域
        QGroupBox* posGroup = new QGroupBox("Current Position");
        QHBoxLayout* posLayout = new QHBoxLayout(posGroup);

        QLabel* posLabel = new QLabel("X=0.00  Y=0.00  Z=0.00");
        posLayout->addWidget(posLabel);

        mainLayout->addWidget(posGroup);
        mainLayout->addStretch ();

        // 绑定信号
        auto moveAxis = [=](const QString& axis, int dir) {
            double step = stepEdit->text().toDouble();
            if (axis == "X") *curX += dir * step;
            if (axis == "Y") *curY += dir * step;
            if (axis == "Z") *curZ += dir * step;

            MotionStageWorker::getIns().setPos(*curX, *curY, *curZ);

            posLabel->setText(QString("X=%1  Y=%2  Z=%3")
                                  .arg(*curX, 0, 'f', 2)
                                  .arg(*curY, 0, 'f', 2)
                                  .arg(*curZ, 0, 'f', 2));
        };

        QObject::connect(btnXPos, &QPushButton::clicked, [=]() { moveAxis("X", +1); });
        QObject::connect(btnXNeg, &QPushButton::clicked, [=]() { moveAxis("X", -1); });
        QObject::connect(btnYPos, &QPushButton::clicked, [=]() { moveAxis("Y", +1); });
        QObject::connect(btnYNeg, &QPushButton::clicked, [=]() { moveAxis("Y", -1); });
        QObject::connect(btnZPos, &QPushButton::clicked, [=]() { moveAxis("Z", +1); });
        QObject::connect(btnZNeg, &QPushButton::clicked, [=]() { moveAxis("Z", -1); });

        return widget;
    }


    QWidget* createRTCSettingWidget() {
        QWidget* widget = new QWidget();
        QVBoxLayout* mainLayout = new QVBoxLayout(widget);

        // 控制卡类型选择
        QGroupBox* cardBox = new QGroupBox("Control Card:");
        QHBoxLayout* cardLayout = new QHBoxLayout(cardBox);

        QRadioButton* testRadio = new QRadioButton("Test");
        QRadioButton* rtc5Radio = new QRadioButton("RTC5");
        QRadioButton* rtc6Radio = new QRadioButton("RTC6");
        testRadio->setChecked(true);

        cardLayout->addWidget(testRadio);
        cardLayout->addWidget(rtc5Radio);
        cardLayout->addWidget(rtc6Radio);

        mainLayout->addWidget(cardBox);


        // 校正文件选择
        QGroupBox* fileGroup = new QGroupBox("Correction File:");
        QHBoxLayout* fileLayout = new QHBoxLayout(fileGroup);

        QPushButton* loadCorrectionButton = new QPushButton("Load Correction File");
        QString* correctionFilePath = new QString();

        QObject::connect(loadCorrectionButton, &QPushButton::clicked, widget, [=]() {
            QString path = QFileDialog::getOpenFileName(nullptr, "Choose Correction File", QDir::currentPath(), "Correction Files (*.ct5);;All Files (*)");
            if (!path.isEmpty()) {
                *correctionFilePath = path;
                loadCorrectionButton->setText(QFileInfo(path).fileName());
            }
        });

        fileLayout->addWidget(loadCorrectionButton);
        fileLayout->addStretch();
        mainLayout->addWidget(fileGroup);


        // 参数设置
        QGroupBox* paramGroup = new QGroupBox("Parameters:");
        QGridLayout* paramLayout = new QGridLayout(paramGroup);

        QLineEdit* scaleEdit = new QLineEdit("1");
        QLineEdit* scaleCorX = new QLineEdit("1.0");
        QLineEdit* scaleCorY = new QLineEdit("1.0");
        QLineEdit* rotationEdit = new QLineEdit("0.0");
        QLineEdit* offsetX = new QLineEdit("0.0");
        QLineEdit* offsetY = new QLineEdit("0.0");

        QComboBox* laserModeBox = new QComboBox();
        laserModeBox->addItems({ "YAG1", "YAG2", "YAG3", "CO2" });

        QComboBox* executeModeBox = new QComboBox();
        executeModeBox->addItems({ "DoubleLists", "SingleList", "CircleList" });

        QWidget* scaleCorWidget = new QWidget();
        QHBoxLayout* scaleCorLayout = new QHBoxLayout(scaleCorWidget);
        scaleCorLayout->setContentsMargins(0, 0, 0, 0);
        scaleCorLayout->setSpacing(6);
        scaleCorLayout->addWidget(scaleCorX);
        scaleCorLayout->addWidget(scaleCorY);

        QWidget* offsetWidget = new QWidget();
        QHBoxLayout* offsetLayout = new QHBoxLayout(offsetWidget);
        offsetLayout->setContentsMargins(0, 0, 0, 0);
        offsetLayout->setSpacing(6);
        offsetLayout->addWidget(offsetX);
        offsetLayout->addWidget(offsetY);

        paramLayout->addWidget(new QLabel("Scale:"),       0, 0);
        paramLayout->addWidget(scaleEdit,                  0, 1);

        paramLayout->addWidget(new QLabel("ScaleCor:"),    1, 0);
        paramLayout->addWidget(scaleCorWidget,             1, 1, 1, 3);  // 合并3列宽

        paramLayout->addWidget(new QLabel("Rotation:"),    2, 0);
        paramLayout->addWidget(rotationEdit,               2, 1);

        paramLayout->addWidget(new QLabel("Offset:"),      3, 0);
        paramLayout->addWidget(offsetWidget,               3, 1, 1, 3);

        paramLayout->addWidget(new QLabel("Laser Mode:"),  4, 0);
        paramLayout->addWidget(laserModeBox,               4, 1);

        paramLayout->addWidget(new QLabel("Execute Mode:"),5, 0);
        paramLayout->addWidget(executeModeBox,             5, 1);

        mainLayout->addWidget(paramGroup);



        // 添加间隔
        mainLayout->addStretch ();


        // Apply 按钮
        QPushButton* applyButton = new QPushButton("Apply");
        mainLayout->addWidget(applyButton);


        // 绑定信号
        QObject::connect(applyButton, &QPushButton::clicked,widget, [=]() {
            RTCSettings settings;
            settings.correctionFilePath = *correctionFilePath;
            settings.scale = scaleEdit->text().toDouble();
            settings.scaleCorX = scaleCorX->text().toDouble();
            settings.scaleCorY = scaleCorY->text().toDouble();
            settings.rotation = rotationEdit->text().toDouble();
            settings.offsetX = offsetX->text().toDouble();
            settings.offsetY = offsetY->text().toDouble();
            settings.laserMode = laserModeBox->currentText();
            settings.executeMode = executeModeBox->currentText();

            // 调用laserWoker部分;
            if (rtc5Radio->isChecked()){
                auto device = std::make_unique<LaserDeviceRTC5> ();
                device->m_settings = settings;
                LaserWorker::getIns().setDevice(std::move(device));
            } else if (rtc6Radio->isChecked()){
                // auto device = std::make_unique<LaserDeviceRTC6> ();
                // device->m_settings = settings;
                // LaserWorker::getIns().setDevice(std::move(device));
            } else if (testRadio->isChecked()) {
                auto device = std::make_unique<LaserDeviceTest> ();
                LaserWorker::getIns().setDevice(std::move(device));
            }
        });

        return widget;
    };

    QWidget* createMotionStageSettingWidget() {
        QWidget* widget = new QWidget();
        QVBoxLayout* mainLayout = new QVBoxLayout(widget);

        /* *******************************************************************************
         选轴
        ******************************************************************************* */
        QGroupBox* stageBox = new QGroupBox("Motion Stage:");
        QHBoxLayout* controllerLayout = new QHBoxLayout(stageBox);

        QRadioButton* googolRadio = new QRadioButton("Googol");
        QRadioButton* thorlabsRadio = new QRadioButton("Thorlabs");
        QRadioButton* testRadio = new QRadioButton("Test");
        testRadio->setChecked(true);

        controllerLayout->addWidget(testRadio);
        controllerLayout->addWidget(googolRadio);
        controllerLayout->addWidget(thorlabsRadio);
        controllerLayout->addStretch();

        mainLayout->addWidget(stageBox);

        /* *******************************************************************************
         对应参数设置
        ******************************************************************************* */
        QGroupBox* paramBox = new QGroupBox("Params Setting:");
        QVBoxLayout* paramBoxLayout = new QVBoxLayout(paramBox);
        QStackedWidget* paramStack = new QStackedWidget();

        // Test
        QWidget* testParamWidget = new QWidget();
        paramStack->addWidget(testParamWidget);

        // Googol
        QWidget* googolParamWidget = new QWidget();
        paramStack->addWidget(googolParamWidget);

        // Thorlabs
        QWidget* thorlabsParamWidget = new QWidget();
        QFormLayout* thorlabsForm = new QFormLayout(thorlabsParamWidget);
        QLineEdit* thorlabsSerialEdit = new QLineEdit("00000000");
        thorlabsForm->addRow("Serial No:", thorlabsSerialEdit);
        paramStack->addWidget(thorlabsParamWidget);

        paramBoxLayout->addWidget(paramStack);
        mainLayout->addWidget(paramBox);

        // 响应 radio 变化切换参数页
        QObject::connect(testRadio, &QRadioButton::toggled, widget, [=](bool checked){
            if (checked) paramStack->setCurrentIndex(0);
        });
        QObject::connect(googolRadio, &QRadioButton::toggled, widget, [=](bool checked){
            if (checked) paramStack->setCurrentIndex(1);
        });
        QObject::connect(thorlabsRadio, &QRadioButton::toggled, widget, [=](bool checked){
            if (checked) paramStack->setCurrentIndex(2);
        });

        /* *******************************************************************************
         确认
        ******************************************************************************* */
        QPushButton* applyButton = new QPushButton("Apply");
        mainLayout->addWidget(applyButton);

        QObject::connect(applyButton, &QPushButton::clicked, widget, [=]() {
            if (googolRadio->isChecked()) {
                auto device = std::make_unique<MotionStageDeviceGoogol>();
                MotionStageWorker::getIns().setDevice(std::move(device));
            } else if (thorlabsRadio->isChecked()) {
                QString serial = thorlabsSerialEdit->text();
                auto device = std::make_unique<MotionStageDeviceThorlabs>();
                strncpy(device->m_serialNo, serial.toStdString().c_str(), sizeof(device->m_serialNo));
                MotionStageWorker::getIns().setDevice(std::move(device));
            } else if (testRadio->isChecked()) {
                auto device = std::make_unique<MotionStageDeviceTest>();
                MotionStageWorker::getIns().setDevice(std::move(device));
            }
        });

        return widget;
    }


public:
    void registerDrawButton(QToolButton* btn) {
        m_drawButtons.push_back(btn);
    }

    void setAllDrawButtonChecked(bool checked) {
        for (auto * btn : m_drawButtons) {
            btn->setChecked(checked);
        }
    }

    void registerToolButton(QToolButton* btn) {
        m_toolButtons.push_back(btn);
    }

    void setAllToolButtonChecked(bool checked) {
        for (auto * btn : m_toolButtons) {
            btn->setChecked(checked);
        }
    }

private:
    static UiManager ins;
    UiManager() {};
    UiManager(const UiManager &);
    ~UiManager() {};
    UiManager &operator = (const UiManager &);
public:
    static UiManager &getIns();
};

#endif // UIMANAGER_H
