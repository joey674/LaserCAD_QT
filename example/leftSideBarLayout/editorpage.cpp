#include "editorpage.h"
#include <QLabel>
#include <QVBoxLayout>

EditorPage::EditorPage(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("edit page"));
}
