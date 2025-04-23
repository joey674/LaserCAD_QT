#include "uimanager.h"

UiManager UiManager::ins;

UiManager &UiManager::getIns() {
    return ins;
}

Ui::MainWindow *UiManager::UI() {
    return m_ui.get();
}

void UiManager::setUI(std::shared_ptr < Ui::MainWindow > newUi) {
    m_ui = std::move(newUi);
}

