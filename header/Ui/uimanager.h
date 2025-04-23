#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <QMainWindow>
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class UiManager {
private:
    std::shared_ptr < Ui::MainWindow > m_ui;
    std::vector < QToolButton * > m_drawButtons;
    std::vector < QToolButton * > m_toolButtons;
public:
    Ui::MainWindow *UI();
    void setUI(std::shared_ptr < Ui::MainWindow > newUi);
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
