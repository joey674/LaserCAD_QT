#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <QMainWindow>
#include <QToolButton>
#include <QWidget>
#include <QGridLayout>
#include "graphicsview.h"
#include "treeview.h"
#include "tabwidget.h"
#include <QHBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QStatusBar>
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
    void initLayout(QWidget *parent) {
        QWidget *central = new QWidget(parent);
        QGridLayout *gridLayout = new QGridLayout(central);
        parent->setLayout(new QVBoxLayout());
        parent->layout()->addWidget(central);
        /// 第一行
        ///
        QHBoxLayout *firstHLayout = new QHBoxLayout();
        // projectButton
        createProjectButton = new QToolButton(central);
        firstHLayout->addWidget(createProjectButton);
        openProjectButton = new QToolButton(central);
        firstHLayout->addWidget(openProjectButton);
        saveProjectButton = new QToolButton(central);
        firstHLayout->addWidget(saveProjectButton);
        QFrame *splitLine1 = new QFrame(central);// 插入分隔线
        splitLine1->setFrameShape(QFrame::VLine);
        splitLine1->setFrameShadow(QFrame::Sunken);
        firstHLayout->addWidget(splitLine1);
        // layerButton
        addLayerButton = new QToolButton(central);
        firstHLayout->addWidget(addLayerButton);
        deleteLayerButton = new QToolButton(central);
        firstHLayout->addWidget(deleteLayerButton);
        firstHLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
        gridLayout->addLayout(firstHLayout, 0, 0, 1, 3);
        /// 第二行
        ///
        QHBoxLayout *secondHLayout = new QHBoxLayout();
        // copy/pasteButton
        copyButton = new QToolButton(central);
        secondHLayout->addWidget(copyButton);
        cutButton = new QToolButton(central);
        secondHLayout->addWidget(cutButton);
        pasteButton = new QToolButton(central);
        secondHLayout->addWidget(pasteButton);
        deleteButton = new QToolButton(central);
        secondHLayout->addWidget(deleteButton);
        QFrame *splitLine3 = new QFrame(central);// 插入分隔线
        splitLine3->setFrameShape(QFrame::VLine);
        splitLine3->setFrameShadow(QFrame::Sunken);
        secondHLayout->addWidget(splitLine3);
        // combined break button
        combineButton = new QToolButton(central);
        secondHLayout->addWidget(combineButton);
        breakButton = new QToolButton(central);
        secondHLayout->addWidget(breakButton);
        breakCopiedItemButton = new QToolButton(central);
        secondHLayout->addWidget(breakCopiedItemButton);
        breakContourFillItemButton = new QToolButton(central);
        secondHLayout->addWidget(breakContourFillItemButton);
        breakHatchFillItemButton = new QToolButton(central);
        secondHLayout->addWidget(breakHatchFillItemButton);
        QFrame *splitLine3_1 = new QFrame(central);// 插入分隔线
        splitLine3_1->setFrameShape(QFrame::VLine);
        splitLine3_1->setFrameShadow(QFrame::Sunken);
        secondHLayout->addWidget(splitLine3_1);
        // toolButton
        editButton = new QToolButton(central);
        secondHLayout->addWidget(editButton);
        mirrorHorizontalButton = new QToolButton(central);
        secondHLayout->addWidget(mirrorHorizontalButton);
        mirrorVerticalButton = new QToolButton(central);
        secondHLayout->addWidget(mirrorVerticalButton);
        centerButton = new QToolButton(central);
        secondHLayout->addWidget(centerButton);
        QFrame *splitLine4 = new QFrame(central);// 插入分隔线
        splitLine4->setFrameShape(QFrame::VLine);
        splitLine4->setFrameShadow(QFrame::Sunken);
        secondHLayout->addWidget(splitLine4);
        // sceneButton
        dragSceneButton = new QToolButton(central);
        secondHLayout->addWidget(dragSceneButton);
        // utilsButton
        drawTestLineButton = new QToolButton(central);
        secondHLayout->addWidget(drawTestLineButton);
        // redoButton = new QToolButton(central);
        // secondHLayout->addWidget(redoButton);
        // undoButton = new QToolButton(central);
        // secondHLayout->addWidget(undoButton);
        QFrame *splitLine5 = new QFrame(central);// 插入分隔线
        splitLine5->setFrameShape(QFrame::VLine);
        splitLine5->setFrameShadow(QFrame::Sunken);
        secondHLayout->addWidget(splitLine5);
        // signalButton
        delayTimeButton = new QToolButton(central);
        secondHLayout->addWidget(delayTimeButton);
        digitalInButton = new QToolButton(central);
        secondHLayout->addWidget(digitalInButton);
        digitalOutButton = new QToolButton(central);
        secondHLayout->addWidget(digitalOutButton);
        doPauseButton = new QToolButton(central);
        secondHLayout->addWidget(doPauseButton);
        loopButton = new QToolButton(central);
        secondHLayout->addWidget(loopButton);
        motionButton = new QToolButton(central);
        secondHLayout->addWidget(motionButton);
        secondHLayout->addSpacerItem(
            new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
        QFrame *splitLine6 = new QFrame(central); // 插入分隔线
        splitLine6->setFrameShape(QFrame::VLine);
        splitLine6->setFrameShadow(QFrame::Sunken);
        secondHLayout->addWidget(splitLine6);
        // hardwareButton
        markButton = new QToolButton(central);
        secondHLayout->addWidget(markButton);
        gridLayout->addLayout(secondHLayout, 1, 0, 1, 3);
        // 主控件布局
        QHBoxLayout *mainLayout = new QHBoxLayout(central);
        treeView = new TreeView(central); // 左：TreeView，占比 1
        mainLayout->addWidget(treeView, /*stretch=*/1);
        // tabwidgets
        // editTabWidget = new TabWidget(central);// 中：TabWidget，占比 1
        // mainLayout->addWidget(editTabWidget, /*stretch=*/1);
        // 中间：两个 TabWidget 垂直堆叠，占 1 宽度
        QWidget *tabContainer = new QWidget(central);
        QVBoxLayout *tabContainerLayout = new QVBoxLayout(tabContainer);
        systemTabWidget = new TabWidget(central);        // 上方 TabWidget
        tabContainerLayout->addWidget(systemTabWidget, /*stretch=*/1);
        editTabWidget = new TabWidget(central);        // 下方TabWidget
        tabContainerLayout->addWidget(editTabWidget, /*stretch=*/1);
        mainLayout->addWidget(tabContainer, /*stretch=*/1);
        //
        graphicsView = new GraphicsView(central); // 右：GraphicsView，占比 3
        mainLayout->addWidget(graphicsView, /*stretch=*/3);
        QVBoxLayout *drawButtonLayout = new QVBoxLayout();// 最右：绘图按钮栏，占最小固定宽度
        drawPointButton = new QToolButton(central);
        drawButtonLayout->addWidget(drawPointButton);
        drawLineButton = new QToolButton(central);
        drawButtonLayout->addWidget(drawLineButton);
        drawArcButton = new QToolButton(central);
        drawButtonLayout->addWidget(drawArcButton);
        drawPolylineButton = new QToolButton(central);
        drawButtonLayout->addWidget(drawPolylineButton);
        drawCircleButton = new QToolButton(central);
        drawButtonLayout->addWidget(drawCircleButton);
        drawRectButton = new QToolButton(central);
        drawButtonLayout->addWidget(drawRectButton);
        drawEllipseButton = new QToolButton(central);
        drawButtonLayout->addWidget(drawEllipseButton);
        drawPolygonButton = new QToolButton(central);
        drawButtonLayout->addWidget(drawPolygonButton);
        drawSpiralButton = new QToolButton(central);
        drawButtonLayout->addWidget(drawSpiralButton);
        drawButtonLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
        QWidget *drawContainer = new QWidget(central);
        drawContainer->setLayout(drawButtonLayout);
        gridLayout->addLayout(mainLayout, 2, 0, 1, 3);
        //
        drawContainer->setMinimumWidth(60);
        mainLayout->addWidget(drawContainer, /*stretch=*/0);
        // 状态栏
        // statusBar = new QStatusBar(parent);
        // if (auto *mainWindow = qobject_cast < QMainWindow * > (parent)) {
        //     mainWindow->setStatusBar(statusBar);
        // }
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
