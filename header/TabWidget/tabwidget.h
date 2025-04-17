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
#include "editcontroller.h"

class TabWidget : public QTabWidget {
    Q_OBJECT
public:
    explicit TabWidget(QWidget *parent = nullptr) {};

    void clearAllTabs() {
        while (count() > 0) {
            removeTab(0);
        }
    }

    void addCopyTab(const UUID uuid) {
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
        spacingSpin->setValue(100);
        QSpinBox* countSpin = new QSpinBox();
        countSpin->setRange(1, 9999);
        countSpin->setValue(10);
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
            EditController::getIns().onTabWidgetCopyTabVectorCopy(dir, spacing, count);
        });
        // --- Matrix Copy Layout ---
        QWidget* matrixPage = new QWidget();
        QFormLayout* matrixLayout = new QFormLayout(matrixPage);
        QLineEdit* horizontalVecEdit = new QLineEdit("1, 0");
        QLineEdit* verticalVecEdit = new QLineEdit("0, 1");
        QDoubleSpinBox* hSpacingSpin = new QDoubleSpinBox();
        hSpacingSpin->setRange(0, 9999);
        hSpacingSpin->setValue(100);
        QDoubleSpinBox* vSpacingSpin = new QDoubleSpinBox();
        vSpacingSpin->setRange(0, 9999);
        vSpacingSpin->setValue(100);
        QSpinBox* hCountSpin = new QSpinBox();
        hCountSpin->setRange(1, 9999);
        hCountSpin->setValue(10);
        QSpinBox* vCountSpin = new QSpinBox();
        vCountSpin->setRange(1, 9999);
        vCountSpin->setValue(10);
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
            EditController::getIns().onTabWidgetCopyTabMatrixCopy(
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
    void addOffsetTab(const UUID uuid) {
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
            EditController::getIns ().onTabWidgetOffsetTabParallelOffset(offset, offsetNum);
        });
        this->addTab(offsetTab, "Offset");
    }
    void addMarkTab(const UUID uuid) {
        QWidget* markTab = new QWidget();
        QVBoxLayout* mainLayout = new QVBoxLayout(markTab);
        // 表单布局
        QFormLayout* formLayout = new QFormLayout();
        QDoubleSpinBox* markSpeedSpin = new QDoubleSpinBox();
        markSpeedSpin->setRange(0, 100000);
        markSpeedSpin->setValue(1000.0);
        QDoubleSpinBox* jumpSpeedSpin = new QDoubleSpinBox();
        jumpSpeedSpin->setRange(0, 100000);
        jumpSpeedSpin->setValue(3000.0);
        QSpinBox* frequencySpin = new QSpinBox();
        frequencySpin->setRange(0, 1000000);
        frequencySpin->setValue(100000);
        QSpinBox* wobelAmlSpin = new QSpinBox();
        wobelAmlSpin->setRange(0, 100000);
        wobelAmlSpin->setValue(0);
        QSpinBox* repetTimeSpin = new QSpinBox();
        repetTimeSpin->setRange(1, 1000);
        repetTimeSpin->setValue(1);
        QDoubleSpinBox* powerSpin = new QDoubleSpinBox();
        powerSpin->setRange(0, 100);
        powerSpin->setDecimals(2);
        powerSpin->setValue(0.0);
        QDoubleSpinBox* pulseWidthSpin = new QDoubleSpinBox();
        pulseWidthSpin->setRange(0, 1000);
        pulseWidthSpin->setDecimals(2);
        pulseWidthSpin->setValue(2.0);
        QSpinBox* freqSpin = new QSpinBox();
        freqSpin->setRange(0, 100000);
        freqSpin->setValue(100);
        // QCheckBox* vectorDependentCheck = new QCheckBox("Vector Dependent:");
        // QComboBox* vectorCombo = new QComboBox();  // 可添加项
        // QLineEdit* vectorLineEdit = new QLineEdit("-2147483");
        // Confirm 按钮
        QPushButton* confirmBtn = new QPushButton("Confirm");
        // 添加到表单布局
        formLayout->addRow("Mark Speed:", markSpeedSpin);
        formLayout->addRow("Jump Speed:", jumpSpeedSpin);
        formLayout->addRow("Frequency:", frequencySpin);
        formLayout->addRow("Wobel Aml:", wobelAmlSpin);
        formLayout->addRow("Repet Time:", repetTimeSpin);
        formLayout->addRow("Power:", powerSpin);
        formLayout->addRow("Pulse Width:", pulseWidthSpin);
        formLayout->addRow("Freq:", freqSpin);
        // formLayout->addRow(vectorDependentCheck);
        // vector dependent 区域横排
        QHBoxLayout* vectorLayout = new QHBoxLayout();
        // vectorLayout->addWidget(vectorCombo);
        // vectorLayout->addWidget(vectorLineEdit);
        formLayout->addRow("", vectorLayout);
        mainLayout->addLayout(formLayout);
        mainLayout->addWidget(confirmBtn);
        // 点击事件绑定
        connect(confirmBtn, &QPushButton::clicked, markTab, [ = ]() {
            // 示例调用（根据你的接口调整）
            EditController::getIns().onTabWidgetMarkTab(
                // markSpeedSpin->value(),
                // jumpSpeedSpin->value(),
                // frequencySpin->value(),
                // wobelAmlSpin->value(),
                // repetTimeSpin->value(),
                // powerSpin->value(),
                // pulseWidthSpin->value(),
                // freqSpin->value(),
                // // vectorDependentCheck->isChecked(),
                // // vectorCombo->currentText(),
                // // vectorLineEdit->text().toInt()
            );
        });
        this->addTab(markTab, "Mark");
    }

    void addDelayTab(const UUID uuid) {}

    void addArcGeometryTab(const UUID uuid) {
        // auto map = Manager::getIns().propertyMapFind(uuid, PropertyIndex::Geometry).toMap();
        auto item = Manager::getIns().itemMapFind(uuid);
        QPointF v0 = item->getVertexPos(0);
        QPointF v1 = item->getVertexPos(1);
        double angle = item->getVertex(1).angle;
        //
        QWidget* arcTab = new QWidget();
        QVBoxLayout* mainLayout = new QVBoxLayout(arcTab);
        QFormLayout* formLayout = new QFormLayout();
        // 起点
        QDoubleSpinBox* startX = new QDoubleSpinBox();
        startX->setRange(-1e6, 1e6);
        startX->setValue(v0.x ());
        QDoubleSpinBox* startY = new QDoubleSpinBox();
        startY->setRange(-1e6, 1e6);
        startY->setValue(v0.y ());
        // 终点
        QDoubleSpinBox* endX = new QDoubleSpinBox();
        endX->setRange(-1e6, 1e6);
        endX->setValue(v1.x ());
        QDoubleSpinBox* endY = new QDoubleSpinBox();
        endY->setRange(-1e6, 1e6);
        endY->setValue(v1.y ());
        // angle
        QDoubleSpinBox* angleSpin = new QDoubleSpinBox();
        angleSpin->setRange(-359.99, 359.99);
        angleSpin->setDecimals(2);
        angleSpin->setValue(angle);
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
            if (angle == 0) {
                WARN_MSG("angle can not be 0");
                return;
            }
            EditController::getIns().onTabWidgetArcGeometryTab(start, end, angle);
        });
        this->addTab(arcTab, "Arc Geometry");
    }
    void addCircleGeometryTab(const UUID uuid) {
        auto itemptr = Manager::getIns().itemMapFind(uuid);
        auto item = static_cast < CircleItem * > (itemptr.get());
        QPointF center = item->getVertexPos(0);
        double radius = item->getRadius();
        //
        QWidget* circleTab = new QWidget();
        QVBoxLayout* mainLayout = new QVBoxLayout(circleTab);
        QFormLayout* formLayout = new QFormLayout();
        // 圆心 X
        QDoubleSpinBox* centerX = new QDoubleSpinBox();
        centerX->setRange(-1e6, 1e6);
        centerX->setValue(center.x ());
        // 圆心 Y
        QDoubleSpinBox* centerY = new QDoubleSpinBox();
        centerY->setRange(-1e6, 1e6);
        centerY->setValue(center.y ());
        // 半径
        QDoubleSpinBox* radiusSpin = new QDoubleSpinBox();
        radiusSpin->setRange(0.001, 1e6);
        radiusSpin->setValue(radius);
        // 按钮
        QPushButton* confirmBtn = new QPushButton("Confirm");
        // 加入表单
        formLayout->addRow("Center X:", centerX);
        formLayout->addRow("Center Y:", centerY);
        formLayout->addRow("Radius:", radiusSpin);
        mainLayout->addLayout(formLayout);
        mainLayout->addWidget(confirmBtn);
        // 点击事件绑定
        connect(confirmBtn, &QPushButton::clicked, circleTab, [ = ]() {
            QPointF center(centerX->value(), centerY->value());
            double radius = radiusSpin->value();
            EditController::getIns().onTabWidgetCircleGeometryTab(center, radius);
        });
        this->addTab(circleTab, "Circle Geometry");
    }
    void addLineGeometryTab(const UUID uuid) {
        auto item = Manager::getIns().itemMapFind(uuid);
        QPointF v0 = item->getVertexPos(0);
        QPointF v1 = item->getVertexPos(1);
        //
        QWidget* lineTab = new QWidget();
        QVBoxLayout* mainLayout = new QVBoxLayout(lineTab);
        QFormLayout* formLayout = new QFormLayout();
        QDoubleSpinBox* v0x = new QDoubleSpinBox();
        v0x->setRange(-1e6, 1e6);
        v0x->setValue(v0.x ());
        QDoubleSpinBox* v0y = new QDoubleSpinBox();
        v0y->setRange(-1e6, 1e6);
        v0y->setValue(v0.y ());
        QDoubleSpinBox* v1x = new QDoubleSpinBox();
        v1x->setRange(-1e6, 1e6);
        v1x->setValue(v1.x ());
        QDoubleSpinBox* v1y = new QDoubleSpinBox();
        v1y->setRange(-1e6, 1e6);
        v0y->setValue(v1.y ());
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
            EditController::getIns().onTabWidgetLineGeometryTab(v0, v1);
        });
        this->addTab(lineTab, "Line Geometry");
    }
    void addPointGeometryTab(const UUID uuid) {
        auto item = Manager::getIns().itemMapFind(uuid);
        QPointF v0 = item->getVertexPos(0);
        //
        QWidget* pointTab = new QWidget();
        QVBoxLayout* mainLayout = new QVBoxLayout(pointTab);
        QFormLayout* formLayout = new QFormLayout();
        QDoubleSpinBox* xSpin = new QDoubleSpinBox();
        xSpin->setRange(-1e6, 1e6);
        xSpin->setValue(v0.x());
        QDoubleSpinBox* ySpin = new QDoubleSpinBox();
        ySpin->setRange(-1e6, 1e6);
        ySpin->setValue(v0.y());
        QPushButton* confirmBtn = new QPushButton("Confirm");
        formLayout->addRow("X:", xSpin);
        formLayout->addRow("Y:", ySpin);
        mainLayout->addLayout(formLayout);
        mainLayout->addWidget(confirmBtn);
        connect(confirmBtn, &QPushButton::clicked, pointTab, [ = ]() {
            QPointF pt(xSpin->value(), ySpin->value());
            EditController::getIns().onTabWidgetPointGeometryTab(pt);
        });
        this->addTab(pointTab, "Point Geometry");
    }
    void addPolylineGeometryTab(const UUID uuid) {
    }

};

#endif // TABWIDGET_H
