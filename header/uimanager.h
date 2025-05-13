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
    // ToolButton
    QToolButton *breakCopiedItemButton;
    QToolButton *breakOffsetItemButton;
    QToolButton *centerButton;
    QToolButton *copyButton;
    QToolButton *cutButton;
    QToolButton *deleteButton;
    QToolButton *dragSceneButton;
    QToolButton *drawTestLineButton;
    QToolButton *editButton;
    QToolButton *mirrorHorizontalButton;
    QToolButton *mirrorVerticalButton;
    QToolButton *pasteButton;
    QToolButton *redoButton;
    QToolButton *undoButton;
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
    //
    GraphicsView *graphicsView;
    TreeView *treeView;
    QStatusBar *statusBar;
    TabWidget *tabWidget;
    // TabWidget *systemTabWidget;
public:
    void initLayout(QWidget *parent) {
        QWidget *central = new QWidget(parent);
        QGridLayout *gridLayout = new QGridLayout(central);
        parent->setLayout(new QVBoxLayout());
        parent->layout()->addWidget(central);
        // 项目+图层按钮行
        QHBoxLayout *projectLayout = new QHBoxLayout();
        openProjectButton = new QToolButton(central);
        projectLayout->addWidget(openProjectButton);
        saveProjectButton = new QToolButton(central);
        projectLayout->addWidget(saveProjectButton);
        createProjectButton = new QToolButton(central);
        projectLayout->addWidget(createProjectButton);
        addLayerButton = new QToolButton(central);
        projectLayout->addWidget(addLayerButton);
        deleteLayerButton = new QToolButton(central);
        projectLayout->addWidget(deleteLayerButton);
        projectLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
        gridLayout->addLayout(projectLayout, 0, 0, 1, 3);
        // 工具 + 硬件按钮行
        QHBoxLayout *toolLayout = new QHBoxLayout();
        breakCopiedItemButton = new QToolButton(central);
        toolLayout->addWidget(breakCopiedItemButton);
        breakOffsetItemButton = new QToolButton(central);
        toolLayout->addWidget(breakOffsetItemButton);
        centerButton = new QToolButton(central);
        toolLayout->addWidget(centerButton);
        copyButton = new QToolButton(central);
        toolLayout->addWidget(copyButton);
        cutButton = new QToolButton(central);
        toolLayout->addWidget(cutButton);
        deleteButton = new QToolButton(central);
        toolLayout->addWidget(deleteButton);
        dragSceneButton = new QToolButton(central);
        toolLayout->addWidget(dragSceneButton);
        drawTestLineButton = new QToolButton(central);
        toolLayout->addWidget(drawTestLineButton);
        editButton = new QToolButton(central);
        toolLayout->addWidget(editButton);
        mirrorHorizontalButton = new QToolButton(central);
        toolLayout->addWidget(mirrorHorizontalButton);
        mirrorVerticalButton = new QToolButton(central);
        toolLayout->addWidget(mirrorVerticalButton);
        pasteButton = new QToolButton(central);
        toolLayout->addWidget(pasteButton);
        redoButton = new QToolButton(central);
        toolLayout->addWidget(redoButton);
        undoButton = new QToolButton(central);
        toolLayout->addWidget(undoButton);
        delayTimeButton = new QToolButton(central);
        toolLayout->addWidget(delayTimeButton);
        digitalInButton = new QToolButton(central);
        toolLayout->addWidget(digitalInButton);
        digitalOutButton = new QToolButton(central);
        toolLayout->addWidget(digitalOutButton);
        doPauseButton = new QToolButton(central);
        toolLayout->addWidget(doPauseButton);
        loopButton = new QToolButton(central);
        toolLayout->addWidget(loopButton);
        markButton = new QToolButton(central);
        toolLayout->addWidget(markButton);
        motionButton = new QToolButton(central);
        toolLayout->addWidget(motionButton);
        toolLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
        gridLayout->addLayout(toolLayout, 1, 0, 1, 3);
        // 主控件布局
        QHBoxLayout *mainLayout = new QHBoxLayout(central);
        treeView = new TreeView(central); // 左：TreeView，占比 1
        mainLayout->addWidget(treeView, /*stretch=*/1);
        tabWidget = new TabWidget(central);// 中：TabWidget，占比 1
        mainLayout->addWidget(tabWidget, /*stretch=*/1);
        graphicsView = new GraphicsView(central); // 右：GraphicsView，占比 3
        mainLayout->addWidget(graphicsView, /*stretch=*/3);
        QVBoxLayout *drawButtonLayout = new QVBoxLayout();// 最右：绘图按钮栏，占最小固定宽度
        drawArcButton = new QToolButton(central);
        drawButtonLayout->addWidget(drawArcButton);
        drawCircleButton = new QToolButton(central);
        drawButtonLayout->addWidget(drawCircleButton);
        drawEllipseButton = new QToolButton(central);
        drawButtonLayout->addWidget(drawEllipseButton);
        drawLineButton = new QToolButton(central);
        drawButtonLayout->addWidget(drawLineButton);
        drawPointButton = new QToolButton(central);
        drawButtonLayout->addWidget(drawPointButton);
        drawPolygonButton = new QToolButton(central);
        drawButtonLayout->addWidget(drawPolygonButton);
        drawPolylineButton = new QToolButton(central);
        drawButtonLayout->addWidget(drawPolylineButton);
        drawRectButton = new QToolButton(central);
        drawButtonLayout->addWidget(drawRectButton);
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
/// Manager Initialization
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
