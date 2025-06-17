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
    QToolButton *markButton;
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
        // 左侧栏容器
        QWidget *sideBar = new QWidget;
        sideBar->setFixedWidth(100);
        sideBar->setStyleSheet(R"(
        background-color: #2b2b2b;
    )");

        QVBoxLayout *btnLayout = new QVBoxLayout(sideBar);
        btnLayout->setSpacing(10);
        btnLayout->setContentsMargins(10, 20, 10, 20);

        auto createButton = [](const QString &text) {
            QToolButton *btn = new QToolButton;
            btn->setText(text);
            btn->setCheckable(true);
            btn->setFixedSize(100, 40);
            btn->setStyleSheet(R"(
            QToolButton {
                color: white;
                background: transparent;
                font-size: 16px;
                border: none;
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

        QToolButton *btnProject = createButton("draw");
        QToolButton *btnEditor = createButton("control");
        btnProject->setChecked(true); // 初始选中

        btnLayout->addWidget(btnProject);
        btnLayout->addWidget(btnEditor);
        btnLayout->addStretch();

        // 页面栈区域
        QStackedWidget *stack = new QStackedWidget;
        stack->addWidget(initDrawPage());
        stack->addWidget(initControlPage());

        // 总体布局
        QHBoxLayout *mainLayout = new QHBoxLayout(parent);
        mainLayout->setMargin(0);
        mainLayout->setSpacing(0);
        mainLayout->addWidget(sideBar);
        mainLayout->addWidget(stack);

        // 页面切换逻辑
        parent->connect(btnProject, &QToolButton::clicked, parent, [=]() {
            btnProject->setChecked(true);
            btnEditor->setChecked(false);
            stack->setCurrentIndex(0);
        });
        parent->connect(btnEditor, &QToolButton::clicked, parent, [=]() {
            btnEditor->setChecked(true);
            btnProject->setChecked(false);
            stack->setCurrentIndex(1);
        });
    }

    QWidget *initDrawPage()
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
        mainGLayout->addLayout(buttonHLayout1, 0, 0, 1, 3);

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

        // hardwareButton
        markButton = new QToolButton(page);
        buttonHLayout2->addWidget(markButton);

        //
        buttonHLayout2->addSpacerItem(
            new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

        mainGLayout->addLayout(buttonHLayout2, 1, 0, 1, 3);

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
        mainGLayout->addLayout(widgetBLayout3, 2, 0, 1, 3);

        //
        return page;
    }

    QWidget *initControlPage()
    {
        QWidget *page = new QWidget;
        QGridLayout *mainGLayout = new QGridLayout(page);
        page->setLayout(mainGLayout);

        systemTabWidget = new TabWidget(page);
        mainGLayout->addWidget(systemTabWidget);

        return page;
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
/// ItemManager Initialization
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
