#include "uimanager.h"

UiManager UiManager::ins;

UiManager &UiManager::getIns()
{
    return ins;
}

void UiManager::setAllDrawButtonChecked(bool isChecked)
{
    ui->drawArcButton->setChecked(isChecked);
    ui->drawCircleButton->setChecked(isChecked);
    ui->drawEllipseButton->setChecked(isChecked);
    ui->drawPolylineButton->setChecked(isChecked);
    ui->drawPolygonButton->setChecked(isChecked);
    ui->drawRectButton->setChecked(isChecked);
    ui->drawSpiralButton->setChecked(isChecked);
}

void UiManager::setAllToolButtonChecked(bool isChecked)
{
    ui->editButton->setChecked(isChecked);
    ui->dragSceneButton->setChecked(isChecked);
    ui->centerButton->setChecked(isChecked);
    ui->createOffsetButton->setChecked(isChecked);
    ui->deleteButton->setChecked(isChecked);
    ui->rotateButton->setChecked(isChecked);
    ui->drawTestLineButton->setChecked(isChecked);
}

Ui::MainWindow *UiManager::UI(){
    return ui.get();
}

void UiManager::setUI(std::unique_ptr<Ui::MainWindow> newUi)
{
    ui = std::move(newUi);
}

