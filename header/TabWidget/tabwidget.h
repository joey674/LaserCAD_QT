#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QCheckBox>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QStackedWidget>
#include <QTabWidget>
#include "editcontroller.h"
#include "protocol.h"
#include "utils.hpp"
#include <polylinecombine.hpp>
#include <QGroupBox>
#include <QRadioButton>
#include <QButtonGroup>

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
            EditController::getIns().onTabWidgetCopyTabVectorCopy(VectorCopyParams{dir, spacing, count});
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
        QComboBox* copyOrderCombo = new QComboBox();
        copyOrderCombo->addItem("Zig-Zag by Row", 0);
        copyOrderCombo->addItem("Zig-Zag by Column", 1);
        copyOrderCombo->addItem("Sequential by Row", 2);
        copyOrderCombo->addItem("Sequential by Column", 3);
        QPushButton* matrixConfirmBtn = new QPushButton("Confirm");
        matrixLayout->addRow("Horizontal Vector:", horizontalVecEdit);
        matrixLayout->addRow("Vertical Vector:", verticalVecEdit);
        matrixLayout->addRow("Horizontal Spacing:", hSpacingSpin);
        matrixLayout->addRow("Vertical Spacing:", vSpacingSpin);
        matrixLayout->addRow("Horizontal Count:", hCountSpin);
        matrixLayout->addRow("Vertical Count:", vCountSpin);
        matrixLayout->addRow("Copy Order:", copyOrderCombo);
        matrixLayout->addRow("", matrixConfirmBtn);
        QObject::connect(matrixConfirmBtn, &QPushButton::clicked, copyTab, [ = ]() {
            QPointF hVec = parseStringToPointF(horizontalVecEdit->text());
            QPointF vVec = parseStringToPointF(verticalVecEdit->text());
            double hSpacing = hSpacingSpin->value();
            double vSpacing = vSpacingSpin->value();
            int hCount = hCountSpin->value();
            int vCount = vCountSpin->value();
            int copyOrder = 0;
            copyOrder = copyOrderCombo->currentData().toInt();
            EditController::getIns().onTabWidgetCopyTabMatrixCopy(MatrixCopyParams{
                hVec, vVec, hSpacing, vSpacing, hCount, vCount, copyOrder});
        });
        // 添加两个页面
        stackedWidget->addWidget(vectorPage); // index 0
        stackedWidget->addWidget(matrixPage); // index 1
        QObject::connect(modeCombo, QOverload < int >::of(&QComboBox::currentIndexChanged), stackedWidget, &QStackedWidget::setCurrentIndex);
        mainLayout->addWidget(stackedWidget);
        this->addTab(copyTab, "Copy");
    }
    void addOffsetTab(const UUID uuid) {
        auto item = Manager::getIns().itemMapFind(uuid);
        auto offset = item->getOffsetParams ().offset;
        auto offsetCount = item->getOffsetParams ().offsetCount;
        if (offset == 0 && offsetCount == 0) {
            offset = 10;
            offsetCount = 3;
        }
        //
        QWidget* offsetTab = new QWidget();
        QVBoxLayout* mainLayout = new QVBoxLayout(offsetTab);
        // 输入字段
        QFormLayout* formLayout = new QFormLayout();
        QDoubleSpinBox* spacingSpin = new QDoubleSpinBox();
        spacingSpin->setRange(-9999, 9999);
        spacingSpin->setValue(offset);
        QSpinBox* countSpin = new QSpinBox();
        countSpin->setRange(0, 9999);
        countSpin->setValue(offsetCount);
        QPushButton* confirmBtn = new QPushButton("Confirm");
        formLayout->addRow("Offset:", spacingSpin);
        formLayout->addRow("Offset Count:", countSpin);
        mainLayout->addLayout(formLayout);
        mainLayout->addWidget(confirmBtn);
        // connect 按钮
        connect(confirmBtn, &QPushButton::clicked, offsetTab, [ = ]() {
            double offset = spacingSpin->value();
            int offsetNum = countSpin->value();
            EditController::getIns ().onTabWidgetOffsetTabParallelOffset(OffsetParams{offset, offsetNum});
        });
        this->addTab(offsetTab, "Offset");
    }
    void addMarkParamsTab(const UUID uuid) {
        auto item = Manager::getIns().itemMapFind(uuid);
        auto params = item->getMarkParams();
        //
        QWidget* markTab = new QWidget();
        QVBoxLayout* mainLayout = new QVBoxLayout(markTab);
        // 表单布局
        QFormLayout* formLayout = new QFormLayout();
        QDoubleSpinBox* markSpeedSpin = new QDoubleSpinBox();
        markSpeedSpin->setRange(0, 100000);
        markSpeedSpin->setValue(params.markSpeed);
        QDoubleSpinBox* jumpSpeedSpin = new QDoubleSpinBox();
        jumpSpeedSpin->setRange(0, 100000);
        jumpSpeedSpin->setValue(params.jumpSpeed);
        QSpinBox* frequencySpin = new QSpinBox();
        frequencySpin->setRange(0, 1000000);
        frequencySpin->setValue(params.frequency);
        QSpinBox* wobelAmlSpin = new QSpinBox();
        wobelAmlSpin->setRange(0, 100000);
        wobelAmlSpin->setValue(params.wobelAml);
        QSpinBox* repetTimeSpin = new QSpinBox();
        repetTimeSpin->setRange(1, 1000);
        repetTimeSpin->setValue(params.repetTime);
        QDoubleSpinBox* powerSpin = new QDoubleSpinBox();
        powerSpin->setRange(0, 100);
        powerSpin->setDecimals(2);
        powerSpin->setValue(params.power);
        QDoubleSpinBox* pulseWidthSpin = new QDoubleSpinBox();
        pulseWidthSpin->setRange(0, 1000);
        pulseWidthSpin->setDecimals(2);
        pulseWidthSpin->setValue(params.pulseWidth);
        QSpinBox* wobelFreqSpin = new QSpinBox();
        wobelFreqSpin->setRange(0, 100000);
        wobelFreqSpin->setValue(params.wobelFreq);
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
        formLayout->addRow("Wobel Freq:", wobelFreqSpin);
        // vector dependent 区域横排
        QHBoxLayout* vectorLayout = new QHBoxLayout();
        formLayout->addRow("", vectorLayout);
        mainLayout->addLayout(formLayout);
        mainLayout->addWidget(confirmBtn);
        // 点击事件绑定
        connect(confirmBtn, &QPushButton::clicked, markTab, [=]() {
            MarkParams params = MarkParams{
                markSpeedSpin->value(),
                jumpSpeedSpin->value(),
                static_cast<unsigned int>(frequencySpin->value()),
                static_cast<unsigned int>(repetTimeSpin->value()),
                powerSpin->value(),
                static_cast<unsigned int>(pulseWidthSpin->value()),
                static_cast<unsigned int>(wobelAmlSpin->value()),
                static_cast<unsigned int>(wobelFreqSpin->value()),
            };
            EditController::getIns().onTabWidgetMarkParamsTab(params);
        });
        this->addTab(markTab, "MarkParams");
    }
    void addDelayParamsTab(const UUID uuid) {
        auto item = Manager::getIns().itemMapFind(uuid);
        auto params = item->getDelayParams();
        QWidget* tab = new QWidget();
        QVBoxLayout* tabLayout = new QVBoxLayout(tab);
        QScrollArea* scrollArea = new QScrollArea();
        scrollArea->setWidgetResizable(true);
        QWidget* content = new QWidget();
        QVBoxLayout* layout = new QVBoxLayout(content);
        layout->setAlignment(Qt::AlignTop);
        layout->setSpacing(10);
        QFormLayout* formLayout = new QFormLayout();
        QSpinBox* startDelaySpin = new QSpinBox();
        startDelaySpin->setRange(0, 1000000);
        startDelaySpin->setValue(params.laserOnDelay);
        formLayout->addRow("Start Delay:", startDelaySpin);
        QSpinBox* endDelaySpin = new QSpinBox();
        endDelaySpin->setRange(0, 1000000);
        endDelaySpin->setValue(params.laserOffDelay);
        formLayout->addRow("End Delay:", endDelaySpin);
        QSpinBox* polygonDelaySpin = new QSpinBox();
        polygonDelaySpin->setRange(0, 1000000);
        polygonDelaySpin->setValue(params.polygonDelay);
        formLayout->addRow("Polygon Delay:", polygonDelaySpin);
        QSpinBox* markDelaySpin = new QSpinBox();
        markDelaySpin->setRange(0, 1000000);
        markDelaySpin->setValue(params.markDelay);
        formLayout->addRow("Mark Delay:", markDelaySpin);
        QSpinBox* jumpDelaySpin = new QSpinBox();
        jumpDelaySpin->setRange(0, 1000000);
        jumpDelaySpin->setValue(params.jumpDelay);
        formLayout->addRow("Jump Delay:", jumpDelaySpin);
        layout->addLayout(formLayout);
        QPushButton* confirmBtn = new QPushButton("Confirm");
        confirmBtn->setFixedWidth(100);
        layout->addWidget(confirmBtn, 0, Qt::AlignCenter);
        connect(confirmBtn, &QPushButton::clicked, tab, [=]() {
            DelayParams params = {static_cast<unsigned int>(startDelaySpin->value()),
                                  static_cast<unsigned int>(endDelaySpin->value()),
                                  static_cast<unsigned int>(polygonDelaySpin->value()),
                                  static_cast<unsigned int>(markDelaySpin->value()),
                                  static_cast<unsigned int>(jumpDelaySpin->value())};
            EditController::getIns().onTabWidgetDelayParamsTab(params);
        });
        content->setLayout(layout);
        scrollArea->setWidget(content);
        tabLayout->addWidget(scrollArea);
        this->addTab(tab, "DelayParams");
    }

    void addArcGeometryTab(const UUID uuid) {
        auto item = Manager::getIns().itemMapFind(uuid);
        QPointF v0 = item->getVertexInScene(0).point;
        QPointF v1 = item->getVertexInScene(1).point;
        double angle = item->getVertexInScene(1).angle;
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
        this->addTab(arcTab, "Geometry");
    }
    void addCircleGeometryTab(const UUID uuid) {
        auto itemptr = Manager::getIns().itemMapFind(uuid);
        auto item = static_cast < CircleItem * > (itemptr.get());
        QPointF center = item->getVertexInScene(0).point;
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
        this->addTab(circleTab, "Geometry");
    }
    void addLineGeometryTab(const UUID uuid) {
        auto item = Manager::getIns().itemMapFind(uuid);
        QPointF v0 = item->getVertexInScene(0).point;
        QPointF v1 = item->getVertexInScene(1).point;
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
        this->addTab(lineTab, "Geometry");
    }
    void addPointGeometryTab(const UUID uuid) {
        auto item = Manager::getIns().itemMapFind(uuid);
        QPointF v0 = item->getVertexInScene(0).point;
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
        this->addTab(pointTab, "Geometry");
    }
    void addPolylineGeometryTab(const UUID uuid) {
        auto itemPtr = Manager::getIns().itemMapFind(uuid);
        auto item = static_cast < PolylineItem * > (itemPtr.get());
        uint count = item->getVertexCount();
        // 创建 scroll 区域
        QScrollArea *scrollArea = new QScrollArea();
        QWidget *innerWidget = new QWidget();
        QVBoxLayout *mainLayout = new QVBoxLayout(innerWidget);
        // 存储每个 vertex 的输入组件
        struct VertexInput {
            QDoubleSpinBox *x;
            QDoubleSpinBox *y;
            QDoubleSpinBox *angle;
        };
        QVector < VertexInput > vertexInputs;
        for (uint i = 0; i < count; ++i) {
            QPointF pos = item->getVertexInScene(i).point;
            double angle = item->getVertexInScene(i).angle;
            QDoubleSpinBox *vx = new QDoubleSpinBox();
            vx->setStyleSheet("QAbstractSpinBox::up-button, QAbstractSpinBox::down-button { width: "
                              "0; height: 0;  }");
            QDoubleSpinBox *vy = new QDoubleSpinBox();
            vy->setStyleSheet("QAbstractSpinBox::up-button, QAbstractSpinBox::down-button { width: "
                              "0; height: 0;  }");
            QDoubleSpinBox *va = new QDoubleSpinBox();
            va->setStyleSheet("QAbstractSpinBox::up-button, QAbstractSpinBox::down-button { width: "
                              "0; height: 0;  }");
            vx->setRange(-1e6, 1e6);
            vy->setRange(-1e6, 1e6);
            va->setRange(-360, 360);
            vx->setDecimals(3);
            vy->setDecimals(3);
            va->setDecimals(2);
            vx->setValue(pos.x());
            vy->setValue(pos.y());
            va->setValue(i == 0 ? 0.0 : angle); // 第一个点 angle 固定为 0
            if (i == 0) {
                va->setEnabled(false);    // 不让编辑
            }
            // 横向布局: "Vertex i: X [ ] Y [ ] Angle [ ]"
            QHBoxLayout *lineLayout = new QHBoxLayout();
            QLabel *label = new QLabel(QString("Vertex %1:").arg(i));
            label->setMinimumWidth(60);
            QLabel *xLabel = new QLabel("X:");
            QLabel *yLabel = new QLabel("Y:");
            QLabel *aLabel = new QLabel("Angle:");
            xLabel->setMinimumWidth(10);
            yLabel->setMinimumWidth(10);
            aLabel->setMinimumWidth(50);
            vx->setFixedWidth(60);
            vy->setFixedWidth(60);
            va->setFixedWidth(60);
            lineLayout->addWidget(label);
            lineLayout->addWidget(xLabel);
            lineLayout->addWidget(vx);
            lineLayout->addWidget(yLabel);
            lineLayout->addWidget(vy);
            lineLayout->addWidget(aLabel);
            lineLayout->addWidget(va);
            lineLayout->addStretch();
            mainLayout->addLayout(lineLayout);
            vertexInputs.append(VertexInput{vx, vy, va});
        }
        // Confirm 按钮
        QPushButton *confirmBtn = new QPushButton("Confirm");
        confirmBtn->setFixedWidth(100);
        confirmBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        mainLayout->addWidget(confirmBtn, 0, Qt::AlignCenter);
        // 设置 scroll 区域
        scrollArea->setWidget(innerWidget);
        scrollArea->setWidgetResizable(true);
        // 加入 tab
        QWidget *tab = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout(tab);
        layout->addWidget(scrollArea);
        // 点击事件
        connect(confirmBtn, &QPushButton::clicked, tab, [ = ]() {
            std::vector < Vertex > result;
            for (int i = 0; i < vertexInputs.size(); ++i) {
                const auto &w = vertexInputs[i];
                Vertex v;
                v.point = QPointF(w.x->value(), w.y->value());
                v.angle = (i == 0 ? 0.0 : w.angle->value());
                result.push_back(v);
            }
            EditController::getIns().onTabWidgetPolylineGeometryTab(result);
        });
        this->addTab(tab, "Geometry");
    }
    void addEllipseGeometryTab(const UUID uuid) {
        auto ptr = Manager::getIns().itemMapFind(uuid);
        auto item = static_cast < EllipseItem * > (ptr.get());
        QPointF center = item->getVertexInScene(0).point;
        double radiusX = item->getRadiusX();
        double radiusY = item->getRadiusY();
        double angle = item->getRotateAngle(); // 椭圆的旋转角度（相对于 x 轴）
        QWidget *ellipseTab = new QWidget();
        QVBoxLayout *mainLayout = new QVBoxLayout(ellipseTab);
        QFormLayout *formLayout = new QFormLayout();
        // 中心点
        QDoubleSpinBox *centerX = new QDoubleSpinBox();
        centerX->setRange(-1e6, 1e6);
        centerX->setValue(center.x());
        QDoubleSpinBox *centerY = new QDoubleSpinBox();
        centerY->setRange(-1e6, 1e6);
        centerY->setValue(center.y());
        // 半径
        QDoubleSpinBox *radiusXSpin = new QDoubleSpinBox();
        radiusXSpin->setRange(0.01, 1e6);
        radiusXSpin->setValue(radiusX);
        QDoubleSpinBox *radiusYSpin = new QDoubleSpinBox();
        radiusYSpin->setRange(0.01, 1e6);
        radiusYSpin->setValue(radiusY);
        // 角度
        QDoubleSpinBox *angleSpin = new QDoubleSpinBox();
        angleSpin->setRange(0, 359.99);
        angleSpin->setDecimals(2);
        angleSpin->setValue(angle);
        // 按钮
        QPushButton *confirmBtn = new QPushButton("Confirm");
        // 添加到表单
        formLayout->addRow("Center X:", centerX);
        formLayout->addRow("Center Y:", centerY);
        formLayout->addRow("Radius X:", radiusXSpin);
        formLayout->addRow("Radius Y:", radiusYSpin);
        formLayout->addRow("Angle:", angleSpin);
        mainLayout->addLayout(formLayout);
        mainLayout->addWidget(confirmBtn);
        connect(confirmBtn, &QPushButton::clicked, ellipseTab, [ = ]() {
            QPointF center(centerX->value(), centerY->value());
            double rx = radiusXSpin->value();
            double ry = radiusYSpin->value();
            double angle = angleSpin->value();
            if (rx <= 0 || ry <= 0) {
                WARN_MSG("Radius must be positive");
                return;
            }
            EditController::getIns().onTabWidgetEllipseGeometryTab(center, rx, ry, angle);
        });
        this->addTab(ellipseTab, "Geometry");
    }
    void addRectGeometryTab(const UUID uuid) {
        auto item = Manager::getIns().itemMapFind(uuid);
        QPointF topLeft = item->getVertexInScene(0).point;
        QPointF bottomRight = item->getVertexInScene(1).point;
        QWidget *rectTab = new QWidget();
        QVBoxLayout *mainLayout = new QVBoxLayout(rectTab);
        QFormLayout *formLayout = new QFormLayout();
        // 左上点
        QDoubleSpinBox *topLeftX = new QDoubleSpinBox();
        topLeftX->setRange(-1e6, 1e6);
        topLeftX->setValue(topLeft.x());
        QDoubleSpinBox *topLeftY = new QDoubleSpinBox();
        topLeftY->setRange(-1e6, 1e6);
        topLeftY->setValue(topLeft.y());
        // 右下点
        QDoubleSpinBox *bottomRightX = new QDoubleSpinBox();
        bottomRightX->setRange(-1e6, 1e6);
        bottomRightX->setValue(bottomRight.x());
        QDoubleSpinBox *bottomRightY = new QDoubleSpinBox();
        bottomRightY->setRange(-1e6, 1e6);
        bottomRightY->setValue(bottomRight.y());
        // 按钮
        QPushButton *confirmBtn = new QPushButton("Confirm");
        // 添加到 form layout
        formLayout->addRow("Top Left X:", topLeftX);
        formLayout->addRow("Top Left Y:", topLeftY);
        formLayout->addRow("Bottom Right X:", bottomRightX);
        formLayout->addRow("Bottom Right Y:", bottomRightY);
        mainLayout->addLayout(formLayout);
        mainLayout->addWidget(confirmBtn);
        // 绑定按钮事件
        connect(confirmBtn, &QPushButton::clicked, rectTab, [ = ]() {
            QPointF tl(topLeftX->value(), topLeftY->value());
            QPointF br(bottomRightX->value(), bottomRightY->value());
            if (tl == br) {
                WARN_MSG("Invalid rectangle: two corners are the same");
                return;
            }
            EditController::getIns().onTabWidgetRectGeometryTab(tl, br);
        });
        this->addTab(rectTab, "Geometry");
    }
    void addSpiralGeometryTab(const UUID uuid) {
        auto itemptr = Manager::getIns().itemMapFind(uuid);
        SpiralItem *item = static_cast < SpiralItem * > (itemptr.get());
        QPointF center = item->getVertexInScene(0).point;
        double r0 = item->getStartRadius();
        double r1 = item->getEndRadius();
        double turns = item->getTurns();
        double step = item->getAngleStepDeg();
        QWidget *spiralTab = new QWidget();
        QVBoxLayout *mainLayout = new QVBoxLayout(spiralTab);
        QFormLayout *formLayout = new QFormLayout();
        // 中心点
        QDoubleSpinBox *centerX = new QDoubleSpinBox();
        centerX->setRange(-1e6, 1e6);
        centerX->setValue(center.x());
        QDoubleSpinBox *centerY = new QDoubleSpinBox();
        centerY->setRange(-1e6, 1e6);
        centerY->setValue(center.y());
        // 起始半径
        QDoubleSpinBox *startRadius = new QDoubleSpinBox();
        startRadius->setRange(0.001, 1e6);
        startRadius->setValue(r0);
        // 终止半径
        QDoubleSpinBox *endRadius = new QDoubleSpinBox();
        endRadius->setRange(0.001, 1e6);
        endRadius->setValue(r1);
        // 圈数
        QDoubleSpinBox *turnsSpin = new QDoubleSpinBox();
        turnsSpin->setRange(0.1, 100);
        turnsSpin->setDecimals(2);
        turnsSpin->setValue(turns);
        // 步进角度
        QDoubleSpinBox *stepSpin = new QDoubleSpinBox();
        stepSpin->setRange(0.1, 90.0);
        stepSpin->setDecimals(2);
        stepSpin->setValue(step);
        // 按钮
        QPushButton *confirmBtn = new QPushButton("Confirm");
        // 加入表单
        formLayout->addRow("Center X:", centerX);
        formLayout->addRow("Center Y:", centerY);
        formLayout->addRow("Start Radius:", startRadius);
        formLayout->addRow("End Radius:", endRadius);
        formLayout->addRow("Turns:", turnsSpin);
        formLayout->addRow("Angle Step (deg):", stepSpin);
        mainLayout->addLayout(formLayout);
        mainLayout->addWidget(confirmBtn);
        connect(confirmBtn, &QPushButton::clicked, spiralTab, [ = ]() {
            QPointF center(centerX->value(), centerY->value());
            double r0 = startRadius->value();
            double r1 = endRadius->value();
            double t = turnsSpin->value();
            double step = stepSpin->value();
            if (r0 < 0 || r1 <= 0 || t <= 0 || step <= 0) {
                WARN_MSG("Invalid spiral parameters");
                return;
            }
            EditController::getIns().onTabWidgetSpiralGeometryTab(center, r0, r1, t, step);
        });
        this->addTab(spiralTab, "Geometry");
    }

    void addPolygonGeometryTab(const UUID uuid) {
        auto itemptr = Manager::getIns().itemMapFind(uuid);
        auto item = static_cast < PolygonItem * > (itemptr.get());
        QPointF center = item->getVertexInScene(0).point;
        double radius = item->getRadius();
        uint edgeCount = item->getEdgeCount();
        double angle = item->getRotateAngle();
        QWidget *polygonTab = new QWidget();
        QVBoxLayout *mainLayout = new QVBoxLayout(polygonTab);
        QFormLayout *formLayout = new QFormLayout();
        // 中心点
        QDoubleSpinBox *centerX = new QDoubleSpinBox();
        centerX->setRange(-1e6, 1e6);
        centerX->setValue(center.x());
        QDoubleSpinBox *centerY = new QDoubleSpinBox();
        centerY->setRange(-1e6, 1e6);
        centerY->setValue(center.y());
        // 半径
        QDoubleSpinBox *radiusSpin = new QDoubleSpinBox();
        radiusSpin->setRange(0.001, 1e6);
        radiusSpin->setValue(radius);
        // 边数
        QSpinBox *edgeCountSpin = new QSpinBox();
        edgeCountSpin->setRange(3, 100);
        edgeCountSpin->setValue(static_cast < int > (edgeCount));
        // 旋转角度
        QDoubleSpinBox *angleSpin = new QDoubleSpinBox();
        angleSpin->setRange(0.0, 359.99);
        angleSpin->setDecimals(2);
        angleSpin->setValue(angle);
        QPushButton *confirmBtn = new QPushButton("Confirm");
        formLayout->addRow("Center X:", centerX);
        formLayout->addRow("Center Y:", centerY);
        formLayout->addRow("Radius:", radiusSpin);
        formLayout->addRow("Edge Count:", edgeCountSpin);
        formLayout->addRow("Angle (°):", angleSpin);
        mainLayout->addLayout(formLayout);
        mainLayout->addWidget(confirmBtn);
        connect(confirmBtn, &QPushButton::clicked, polygonTab, [ = ]() {
            QPointF center(centerX->value(), centerY->value());
            double radius = radiusSpin->value();
            uint edgeCount = static_cast < uint > (edgeCountSpin->value());
            double angle = angleSpin->value();
            if (radius <= 0 || edgeCount < 3) {
                WARN_MSG("Invalid polygon parameters");
                return;
            }
            EditController::getIns().onTabWidgetPolygonGeometryTab(center, radius, edgeCount, angle);
        });
        this->addTab(polygonTab, "Geometry");
    }


    ///
    /// \brief addMultiItemsEditTab
    void addMultiItemsEditTab(const std::vector < UUID > & /*uuids*/) {
        QWidget* tab = new QWidget();
        QVBoxLayout* mainLayout = new QVBoxLayout(tab);
        struct FieldWidgets {
            QCheckBox *enableCheck;
            QDoubleSpinBox *valueSpin;
            QDoubleSpinBox *deltaSpin;
        };
        QMap < QString, FieldWidgets > fields;
        // 创建 scroll 区域包裹 form layout
        QScrollArea* scrollArea = new QScrollArea();
        scrollArea->setWidgetResizable(true);
        QWidget* scrollWidget = new QWidget();
        QFormLayout* formLayout = new QFormLayout(scrollWidget);
        scrollWidget->setLayout(formLayout);
        scrollArea->setWidget(scrollWidget);
        scrollArea->setMinimumHeight(300);  // 你可以根据需要设置默认高度
        mainLayout->addWidget(scrollArea);
        auto addField = [&](const QString & name, double defaultValue = 0.0) {
            QCheckBox* check = new QCheckBox(name);
            QDoubleSpinBox* valueSpin = new QDoubleSpinBox();
            QSlider* valueSlider = new QSlider(Qt::Horizontal);
            QDoubleSpinBox* deltaSpin = new QDoubleSpinBox();
            // 设置范围/精度
            double min = -9999.0;
            double max = 9999.0;
            valueSpin->setRange(min, max);
            valueSpin->setDecimals(3);
            deltaSpin->setRange(min, max);
            deltaSpin->setDecimals(3);
            valueSlider->setRange(static_cast < int > (min * 100), static_cast < int > (max * 100));
            // 同步 slider <-> spinbox
            connect(valueSpin, QOverload < double >::of(&QDoubleSpinBox::valueChanged),
            [ = ](double val) {
                valueSlider->setValue(static_cast < int > (val * 100));
            });
            connect(valueSlider, &QSlider::valueChanged,
            [ = ](int val) {
                valueSpin->setValue(val / 100.0);
            });
            // 默认值
            valueSpin->setValue(defaultValue);
            valueSlider->setValue(static_cast < int > (defaultValue * 100));
            deltaSpin->setValue(0);
            // 禁用逻辑
            valueSpin->setEnabled(false);
            valueSlider->setEnabled(false);
            deltaSpin->setEnabled(false);
            connect(check, &QCheckBox::toggled, valueSpin, &QDoubleSpinBox::setEnabled);
            connect(check, &QCheckBox::toggled, valueSlider, &QSlider::setEnabled);
            connect(check, &QCheckBox::toggled, deltaSpin, &QDoubleSpinBox::setEnabled);
            // 控件宽度
            check->setMinimumWidth(180);
            valueSpin->setFixedWidth(80);
            deltaSpin->setFixedWidth(80);
            // 布局组装
            QVBoxLayout* sliderLayout = new QVBoxLayout();
            sliderLayout->setSpacing(2);
            sliderLayout->setContentsMargins(0, 0, 0, 0);
            sliderLayout->addWidget(valueSpin);
            sliderLayout->addWidget(valueSlider);
            QHBoxLayout* hLayout = new QHBoxLayout();
            hLayout->addLayout(sliderLayout);
            hLayout->addSpacing(10);
            hLayout->addWidget(new QLabel("+"));
            hLayout->addWidget(deltaSpin);
            formLayout->addRow(check, hLayout);
            fields[name] = FieldWidgets{check, valueSpin, deltaSpin};
        };
        // 添加字段
        addField("Position.x");
        addField("Position.y");
        addField("MarkParams: markSpeed", 0);
        addField("MarkParams: jumpSpeed", 0);
        addField("MarkParams: frequency", 0);
        addField("MarkParams: repetTime", 0);
        addField("MarkParams: power", 0);
        addField("MarkParams: pulseWidth", 0);
        addField("MarkParams: wobelAml", 0);
        addField("MarkParams: wobelFreq", 0);
        addField("DelayParams: laserOnDelay", 0);
        addField("DelayParams: laserOffDelay", 0);
        addField("DelayParams: markDelay", 0);
        addField("DelayParams: jumpDelay", 0);
        addField("DelayParams: polygonDelay", 0);
        // Confirm 按钮
        QPushButton* ConfirmBtn = new QPushButton("Confirm");
        formLayout->addRow(ConfirmBtn);
        connect(ConfirmBtn, &QPushButton::clicked, tab, [ = ]() {
            std::vector < MultiEditParam > result;
            for (auto it = fields.begin(); it != fields.end(); ++it) {
                const QString& key = it.key();
                const FieldWidgets& w = it.value();
                if (!w.enableCheck->isChecked()) {
                    continue;
                }
                MultiEditParam param;
                param.fieldName = key;
                param.baseValue = w.valueSpin->value();
                param.deltaValue = w.deltaSpin->value();
                result.push_back(param);
            }
            EditController::getIns().onTabWidgetMultiItemsEditTab(result);
        });
        this->addTab(tab, "Multi Edit");
    }

    void addMultiItemsAlignTab(const std::vector < UUID > &) {
        QWidget* tab = new QWidget();
        QVBoxLayout* outerLayout = new QVBoxLayout(tab);
        QScrollArea* scrollArea = new QScrollArea();
        scrollArea->setWidgetResizable(true);
        QWidget* scrollContent = new QWidget();
        QVBoxLayout* mainLayout = new QVBoxLayout(scrollContent);
        mainLayout->setAlignment(Qt::AlignTop);
        mainLayout->setSpacing(10);
        QButtonGroup* hAlignGroup = new QButtonGroup(tab);
        QButtonGroup* vAlignGroup = new QButtonGroup(tab);
        // 水平对齐选项
        QGroupBox* hGroup = new QGroupBox("Horizontal Align");
        QVBoxLayout* hLayout = new QVBoxLayout(hGroup);
        QRadioButton* alignLeft = new QRadioButton("left");
        QRadioButton* alignHCenter = new QRadioButton("center");
        QRadioButton* alignRight = new QRadioButton("right");
        hAlignGroup->addButton(alignLeft, 0);
        hAlignGroup->addButton(alignHCenter, 1);
        hAlignGroup->addButton(alignRight, 2);
        hLayout->addWidget(alignLeft);
        hLayout->addWidget(alignHCenter);
        hLayout->addWidget(alignRight);
        // 垂直对齐选项
        QGroupBox* vGroup = new QGroupBox("Vertical Align");
        QVBoxLayout* vLayout = new QVBoxLayout(vGroup);
        QRadioButton* alignTop = new QRadioButton("top");
        QRadioButton* alignVCenter = new QRadioButton("center");
        QRadioButton* alignBottom = new QRadioButton("bottom");
        vAlignGroup->addButton(alignTop, 0);
        vAlignGroup->addButton(alignVCenter, 1);
        vAlignGroup->addButton(alignBottom, 2);
        vLayout->addWidget(alignTop);
        vLayout->addWidget(alignVCenter);
        vLayout->addWidget(alignBottom);
        // 添加到主 layout 中
        mainLayout->addWidget(hGroup);
        mainLayout->addWidget(vGroup);
        // 确认按钮
        QPushButton* confirmBtn = new QPushButton("Confirm");
        confirmBtn->setFixedWidth(100);
        confirmBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        mainLayout->addWidget(confirmBtn, 0, Qt::AlignCenter);
        scrollContent->setLayout(mainLayout);
        scrollArea->setWidget(scrollContent);
        outerLayout->addWidget(scrollArea);
        // 信号
        connect(confirmBtn, &QPushButton::clicked, tab, [ = ]() {
            int hAlign = hAlignGroup->checkedId();
            int vAlign = vAlignGroup->checkedId();
            qDebug() << "horizontal:" << hAlign;
            qDebug() << "vertical:" << vAlign;
            EditController::getIns().onTabWidgetMultiItemsAlignTab(hAlign, vAlign);
        });
        this->addTab(tab, "Align");
    }

    ///
    /// \brief addDuoItemsBoolOpTab
    void addDuoItemsBoolOpTab(const std::vector < UUID > &uuids) {
        if (uuids.size() != 2) {
            return;
        }
        // 创建 UI
        QWidget *tab = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout(tab);
        QLabel *label = new QLabel("Select Boolean Operation:");
        QComboBox *combo = new QComboBox();
        combo->addItem("Union",
                       QVariant::fromValue(static_cast < int > (cavc::PlineCombineMode::Union)));
        combo->addItem("Exclude",
                       QVariant::fromValue(static_cast < int > (cavc::PlineCombineMode::Exclude)));
        combo->addItem("Intersect",
                       QVariant::fromValue(static_cast < int > (cavc::PlineCombineMode::Intersect)));
        combo->addItem("XOR", QVariant::fromValue(static_cast < int > (cavc::PlineCombineMode::XOR)));
        QPushButton *confirmBtn = new QPushButton("Confirm");
        layout->addWidget(label);
        layout->addWidget(combo);
        layout->addWidget(confirmBtn, 0, Qt::AlignCenter);
        // 仅传出选择项和 uuid
        connect(confirmBtn, &QPushButton::clicked, tab, [ = ]() {
            int opIndex = combo->currentData().toInt();
            cavc::PlineCombineMode mode = static_cast < cavc::PlineCombineMode > (opIndex);
            EditController::getIns().onTabWidgetDuoItemsBoolOpTab(mode);
        });
        this->addTab(tab, "Boolean Op");
    }
};

#endif // TABWIDGET_H
