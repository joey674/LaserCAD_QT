#include "mainwindow.h"
#include "editorpage.h"
#include "projectpage.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QStackedWidget>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    // 左侧按钮区域
    QWidget *sideBar = new QWidget;
    QVBoxLayout *btnLayout = new QVBoxLayout(sideBar);
    btnLayout->setSpacing(0);
    btnLayout->setMargin(0);

    QToolButton *btnProject = new QToolButton;
    // btnProject->setIcon(QIcon(":/icons/project.svg"));
    // btnProject->setToolTip("项目");
    btnProject->setCheckable(true);
    btnProject->setChecked(true); // 初始选中

    QToolButton *btnEditor = new QToolButton;
    // btnEditor->setIcon(QIcon(":/icons/editor.svg"));
    // btnEditor->setToolTip("编辑器");
    btnEditor->setCheckable(true);

    btnLayout->addWidget(btnProject);
    btnLayout->addWidget(btnEditor);
    btnLayout->addStretch();

    // 页面区域
    QStackedWidget *stack = new QStackedWidget;
    stack->addWidget(new ProjectPage);
    stack->addWidget(new EditorPage);

    // 总体布局
    QHBoxLayout *mainLayout = new QHBoxLayout(central);
    mainLayout->setMargin(0);
    mainLayout->addWidget(sideBar);
    mainLayout->addWidget(stack);

    // 切换逻辑
    connect(btnProject, &QToolButton::clicked, [=]() {
        btnProject->setChecked(true);
        btnEditor->setChecked(false);
        stack->setCurrentIndex(0);
    });

    connect(btnEditor, &QToolButton::clicked, [=]() {
        btnEditor->setChecked(true);
        btnProject->setChecked(false);
        stack->setCurrentIndex(1);
    });
}

MainWindow::~MainWindow() {}
