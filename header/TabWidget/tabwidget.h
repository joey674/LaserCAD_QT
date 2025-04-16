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
        countSpin->setRange(1, 9999);
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
        hCountSpin->setRange(1, 9999);
        QSpinBox* vCountSpin = new QSpinBox();
        vCountSpin->setRange(1, 9999);
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
    void addOffsetTab() {
        QWidget* offsetTab = new QWidget();
        QVBoxLayout* mainLayout = new QVBoxLayout(offsetTab);
        // 输入字段
        QFormLayout* formLayout = new QFormLayout();
        QDoubleSpinBox* spacingSpin = new QDoubleSpinBox();
        spacingSpin->setRange(-9999, 9999);
        spacingSpin->setValue(10.0);
        QSpinBox* countSpin = new QSpinBox();
        countSpin->setRange(1, 9999);
        countSpin->setValue(3);
        QPushButton* confirmBtn = new QPushButton("Confirm");
        formLayout->addRow("Offset:", spacingSpin);
        formLayout->addRow("Offset Count:", countSpin);
        mainLayout->addLayout(formLayout);
        mainLayout->addWidget(confirmBtn);
        // connect 按钮
        connect(confirmBtn, &QPushButton::clicked, offsetTab, [ = ]() {
            double offset = spacingSpin->value();
            int offsetNum = countSpin->value();
            EditManager::getIns ().onTabWidgetOffsetTabParallelOffset(offset, offsetNum);
        });
        this->addTab(offsetTab, "Offset");
    }
    void addArcGeometryTab() {
        QWidget* arcTab = new QWidget();
        QVBoxLayout* mainLayout = new QVBoxLayout(arcTab);
        QFormLayout* formLayout = new QFormLayout();
        // 起点
        QDoubleSpinBox* startX = new QDoubleSpinBox();
        startX->setRange(-1e6, 1e6);
        QDoubleSpinBox* startY = new QDoubleSpinBox();
        startY->setRange(-1e6, 1e6);
        // 终点
        QDoubleSpinBox* endX = new QDoubleSpinBox();
        endX->setRange(-1e6, 1e6);
        QDoubleSpinBox* endY = new QDoubleSpinBox();
        endY->setRange(-1e6, 1e6);
        // angle
        QDoubleSpinBox* angleSpin = new QDoubleSpinBox();
        angleSpin->setRange(-360, 360);
        angleSpin->setDecimals(5);
        angleSpin->setValue(0.5);
        // 按钮
        QPushButton* confirmBtn = new QPushButton("Confirm");
        // 添加到 form
        formLayout->addRow("Start X:", startX);
        formLayout->addRow("Start Y:", startY);
        formLayout->addRow("End X:", endX);
        formLayout->addRow("End Y:", endY);
        formLayout->addRow("Angle:", angleSpin);
        mainLayout->addLayout(formLayout);
        mainLayout->addWidget(confirmBtn);
        connect(confirmBtn, &QPushButton::clicked, arcTab, [ = ]() {
            QPointF start(startX->value(), startY->value());
            QPointF end(endX->value(), endY->value());
            double angle = angleSpin->value();
            EditManager::getIns().onTabWidgetArcGeometryTab(start, end, angle);
        });
        this->addTab(arcTab, "Arc Geometry");
    }
    void addCircleGeometryTab() {
        QWidget* circleTab = new QWidget();
        QVBoxLayout* mainLayout = new QVBoxLayout(circleTab);
        QFormLayout* formLayout = new QFormLayout();
        QDoubleSpinBox* centerX = new QDoubleSpinBox();
        centerX->setRange(-1e6, 1e6);
        QDoubleSpinBox* centerY = new QDoubleSpinBox();
        centerY->setRange(-1e6, 1e6);
        QPushButton* confirmBtn = new QPushButton("Confirm");
        formLayout->addRow("Center X:", centerX);
        formLayout->addRow("Center Y:", centerY);
        mainLayout->addLayout(formLayout);
        mainLayout->addWidget(confirmBtn);
        connect(confirmBtn, &QPushButton::clicked, circleTab, [ = ]() {
            QPointF pt(centerX->value(), centerY->value());
            EditManager::getIns().onTabWidgetCircleGeometryTab(pt);
        });
        this->addTab(circleTab, "Circle Geometry");
    }
    void addLineGeometryTab() {
        QWidget* lineTab = new QWidget();
        QVBoxLayout* mainLayout = new QVBoxLayout(lineTab);
        QFormLayout* formLayout = new QFormLayout();
        QDoubleSpinBox* v0x = new QDoubleSpinBox();
        v0x->setRange(-1e6, 1e6);
        QDoubleSpinBox* v0y = new QDoubleSpinBox();
        v0y->setRange(-1e6, 1e6);
        QDoubleSpinBox* v1x = new QDoubleSpinBox();
        v1x->setRange(-1e6, 1e6);
        QDoubleSpinBox* v1y = new QDoubleSpinBox();
        v1y->setRange(-1e6, 1e6);
        QPushButton* confirmBtn = new QPushButton("Confirm");
        formLayout->addRow("Vertex0 X:", v0x);
        formLayout->addRow("Vertex0 Y:", v0y);
        formLayout->addRow("Vertex1 X:", v1x);
        formLayout->addRow("Vertex1 Y:", v1y);
        mainLayout->addLayout(formLayout);
        mainLayout->addWidget(confirmBtn);
        connect(confirmBtn, &QPushButton::clicked, lineTab, [ = ]() {
            QPointF v0(v0x->value(), v0y->value());
            QPointF v1(v1x->value(), v1y->value());
            EditManager::getIns().onTabWidgetLineGeometryTab(v0, v1);
        });
        this->addTab(lineTab, "Line Geometry");
    }
    void addPointGeometryTab() {
        QWidget* pointTab = new QWidget();
        QVBoxLayout* mainLayout = new QVBoxLayout(pointTab);
        QFormLayout* formLayout = new QFormLayout();
        QDoubleSpinBox* xSpin = new QDoubleSpinBox();
        xSpin->setRange(-1e6, 1e6);
        QDoubleSpinBox* ySpin = new QDoubleSpinBox();
        ySpin->setRange(-1e6, 1e6);
        QPushButton* confirmBtn = new QPushButton("Confirm");
        formLayout->addRow("X:", xSpin);
        formLayout->addRow("Y:", ySpin);
        mainLayout->addLayout(formLayout);
        mainLayout->addWidget(confirmBtn);
        connect(confirmBtn, &QPushButton::clicked, pointTab, [ = ]() {
            QPointF pt(xSpin->value(), ySpin->value());
            EditManager::getIns().onTabWidgetPointGeometryTab(pt);
        });
        this->addTab(pointTab, "Point Geometry");
    }
    void addPolylineGeometryTab() {
    }
};

#endif // TABWIDGET_H
