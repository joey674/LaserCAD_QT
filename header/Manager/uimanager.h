#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <QMainWindow>
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class UiManager
{
private:
    std::unique_ptr<Ui::MainWindow> ui;
public:
    Ui::MainWindow* UI();
    void setUI(std::unique_ptr<Ui::MainWindow> newUi);
public:
    void setAllDrawButtonChecked(bool isChecked);
    void setAllToolButtonChecked(bool isChecked);

/// Manager Initialization
private:
    static UiManager ins;
    UiManager(){};
    UiManager(const UiManager&);
    ~UiManager(){};
    UiManager& operator = (const UiManager&);
public:
    static UiManager& getIns();
};

#endif // UIMANAGER_H
