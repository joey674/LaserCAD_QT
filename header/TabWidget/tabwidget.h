#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QComboBox>
#include <QLabel>
#include <QStackedWidget>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QFormLayout>
#include <QLineEdit>
#include "utils.hpp"
#include "editmanager.h"

class TabWidget : public QTabWidget {
    Q_OBJECT
public:
    explicit TabWidget(QWidget *parent = nullptr) {};

    void clearAllTabs() {
        while (count() > 0) {
            removeTab(0);
        }
    }

    void addCopyTab() {
        QWidget* copyTab = new QWidget();
        QVBoxLayout* mainLayout = new QVBoxLayout(copyTab);
        // 1. 复制方式选择
        QComboBox* modeCombo = new QComboBox();
        modeCombo->addItem("Vector Copy");
        modeCombo->addItem("Matrix Copy");
        mainLayout->addWidget(new QLabel("Copy Mode:"));
        mainLayout->addWidget(modeCombo);
        // 2. 使用 stacked widget 切换不同输入区域
        QStackedWidget* stackedWidget = new QStackedWidget();
        // --- Vector Copy Layout ---
        QWidget* vectorPage = new QWidget();
        QFormLayout* vectorLayout = new QFormLayout(vectorPage);
        QLineEdit* directionVecEdit = new QLineEdit("1, 0");
        QDoubleSpinBox* spacingSpin = new QDoubleSpinBox();
        spacingSpin->setRange(0, 9999);
        QSpinBox* countSpin = new QSpinBox();
        countSpin->setRange(1, 999);
        QPushButton* vectorConfirmBtn = new QPushButton("Confirm");
        vectorLayout->addRow("Direction (x, y):", directionVecEdit);
        vectorLayout->addRow("Spacing:", spacingSpin);
        vectorLayout->addRow("Count:", countSpin);
        vectorLayout->addRow("", vectorConfirmBtn);
        // 连接 vectorConfirmBtn 点击事件
        QObject::connect(vectorConfirmBtn, &QPushButton::clicked, copyTab, [ = ]() {
            QPointF dir = parseStringToPointF(directionVecEdit->text());
            double spacing = spacingSpin->value();
            int count = countSpin->value();
            EditManager::getIns().onTabWidgetCopyTabVectorCopy(dir, spacing, count);
        });
        // --- Matrix Copy Layout ---
        QWidget* matrixPage = new QWidget();
        QFormLayout* matrixLayout = new QFormLayout(matrixPage);
        QLineEdit* horizontalVecEdit = new QLineEdit("1, 0");
        QLineEdit* verticalVecEdit = new QLineEdit("0, 1");
        QDoubleSpinBox* hSpacingSpin = new QDoubleSpinBox();
        hSpacingSpin->setRange(0, 9999);
        QDoubleSpinBox* vSpacingSpin = new QDoubleSpinBox();
        vSpacingSpin->setRange(0, 9999);
        QSpinBox* hCountSpin = new QSpinBox();
        hCountSpin->setRange(1, 999);
        QSpinBox* vCountSpin = new QSpinBox();
        vCountSpin->setRange(1, 999);
        QPushButton* matrixConfirmBtn = new QPushButton("Confirm");
        matrixLayout->addRow("Horizontal Vector:", horizontalVecEdit);
        matrixLayout->addRow("Vertical Vector:", verticalVecEdit);
        matrixLayout->addRow("Horizontal Spacing:", hSpacingSpin);
        matrixLayout->addRow("Vertical Spacing:", vSpacingSpin);
        matrixLayout->addRow("Horizontal Count:", hCountSpin);
        matrixLayout->addRow("Vertical Count:", vCountSpin);
        matrixLayout->addRow("", matrixConfirmBtn);
        // 连接 matrixConfirmBtn 点击事件
        QObject::connect(matrixConfirmBtn, &QPushButton::clicked, copyTab, [ = ]() {
            QPointF hVec = parseStringToPointF(horizontalVecEdit->text());
            QPointF vVec = parseStringToPointF(verticalVecEdit->text());
            double hSpacing = hSpacingSpin->value();
            double vSpacing = vSpacingSpin->value();
            int hCount = hCountSpin->value();
            int vCount = vCountSpin->value();
            EditManager::getIns().onTabWidgetCopyTabMatrixCopy(
                hVec, vVec, hSpacing, vSpacing, hCount, vCount);
        });
        // 添加两个页面
        stackedWidget->addWidget(vectorPage); // index 0
        stackedWidget->addWidget(matrixPage); // index 1
        // 切换逻辑
        QObject::connect(modeCombo, QOverload < int >::of(&QComboBox::currentIndexChanged), stackedWidget, &QStackedWidget::setCurrentIndex);
        mainLayout->addWidget(stackedWidget);
        // 添加到 tab 中
        this->addTab(copyTab, "Copy");
    }

};

#endif // TABWIDGET_H
