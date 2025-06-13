#include "projectpage.h"
#include <QLabel>
#include <QVBoxLayout>

ProjectPage::ProjectPage(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("project page"));
}
